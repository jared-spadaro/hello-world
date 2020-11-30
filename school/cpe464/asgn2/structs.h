#ifndef STRUCTS_H
#define STRUCTS_H

#define INIT 1
#define CONFIRM 2
#define ALREADY_EXISTS 3
#define BROADCAST 4
#define MSG 5
#define DOES_NOT_EXIST 7
#define EXIT_REQUEST 8
#define ACK_EXIT 9
#define LIST_REQUEST 10
#define NUM_HANDLES 11
#define LIST_HANDLES 12
#define MAX_HANDLE_LEN 250

/* general chat header, includes in all packets sent */
typedef struct header_t {
   uint16_t packet_len;   /* entire length of the packet */
   uint8_t flag;          /* flag indicating what kind of packet */
} __attribute__ ((packed)) header_t;

/* %M header */
typedef struct msg_t {
   struct header_t header;
   uint8_t num_handles;   /* number of dest handles, range 1-9, defaults to 1 */
   //char *dest_handles;    /* 1 or more dest handles */
   //char *msg;             /* message to send */
} msg_t;
   
/* connection request header (FLAG = 1) */
typedef struct init_t {
   struct header_t header;
   uint8_t handle_len;
   //char *handle;
} init_t;

/* entry for client */
typedef struct client_t {
   uint8_t handle_len;
   char *handle;
   int socket;
   int status;
} __attribute ((packed)) client_t;
   

#endif
