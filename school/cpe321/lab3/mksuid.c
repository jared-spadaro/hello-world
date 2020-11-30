/* Jared Spadaro (jaspadar)
 * CPE321 // Nico
 * 5/24/17
 * This program checks several properties of a file called "sniff",
 * checks that the proper user is running it, and then sets some
 * properties of "sniff." 
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <shadow.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <termios.h>
#include <pwd.h>

#define STUDENT_UID 1000
#define MAX_PASSWD_LEN 32
#define MAX_HASH_LEN 64
#define MAX_USERNAME_LEN 64
#define NUM_SECONDS 60
#define ROOT 0
#define PROJ 95
#define FILE_PROTECTION 4550
#define PWD_PROMPT "Password: "
#define PWD_PROMPT_LEN 10

/* check that student is running this */
void compare_ids(uid_t *uid) {
   *uid = getuid();
   if(*uid != STUDENT_UID) {
      fprintf(stderr, "error: user id not valid\n");
      exit(1);
   }
}

/* compare entered password to password stored in /etc/shadow */
void compare_passwds(uid_t *uid) {
   struct termios tty;
   int i, res;
   char temp, *entered_passwd, *digest, *user;
   struct passwd *pwd_entry;
   struct spwd *real_passwd;
   
   i = 0;
   temp = 0;
   entered_passwd = calloc(MAX_PASSWD_LEN, sizeof(char));
   digest = calloc(MAX_HASH_LEN, sizeof(char));

   pwd_entry = getpwuid(*uid);
   if (pwd_entry == NULL) {
      perror("getpwuid");
      exit(1);
   }
   free(uid);
   uid = NULL;
   user = pwd_entry->pw_name;

   real_passwd = getspnam(user);
   if (real_passwd == NULL) {
      perror("getspnam");
      exit(1);
   }

   res = write(STDOUT_FILENO, PWD_PROMPT, PWD_PROMPT_LEN);
   if (res == -1) {
      perror("write");
      exit(1);
   }

   /* disabling echo on input for user password */ 
   res = tcgetattr(STDIN_FILENO, &tty);
   if (res == -1) {
      perror("tcgetattr");
      exit(1);
   }
   tty.c_lflag &= ~ECHO;
   res = tcsetattr(STDIN_FILENO, TCSANOW, &tty);
   if (res == -1) {
      perror("tcsetattr");
      exit(1);
   }

   while (temp != '\n') {
      res = read(STDIN_FILENO, &temp, sizeof(char));
      if (res == -1) {
         perror("read");
         exit(1);
      }
      entered_passwd[i++] = temp;
   }
   entered_passwd[i-1] = '\0';    
 
   res = write(STDOUT_FILENO, "\n", 1);
   if (res == -1) {
      perror("write");
      exit(1);
   }
   
   digest = crypt(entered_passwd, real_passwd->sp_pwdp);
   if (digest == NULL) {
      perror("crypt");
      exit(1);
   }
   
   free(entered_passwd);
   entered_passwd = NULL;   
   
   tty.c_lflag |= ECHO;
   res = tcsetattr(STDIN_FILENO, TCSANOW, &tty);
   if (res == -1) {
      perror("tcsetattr");
      exit(1);
   }

   /* make sure that passwords match */
   if(strcmp(real_passwd->sp_pwdp, digest)) {
      fprintf(stderr, "incorrect password\n");
      exit(1);
   }
   
   free(digest);
   digest = NULL;
}

/* check to make sure sniff exists and has expected properties */
void check_file() {
   int fd, res;
   struct stat *stats;

   stats = malloc(sizeof(struct stat));
   if (stats == NULL) {
      perror("malloc");
      exit(1);
   }
   
   fd = open("sniff", O_RDONLY);
   if (fd == -1) {
      perror("open");
      exit(1);
   }

   res = fstat(fd, stats);
   if(res == -1) {
      perror("stat");
      exit(1);
   }

   /* check if sniff is a regular file */
   if(!S_ISREG(stats->st_mode)) {
      fprintf(stderr, "error: sniff is not regular file\n");
      exit(1);
   }
   /* check if owner of sniff is student */
   if(stats->st_uid != STUDENT_UID) {
      fprintf(stderr, "error: sniff is not owned by student\n");
      exit(1);
   }
   /* check if owner has execute permission on sniff */
   if(!(S_IXUSR & stats->st_mode)) {
      fprintf(stderr, 
       "error: owner of sniff does not have execute permission\n");
      exit(1);
   }
   /* check if group/world has any permissions on sniff */
   if(((S_IRWXG | S_IRWXO) & stats->st_mode)) { /* should result in a 0 */
      fprintf(stderr, 
       "error: group and/or world has unauthorized permissions on sniff\n");
      exit(1);
   }

   close(fd);
   free(stats);
   stats = NULL;
}

/* check to make sure sniff has been built in the last minute */
void check_mod_time() {
   int fd, res;
   struct stat *stats;
   time_t *current_time;   

   stats = malloc(sizeof(struct stat));   
   if (stats == NULL) {
      perror("malloc");
      exit(1);
   }

   fd = open("sniff", O_RDONLY);
   if (fd == -1) {
      perror("open");
      exit(1);
   }

   res = fstat(fd, stats);
   if(res == -1) {
      perror("stat");
      exit(1);
   }

   current_time = malloc(sizeof(time_t));
   if (current_time == NULL) {
      perror("malloc");
      exit(1);
   }   

   res = time(current_time);
   if (res == -1) {
      perror("time");
      exit(1);
   }
   
   /* check time difference between mod time and current time */
   if(difftime(*current_time, stats->st_mtim.tv_sec) > NUM_SECONDS) {
      fprintf(stderr, "error: sniff was not modified within last minute\n");
      exit(1);
   }

   close(fd);
   free(stats);
   stats = NULL;
   free(current_time);
   current_time = NULL;
} 
  
/* set properties of sniff */
void set_sniff_properties() {
   int fd, res;

   fd = open("sniff", O_RDONLY);
   if (fd == -1) {
      perror("open");
      exit(1);
   }   

   res = fchmod(fd, FILE_PROTECTION);
   if(res == -1) {
      perror("fchmod");  
      exit(1);
   }
 
   res = fchown(fd, ROOT, PROJ);  
   if(res == -1) {
      perror("fchown");
      exit(1);
   }
  
   close(fd);
}
  
int main () {
   uid_t *uid = calloc(1, sizeof(uid_t));

   compare_ids(uid);
   compare_passwds(uid);
   check_file();
   check_mod_time();
   set_sniff_properties();

   exit(0);
}

