/* 
 * File:   uah_dev_manager.c
 * Author: Algunenano
 *
 * Created on June 4, 2011, 5:07 AM
 */

#include <stdlib.h>
#include <string.h>

#include "uah_dev_manager.h"
#include "uah_device0.h"
#include "uah_device1.h"

#include "uah_pcb.h"
#include "uah_scheduler.h"
#include "uah_irq_handlers.h"


struct UAH_DEVICE_Queue deviceQueue;

/* Insertar un dispositivo nuevo */
void uah_dev_insert_queue (struct UAH_DEVICE *pDevice){
    pDevice->next = NULL;
    if (deviceQueue.head == NULL){
        deviceQueue.head = deviceQueue.tail = pDevice; 
    } else {
        deviceQueue.tail->next = pDevice;
        deviceQueue.tail = pDevice;
    }
}

/* Buscar dispositivo */
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
    uah_install_dev_irq_handler(pDevice->deviceIrqHandler, pDevice->irqVector);
}

void uah_init_dev_manager (void){
    deviceQueue.head = deviceQueue.tail = NULL;
    register_dev0();
    register_dev1();
}

int uah_dev_open (char *name){
    int dd;
    struct UAH_DEVICE *pdev;
    
    if ((pdev = uah_get_device_by_name (name)) == NULL)
        return -1;
    
    pdev->deviceOpen(name);

    if ((dd = uah_pcb_add_new_device(UAH_PCB_CURRENT, pdev)) == -1)
        return -1;
    
    return dd;    
}

int uah_dev_read (int devDesc, char *readBuffer, unsigned int maxSize){
    if (UAH_PCB_CURRENT->openDeviceListBitMap & (0x1 << devDesc)){
        return (UAH_PCB_CURRENT->openDeviceList[devDesc]->deviceRead
                        (devDesc,readBuffer,maxSize)
                );
    }
    return -1;
}

int uah_dev_write (int devDesc, char *writeBuffer, unsigned int size){
    if (UAH_PCB_CURRENT->openDeviceListBitMap & (0x1 << devDesc)){
        return (UAH_PCB_CURRENT->openDeviceList[devDesc]->deviceWrite
                        (devDesc,writeBuffer,size)
                );
    }
    return -1;
}

int uah_dev_close (int devDesc){
   if (UAH_PCB_CURRENT->openDeviceListBitMap & (0x1 << devDesc)){
       if (UAH_PCB_CURRENT->openDeviceList[devDesc]->deviceClose
               (devDesc) == -1) return -1;
       uah_pcb_release_device(UAH_PCB_CURRENT,devDesc);
       return 0;
    }
    return -1;
}
