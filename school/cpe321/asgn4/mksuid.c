/* Jared Spadaro (jaspadar)
 * CPE321 // Nico
 * 6/8/17
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
#define MAX_PASSWD_LEN 1024
#define MAX_HASH_LEN 2048
#define MAX_USERNAME_LEN 64
#define NUM_SECONDS 60
#define ROOT 0
#define PROJ 95
#define FILE_PROTECTION 04550
#define PWD_PROMPT "Enter password: "
#define PWD_PROMPT_LEN 16

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
   if (entered_passwd == NULL) {
       perror("calloc");
       exit(1);
   }

   pwd_entry = getpwuid(*uid);
   if (pwd_entry == NULL) {
      perror("getpwuid");
      exit(1);
   }
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

   res = read(STDIN_FILENO, entered_passwd, MAX_PASSWD_LEN);
   if (res == -1) {
      perror("read");
      exit(1);
   }

   if (res > MAX_PASSWD_LEN - 1) {
      fprintf(stderr, "\npassword too long\n");
      exit(1);
   }
   
   if (entered_passwd[res - 1] == '\n') {
      entered_passwd[res - 1] = '\0';
   }
   else {
      entered_passwd[res] = '\0';
   } 

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
  
   /* clear plaintext password */
   memset(entered_passwd, 0, strlen(entered_passwd));  
 
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
}

/* check to make sure sniff exists and has expected properties */
void check_file(int *fd) {
   int res;
   struct stat *stats;

   stats = malloc(sizeof(struct stat));
   if (stats == NULL) {
      perror("malloc");
      exit(1);
   }
   
   *fd = open("sniff", O_RDONLY);
   if (*fd == -1) {
      perror("open");
      exit(1);
   }

   res = fstat(*fd, stats);
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
}

/* check to make sure sniff has been built in the last minute */
int check_mod_time(int *fd) {
   int res;
   struct stat *stats;
   time_t *current_time;   

   stats = malloc(sizeof(struct stat));   
   if (stats == NULL) {
      perror("malloc");
      exit(1);
   }

   res = fstat(*fd, stats);
   if(res == -1) {
      perror("stat");
      exit(1);
   }

   current_time = malloc(sizeof(time_t));
   if (current_time == NULL) {
      perror("malloc");
      exit(1);
   }

   res = (int)time(current_time);
   if (res == -1) {
      perror("time");
      exit(1);
   }

   /* check time difference between mod time and current time */
   if(difftime(*current_time, stats->st_mtim.tv_sec) > NUM_SECONDS) {
      fprintf(stderr, "error: sniff was not modified within last minute\n");
      exit(1);
   }
} 
 
/* set properties of sniff */
void set_sniff_properties(int *fd) {
   int res;

   res = fchmod(*fd, FILE_PROTECTION);
   if(res == -1) {
      perror("fchmod");  
      exit(1);
   }
 
   res = fchown(*fd, ROOT, PROJ);  
   if(res == -1) {
      perror("fchown");
      exit(1);
   }
}
  
int main () {
   uid_t *uid = calloc(1, sizeof(uid_t));
   int *fd = malloc(sizeof(int));

   compare_ids(uid);
   compare_passwds(uid);
   check_file(fd);
   check_mod_time(fd);
   set_sniff_properties(fd);
   close(*fd);

   exit(0);
}

