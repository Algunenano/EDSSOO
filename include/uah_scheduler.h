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

    /* Scheduler */
    void uah_sch_init (void);
    int uah_sch_create_process (const char *name, unsigned int basePriority);
    int uah_sch_exit (int exitcode);
    int uah_sch_schedule (void);
    
    /* Dispatcher */
    void uah_dispatcher (void);



#ifdef	__cplusplus
}
#endif

#endif	/* UAH_SCHEDULER_H */
