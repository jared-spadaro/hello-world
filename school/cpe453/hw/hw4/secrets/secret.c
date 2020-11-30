/** CPE453 Assignment 4
 * Jared Spadaro
 * 11/28/16 Section 3
 * This is a driver for a secret keeper device.
 * It is unfinished and untested.
 */

#include <minix/drivers.h>
#include <minix/driver.h>
#include <stdio.h>
#include <stdlib.h>
#include <minix/ds.h>
#include <minix/const.h>
#include <sys/ucred.h>
#include "secret.h"

/*
 * Function prototypes for the hello driver.
 */
FORWARD _PROTOTYPE( char * secret_name,   (void) );
FORWARD _PROTOTYPE( int secret_open,      (struct driver *d, message *m) );
FORWARD _PROTOTYPE( int secret_close,     (struct driver *d, message *m) );
FORWARD _PROTOTYPE( int secret_ioctl,     (struct driver *d, message *m) );
FORWARD _PROTOTYPE( struct device * secret_prepare, (int device) );
FORWARD _PROTOTYPE( int secret_transfer,  (int procnr, int opcode,
                                          u64_t position, iovec_t *iov,
                                          unsigned nr_req) );
FORWARD _PROTOTYPE( void secret_geometry, (struct partition *entry) );

/* SEF functions and variables. */
FORWARD _PROTOTYPE( void sef_local_startup, (void) );
FORWARD _PROTOTYPE( int sef_cb_init, (int type, sef_init_info_t *info) );
FORWARD _PROTOTYPE( int sef_cb_lu_state_save, (int) );
FORWARD _PROTOTYPE( int lu_state_restore, (void) );

/* Entry points to the hello driver. */
PRIVATE struct driver secret_tab =
{
    nop_name,
    secret_open,
    secret_close,
    secret_prepare,
    secret_transfer,
    nop_cleanup,
    secret_geometry,
    nop_alarm,
    nop_cancel,
    nop_select,
    secret_ioctl,
    do_nop,
};

/** Represents the /dev/secret device. */
PRIVATE struct device secret_device;
/** Contains information about /dev/secret/ */ 
PRIVATE struct secret_dev secret_meta;

/* may not be opened for read/write access */
PRIVATE int secret_open(d, m)
    struct driver *d;
    message *m;
{
    struct ucred cred;
    getnucred(m->IO_ENDPT, &cred);
    if(cred.uid != secret_meta.owner && secret_meta.owner != -1) {  
       sys_safecopyto(m->IO_ENDPT, m->IO_GRANT, 0, 
        (vir_bytes)&perm, strlen(perm), D);
       return EACCES;
    }
    else { 
       /* check flags */ 
       /* if trying to open with r/w access, throw error */
       if((int)m->COUNT & (W_BIT | R_BIT) == (W_BIT | R_BIT)) {           
           sys_safecopyto(m->IO_ENDPT, m->IO_GRANT, 0, (vir_bytes)&no_rw, 
            strlen(no_rw), D);
           return EACCES;
       }
       /* if opening with write permission, and device is full, error */
       if(((int)m->COUNT & W_BIT) && full) {
           sys_safecopyto(m->IO_ENDPT, m->IO_GRANT, 0, (vir_bytes)&dev_full, 
            strlen(dev_full), D);
           return ENOSPC;
       }
       secret_meta.owner = (int)cred.uid;
       return secret_meta.fd++;
    }
    /* return OK; */
}

/* when the last file descriptor is closed after any read fd has been opened, 
 * secret reverts to being empty */
PRIVATE int secret_close(d, m)
    struct driver *d;
    message *m;
{
    secret_meta.secret = NULL;
    secret_meta.owner = -1;
    return OK;
}

PRIVATE struct device * secret_prepare(dev)
    int dev;
{
    secret_device.dv_base.lo = 0;
    secret_device.dv_base.hi = 0;
    secret_device.dv_size.lo = SECRET_SIZE;
    secret_device.dv_size.hi = 0;
    return &secret_device;
}

/* proc_nr = endpoint of calling process
 * opcode = what kind of transfer 
 * position = don't care
 * iov = buffer
 * nr_req = don't care
 */
PRIVATE int hello_transfer(proc_nr, opcode, position, iov, nr_req)
    int proc_nr;
    int opcode;
    u64_t position;
    iovec_t *iov;
    unsigned nr_req;
{
    int bytes, ret;

    if(iov->iov_size > strlen(secret)) {
       bytes = strlen(secret);
    }
    else {
       bytes = iov->iov_size;
    }

    /* for a read, copy secret into iov_addr. for write, copy iov_addr into secret */
    switch (opcode) {
        case DEV_GATHER_S:
            ret = sys_safecopyto(proc_nr, iov->iov_addr, 0, 
             (vir_bytes)secret, bytes, D);
            break;

        case DEV_SCATTER_S:
            ret = sys_safecopyfrom(proc_nr, iov->iov_addr, 0, 
             (vir_bytes)secret, bytes, D);
            secret_meta.full = 1;  
            break;

        default:
            return EINVAL;
    }
    /* return the number of bytes read/written */
    return ret;
}

PRIVATE void hello_geometry(entry)
    struct partition *entry;
{
    entry->cylinders = 0;
    entry->heads     = 0;
    entry->sectors   = 0;
}

PRIVATE void secret_ioctl(d, m)
    struct driver *d;
    message *m;
{
    /* transfer ownership of secret */
    uid_t grantee;
    int res;

    /* only accept one type of ioctl request */
    if(m->REQUEST != SSGRANT) {
        sys_safecopyto(m->IO_ENDPT, m->IO_GRANT, 0, (vir_bytes)&inv_req, 
         strlen(inv_req), D);
        return ENOTTY;
    } 

    res = sys_safecopyfrom(m->IO_ENDPT, m->IO_GRANT, 0, 
     (vir_bytes)&grantee, sizeof(grantee), D);
    
    if(res == -1) { 
        sys_safecopyto(m->IO_ENDPT, m->IO_GRANT, 0, (vir_bytes)&ioc_err, 
         strlen(ioc_err), D);
        return ENOTTY;
    }
    
    secret_meta.owner = grantee;
    return OK;
}

PRIVATE int sef_cb_lu_state_save(int state) {
/* Save the state. */
    ds_publish_mem("secret_store", secret_meta, sizeof(secret_dev), 0);
    return OK;
}

PRIVATE int lu_state_restore() {
/* Restore the state. */
   
    struct secret_dev temp;
    ds_retrieve_mem("secret_store", &temp, sizeof(secret_dev));
    ds_delete_mem("secret_store");
    secret_meta = temp;

    return OK;
}

PRIVATE void sef_local_startup()
{
    
    /*
     * Register init callbacks. Use the same function for all event types
     */
    sef_setcb_init_fresh(sef_cb_init);
    sef_setcb_init_lu(sef_cb_init);
    sef_setcb_init_restart(sef_cb_init);

    /*
     * Register live update callbacks.
     */
    /* - Agree to update immediately when LU is requested in a valid state. */
    sef_setcb_lu_prepare(sef_cb_lu_prepare_always_ready);
    /* - Support live update starting from any standard state. */
    sef_setcb_lu_state_isvalid(sef_cb_lu_state_isvalid_standard);
    /* - Register a custom routine to save the state. */
    sef_setcb_lu_state_save(sef_cb_lu_state_save);

    /* Let SEF perform startup. */
    sef_startup();
}

PRIVATE int sef_cb_init(int type, sef_init_info_t *info)
{
/* Initialize the secret driver. */

    switch(type) {
        case SEF_INIT_FRESH:
        break;

        case SEF_INIT_LU:
            /* Restore the state. */
            lu_state_restore();
        break;

        case SEF_INIT_RESTART:
        break;
    }

    /* Initialization completed successfully. */
    return OK;
}

PUBLIC int main(int argc, char **argv)
{
    /* initialize metadata struct */
    secret_meta.secret = NULL;
    secret_meta.owner = -1;
    secret_meta.full = 0;
    secret_meta.fd = 3;

    /*
     * Perform initialization.
     */
    sef_local_startup();

    /*
     * Run the main loop.
     */
    driver_task(&secret_tab, DRIVER_STD);
    return OK;
}

