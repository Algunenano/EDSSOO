/* 
 * File:   uah_device1.c
 * Author: Algunenano
 *
 * Created on June 4, 2011, 5:44 PM
 */

#include "uah_device1.h"
#include "uah_dev_manager.h"
#include <stdlib.h>
#include <stdio.h>

struct UAH_DEVICE DEV1info;


int DEV1_open (char *deviceName){
    printf ("DEV1_open\n");
    return 0;
}

int DEV1_read (int devDesc, char *readBuffer, unsigned int maxSize){
    printf ("DEV1_read\n");
    return 0;
}

int DEV1_write (int devDesc, char* readBuffer, unsigned int size){
    printf ("DEV1_write\n");
    return 0;
}

int DEV1_close (int devDesc){
    printf ("DEV1_close\n");
    return 0;
}

int register_dev1 (void){
    DEV1info.name = "DEV1";
    DEV1info.deviceOpen = DEV1_open;
    DEV1info.deviceRead = DEV1_read;
    DEV1info.deviceWrite = DEV1_write;
    DEV1info.deviceClose = DEV1_close;
    
    DEV1info.next = NULL;
    
    uah_dev_install (&DEV1info);
    return 0;
}
