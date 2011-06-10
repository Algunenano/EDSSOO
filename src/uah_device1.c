/* 
 * File:   uah_device1.c
 * Author: Algunenano
 *
 * Created on June 4, 2011, 5:44 PM
 */

#include "uah_device1.h"
#include "uah_dev_manager.h"
#include "uah_pcb.h"
#include "uah_scheduler.h"

#include <stdlib.h>
#include <stdio.h>

struct UAH_DEVICE DEV1info;


int DEV1_open (char *deviceName){
    printf ("DEV1_open\n");
    return 0;
}

int DEV1_read (int devDesc, char *readBuffer, unsigned int maxSize){

    uah_pcb_insert_queue_tail(UAH_PCB_CURRENT, &DEV1info.PCB_Queue);
    uah_sch_schedule();
    uah_dispatcher();
    
    return 0;
}

int DEV1_write (int devDesc, char* readBuffer, unsigned int size){

    uah_pcb_insert_queue_tail(UAH_PCB_CURRENT, &DEV1info.PCB_Queue);
    uah_sch_schedule();
    uah_dispatcher();
    
    return 0;
}

int DEV1_close (int devDesc){
    printf ("DEV1_close\n");
    return 0;
}


void DEV1_irq_handler (void){
    struct UAH_PCB* pPCB;
    uah_pcb_extract_queue_head(&pPCB, &DEV1info.PCB_Queue);
    if (pPCB == NULL){
        fprintf(stderr,"DEV1_irq_handler: NO PROCESS FOUND\n");
    } else {
        printf("DEV1_irq_handler\n");
        if (uah_sch_proc_ready(pPCB,pPCB->basePriority) == 1)
            uah_dispatcher();       
    }
}

int register_dev1 (void){
    DEV1info.name = "DEV1";
    DEV1info.deviceOpen = DEV1_open;
    DEV1info.deviceRead = DEV1_read;
    DEV1info.deviceWrite = DEV1_write;
    DEV1info.deviceClose = DEV1_close;
    
    DEV1info.deviceIrqHandler = DEV1_irq_handler;
    DEV1info.irqVector = 40;
    DEV1info.PCB_Queue.head = DEV1info.PCB_Queue.tail = NULL;
    
    DEV1info.next = NULL;
    
    uah_dev_install (&DEV1info);
    return 0;
}