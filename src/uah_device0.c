/* 
 * File:   uah_device0.c
 * Author: Algunenano
 *
 * Created on June 4, 2011, 5:44 PM
 */

#include "uah_device0.h"
#include "uah_dev_manager.h"
#include "uah_pcb.h"
#include "uah_scheduler.h"
#include <stdlib.h>
#include <stdio.h>

struct UAH_DEVICE DEV0info;


int DEV0_open (char *deviceName){
    printf ("DEV0_open\n");
    return 0;
}

int DEV0_read (int devDesc, char *readBuffer, unsigned int maxSize){
    
    uah_pcb_insert_queue_tail(UAH_PCB_CURRENT, &DEV0info.PCB_Queue);
    uah_sch_schedule();
    uah_dispatcher();
    
    return 0;
}

int DEV0_write (int devDesc, char* readBuffer, unsigned int size){

    uah_pcb_insert_queue_tail(UAH_PCB_CURRENT, &DEV0info.PCB_Queue);
    uah_sch_schedule();
    uah_dispatcher();
    
    return 0;
}

int DEV0_close (int devDesc){
    printf ("DEV0_close\n");
    return 0;
}

void DEV0_irq_handler (void){
    struct UAH_PCB* pPCB;
    uah_pcb_extract_queue_head(&pPCB, &DEV0info.PCB_Queue);
    if (pPCB == NULL){
        fprintf(stderr,"DEV0_irq_handler: NO PROCESS FOUND\n");
    } else {
        printf("DEV0_irq_handler\n");
        if (uah_sch_proc_ready(pPCB,pPCB->basePriority) == 1)
            uah_dispatcher();        
    }
}

int register_dev0 (void){
    DEV0info.name = "DEV0";
    DEV0info.deviceOpen = DEV0_open;
    DEV0info.deviceRead = DEV0_read;
    DEV0info.deviceWrite = DEV0_write;
    DEV0info.deviceClose = DEV0_close;
    
    DEV0info.deviceIrqHandler = DEV0_irq_handler;
    DEV0info.irqVector = 38;
    DEV0info.PCB_Queue.head = DEV0info.PCB_Queue.tail = NULL;
    
    DEV0info.next = NULL;
    
    uah_dev_install (&DEV0info);
    
    return 0;
}