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
        _EMU_IRQ_VECTOR_TABLE[_EMU_IRQ_VECTOR_INVALID_INSTRUCTION]();
    }

    _EMU_IRQ_VECTOR_TABLE[_EMU_IRQ_VECTOR_TRAP0+trapNum]();
    
}

void _EMU_HW_IRQ (int vectorNum){
    if (! (((vectorNum>=0) && (vectorNum<16)) || 
           ((vectorNum>=32) && (vectorNum<64))) ) {
        /* Disparar la excepción de error de bus */
        _EMU_IRQ_VECTOR_TABLE[_EMU_IRQ_VECTOR_BUS_ERROR]();
    } else {
        _EMU_IRQ_VECTOR_TABLE[_EMU_IRQ_VECTOR_INT0+vectorNum]();
    }
    
}


/* Variables that will be used as registers*/
long UAH_REG_D0;
long UAH_REG_D1;
long UAH_REG_D2;
long UAH_REG_D3;
long UAH_REG_D4;
long UAH_REG_D5;
long UAH_REG_D6;
long UAH_REG_D7;

long UAH_REG_A0;
long UAH_REG_A1;
long UAH_REG_A2;
long UAH_REG_A3;
long UAH_REG_A4;
long UAH_REG_A5;
long UAH_REG_A6;
long UAH_REG_A7;

long UAH_REG_SR;
