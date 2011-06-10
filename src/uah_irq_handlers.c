/*
 * File:   uah_irq_handlers.c
 * Author: Algunenano
 *
 * Created on April 22, 2011, 12:47 AM
 */

#include "uah_scheduler.h"
#include "uah_irq_handlers.h"
#include "uah_arch_ps.h"
#include <stdio.h>

void _clock_irq_handler (void){
    uah_sch_round_robin();
    printf("clock irq\n");
}

void uah_init_irqs (void){
    /* Configuramos _EMU_IRQ_VECTOR_TABLE para instalar
        _clock_irq_handler como el manejador de interrupción 0
     */
    _EMU_IRQ_VECTOR_TABLE[_EMU_IRQ_VECTOR_INT0] = _clock_irq_handler;
}

void uah_install_dev_irq_handler(void (*irqHandler)(void), int irqNumber){
    if ((irqNumber<0) || (irqNumber>7 && irqNumber<32) || (irqNumber>63)){
        fprintf(stderr,"Error installing irq_handler (uah_install\
irq_hander): irqNumber %d\n",irqNumber);
    } else {
        _EMU_IRQ_VECTOR_TABLE[irqNumber] = irqHandler;
    }
    
}