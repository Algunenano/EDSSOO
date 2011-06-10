/* 
 * File:   uah_irq_handlers.h
 * Author: Algunenano
 *
 * Created on April 22, 2011, 12:47 AM
 */

#ifndef UAH_IRQ_HANDLERS_H
#define	UAH_IRQ_HANDLERS_H

#ifdef	__cplusplus
extern "C" {
#endif

    void uah_init_irqs (void);
    void uah_install_dev_irq_handler(void (*irqHandler)(void), int irqNumber);



#ifdef	__cplusplus
}
#endif

#endif	/* UAH_IRQ_HANDLERS_H */

