#include "asgn3.h"

/* set up server */
uint32_t udp_server(int port) {
   int socket_fd = 0;
   struct sockaddr_in local;  /* our local socket address */
   uint32_t addr_len = sizeof(local);

   /* create the socket */
   if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
      perror("server socket creation");
      exit(-1);
   }
 
   /* set up the socket */
   local.sin_family = AF_INET; /* internet family */
   local.sin_addr.s_addr = INADDR_ANY; /* wild card machine address */
   local.sin_port = htons(port);  /* if 0, system chooses port */
   
   /* bind socket address to a port */
   if (bind(socket_fd, (struct sockaddr *)&local, addr_len) < 0) {
      perror("server bind");
      exit(-1);
   }

   /* get port name and print it out */
   getsockname(socket_fd, (struct sockaddr *)&local, &addr_len);
   printf("Using Port %d\n", ntohs(local.sin_port));

   return socket_fd;
}



/* returns pointer to sockaddr_in or NULL if host not found, and socket fd */
uint32_t udp_client_setup(char *hostname, uint16_t port, Connection *connection) {
   struct hostent *hp = NULL;  /* remote host address */
   
   connection->socket_fd = 0;
   connection->len = sizeof(struct sockaddr_in);
   
   /* create socket */
   if ((connection->socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
      perror("clilent socket creation"); 
      exit(-1);
   }

   /* designate addressing family */
   connection->remote.sin_family = AF_INET;

   /* get address of remote host */
   hp = gethostbyname(hostname);
 
   if (hp == NULL) {
      printf("Host not found: %s\n", hostname);
      return -1;
   }

   memcpy(&(connection->remote.sin_addr), hp->h_addr, hp->h_length);

   /* store port used on remote side */
   connection->remote.sin_port = htons(port);

   return 0;
}


/* select and supporting code */
int32_t select_call(int32_t socket_fd, int32_t seconds, int32_t microseconds, 
 int32_t set_null) {
   fd_set fds;
   struct timeval timeout;
   struct timeval *timeout_p = NULL;   

   if(set_null == NOT_NULL) {
      timeout.tv_sec = seconds;  /* 1 second timeout whenever we block */
      timeout.tv_usec = microseconds;
      timeout_p = &timeout;
   }
   //else {
      //flags = fcntl(socket_fd, F_GETFL, 0);
      //fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);
   //}

   FD_ZERO(&fds);
   FD_SET(socket_fd, &fds);

   if(select(socket_fd + 1, &fds, NULL, NULL, timeout_p) < 0) {
      perror("select");
      exit(-1);
   }

   if(FD_ISSET(socket_fd, &fds)) {
      return 1;
   }
   else {
      return 0;
   }
}


/* constructcs header and sends packet */
int32_t send_buf(uint8_t *buf, uint32_t len, Connection *connection, 
 uint8_t flag, uint32_t seq, uint8_t *packet) {
   int32_t sent_len = 0;
   int32_t sending_len = 0;
   
   /* set up packet (seq, crc, flag, data) */
   if (len > 0) {
      memcpy(&packet[sizeof(Header)], buf, len);  /* copy data to packet */
   }

   sending_len = createHeader(len, flag, seq, packet);
   sent_len = safeSend(packet, sending_len, connection);
   return sent_len;
}


/* creates header and places in front of data */
int createHeader(uint32_t len, uint8_t flag, uint32_t seq, uint8_t *packet) {
   Header *hdr = (Header *)packet;
   uint16_t cksum;

   seq = htonl(seq);
   memcpy(&(hdr->seq), &seq, sizeof(seq));
   hdr->flag = flag;
   memset(&(hdr->cksum), 0, sizeof(cksum));
   cksum = in_cksum((unsigned short *)packet, len + sizeof(Header));
   memcpy(&(hdr->cksum), &cksum, sizeof(cksum));

   return len + sizeof(Header);
}


/* reads in a packet and extracts header and data */
int32_t recv_buf(uint8_t *buf, int32_t len, int32_t recv_sk_fd, 
 Connection *connection, uint8_t *flag, uint32_t *seq) {
   char data_buf[MAX_BUF_LEN];   
   int32_t recv_len = 0;
   int32_t data_len = 0;

   recv_len = safeRecv(recv_sk_fd, data_buf, len, connection);
   data_len = retrieveHeader(data_buf, recv_len, flag, seq);

   /* copy data over */
   if (data_len > 0) {
      memcpy(buf, &data_buf[sizeof(Header)], data_len);
   }
   return data_len;
}


/* extract data from received header */
int retrieveHeader(char *data_buf, int recv_len, uint8_t *flag, uint32_t *seq) {
   Header *hdr = (Header *)data_buf;
   int ret = 0;

   if (in_cksum((unsigned short *)data_buf, recv_len) != 0) {
      ret = CRC_ERROR;
   }
   else {
      *flag = hdr->flag;
      memcpy(seq, &(hdr->seq), sizeof(hdr->seq));
      *seq = ntohl(*seq);
      ret = recv_len - sizeof(Header);
   }
   return ret;
}


/* safely send packet */
int32_t safeSend(uint8_t *packet, uint32_t len, Connection *connection) {
   int send_len = 0;

   if((send_len = sendtoErr(connection->socket_fd, packet, len, 0, 
    (struct sockaddr *)&(connection->remote), connection->len)) < 0) {
      perror("sendto");
      exit(-1);
   }
 
   return send_len;
}


/* safely receive packet */
int32_t safeRecv(int recv_socket_fd, char *data_buf, int len, Connection *connection) {
   int recv_len = 0;
   uint32_t remote_len = sizeof(struct sockaddr_in);

   if ((recv_len = recvfrom(recv_socket_fd, data_buf, len, 0, 
    (struct sockaddr *)&(connection->remote), &remote_len)) < 0) {
      perror("recv from");
      exit(-1);
   }

   connection->len = remote_len;

   return recv_len;
}   


/* process select and keep track of number of tries */
int processSelect(Connection *client, int *retry_cnt, int timeout_state, 
 int data_ready_state, int done_state) {
   int ret = data_ready_state;

   (*retry_cnt)++;
   if (*retry_cnt > MAX_TRIES) {
      printf("Sent data %d times, no ACK. Terminating...\n", MAX_TRIES);
      ret = done_state;
   }
   else {
      if (select_call(client->socket_fd, SHORT_TIME, 0, NOT_NULL) == 1) {
         *retry_cnt = 0;
         ret = data_ready_state;
      }
      else {
         ret = timeout_state;
      }
   }
   return ret;
}


































   
