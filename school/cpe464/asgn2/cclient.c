#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "testing.h"
#include "structs.h"
#include "networks.h"

#define MAX_BUF 1024

void Safe_Send (int socket, void *buf, int len) {
   int ret;
   ret = send(socket, buf, len, 0);
   if (ret < 0) {
      perror("send");
      exit(1);
   }
}

int Setup (char *handle, char *hostname, char *port) {
   int socket = 0, handle_len;
   struct header_t *header;   
   char *buf;

   handle_len = strlen(handle);
   header = malloc(sizeof(header_t));

   header->packet_len = handle_len + sizeof(header_t) + 1;
   header->flag = INIT;

   buf = malloc(header->packet_len);

   memcpy(buf, header, sizeof(header_t));
   buf += sizeof(header_t);
   memcpy(buf, &handle_len, 1);
   buf++;
   memcpy(buf, handle, handle_len);
   buf = buf - sizeof(header_t) - 1;

   socket = tcpClientSetup(hostname, port); /* connect call */

   Safe_Send(socket, buf, header->packet_len);

   recv(socket, header, sizeof(header_t), 0);
   if (header->flag != CONFIRM) {
      printf("bad handle. exiting\n");
      exit(1);
   }
   
   return socket;
}
   
void SendMessagePacket(int socket, uint16_t packet_len, char *sending_handle, 
 uint8_t sending_handle_len, uint8_t num_dest_handles, char *dest_handles, 
 uint8_t *dest_handle_lengths, char *msg, uint16_t msg_len) {
   int i, ndx = 0, net_packet_len, flag;
   char *buffer = malloc(packet_len); /* buffer to send packet */

   net_packet_len = packet_len;  
   flag = MSG; 

   memcpy(buffer, &packet_len, sizeof(uint16_t));
   buffer += sizeof(uint16_t);
   memcpy(buffer, &flag, 1);
   buffer++;
   memcpy(buffer, &sending_handle_len, sizeof(uint8_t));
   buffer += sizeof(uint8_t);
   memcpy(buffer, sending_handle, sending_handle_len);
   buffer += sending_handle_len;
   memcpy(buffer, &num_dest_handles, sizeof(uint8_t));
   buffer += sizeof(uint8_t);
    
   /* place dest handle lengths and handles in buffer */
   for (i = 0; i < num_dest_handles; i++) {
      memcpy(buffer, &dest_handle_lengths[i], sizeof(uint8_t));
      buffer++;
      memcpy(buffer, &dest_handles[ndx], dest_handle_lengths[i]);
      buffer += dest_handle_lengths[i];
      ndx += dest_handle_lengths[i];
   }
   
   memcpy(buffer, msg, msg_len);
   buffer += msg_len;
   buffer -= packet_len; /* back to start */

   Safe_Send(socket, buffer, packet_len); 
}
  
/* function for creating message packet */
void ProcessMessage (int socket, char *sending_handle, char *input, 
 int send_len) {
   uint8_t sending_handle_len = strlen(sending_handle);
   uint8_t num_dest_handles;
   uint8_t *dest_handle_lengths;
   uint16_t packet_len = 5 + sending_handle_len;
   uint16_t msg_len = 0;
   char *dest_handles, *temp;
   char *msg = malloc(1000);
   int total_dest_handle_len = 0;
   int j, i = 0, len = 0, flag = 0;

   temp = malloc(1);
   input += 3; /* jump past the "%M_" */
   memcpy(temp, input, 1); /* one char denoting # of dest handles */
   num_dest_handles = strtol(temp, NULL, 10);
   
   if (num_dest_handles == 0) { 
      /* case where this field was omitted and strtol returned 0 */
      num_dest_handles = 1;
   } 
   else {
      flag = 1;
      input += 2; /* there was a # and we now skip past it */
   }

   /* array of 8-bit numbers which holds the lengths of the 
    * destination handles, in order */ 
   dest_handle_lengths = malloc(num_dest_handles);

   /* array of chars which holds the handles themselves, in order */
   dest_handles = malloc(num_dest_handles * MAX_HANDLE_LEN);

   /* use whitespace as delimiter to parse dest handles */
   for (j = 0; j < num_dest_handles; j++) {
      while (input[i] != ' ') {
         dest_handles[i-j] = input[i];
         i++;
         len++;
      }
      dest_handle_lengths[j] = len;
      total_dest_handle_len += len;
      i++; /* skip past whitespace */
      len = 0;
   }
   packet_len += total_dest_handle_len;
   packet_len += num_dest_handles; /* one byte for each handle */

   /* point input to start of message */
   input += total_dest_handle_len + num_dest_handles;

   /* now must find length of message to add to packet length
    * and copy message into string */ 
   msg_len = send_len - 3 - total_dest_handle_len - num_dest_handles;
   if (flag) {
      msg_len -= 2; /* if # dest handles we included, subtract those 2 chars */
   }
   memcpy(msg, input, msg_len);
   packet_len += msg_len;
   SendMessagePacket(socket, packet_len, sending_handle, sending_handle_len, 
    num_dest_handles, dest_handles, dest_handle_lengths, msg, msg_len);    
}

/* M, B, L, E */
void ProcessCmd (int socket, char *sending_handle, char *packet, 
 char cmd, int send_len) {
   if(cmd == 'M' || cmd == 'm') {
      ProcessMessage(socket, sending_handle, packet, send_len);      
   }    
      
   printf("$: ");
}

void Run (int socket, char *name) {
   int send_len, rec;
   char *buf = malloc(MAX_BUF); 
   char *rec_buf = malloc(MAX_BUF);
   fcntl(socket, F_SETFL, O_NONBLOCK); /* client is nonblocking */
   
   fd_set fds;
   FD_ZERO(&fds);
   FD_SET(socket, &fds);
   FD_SET(0, &fds);

   while (1) {
      printf("$: ");
      send_len = 0;
 
      select(socket+1, &fds, NULL, NULL, NULL);

      if(FD_ISSET(0, &fds)) {
         while ((buf[send_len] = getchar()) != '\n' && send_len < MAX_BUF - 1) {
            send_len++;
         }
         buf[send_len] = '\0';
         if (buf[0] == '%') {
            ProcessCmd(socket, name, buf, buf[1], send_len);
         }
      }
      else if (FD_ISSET(socket, &fds)) {
         rec = recv(socket, rec_buf, MAX_BUF, 0);
         if (rec > 0) {
            printf("%s\n", rec_buf);
         }
      }
      else {} 
      FD_ZERO(&fds);
      FD_SET(socket, &fds);
      FD_SET(0, &fds);
  
   }
}
    
int main (int argc, char **argv) {
   int socket;
   if (argc != 4) {
      printf("usage: %s handle server-name server-port\n", argv[0]);
      exit(1);
   }
   socket = Setup(argv[1], argv[2], argv[3]);
   Run(socket, argv[1]);
   return 0;
} 

