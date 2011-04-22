/*
 * File:   uah_sys_calls.c
 * Author: Algunenano
 *
 * Created on April 21, 2011, 10:35 PM
 */
#include "uah_sys_calls.h"
#include "uah_arch_ps.h"
#include <stdio.h>

void do_sys_call_manager (void){

    printf("sys_call_manager\n");
}

void uah_init_traps (void){
    /* Configuramos _EMU_IRQ_VECTOR_TABLE para instalar
        do_sys_call_manager como el manejador del trap 0
     */
    _EMU_IRQ_VECTOR_TABLE.table[_EMU_IRQ_VECTOR_TRAP0] = do_sys_call_manager;
}


#define __NR_num_sys_calls 2
_EMU_IRQ_VECTOR _UAH_SYS_CALLS_TABLE[__NR_num_sys_calls];