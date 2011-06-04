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

    struct UAH_DEVICE {
        char *name;
        int openCounter;
        int (*deviceOpen) (char *name);
        int (*deviceRead) (int devDesc, char *readBuffer, unsigned int maxSize);
        int (*deviceWrite)(int devDesc, char *writeBuffer, unsigned int maxSize);
        int (*deviceClose)(int devDesc);
        struct UAH_DEVICE *next;
    };
    
    struct UAH_DEVICE_Queue {
        struct UAH_DEVICE *head;
        struct UAH_DEVICE *tail;
    };
    
    void uah_dev_install (struct UAH_DEVICE *pDevice);



#ifdef	__cplusplus
}
#endif

#endif	/* UAH_DEV_MANAGER_H */

