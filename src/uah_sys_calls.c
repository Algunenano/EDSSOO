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
    _EMU_IRQ_VECTOR_TABLE[_EMU_IRQ_VECTOR_TRAP0] = do_sys_call_manager;
}


/* LLAMADAS AL SISTEMA */
#define __NR_num_sys_calls 2

typedef void (*_EMU_SYS_CALLS_VECTOR[_EMU_IRQ_VECTOR_LENGHT]) (void);


#define _NR_UAH_pause 0
#define _NR_UAH_exit 1

/* Macro para el tipo que retorna una función */
#define _ASMLink_T(type)\
    void\

/* Macro previa al uso de cada parámetros en el cuerpo de la función*/
#define _ASM_P *

/* Macro para la instrucción de retorno de la función */
#define _ASMLink_Return(var)\
    UAH_REG_D0=(long)var

/* Macro que se emplea en la declaración de 0 parámetros */
#define _ASMLink_P0(Param0)\
    (void){

/* Macro que se emplea en la declaración de un parámetro */
#define _ASMLink_P1(Ptype1, Param1)\
    (void){\
    Ptype1 *Param1=(Ptype1 *)(& UAH_REG_D1);

/* Definición de las rutinas de servicio */
_ASMLink_T(int) DO_UAH_pause _ASMLink_P0(void)

        printf("UAH_pause\n");
        _ASMLink_Return(0);
}

_ASMLink_T(int) DO_UAH_exit _ASMLink_P1(int, exitcode)

        printf("UAH_exit\t exitcode = %i\n", _ASM_P exitcode);
        _ASMLink_Return(0);
}

/* CREACIÓN E INICIALIZACIÓN DE LA ESTRUCTURA */
_EMU_SYS_CALLS_VECTOR (_UAH_SYS_CALLS_TABLE[__NR_num_sys_calls]) = {DO_UAH_pause, DO_UAH_exit};
