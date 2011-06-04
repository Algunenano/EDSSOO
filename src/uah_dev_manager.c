/* 
 * File:   uah_dev_manager.c
 * Author: Algunenano
 *
 * Created on June 4, 2011, 5:07 AM
 */

#include <uah_dev_manager.h>
#include <stdlib.h>
#include <string.h>


struct UAH_DEVICE_Queue deviceQueue;


void uah_dev_insert_queue (struct UAH_DEVICE *pDevice){
    pDevice->next = NULL;
    if (deviceQueue.head == NULL){
        deviceQueue.head = deviceQueue.tail = pDevice; 
    } else {
        deviceQueue.tail->next = pDevice;
        deviceQueue.tail = pDevice;
    }
}

struct UAH_DEVICE *uah_get_device_by_name (char *name){
    struct UAH_DEVICE *pdev = deviceQueue.head;
    
    while (pdev != NULL){
        if (strcmp (name, pdev->name) == 0)
            return pdev;
        else pdev = pdev->next;
    }
    
    return NULL;
    
}

/* Instala un dispositivo concreto en el sistema */
void uah_dev_install (struct UAH_DEVICE *pDevice){
    uah_dev_insert_queue(pDevice);
}
