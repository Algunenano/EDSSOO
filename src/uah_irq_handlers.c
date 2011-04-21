/*
 * File:   uah_irq_handlers.h
 * Author: Algunenano
 *
 * Created on April 22, 2011, 12:47 AM
 */

#include "uah_irq_handlers.h"
#include "uah_arch_ps.h"
#include <stdio.h>

void _clock_irq_handler (void){

    printf("clock irq\n");
}

void uah_init_irqs (void){
    /* Configuramos _EMU_IRQ_VECTOR_TABLE para instalar
        _clock_irq_handler como el manejador de interrupción 0
     */
    _EMU_IRQ_VECTOR_TABLE.table[_EMU_IRQ_VECTOR_INT0] = _clock_irq_handler;
}