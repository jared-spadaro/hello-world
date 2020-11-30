/* Jared Spadaro (jaspadar)
 * CPE453 // Nico
 * 11/10/16
 * This program checks several properties of a file called "sniff",
 * checks that the proper user is running it, and then sets some
 * properties of "sniff." 
 * This program must run with root privelege.
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

#define NUMFORKS 2
#define STUDENT_UID 2564019
#define MAX_PASSWD_LEN 256
#define MAX_USERNAME_LEN 30
#define NUM_SECONDS 60
#define ROOT 0
#define PROJ 95
#define FILE_PROTECTION 04550

static const char salt[] = "XJ";
static const char student_username[] = "jaspadar";

/* check that student is running this */
void compare_ids() {
   uid_t real_uid = getuid();
   if(real_uid != STUDENT_UID) {
      fprintf(stderr, "User ID not valid. Exiting...\n");
      exit(1);
   }  
}

void compare_passwds() {
   struct termios tty;
   char *passwd = malloc(MAX_PASSWD_LEN);
   char *encrypted_passwd = malloc(MAX_PASSWD_LEN);
   struct spwd *shadow_passwd = malloc(sizeof(struct spwd));
  
   /* disabling echo on input for user password */ 
   printf("Enter password: ");
   tcgetattr(STDIN_FILENO, &tty);
   tty.c_lflag &= ~ECHO;
   tcsetattr(STDIN_FILENO, TCSANOW, &tty); 
   fgets(passwd, MAX_PASSWD_LEN, stdin);
   tty.c_lflag |= ECHO;
   tcsetattr(STDIN_FILENO, TCSANOW, &tty);
   printf("\n");
   
   encrypted_passwd = crypt(passwd, salt);
   shadow_passwd = getspnam(student_username);
   /* check that we have root privelege */
   if(shadow_passwd == NULL) {
      perror("Error when retrieving shadow password");
      exit(1);
   }
   else {
      /* make sure that passwords match */
      if(strcmp(encrypted_passwd, shadow_passwd->sp_pwdp)) {
         fprintf(stderr, "Incorrect password. Exiting...\n");
         exit(1);
      }
   }
}

void check_file() {
   int res;
   struct stat *stats = malloc(sizeof(struct stat));;
   res = stat("sniff", stats);
   if(res == -1) {
      perror("Error in checking sniff file");
      exit(1);
   }
   /* check if sniff is a regular file */
   if(!S_ISREG(stats->st_mode)) {
      fprintf(stderr, "Error: sniff is not regular file. Exiting...\n");
      exit(1);
   }
   /* check if owner of sniff is student */
   if(stats->st_uid != STUDENT_UID) {
      fprintf(stderr, "Error: sniff is not owned by student. Exiting...\n");
      exit(1);
   }
   /* check if owner has execute permission on sniff */
   if(!(S_IXUSR & stats->st_mode)) {
      fprintf(stderr, "Error: owner of sniff does not have execute permission. Exiting...\n");
      exit(1);
   }
   /* check if group/world has any permissions on sniff */
   if(((S_IRWXG | S_IRWXO) & stats->st_mode)) { /* should result in a 0 */
      fprintf(stderr, "Error: group and/or world has unauthorized permissions on sniff. Exiting...\n");
      exit(1);
   }
}

void check_mod_time() {
   int res;
   struct stat *stats = malloc(sizeof(struct stat));
   res = stat("sniff", stats);
   /* make sure sniff exists */
   if(res == -1) {
      perror("Error in checking sniff file");
      exit(1);
   }
   time_t *current_time = malloc(sizeof(time_t));
   time(current_time);
   /* check time difference between mod time and current time */
   if(difftime(*current_time, stats->st_mtim.tv_sec) > NUM_SECONDS) {
      fprintf(stderr, "Error: sniff was not modified within last minute. Exiting...\n");
      exit(1);
   }
} 
  
void set_sniff_properties() {
   /* set uid to owner and give r/x to owner and group */
   int res = chmod("sniff", FILE_PROTECTION);
   if(res == -1) {
      perror("chmod");  
      exit(1);
   }
   /* set owner of sniff to root, group to proj */
   res = chown("sniff", ROOT, PROJ);
   /* will fail without root privelege */
   if(res == -1) {
      perror("chown");
      exit(1);
   }
}
  
int main () {
   compare_ids();
   compare_passwds();
   check_file();
   check_mod_time();
   set_sniff_properties();
   return 0;
}

