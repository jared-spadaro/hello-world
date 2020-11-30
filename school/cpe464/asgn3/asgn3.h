#ifndef ASGN3_H
#define ASGN3_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdint.h>

#include "cpe464.h"

#define MAX_BUF_LEN 1400
#define SHORT_TIME 1
#define LONG_TIME 10
#define MAX_TRIES 10
#define SET_NULL 0
#define NOT_NULL 1
#define MAX_FILENAME_LEN 100

typedef struct connection Connection;
typedef struct header Header;
typedef struct window_buf WindowBuffer;

#pragma pack(1)

struct connection {
   int32_t socket_fd;
   struct sockaddr_in remote;
   uint32_t len;
};

struct header {
   uint32_t seq;
   uint16_t cksum;
   uint8_t flag;
}; 

struct window_buf {
   uint8_t data_buf[MAX_BUF_LEN];
   uint32_t seq;
   uint32_t len;
   uint8_t written;
};

enum FLAG {
   NOT_USED, HANDSHAKE_REQUEST, HANDSHAKE_RESPONSE, DATA, UNUSED, RR, SREJ, FILENAME, FNAME_OK, 
   FNAME_ACK, FNAME_ERR, END_OF_FILE, EOF_ACK, CRC_ERROR = -1
};

uint32_t udp_server(int);
uint32_t udp_client_setup(char *, uint16_t, Connection *);
int32_t select_call(int32_t, int32_t, int32_t, int32_t);
int32_t send_buf(uint8_t *, uint32_t, Connection *, uint8_t, uint32_t, uint8_t *);
int createHeader(uint32_t, uint8_t, uint32_t, uint8_t *);
int32_t recv_buf(uint8_t *, int32_t, int32_t, Connection *, uint8_t *, uint32_t *);
int retrieveHeader(char *, int, uint8_t *, uint32_t *);
int32_t safeSend(uint8_t *, uint32_t, Connection *);
int32_t safeRecv(int, char *, int, Connection *);
int processSelect(Connection *, int *, int, int, int);

#endif
