/*
 * File:   uah_exc_handlers.c
 * Author: Algunenano
 *
 * Created on April 22, 2011, 1:36 AM
 */

#include "uah_exc_handlers.h"
#include "uah_arch_ps.h"
#include <stdio.h>

void _InvalidIns_exc_handler (void){

    printf ("Invalid Instruction\n");
}

void _BusError_exc_handler (void){

    printf ("Bus Error\n");
}

void uah_init_excep (void){
/* Configuramos _EMU_IRQ_VECTOR_TABLE para instalar
 las funciones previas como manejadores de excepciones en 16 y 17
 */
    _EMU_IRQ_VECTOR_TABLE.table[16] = _InvalidIns_exc_handler;
    _EMU_IRQ_VECTOR_TABLE.table[17] = _BusError_exc_handler;
    
}