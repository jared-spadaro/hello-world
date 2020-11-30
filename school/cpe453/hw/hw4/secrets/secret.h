#ifndef __SECRET_H
#define __SECRET_H

#define SECRET_SIZE 8192

const char *perm = "Permission denied\n";
const char *dev_full = "Device full\n";
const char *no_rw = "Read/write access not allowed\n";
const char *inv_req = "Invalid request\n";
const char *ioc_err = "Error in ioctl request\n";

typedef struct secret_dev {
   char secret[SECRET_SIZE];
   int owner; /* the uid owner of the secret */
   int full; /* flag for checking if device is full */
   int fd; /* start fds at 3 to avoid stdin, stdout, stderr */
} secret_dev;
   
#endif /* __SECRET_H */
