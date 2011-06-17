/* 
 * File:   uah_scheduler.h
 * Author: Algunenano
 *
 * Created on April 25, 2011, 5:08 AM
 */

#ifndef UAH_SCHEDULER_H
#define	UAH_SCHEDULER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "uah_pcb.h"

    extern struct UAH_PCB *UAH_PCB_CURRENT;
    
    #define UAH_PCB_Queues_Number 8
    
    /* Scheduler */
    void uah_sch_init (void);
    int uah_sch_create_process (const char *name, unsigned int basePriority);
    int uah_sch_exit (int exitcode);
    int uah_sch_schedule (void);
    int uah_sch_proc_ready (struct UAH_PCB *pPCB, unsigned int priority);
    
    /* Dispatcher */
    void uah_dispatcher (void);
    
    /* Scheduling */
    void uah_sch_round_robin (void);
    
    int uah_sch_proc_sort_list_ready (struct UAH_PCB *pPCBList);



#ifdef	__cplusplus
}
#endif

#endif	/* UAH_SCHEDULER_H */

