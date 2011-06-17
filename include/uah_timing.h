/* 
 * File:   uah_timing.h
 * Author: Algunenano
 *
 * Created on June 11, 2011, 3:01 AM
 */

#ifndef UAH_TIMING_H
#define	UAH_TIMING_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    extern struct UAH_PCB *pTimingList;

    int uah_timing_sleep (unsigned long ms);
    int uah_timing_clk_tick();


#ifdef	__cplusplus
}
#endif

#endif	/* UAH_TIMING_H */

