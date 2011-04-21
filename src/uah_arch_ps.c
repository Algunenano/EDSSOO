/*
 * File:   uah_arch_ps.c
 * Author: Algunenano
 *
 * Created on April 4, 2011, 7:07 PM
 */
#include "uah_arch_ps.h"
    /* Declaración de la tabla */
_EMU_IRQ_VECTOR _EMU_IRQ_VECTOR_TABLE;


void _EMU_TRAP (int trapNum){
    if ((trapNum<0) || (trapNum>7)){
        /* Disparar la excepción de instrucción inválida */
        _EMU_IRQ_VECTOR_TABLE.table[_EMU_IRQ_VECTOR_INVALID_INSTRUCTION]();
    }
}

void _EMU_HW_IRQ (int vectorNum){
    if (! (((vectorNum>=0) && (vectorNum<16)) || 
           ((vectorNum>=32) && (vectorNum<64))) ) {
        /* Disparar la excepción de error de bus */
        _EMU_IRQ_VECTOR_TABLE.table[_EMU_IRQ_VECTOR_BUS_ERROR]();
    }
    
}
