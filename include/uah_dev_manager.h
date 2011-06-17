/* 
 * File:   uah_dev_manager.h
 * Author: Algunenano
 *
 * Created on June 4, 2011, 5:07 AM
 */

#ifndef UAH_DEV_MANAGER_H
#define	UAH_DEV_MANAGER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "uah_pcb.h"
    
    /* Lista de dispositivos disponibles */
    extern struct UAH_DEVICE_Queue deviceQueue;
    
    struct UAH_DEVICE {
        char *name;
        int openCounter;
        int (*deviceOpen) (char *name);
        int (*deviceRead) (int devDesc, char *readBuffer, unsigned int maxSize);
        int (*deviceWrite)(int devDesc, char *writeBuffer, unsigned int maxSize);
        int (*deviceClose)(int devDesc);
        struct UAH_DEVICE *next;
        
        struct UAH_PCB_Queue PCB_Queue; /* Cola de procesos bloqueados */
                /* Manejador de interrupción asociado al dispositivo */
        int irqVector;
        void (*deviceIrqHandler) (void);
    };
    
    struct UAH_DEVICE_Queue {
        struct UAH_DEVICE *head;
        struct UAH_DEVICE *tail;
    };
    
    void uah_dev_install (struct UAH_DEVICE *pDevice);
    
    void uah_init_dev_manager (void);
    
    int uah_dev_open (char *name);
    int uah_dev_read (int devDesc, char *readBuffer, unsigned int maxSize);
    int uah_dev_write (int devDesc, char *writeBuffer, unsigned int size);
    int uah_dev_close (int devDesc);



#ifdef	__cplusplus
}
#endif

#endif	/* UAH_DEV_MANAGER_H */

