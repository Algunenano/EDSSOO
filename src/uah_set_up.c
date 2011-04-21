/*
 * File:   uah_set_up.c
 * Author: Algunenano
 *
 * Created on April 22, 2011, 1:44 AM
 */

#include "uah_set_up.h"
#include "uah_arch_ps.h"
#include "uah_irq_handlers.h"
#include "uah_sys_calls.h"
#include "uah_exc_handlers.h"
#include <stdio.h>

void _dummy_handler (void){

    printf("dummy handler\n");
}

void uah_set_up (void){
    int i;
    /* Inicialización por defecto de la tabla de vectores */
    for (i=0; i<_EMU_IRQ_VECTOR_LENGHT; i++)
        _EMU_IRQ_VECTOR_TABLE.table[i]= _dummy_handler;

    uah_init_traps();
    uah_init_irqs();
    uah_init_excep();
}