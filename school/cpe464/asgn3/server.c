/* Server for sliding window file transfer
 * Written by Jared Spadaro 
 * 3/14/17
 * CPE464 Prof Smith
 */

#include "asgn3.h"

enum State {
   START_STATE, HANDSHAKE_STATE, FILENAME_EXCHANGE_STATE, 
   FILENAME_RESPONSE_STATE, SEND_DATA_STATE, WAIT_ON_FILENAME_ACK,
   NONBLOCK_WAIT_ON_ACK_STATE, BLOCK_WAIT_ON_ACK_STATE, WAIT_ON_EOF_ACK_STATE, 
   DONE_STATE
};

typedef enum State STATE;

int processArgs (int argc, char **argv) {
   int port;

   if (argc < 2 || argc > 3) {
      printf("Usage: %s error-rate [port-number]\n", argv[0]);
      exit(-1);
   }
   if (argc == 3) {
      port = atoi(argv[2]);
   }
   else {
      port = 0;
   }  
   
   return port;
}

/* establish connection with client */
STATE handshake (int32_t server_sk_fd, Connection *client) {
   uint32_t recv_len = 0;
   uint8_t response[1];
   uint8_t rec_buf[sizeof(Header)];
   uint8_t send_packet[sizeof(Header)];   
   uint8_t flag;
   uint32_t seq_recv;
   uint32_t sent;
   int ret = DONE_STATE;

   /* block until client sends handshake */
   if (select_call(server_sk_fd, 0, 0, SET_NULL) == 1) {
      /* receive the handshake request */
      recv_len = recv_buf(rec_buf, sizeof(Header), 
       server_sk_fd, client, &flag, &seq_recv);
      if (recv_len == CRC_ERROR) {
         return HANDSHAKE_STATE;
      }
      if (flag == HANDSHAKE_REQUEST) {
         if ((client->socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            perror("open client socket");
            exit(-1);
         }
         /* send the handshake response */
         sent = send_buf(response, 0, client, 
          HANDSHAKE_RESPONSE, 0, send_packet); 
         ret = FILENAME_EXCHANGE_STATE;
      }
      else {
         printf("received bogus data\n");
      }
   }
   return ret;
}

STATE check_filename(uint8_t *filename, int *fd) {
   int ret;

   *fd = open((char *)filename, O_RDONLY);
   if (*fd < 0) {
      printf("File '%s' not found\n", filename);
      ret = FNAME_ERR;
   }
   else {
      ret = FNAME_OK;
   }
   return ret;
}  

/* recv filename, check if it exists, respond accordingly */
/* also recv window size and buffer size for sending packets */
STATE recv_filename(Connection *client, uint8_t *filename, uint32_t *win_size, 
 uint16_t *buf_size, int *fd) {
   uint32_t recv_len = 0;
   uint8_t response[1];
   uint8_t rec_buf[MAX_BUF_LEN];
   uint8_t send_packet[sizeof(Header)];   
   uint8_t recv_flag;
   uint32_t seq_recv;
   int ret = DONE_STATE;
   uint32_t fname_len;
   uint8_t send_flag;
   int32_t sent;

   if (select_call(client->socket_fd, LONG_TIME, 0, NOT_NULL) == 1) {
      /* receive filename, winsize, bufsize */
      recv_len = recv_buf(rec_buf, MAX_BUF_LEN, 
       client->socket_fd, client, &recv_flag, &seq_recv);
      if (recv_len == CRC_ERROR) {
         ret = FILENAME_EXCHANGE_STATE;
      }
      else {
         if (recv_flag == FILENAME) {
            fname_len = recv_len - sizeof(uint32_t) - sizeof(uint16_t);
            /* extract filename */
            memcpy(filename, rec_buf, fname_len); 
            filename[fname_len] = '\0';
            send_flag = check_filename(filename, fd);
            if (send_flag == FNAME_OK) {
               ret = SEND_DATA_STATE;
               /* extract window size */
               memcpy(win_size, rec_buf + fname_len, sizeof(uint32_t));
               /* extract buffer size */
               memcpy(buf_size, rec_buf + fname_len + sizeof(uint32_t), 
                sizeof(uint16_t));   
            }
            sent = send_buf(response, 0, client, send_flag, 0, send_packet); 
         }
         else if (recv_flag == HANDSHAKE_REQUEST) {
            /* send the handshake response */
            sent = send_buf(response, 0, client, HANDSHAKE_RESPONSE, 0, send_packet); 
            ret = FILENAME_EXCHANGE_STATE;
         }
         else {
            printf("Bad flag received\n");
            ret = FILENAME_EXCHANGE_STATE;
         }  
      }
   }
   return ret;
}

void store_packet(WindowBuffer **win_buf, int32_t recv_len, 
 uint8_t *data_buf, uint32_t recv_seq, uint32_t win_size, int32_t *loc) {
   WindowBuffer *temp;

   if (*loc == win_size) {
      *loc = 0;
   }

   temp = *win_buf + (*loc);

   memcpy(temp->data_buf, data_buf, recv_len);
   temp->seq = recv_seq;
   temp->len = recv_len;
   temp->written = 0;

   (*loc)++;
}  

void send_srej_packet(WindowBuffer **win_buf, 
 uint32_t srej_seq, uint32_t win_size, Connection *client) {
   int i;
   WindowBuffer *temp;
   uint8_t packet[MAX_BUF_LEN + sizeof(Header)];

   for (i = 0; i < win_size; i++) {
      temp = *win_buf + i;
      if (temp->seq == srej_seq) {
         send_buf(temp->data_buf, temp->len, client, DATA, temp->seq, packet); 
         temp->written = 1;
         i = win_size;
      }
   }
}

/* returns either done, send_eof, or send_data states */
STATE send_data(Connection *client, uint32_t *win_size, uint16_t *buf_size,
 int *fd, uint32_t *seq, int32_t *upper_edge, uint32_t *curr_ack, 
 WindowBuffer **win_buf, int32_t *loc, int32_t *is_srej, int32_t *eof) {
   uint8_t *buf;
   uint8_t *packet;
   int32_t len_read;
   int ret = DONE_STATE;
   static int current = 0;   

   buf = calloc(sizeof(uint8_t), *buf_size);
   packet = calloc(sizeof(uint8_t), *buf_size + sizeof(Header));
   
   if (*win_buf == NULL) {
      *win_buf = calloc(sizeof(WindowBuffer), *win_size);
   }

   /* initialize upper window edge just once */
   if (*upper_edge == 0) {  
      *upper_edge = *win_size - 1;  
   }

   len_read = read(*fd, buf, *buf_size);
   printf("buffer = %s\n", buf);
   if (len_read < 0) {
      perror("server read");
   }
   else if(len_read == 0) {
      if (*curr_ack == (*seq) - 1) {
         send_buf(buf, 1, client, END_OF_FILE, *seq, packet);
         ret = BLOCK_WAIT_ON_ACK_STATE;
         *eof = 1;
      }
      else {
         ret = BLOCK_WAIT_ON_ACK_STATE;
         *eof = 0;
      }
   }
   else {  /* normal data send */
      if (current <= *upper_edge) {
         send_buf(buf, len_read, client, DATA, *seq, packet);  
         store_packet(win_buf, len_read, buf, *seq, *win_size, loc);
         (*seq)++;
         if (*is_srej == 0) {
            current++;
         }
         ret = NONBLOCK_WAIT_ON_ACK_STATE;
      }
      else {
         ret = BLOCK_WAIT_ON_ACK_STATE;
      }
   }
   return ret;
}
 
/* gets run every time server reads data. no retry count needed */
STATE recv_ack_nonblocking(Connection *client, int32_t *upper_edge, 
 uint32_t *curr_ack, WindowBuffer **win_buf, int32_t *loc, uint32_t *win_size,
 int32_t *is_srej) {
   uint8_t rec_buf[sizeof(uint32_t)];
   uint8_t recv_flag = 0;
   uint32_t recv_seq = 0;
   uint32_t *recv_rr = calloc(sizeof(uint32_t), 1);
   int32_t recv_len;
   uint32_t srej_seq;

   if (select_call(client->socket_fd, 0, 0, NOT_NULL) == 1) {
      recv_len = recv_buf(rec_buf, sizeof(uint32_t) + sizeof(Header), 
       client->socket_fd, client, &recv_flag, &recv_seq);
      
      if (recv_len == CRC_ERROR) {
         /* ignore. can't do anything about it */
         return SEND_DATA_STATE;
      }

      if (recv_flag == RR) {
         recv_rr = (uint32_t *)rec_buf;
         *recv_rr = ntohl(*recv_rr);
         *curr_ack = *recv_rr;
         
         (*upper_edge)++;
         *is_srej = 0;
      }
      else if (recv_flag == SREJ) {
         memcpy(&srej_seq, (uint32_t *)rec_buf, sizeof(uint32_t));
         srej_seq = ntohl(srej_seq);
         /* pull srej packet from buffer and send */
         send_srej_packet(win_buf, srej_seq, *win_size, client);    
         *is_srej = 1;    
      }      
      else {
         printf("got something other than RR. exiting...\n");
         exit(-1);
      }
   }
   return SEND_DATA_STATE;
}
  
STATE recv_ack_blocking(Connection *client, int32_t *upper_edge, 
 uint32_t *curr_ack, WindowBuffer **win_buf, int32_t *loc, uint32_t *win_size,
 int32_t *is_srej, int32_t *eof, uint32_t *seq) {
   uint8_t rec_buf[sizeof(uint32_t)];
   uint8_t recv_flag = 0;
   uint32_t recv_seq = 0;
   static int retryCount = 0;
   int ret = DONE_STATE;   
   uint32_t *recv_rr = calloc(sizeof(uint32_t), 1);
   int32_t recv_len;
   uint32_t srej_seq;
   uint8_t buf[1];
   uint8_t packet[sizeof(Header)];
 
   /* check for an RR, waiting for 1 second */
   if ((ret = processSelect(client, &retryCount, BLOCK_WAIT_ON_ACK_STATE, 
    SEND_DATA_STATE, DONE_STATE)) == SEND_DATA_STATE) {
      recv_len = recv_buf(rec_buf, sizeof(Header) + sizeof(uint32_t), 
       client->socket_fd, client, &recv_flag, &recv_seq); 

      if (recv_len == CRC_ERROR) {
         return BLOCK_WAIT_ON_ACK_STATE;
      }

      if (recv_flag == RR) {
         recv_rr = (uint32_t *)rec_buf;
         *recv_rr = ntohl(*recv_rr);
         *curr_ack = *recv_rr;

         (*upper_edge)++;
         *is_srej = 0;
      }
      else if (recv_flag == SREJ) {
         memcpy(&srej_seq, (uint32_t *)rec_buf, sizeof(uint32_t));
         srej_seq = ntohl(srej_seq);
         /* pull srej packet from buffer and send */
         send_srej_packet(win_buf, srej_seq, *win_size, client);
         *is_srej = 1;
      }
      else if (recv_flag == EOF_ACK) {
         printf("Done\n");
         return DONE_STATE;
      }
      else {}
         
   }
   else if (ret == BLOCK_WAIT_ON_ACK_STATE) {
      if (*eof == 0) {
         printf("resending lowest un-RR'd packet\n");
         send_srej_packet(win_buf, *curr_ack + 1, *win_size, client);
      }
      else {
         printf("resending eof\n");
         send_buf(buf, 1, client, END_OF_FILE, *seq, packet);
      }
   }
   return ret;
}

STATE recv_eof_ack(Connection *client) {
   uint8_t recv_flag;
   uint32_t recv_seq;
   uint8_t rec_buf[1];
   int32_t recv_len;

   if (select_call(client->socket_fd, LONG_TIME, 0, NOT_NULL) == 1) {
      recv_len = recv_buf(rec_buf, sizeof(Header), client->socket_fd, 
       client, &recv_flag, &recv_seq);
      if (recv_len == CRC_ERROR) {
         return WAIT_ON_EOF_ACK_STATE;
      }
      else if (recv_flag == EOF_ACK) {
         return DONE_STATE;
      }
      else {}
   } 
   return DONE_STATE;
}


/* run the server */
void runServer(int32_t server_sk_fd) {
   STATE state = HANDSHAKE_STATE;
   Connection client;
   uint32_t *win_size = malloc(sizeof(uint32_t));
   uint16_t *buf_size = malloc(sizeof(uint16_t));
   uint8_t filename[MAX_FILENAME_LEN];
   int *fd = malloc(sizeof(int));
   uint32_t *seq = malloc(sizeof(uint32_t));
   int32_t *upper_edge = malloc(sizeof(int32_t));
   uint32_t *curr_ack = malloc(sizeof(int32_t));
   WindowBuffer *win_buf = NULL;
   int32_t *loc = calloc(sizeof(int32_t), 1);
   int32_t *is_srej = calloc(sizeof(int32_t), 1); 
   int32_t *eof = calloc(sizeof(int32_t), 1);
   *seq = 0;
   *upper_edge = 0;
   *curr_ack = 0;

   while (state != DONE_STATE) {
      switch(state) {
         case HANDSHAKE_STATE:
            state = handshake(server_sk_fd, &client);
            break;
     
         case FILENAME_EXCHANGE_STATE:
            state = recv_filename(&client, filename,
             win_size, buf_size, fd);
            break; 

         case SEND_DATA_STATE:
            state = send_data(&client, win_size, buf_size, fd, 
             seq, upper_edge, curr_ack, &win_buf, loc, is_srej, eof);
            break;

         case NONBLOCK_WAIT_ON_ACK_STATE:
            state = recv_ack_nonblocking(&client, upper_edge, 
             curr_ack, &win_buf, loc, win_size, is_srej);
            break;

         case BLOCK_WAIT_ON_ACK_STATE:
            state = recv_ack_blocking(&client, upper_edge, 
             curr_ack, &win_buf, loc, win_size, is_srej, eof, seq);
            break; 

         case WAIT_ON_EOF_ACK_STATE:
            state = recv_eof_ack(&client);
            break;

         case DONE_STATE:
            printf("In done state\n");
            exit(0);
            break;
      
         default:
            printf("In default state\n");
            exit(-1);
            break;
      }
   }
}
 
void process_server (int32_t server_sk_fd) {
   pid_t pid = 0;
   int status = 0;

   /* get new client connection, fork child, parent process waits */
   while (1) {
      /* block waiting for new client */
      if (select_call(server_sk_fd, LONG_TIME, 0, SET_NULL) == 1) {
         pid = fork();
         if (pid < 0) {
            perror("fork");
         }
         if (pid == 0) {
            runServer(server_sk_fd);
            exit(0);
         }

         while (waitpid(-1, &status, WNOHANG) > 0) {}
      }
   }
}
 
int main (int argc, char **argv) {
   int port;
   int32_t server_sk_fd;
   uint32_t *seq = malloc(sizeof(uint32_t));
   *seq = 0;

   port = processArgs(argc, argv);
   sendtoErr_init(atof(argv[1]), DROP_OFF, FLIP_ON, DEBUG_ON, RSEED_ON);

   /* set up main server port */
   server_sk_fd = udp_server(port);

   process_server(server_sk_fd);

   return 0;
}
