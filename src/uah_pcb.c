/* 
 * File:   uah_pcb.c
 * Author: Algunenano
 *
 * Created on April 25, 2011, 5:02 AM
 * Lacks of NULL checks...
 */

#include "uah_pcb.h"
#include <stdio.h>

/* Función que inserta el PCB al final de la cola apuntada por pQueue*/
void uah_pcb_insert_queue_tail (struct UAH_PCB *pPCB, 
        struct UAH_PCB_Queue *pQueue){
    if (pQueue->tail)
        pQueue->tail->next = pPCB;
    pQueue->tail = pPCB;
    pPCB->next = NULL;
    
    if (!pQueue->head)
        pQueue->head = pPCB;
    
}

/* Función que inserta el PCB en la cabeza de la cola apuntada por pQueue */
void uah_pcb_insert_queue_head (struct UAH_PCB *pPCB, 
        struct UAH_PCB_Queue *pQueue){
    pPCB->next = pQueue->head;
    pQueue->head = pPCB;
    
    if (!pQueue->tail){
        pQueue->tail = pPCB;
        pPCB->next = NULL;
    }
}

/* Extrae el PCB situado a la cabeza de la cola apuntada por pQueue.
   Si la cola no tiene ningún elemento tomará el valor NULL */
void uah_pcb_extract_queue_head (struct UAH_PCB **pPCB, 
struct UAH_PCB_Queue *pQueue){
    if (!pQueue->head)
        *pPCB = NULL;
    else {
        *pPCB = pQueue->head;
        pQueue->head = pQueue->head->next;
        if (!pQueue->head) pQueue->tail = NULL;
    }   
    
}

int uah_pcb_add_new_device (struct UAH_PCB *pPCB, struct UAH_DEVICE *pDevice){
    int i = 0;
    
    while ((pPCB->openDeviceListBitMap >> i) &0x1){
        i++;
        
        if (i == UAH_MAX_NUM_OPEN_DEVICES)
            return -1;
    }
    
    pPCB->openDeviceListBitMap |= (0x1 << i);
    pPCB->openDeviceList[i] = pDevice;
    pPCB->openDeviceCounter++;
    
    return i;
}

void uah_pcb_release_device (struct UAH_PCB *pPCB, int numDevice){
    pPCB->openDeviceListBitMap &= ~(0x1 << numDevice);
    pPCB->openDeviceList[numDevice] = NULL;
    pPCB->openDeviceCounter--;
}
