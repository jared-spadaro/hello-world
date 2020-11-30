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
#include <sys/select.h>
#include <stdint.h>
#include <fcntl.h>

#include "testing.h"
#include "networks.h"
#include "structs.h"

#define MAX_BUF 1024
#define CLIENT_ARRAY_SIZE 16
#define FREE 0
#define USED 1


int safe_recv (int socket, void *buf, int len) {
   int ret;
   if ((ret = recv(socket, buf, len, 0)) < 0) {
      perror("recv");
      exit(1);
   }  
   return ret; 
}

void Print_Client (struct client_t *client_info) {
   printf("New client connected.\n");
   printf("handle length = %d\n", client_info->handle_len);
   printf("handle = %s\n", client_info->handle);
   printf("socket = %d\n", client_info->socket);
}

int Find_Client (struct client_t *client_info, char *handle, 
 int num_clients) {
   int i;
   for (i = 0; i < num_clients; i++) {
      if(!strcmp(client_info[i].handle, handle) && 
          client_info[i].status == USED) {
         return client_info[i].socket;
      }
   }
   return -1;
}

void CheckHandle (int client_socket, struct client_t *client_info,
 int num_clients, char *newhandle) {
   int i, flag = 2;
   struct header_t *header = malloc(sizeof(header_t));
   for (i = 0; i < num_clients; i++) {
      if (!strcmp(client_info[i].handle, newhandle)) {
         flag = 3;
      }
   }
   header->packet_len = 3;
   header->flag = flag;
   send(client_socket, header, sizeof(header), 0);
   if (flag == 3) {
      close(client_socket);
      client_info[num_clients].status = FREE;
   }     
}
 
        

/* add new client metadata to our array of clients */
void Add_Client (int client_socket, struct client_t *client_info, 
 int num_clients) {
   int handle_len = 0;
   struct header_t *header_init = malloc(sizeof(header_t));
   struct client_t *new = client_info + num_clients;

   new->socket = client_socket;
   new->status = USED;
  
   /* get client info (handle, handle len, etc.) */
   safe_recv(client_socket, header_init, sizeof(header_t)); /* get chat header */
   safe_recv(client_socket, &handle_len, 1); /* get handle len */

   /* for now, assume flag = 1 */
   //printf("received flag = %d\n", header_init->flag);

   /* transfer info to client entry */
   new->handle_len = handle_len;
   new->handle = malloc(handle_len);
 
   safe_recv(client_socket, new->handle, handle_len);

   /* now respond with flag = 2 or flag = 3 */
   CheckHandle(client_socket, client_info, num_clients, new->handle);

}
   
void ForwardMessage(char *sending_handle, uint8_t sending_handle_len, 
 uint8_t num_dest_handles, uint8_t *dest_handle_lens, char *dest_handles, 
 char *msg, struct client_t *clients, int num_clients) {
   int i, ret, sent = 0;
   char *message;
   char *temp = dest_handles;

   message = malloc(sending_handle_len + strlen(msg) + 2);
   memcpy(message, sending_handle, sending_handle_len);
   message += sending_handle_len;
   *message = ':';
   message++;
   *message = ' ';
   message++;
   memcpy(message, msg, strlen(msg));
   message = message - 2 - sending_handle_len;
   /* forward message to clients */
   for (i = 0; i < num_dest_handles; i++) {
      ret = Find_Client(clients, temp, num_clients);
      if (ret != -1) {
         sent = send(ret, message, sending_handle_len + strlen(msg) + 2, 0);
         //printf("sent %d bytes to socket %d\n", sent, ret);
      }
      temp += dest_handle_lens[i];
   }    
   //exit(0);
}

/* function for forwarding messages to other clients */
void ParseMessage (int socket, struct header_t *header,
 struct client_t *client_info, int num_clients) {
   char *msg, *buf, *sending_handle, *dest_handles;
   int ret, ndx = 0, hdr_len = 5, msg_len, i, packet_len;
   uint8_t *dest_handle_lens, num_dest_handles, sending_handle_len; 
 
   packet_len = header->packet_len;
   buf = malloc(packet_len - sizeof(header_t));
 
   ret = safe_recv(socket, buf, header->packet_len - sizeof(header_t));
   
   memcpy(&sending_handle_len, buf, 1);
   buf++;
   hdr_len += sending_handle_len;
   sending_handle = malloc(sending_handle_len);
   memcpy(sending_handle, buf, sending_handle_len);
   buf += sending_handle_len;
   memcpy(&num_dest_handles, buf, 1);
   buf++;
   dest_handles = malloc(num_dest_handles * MAX_HANDLE_LEN);
   dest_handle_lens = malloc(num_dest_handles);
   for (i = 0; i < num_dest_handles; i++) {
      memcpy(&dest_handle_lens[i], buf, 1);
      buf++;
      hdr_len++;
      memcpy(&dest_handles[ndx], buf, dest_handle_lens[i]);
      buf += dest_handle_lens[i];
      ndx += dest_handle_lens[i];
      hdr_len += dest_handle_lens[i];
   }
   msg_len = packet_len - hdr_len;
   msg = malloc(msg_len);
   memcpy(msg, buf, msg_len);
   ForwardMessage(sending_handle, sending_handle_len, num_dest_handles,
    dest_handle_lens, dest_handles, msg, client_info, num_clients);
} 

    

void ProcessPacket (int socket, struct client_t *client_info, 
 int num_clients) {
   struct header_t *header;
   int ret;
   header = malloc(sizeof(header_t));         

   /* first read header to see how long packet is and check flag */
   ret = safe_recv(socket, header, sizeof(header_t));
   
   if (header->flag == INIT) {

   }
   else if (header->flag == MSG) {
      ParseMessage(socket, header, client_info, num_clients);
   }
}
   

/* using select, check to see if anyone has something to send.
 * then process all of the pending clients' requests */
void ProcessRequests (struct client_t *client_info, int num_clients,
 int server_socket) {
   int i;
   fd_set fds;
   
   FD_ZERO(&fds);

   /* add all open sockets to fd set */
   FD_SET(server_socket, &fds);   
   for (i = 0; i < num_clients; i++) {
      FD_SET(client_info[i].socket, &fds);
   }

   /* see who is waiting for processing */
   select(client_info[num_clients-1].socket+1, &fds, NULL, NULL, NULL);
  
   /* process pending requests */ 
   for (i = 0; i < num_clients; i++) {
      if (FD_ISSET(client_info[i].socket, &fds)) {
         ProcessPacket(client_info[i].socket, client_info, num_clients);
      }
   }
}

void Init_Client_Info (struct client_t *client_info, int size) {
   int i;
   for (i = 0; i < size; i++) {
      client_info[i].status = FREE;
      client_info[i].socket = -1;
      client_info[i].handle = NULL;
      client_info[i].handle_len = 0;
   }
}

void Run (uint16_t port) {
   int client_socket = -1, server_socket = -1, num_clients = 0;

   server_socket = tcpServerSetup(port);      /* init server */
   fcntl(server_socket, F_SETFL, O_NONBLOCK); /* server is nonblocking */

   struct client_t *client_info = malloc(sizeof(client_t) * CLIENT_ARRAY_SIZE);
   Init_Client_Info(client_info, CLIENT_ARRAY_SIZE);

   /* server runs until terminated with ^C */ 
   while (1) {
      client_socket = tcpAccept(server_socket);
      
      /* NEW CLIENT SETUP */
      if (client_socket != -1) {
         Add_Client(client_socket, client_info, num_clients);
         num_clients++;
      }
    
      /* PROCESS REQUESTS FROM EXISTING CLIENTS */
      if (num_clients > 0) {
         ProcessRequests(client_info, num_clients, server_socket);        
      }
      
      client_socket = -1;
   }
}

int main (int argc, char **argv) {
   uint16_t port = 0;
   if (argc > 1) {
      port = (uint16_t)strtol(argv[1], NULL, 10);
   }
   Run(port);
   return 0;
}




