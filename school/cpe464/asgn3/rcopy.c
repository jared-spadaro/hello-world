/* Rcopy for sliding window file transfer
 * Written by Jared Spadaro 
 * 3/14/17
 * CPE464 Prof Smith
 */

#include "asgn3.h"

enum State {
   START_STATE, HANDSHAKE_STATE, FILENAME_EXCHANGE_STATE, 
    RECV_DATA_STATE, RECV_EOF_STATE, DONE_STATE
};
typedef enum State STATE;

void checkArgs (int argc, char **argv) {
   if (argc != 8) {
      printf("Usage: %s local-file remote-file window-size buffer-size"
             " error-percent remote-machine remote-port\n", argv[0]);
      exit(-1);
   }
   if (strlen(argv[1]) > 100 || strlen(argv[2]) > 100) {
      printf("Filename lengths exceed limit of 100 characters\n");
      exit(-1);
   }
   if (atoi(argv[4]) > MAX_BUF_LEN) {
      printf("Buffer size exceeds limit of %d bytes\n", MAX_BUF_LEN);
      exit(-1);
   }
   if (atof(argv[5]) < 0 || atoi(argv[5]) > 1) {
      printf("Error percent must be between 0 and 1\n");
      exit(-1);
   }
}

/* set up rcopy's socket */
STATE start(char **argv, Connection *server) {
   STATE ret;

   /* if connected to server before, close server socket before reopening */
   if (server->socket_fd > 0) {
      close(server->socket_fd);
   }

   /* if host can not be found, exit */
   if (udp_client_setup(argv[6], atoi(argv[7]), server) < 0) {
      ret = DONE_STATE;
   }
   else {
      ret = HANDSHAKE_STATE;
   }
   return ret;
}        

/* initial handshake between rcopy and server */
STATE handshake (Connection *server) {
   int ret = DONE_STATE;
   uint8_t rec_buf[sizeof(Header)];
   uint8_t sen_buf[1];
   uint8_t packet[sizeof(Header)];
   static int retryCount = 0; 
   uint32_t recv_seq;   
   uint32_t recv_len;
   uint8_t recv_flag; 

   send_buf(sen_buf, 0, server, HANDSHAKE_REQUEST, 0, packet); 
   
   /* check for a reply, waiting for 1 second */
   if ((ret = processSelect(server, &retryCount, HANDSHAKE_STATE, 
    FILENAME_EXCHANGE_STATE, DONE_STATE)) == FILENAME_EXCHANGE_STATE) {
      recv_len = recv_buf(rec_buf, sizeof(Header), 
       server->socket_fd, server, &recv_flag, &recv_seq); 
   
      if (recv_len == CRC_ERROR) {
         //printf("[HANDSHAKE RESPONSE] CRC error. resending handshake request\n");
         return HANDSHAKE_STATE;
      }
   }
   return (STATE)ret;
}
  
/* send filename, window size, and buffer size to server */
STATE send_filename (Connection *server, char *filename, size_t filename_len,
 uint32_t win_size, uint16_t buf_size, uint8_t *first_pkt_buf) {
   uint32_t data_len = filename_len + sizeof(win_size) + sizeof(buf_size);
   uint8_t sen_buf[data_len];
   uint8_t packet[sizeof(Header) + data_len];
   uint8_t rec_buf[MAX_BUF_LEN];
   static int retryCount = 0;   
   int ret = DONE_STATE;
   uint32_t recv_len, recv_seq;  
   uint8_t recv_flag;

   memcpy(sen_buf, filename, filename_len);
   memcpy(sen_buf + filename_len, &win_size, sizeof(win_size));
   memcpy(sen_buf + filename_len + sizeof(win_size), &buf_size, 
    sizeof(buf_size));
  
   send_buf(sen_buf, data_len, server, FILENAME, 0, packet);

   /* check for a reply, waiting for  1 second */
   if ((ret = processSelect(server, &retryCount, FILENAME_EXCHANGE_STATE,
    RECV_DATA_STATE, DONE_STATE)) == RECV_DATA_STATE) {
      /* now check for ok filename */
      recv_len = recv_buf(rec_buf, MAX_BUF_LEN + sizeof(Header), 
       server->socket_fd, server, &recv_flag, &recv_seq);
      if (recv_len == CRC_ERROR) {
         //printf("[FILENAME RESPONSE] CRC error. going to RECV_DATA\n");
         return RECV_DATA_STATE;  
      }

      if (recv_flag == FNAME_ERR) {
         printf("Server couldn't find remote file\n");
         ret = DONE_STATE;
      }
      else if (recv_flag == FNAME_OK) {
         ret = RECV_DATA_STATE;
      }
      else if (recv_flag == DATA) {
         first_pkt_buf = malloc(MAX_BUF_LEN);
         memcpy(first_pkt_buf, rec_buf, recv_len);
         ret = RECV_DATA_STATE;
      }  
      else {
         printf("Error receiving data\n");
         ret = DONE_STATE;
      }
   }
   return (STATE)ret;
} 

void send_srej (Connection *server, uint32_t *expected_seq, uint32_t *seq) {
   uint8_t sen_buf[sizeof(int32_t)];
   uint8_t packet[sizeof(Header) + sizeof(int32_t)];
   int32_t srej_num = *expected_seq;

   srej_num = htonl(srej_num);
   memcpy(sen_buf, &srej_num, sizeof(uint32_t));
   srej_num = ntohl(srej_num);
   send_buf(sen_buf, sizeof(int32_t), server, SREJ, *seq, packet);
  (*seq)++;
}
 
void init_winbuf (WindowBuffer **win_buf, uint32_t win_size) {
   int i;
   WindowBuffer *temp;
   for (i = 0; i < win_size; i++) {
      temp = *win_buf + i;
      temp->written = 1;
   }
}
     
void store_packet(WindowBuffer **win_buf, int32_t recv_len, 
 uint8_t *data_buf, uint32_t recv_seq, uint32_t win_size) {
   int i;
   WindowBuffer *temp;
   
   for (i = 0; i < win_size; i++) {
      temp = *win_buf + i;
      if (temp->written) {
         memcpy(temp->data_buf, data_buf, recv_len);
         temp->seq = recv_seq;
         temp->len = recv_len;
         temp->written = 0;
         i = win_size;
      }
   }
}  

/* check buffer for packets that we can be written and acked */
void check_buf_for_expected_packet(WindowBuffer **win_buf, uint32_t *expected_seq, 
 uint32_t win_size, int fd, uint32_t *curr_seq, uint32_t ack_seq, Connection *server) {
   int i = 0;
   uint8_t *sen_data_buf = calloc(sizeof(uint32_t), 1); 
   uint8_t packet[sizeof(uint32_t) + sizeof(Header)];
   WindowBuffer *temp;

   while (i < win_size) {
      temp = *win_buf + i;
      if (temp->seq == *expected_seq && temp->written == 0) {
         ack_seq = htonl(temp->seq);
         memcpy(sen_data_buf, &ack_seq, sizeof(uint32_t));
         send_buf(sen_data_buf, sizeof(uint32_t), server, RR, *curr_seq, packet);            
         (*curr_seq)++;
         
         write(fd, temp->data_buf, temp->len);
         temp->written = 1;
         (*expected_seq)++;
         i = -1;
      }
      i++;
   }
}

STATE recv_data (Connection *server, uint32_t *seq, uint32_t *expected_seq, 
 int fd, uint8_t *first_pkt_buf, WindowBuffer **win_buf, uint32_t win_size,
 uint32_t *expected_srej_seq) {
   uint8_t data_buf[MAX_BUF_LEN];
   uint8_t *sen_data_buf;
   uint8_t packet[MAX_BUF_LEN];
   int32_t recv_len = 0;
   uint8_t flag = 0;
   uint32_t recv_seq = 0;   
   
   if (*win_buf == NULL) {
      *win_buf = calloc(sizeof(WindowBuffer), win_size);
      init_winbuf(win_buf, win_size);
   }
   sen_data_buf = calloc(sizeof(uint32_t), 1);

   if (first_pkt_buf != NULL) {
      recv_seq = 0;
      recv_seq = htonl(recv_seq);
      memcpy(sen_data_buf, &recv_seq, sizeof(uint32_t));
      recv_seq = ntohl(recv_seq);
      send_buf(sen_data_buf, sizeof(uint32_t), server, RR, *seq, packet);
      (*seq)++;
         
      write(fd, &data_buf, recv_len);
      (*expected_seq)++;
      return RECV_DATA_STATE;
   }

   if (select_call(server->socket_fd, LONG_TIME, 0, NOT_NULL) == 0) {
      printf("10 second timeout. exiting...\n");
      return DONE_STATE;
   }
   
   recv_len = recv_buf(data_buf, MAX_BUF_LEN + sizeof(Header), 
    server->socket_fd, server, &flag, &recv_seq);

   if (recv_len == CRC_ERROR) {
      /* do nothing. we just wait until we get an out of order packet
       * and then SREJ the missing packet */          
      return RECV_DATA_STATE;
   }

   if (flag == END_OF_FILE) {
      /* send eof ack */
      send_buf(sen_data_buf, 0, server, EOF_ACK, *seq, packet); 
      printf("Transfer complete\n");
      return DONE_STATE;
   }
   else if (flag != DATA) {
      printf("in RECV_DATA, got a flag other than EOF or DATA. terminating\n");
      exit(-1);
   }
   else {
      if (recv_seq < *expected_seq) {
         /* do nothing */
      }
      else if(recv_seq == *expected_seq) {
         /* go into buffer and see how many writes/acks we can do */
         store_packet(win_buf, recv_len, data_buf, recv_seq, win_size);
         check_buf_for_expected_packet(win_buf, 
          expected_seq, win_size, fd, seq, recv_seq, server);
      }
      else {
         /* send SREJ for expected_seq packet */
         send_srej(server, expected_seq, seq);
         /* store packet we just received in buffer */
         store_packet(win_buf, recv_len, data_buf, recv_seq, win_size);
      }
   }
   return RECV_DATA_STATE;
}

int open_localfile(char *localfile) {
   int fd;
   fd = open(localfile, O_WRONLY | O_CREAT);
   if (fd == -1) {
      perror("local file open");
      exit(-1);
   }
   return fd;
}
 
int main (int argc, char **argv) {
   Connection server;
   STATE state = START_STATE;  
   int fd;
   uint32_t *seq = malloc(sizeof(uint32_t));
   uint32_t *expected_seq = malloc(sizeof(uint32_t));
   uint8_t *first_pkt_buf = NULL;
   uint32_t *expected_srej_seq = calloc(sizeof(uint32_t), 1);
   WindowBuffer *win_buf = NULL;
   *seq = 0;
   *expected_seq = 0;

   checkArgs(argc, argv);

   sendtoErr_init(atof(argv[5]), DROP_OFF, FLIP_ON, DEBUG_ON, RSEED_ON);

   fd = open_localfile(argv[1]);

   while (state != DONE_STATE) { 
      switch (state) {
         case START_STATE:
            state = start(argv, &server);
            break;
      
         case HANDSHAKE_STATE:
            state = handshake(&server);
            break;
   
         case FILENAME_EXCHANGE_STATE:
            state = send_filename(&server, argv[2], strlen(argv[2]),
             (uint32_t)atoi(argv[3]), (uint16_t)atoi(argv[4]), first_pkt_buf);
            break; 
    
         case RECV_DATA_STATE:
            state = recv_data(&server, seq, expected_seq, fd, first_pkt_buf,
             &win_buf, (uint32_t)atoi(argv[3]), expected_srej_seq);
            break;
     
         case DONE_STATE:
            printf("In done state\n");
            exit(0);
            break;

         default:
            printf("ERROR - in default state!\n");
            break;
      }
   }

   return 0;
}
