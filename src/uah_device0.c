/* 
 * File:   uah_device0.c
 * Author: Algunenano
 *
 * Created on June 4, 2011, 5:44 PM
 */

#include "uah_device0.h"
#include "uah_dev_manager.h"
#include <stdlib.h>
#include <stdio.h>

struct UAH_DEVICE DEV0info;


int DEV0_open (char *deviceName){
    printf ("DEV0_open\n");
    return 0;
}

int DEV0_read (int devDesc, char *readBuffer, unsigned int maxSize){
    printf ("DEV0_read\n");
    return 0;
}

int DEV0_write (int devDesc, char* readBuffer, unsigned int size){
    printf ("DEV0_write\n");
    return 0;
}

int DEV0_close (int devDesc){
    printf ("DEV0_close\n");
    return 0;
}

int register_dev0 (void){
    DEV0info.name = "DEV0";
    DEV0info.deviceOpen = DEV0_open;
    DEV0info.deviceRead = DEV0_read;
    DEV0info.deviceWrite = DEV0_write;
    DEV0info.deviceClose = DEV0_close;
    
    DEV0info.next = NULL;
    
    uah_dev_install (&DEV0info);
    
    return 0;
}