#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include "cpe464.h"
#include "udp.h"

#define MAX_BUF 1000
#define MAX_INPUT_BUF 1024

#define NON_BLOCKING 0
#define BLOCKING 1

void client (int *writer, int *reader, int msg_len, int win_size) {
   int recv = 0, curr = 0, sent = 0;
   char curr_ack = 0;
   char *buf = (char *)malloc(MAX_BUF);
   
   close(writer[0]);
   close(reader[1]);

   while (curr < msg_len) {
      usleep(500);
      if (select_call(reader[0], BLOCKING)) {
         recv = read(reader[0], &buf[curr], 1);
         if (recv < 0) {
            perror("client read");
            exit(-1);
         }
         printf("client received %c (curr = %d)\n", buf[curr], curr);
         curr += recv; /* should be 1 */
         sent = write(writer[1], &curr_ack, 1);
         if (sent < 0) {
            perror("client write");
            exit(-1);
         }
         printf("client sending ack %d\n", curr_ack);
         curr_ack++;
      }
   }
}


void server (int *writer, int *reader, char *msg, int msg_len, int win_size) {
   int i = 0, curr = 0, recv = 0, sent = 0, open = 1;
   int lower_edge = 0, upper_edge = win_size, curr_ack = 0;   
   char *recv_buf = (char *)malloc(MAX_BUF);
   
   close(writer[0]);
   close(reader[1]);

   while (curr_ack < msg_len) {
      if (open) {
         sent = write(writer[1], &msg[curr], 1);
         if (sent < 0) {
            perror("server write");
            exit(-1);
         }
         if (sent > 0) {
            printf("server sent %c (curr = %d)\n", msg[curr], curr);
            curr += sent; /* should be 1 */           
         }
         if (curr == upper_edge) {
            printf("window closed\n");
            open = 0;
         }
      }
      if (select_call(reader[0], BLOCKING)) { /* if there are acks in pipe */
         recv = read(reader[0], &recv_buf[curr_ack], 1);
         if (recv < 0) {
            perror("server read");
            exit(-1);
         }
         printf("server received ack %d\n", recv_buf[curr_ack]);
         upper_edge += recv;
         curr_ack++;
         if (!open) {
            open = 1;  /* we got ack(s), so window is open again */
            printf("window reopened\n");
         }
      }
      if (curr_ack == msg_len) {
         printf("transfer complete\n");
      }
   }
   wait(NULL);
}
   

void pipe_and_fork (char *msg, int win_size) {
   pid_t pid;
   int msg_len, sent;
   int client_write[2], server_write[2]; 
   char *buf = (char *)malloc(MAX_BUF);   

   msg_len = strlen(msg);
   pipe(client_write);
   pipe(server_write);
   pid = fork();
   
   if (pid < 0) {
      perror("fork");
      exit(-1);
   }
   else if (pid) { /* parent */
      server(server_write, client_write, msg, msg_len, win_size);
   }
   else {  /* child */
      client(client_write, server_write, msg_len, win_size);
   }
}

void read_file (char *buf, char *filename) {
   int fd, bytes_read = 0, recv = 1;

   fd = open(filename, O_RDONLY);
   while (recv != 0) {
      recv = read(fd, &buf[bytes_read], 1);
      if (recv < 0) {
         perror("read");
         exit(-1);
      }
      if (recv > 0) {
         bytes_read++;
      }
   }
}

int main (int argc, char **argv) {
   int win_size;
   char *inbuf = (char *)malloc(MAX_INPUT_BUF);   

   if (argc < 3) {
      printf("Usage: ./window window_size filename\n");
      exit(-1);
   }
   win_size = strtol(argv[1], NULL, 10);
   read_file(inbuf, argv[2]);
   pipe_and_fork(inbuf, win_size);
   return 0;
}
