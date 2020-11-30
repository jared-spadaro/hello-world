/* Asgn 5 - the min programs
 * Jared Spadaro
 * CS453 Section 3 Nico
 * This program takes a filesystem image and a path
 * and lists the contents of the given path
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include <string.h>

#define P_FLAG 0
#define S_FLAG 1
#define V_FLAG 2
#define MAGIC_PART 0xAA55
#define PART_TYPE 0x81
#define PART_TABLE_ENTRY_SIZE 16
#define PART_TABLE_LOC 0x1BE
#define MAGIC_LOC 510
#define SECTOR_SIZE 512
#define BOOTBLOCK_SIZE 1024
#define SUPERBLOCK_SIZE 1024
#define DIRECT_ZONES 7
#define REG_FILE 0
#define DIR_FILE 1
#define OTHER_FILE -1
#define MAX_FILENAME_SIZE 60
#define INODE_SIZE 64
#define MODE_STRING_LEN 11

typedef struct fs_info {
   int part;        /* indicates the partition to be read from */
   int subpart;     /* indicates the subpartition to be read from */
   int verbose;     /* indicates whether we are running verbosely or not */
   char *image;     /* the filesystem image we will be reading from */
   char *path;      /* path to list */
} fs_info;

typedef struct part_info {
  int *start;       /* first sector of partition, measured from start of disk */
  int *size;        /* size of partition, in sectors */
} part_info;

typedef struct superblock_t {
   uint32_t ninodes;         /* number of inodes in FS */
   uint16_t pad1;            /* padding */
   int16_t i_blocks;         /* # blocks used by inode bitmap */
   int16_t z_blocks;         /* # blocks used by zone bitmap */
   uint16_t firstdata;       /* # of first data zone */
   int16_t log_zone_size;    /* logs2 of blocks per zone */
   int16_t pad2;             /* padding */
   uint32_t max_file;        /* max file size */
   uint32_t zones;           /* # zones on disk */
   int16_t magic;            /* magic number */
   int16_t pad3;             /* padding */
   uint16_t blocksize;       /* block size in bytes */
   uint8_t subversion;       /* filesystem sub-version */
} superblock_t;

typedef struct inode_t {
   uint16_t mode;
   uint16_t links;
   uint16_t uid;
   uint16_t gid;
   uint32_t size;
   int32_t atime;
   int32_t mtime;
   int32_t ctime;
   uint32_t zone[DIRECT_ZONES];
   uint32_t indirect;
   uint32_t two_indirect;
   uint32_t unused;
} inode_t;

typedef struct dir_t {
   uint32_t inode;
   char name[60];
} dir_t;

/* function for printing out usage information */
void Usage () {
   printf("usage: minls  [ -v ] [ -p num [ -s num ] ] imagefile" 
    " [ path ]\n");
   printf("Options:\n"
    "-p part    --- select partition for filesystem (default: none)\n"
    "-s sub     --- select subpartition for filesystem (default: none)\n"
    "-h help    --- print usage information and exit\n"
    "-v verbose --- increase verbosity level\n");
   exit(1);
}

int CheckFlag (char *flag) {
   if(!strcmp("-p", flag)) {
      return P_FLAG;
   }             
   if(!strcmp("-s", flag)) {
      return S_FLAG; 
   }             
   if(!strcmp("-v", flag)) {
      return V_FLAG;
   }
   return -1;
}             
  
/* function for processing the optional command 
 * line arguments for minls and minget
 */
void CmdArgs (int num, char **args, struct fs_info *info) {
   int i = 1, ret;
   while (i < num) {
      if (args[i][0] == '-') {
         ret = CheckFlag(args[i]);
         if (ret == P_FLAG) {
            info->part = strtol(args[++i], NULL, 10);
         }
         else if (ret == S_FLAG) {
            info->subpart = strtol(args[++i], NULL, 10);
         }
         else if (ret == V_FLAG) {
            info->verbose = 1;
         }
         else {
            Usage();
         }
      }
      else {
         info->image = args[i++];
         info->path = args[i];                      
      }
      i++; 
   }        
}

void InitStructs (struct fs_info *fs_info, struct part_info *part_info, 
 struct part_info *subpart_info) {
   fs_info->part = -1;
   fs_info->subpart = -1;
   fs_info->verbose = 0;
   fs_info->image = NULL;
   fs_info->path = NULL;

   part_info->start = malloc(sizeof(int));
   part_info->size = malloc(sizeof(int));
   
   subpart_info->start = malloc(sizeof(int));
   subpart_info->size = malloc(sizeof(int));
}

void CheckInfo (struct fs_info *info) {
   printf("part = %d\n", info->part);
   printf("subpart = %d\n", info->subpart);
   printf("verbosity = %d\n", info->verbose);
   printf("image = %s\n", info->image);
   printf("path = %s\n", info->path);
}

/* helper function for checking return value of fseek(3) */
void SafeSeek (FILE *stream, int offset, int whence) {
   if (-1 == fseek(stream, offset, whence)) { 
      perror("fseek");
      fprintf(stderr, "attempted to seek with offset %d\n", offset);
      exit(1);
   }
}

/* helper function for checking return value of fread(3) */  
void SafeRead (void *buffer, int numbytes, int numitems, FILE *stream) {
   int itemsRead;
   itemsRead = fread(buffer, numbytes, numitems, stream);
   if (numitems != numitems) {
      fprintf(stderr, "Error: fread: %d item(s) read (expected %d)\n", 
       itemsRead, numitems);
      exit(1);
   }
}

/* helper function for printing error message and exiting */
void PrintError(char *msg) {
   fprintf(stderr, msg);
   exit(EXIT_FAILURE);
}

/* this function is called after we have confirmed that the 
 * user has indicated that the disk is partitioned 
 * offset gives location of partition (if we are seeking a subpartition,
 * otherwise offset is 0)
 */
void SeekPartition(struct fs_info *fs_info, struct part_info *part_info, 
 FILE *stream, int offset) {
   int *magic = malloc(sizeof(int));
   int *part_type = malloc(sizeof(int));
   /* first, we must check if this is a valid partition table */
   SafeSeek(stream, MAGIC_LOC + offset, SEEK_SET);
   SafeRead(magic, sizeof(uint8_t), 2, stream);
   if (*magic != MAGIC_PART) {
      PrintError("Error: Invalid partition table detected. Exiting...\n");
   }
   /* from this point forward, we know that we have a valid partition table */
   SafeSeek(stream, PART_TABLE_LOC + offset, SEEK_SET);
   /* move to desired partition table entry */
   if (!offset) {
      SafeSeek(stream, fs_info->part * PART_TABLE_ENTRY_SIZE, SEEK_CUR);
   }
   else {
      SafeSeek(stream, fs_info->subpart * PART_TABLE_ENTRY_SIZE, SEEK_CUR);
   }
   /* move to type of partition to determine if its minix */
   SafeSeek(stream, sizeof(int8_t) * 4, SEEK_CUR);
   SafeRead(part_type, sizeof(uint8_t), 1, stream);
   if (*part_type != PART_TYPE) {
      PrintError("Error: wrong partition type. Exiting...\n");
   }
   /* seek to number of first sector */
   SafeSeek(stream, sizeof(int8_t) * 3, SEEK_CUR);
   /* read ABSOLUTE starting location of part/subpart */
   SafeRead(part_info->start, sizeof(uint32_t), 1, stream);
   /* read size of part/subpart */
   SafeRead(part_info->size, sizeof(uint32_t), 1, stream);
}

FILE *OpenFS (char *filename) {
   FILE *stream = fopen(filename, "r");
   if (stream == NULL) {
      perror("fopen");
      exit(1);
   }
   return stream;
}

void PrintSuperBlock (struct superblock_t *super) {
   printf("\nSuperblock Contents:\nStored Fields:\n"
    "  ninodes              %9u\n"
    "  i_blocks             %9d\n"
    "  z_blocks             %9d\n"
    "  firstdata            %9u\n"
    "  log_zone_size        %9d\n"
    "  max_file            %9u\n"
    "  zones                %9u\n"
    "  magic                %9X\n"
    "  blocksize            %9u\n"
    "  subversion           %9u\n\n",
    super->ninodes, super->i_blocks, super->z_blocks, super->firstdata, 
    super->log_zone_size, super->max_file, super->zones, super->magic,  
    super->blocksize, super->subversion);
}
 
/* gather metadata contained in superblock.
 * the "part" argument may represent either partition
 * info or subpartition info. or it may be null if the 
 * disk is unpartitioned
 */
void ReadSuperBlock (FILE *stream, struct superblock_t *super, 
 struct part_info *part) {
   int offset;       /* in bytes */
   if (part == NULL) {
      offset = 0;
   }
   else {
      offset = *part->start * SECTOR_SIZE;
   }
   SafeSeek(stream, SUPERBLOCK_SIZE + offset, SEEK_SET);
   SafeRead(super, sizeof(superblock_t), 1, stream);
}

void Print_iNode (struct inode_t *inode) {
   printf("File inode:\n");
   printf("  uint16_t mode        %9X\n", inode->mode);
   printf("  uint16_t links       %9d\n", inode->links);
   printf("  uint16_t uid         %9d\n", inode->uid);
   printf("  uint16_t gid         %9d\n", inode->gid);
   printf("  uint32_t size        %9d\n", inode->size);
   printf("  uint32_t atime      %9d\n", inode->atime);
   printf("  uint32_t mtime      %9d\n", inode->mtime);
   printf("  uint32_t ctime      %9d\n\n", inode->ctime);
   int i;
   printf("  Direct zones:\n");
   for (i = 0; i < DIRECT_ZONES; i++) {
      printf("            zone[%d]   =    %9d\n", i, inode->zone[i]);
   }
   printf("  uint32_t  indirect       %9d\n", inode->indirect);
   printf("  uint32_t  two_indirect   %9d\n\n", inode->two_indirect);
}
 
int QueryMode (uint16_t mode) {
   int ret;
   if (S_ISREG(mode)) {
      ret = REG_FILE;
   }
   else if (S_ISDIR(mode)) {
      ret = DIR_FILE;
   }
   else {
      ret = OTHER_FILE;
   }
   return ret;
}

/* this function navigates us to the iNode given and reads it */
void Read_iNode (FILE *stream, struct part_info *part, 
 struct superblock_t *super, struct inode_t *inode, int inode_num) {
   int offset;
   if(part == NULL) {
     offset = 0;
   }
   else {
     offset = *part->start * SECTOR_SIZE;
   }
   SafeSeek(stream, 2 * super->blocksize + offset, SEEK_SET);
   /* we are now at start of inode bit map */
   SafeSeek(stream, (super->blocksize * (super->i_blocks + super->z_blocks)) + 
    (((inode_num - 1) * INODE_SIZE)), SEEK_CUR);
   /* we are now at start of inodes zones */
   SafeRead(inode, sizeof(inode_t), 1, stream);
}

void FormatPermissions (uint16_t mode, uint16_t mask, char perm,
 int start, char *formatted) {
   int i = start;
   while (i < MODE_STRING_LEN) {
      if (mask & mode) {
         formatted[i] = perm;
      }
      i += 3;
      mask >>= 3;   
   }
}  

void FormatMode (char *formatted, uint16_t mode, int type) {
   int i;
   formatted[MODE_STRING_LEN - 1] = '\0';
   for (i = 0; i < MODE_STRING_LEN - 1; i++) {
      formatted[i] = '-';
   }
   if (type == DIR_FILE) {
      formatted[0] = 'd';
   }
   FormatPermissions(mode, 0400, 'r', 1, formatted);
   FormatPermissions(mode, 0200, 'w', 2, formatted);
   FormatPermissions(mode, 0100, 'x', 3, formatted);
}

void CreateDirArray (struct dir_t **dir_array, int num_dirs) {
   int i;
   for (i = 0; i < num_dirs; i++) {
      dir_array[i] = malloc(sizeof(dir_t));
   }
}

void PrintFileMetadata (FILE *stream, struct inode_t *inode, int zone_ndx,
 struct part_info *part, struct superblock_t *super, struct fs_info *fs) {
   int zonesize = super->blocksize << super->log_zone_size;
   int i, type = QueryMode(inode->mode);
   struct inode_t *new_inode = malloc(sizeof(inode_t));
   char *formatted_mode = malloc(MODE_STRING_LEN);
   int num_subdirs = inode->size / sizeof(dir_t);
   struct dir_t **dir_array = malloc(sizeof(dir_t) * num_subdirs);
   if (fs->verbose) {
      Print_iNode(inode);
   }
   if (type == REG_FILE) {
      FormatMode(formatted_mode, inode->mode, type); 
      printf("%s%9d %s\n", formatted_mode, inode->size, fs->path);
   }
   else if (type == DIR_FILE) {
      CreateDirArray(dir_array, num_subdirs);
      SafeSeek(stream, zonesize * inode->zone[zone_ndx] + 
       (*part->start * SECTOR_SIZE), SEEK_SET);
      printf("%s:\n", fs->path);
      for (i = 0; i < num_subdirs; i++) {
         SafeRead(dir_array[i], sizeof(dir_t), 1, stream);
      }
      for (i = 0; i < num_subdirs; i++) {
         Read_iNode(stream, part, super, new_inode, dir_array[i]->inode);
         FormatMode(formatted_mode, new_inode->mode, 
           QueryMode(new_inode->mode));
         printf("%s%9d %s\n", formatted_mode, new_inode->size, 
          dir_array[i]->name);
      }

   }
   else {
      printf("error: not a reg file or dir\n");
      exit(1);
   }
} 

/* we have the inode for the directory we are in (starting with root).
 * now we use the info contained in it to go to the proper data zones
 * and see what the directory has (whether it be more dirs, reg files, etc)
 */
void TraverseDir (FILE *stream, struct inode_t *inode, struct part_info *part, 
 struct superblock_t *super, char **parsed_path, int path_ndx, int zone_ndx,
 struct fs_info *fs) {
   struct dir_t *dir = malloc(sizeof(dir_t));
   int type = QueryMode(inode->mode);
   int zonesize = super->blocksize << super->log_zone_size;
   int i;
   int num_subdirs = inode->size / sizeof(dir_t);
   struct inode_t *new_inode = malloc(sizeof(inode_t));
   
   if (type != DIR_FILE || parsed_path[path_ndx] == NULL) {
      PrintFileMetadata(stream, inode, zone_ndx, part, super, fs);     
      exit(0);
   }
   /* from this point forward, we know that we are traversing a dir */
   SafeSeek(stream, (zonesize * inode->zone[0]) + (*part->start * SECTOR_SIZE),
    SEEK_SET);
   for (i = 0; i < num_subdirs; i++) {
      /* read the next directory entry */
      SafeRead(dir, sizeof(dir_t), 1, stream);
      /* if we have a match, use this dirs inode and call traverse again */
      if(!strcmp(dir->name, parsed_path[path_ndx])) {
         Read_iNode(stream, part, super, new_inode, dir->inode);
         TraverseDir(stream, new_inode, part, super, parsed_path, 
          ++path_ndx, zone_ndx, fs);
      }
   } 
   printf("error: invalid path\n");
   exit(1);
}
 
char **ParsePath (char *path, int numTokens) {
   int i;
   char *result = malloc(MAX_FILENAME_SIZE);
   char **parsed_paths = malloc(numTokens * sizeof(char *));
   if (path == NULL) {
      return NULL;
   }
   for (i = 0; i < numTokens; i++) {
      if (i == 0) {
         result = strtok(path, "/");
      }
      else {
         result = strtok(NULL, "/");
      }
      parsed_paths[i] = result;
   }
   return parsed_paths;  
}    
 
int CountTokens (char *path) {
   int i, count = 2;
   if (path == NULL) {
      return -1;
   }
   for (i = 0; path[i]; i++) {
      if (path[i] == '/') {
         count++;
      }
   }
   return count;
}
   

void Goto_Partition (struct fs_info *fs, struct part_info *part,
 struct part_info *subpart, FILE *stream) {
   if (fs->part != -1) {
      SeekPartition(fs, part, stream, 0);
      if (fs->subpart != -1) {
         SeekPartition(fs, subpart, stream, 
          *part->start * SECTOR_SIZE);
      } 
   }
}

void Initialize (struct fs_info *fs, struct part_info *part, 
 struct part_info *subpart, int argc, char **argv) {
   InitStructs(fs, part, subpart);
   CmdArgs(argc, argv, fs);
   if(fs->image == NULL) {
      Usage();
   }
}

void Read_Super (FILE *stream, struct superblock_t *super, 
 struct inode_t *inode, struct part_info *part, struct part_info *subpart, 
 struct fs_info *fs) {
   if (fs->part == -1) {
      ReadSuperBlock(stream, super, NULL);
      Read_iNode(stream, NULL, super, inode, 1);
   }
   else if (fs->subpart == -1) {
      ReadSuperBlock(stream, super, part);
      Read_iNode(stream, part, super, inode, 1);
   }
   else {
      ReadSuperBlock(stream, super, subpart);
      Read_iNode(stream, subpart, super, inode, 1);
   }
   if (fs->verbose) {
      PrintSuperBlock(super);
   }
}

void FollowPath (FILE *stream, struct fs_info *fs, struct inode_t *inode,
 struct superblock_t *super, struct part_info *part) {
   int numTokens, path_length;
   if (fs->path != NULL && strcmp(fs->path, "/")) { 
      path_length = (int)strlen(fs->path);
      char path[path_length + 1];
      memcpy(path, fs->path, path_length); 
      path[path_length] = '\0';
      numTokens = CountTokens(path);
      char **parsed_path = ParsePath(path, numTokens);
      /* "base case" for recursion (uses root_inode) */
      TraverseDir(stream, inode, part, super, parsed_path, 0, 0, 
       fs);
   }
   /* just list the root directory */
   else {
      fs->path = "/";
      PrintFileMetadata(stream, inode, 0, part, super, fs);
   }
}

int main (int argc, char **argv) {
   struct fs_info *fs_info = malloc(sizeof(fs_info));
   struct part_info *part_info = malloc(sizeof(part_info));
   struct part_info *subpart_info = malloc(sizeof(part_info));
   struct superblock_t *super = malloc(sizeof(superblock_t));
   struct inode_t *root_inode = malloc(sizeof(inode_t));
   FILE *stream;

   Initialize(fs_info, part_info, subpart_info, argc, argv);
   stream = OpenFS(fs_info->image);
   Goto_Partition(fs_info, part_info, subpart_info, stream);
   Read_Super(stream, super, root_inode, part_info, subpart_info, fs_info);
    
   FollowPath(stream, fs_info, root_inode, super, part_info);
      
   return 0;
}
