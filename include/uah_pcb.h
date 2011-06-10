/* 
 * File:   uah_pcb.h
 * Author: Algunenano
 *
 * Created on April 25, 2011, 5:02 AM
 */

#ifndef UAH_PCB_H
#define	UAH_PCB_H

#ifdef	__cplusplus
extern "C" {
#endif
    

#define UAH_MAX_NUM_OPEN_DEVICES 32
    
    struct UAH_DEVICE; /* Problemas de doble referencia! */
    
    struct UAH_PCB{
        int pid;
        const char *name;
        unsigned int basePriority;
        struct UAH_PCB *next;
        
        struct UAH_DEVICE *openDeviceList[UAH_MAX_NUM_OPEN_DEVICES];
        unsigned int openDeviceListBitMap;
        int openDeviceCounter;
        
    };
    
    struct UAH_PCB_Queue{
        struct UAH_PCB *head;
        struct UAH_PCB *tail;
    };
    
    #include "uah_dev_manager.h"

    void uah_pcb_insert_queue_tail (struct UAH_PCB *pPCB, struct UAH_PCB_Queue *pQueue);
    void uah_pcb_insert_queue_head (struct UAH_PCB *pPCB, struct UAH_PCB_Queue *pQueue);
    void uah_pcb_extract_queue_head (struct UAH_PCB **pPCB, struct UAH_PCB_Queue *pQueue);

    
    int uah_pcb_add_new_device (struct UAH_PCB *pPCB, struct UAH_DEVICE *pDevice);
    void uah_pcb_release_device (struct UAH_PCB *pPCB, int numDevice);


#ifdef	__cplusplus
}
#endif

#endif	/* UAH_PCB_H */

