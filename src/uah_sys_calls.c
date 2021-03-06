/*
 * File:   uah_sys_calls.c
 * Author: Algunenano
 *
 * Created on April 21, 2011, 10:35 PM
 */
#include "uah_sys_calls.h"
#include "uah_scheduler.h"
#include "uah_dev_manager.h"
#include "uah_timing.h"
#include <stdio.h>

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
    Ptype1 *Param1 = (Ptype1 *) (&UAH_REG_D1);

/* Dos y tres parámetros */
#define _ASMLink_P2(Ptype1, Param1, Ptype2, Param2)\
    (void){\
    Ptype1 *Param1 = (Ptype1 *) (&UAH_REG_D1);\
    Ptype2 *Param2 = (Ptype2 *) (&UAH_REG_D2);

#define _ASMLink_P3(Ptype1, Param1, Ptype2, Param2, Ptype3, Param3)\
    (void){\
    Ptype1 *Param1 = (Ptype1 *) (&UAH_REG_D1);\
    Ptype2 *Param2 = (Ptype2 *) (&UAH_REG_D2);\
    Ptype3 *Param3 = (Ptype3 *) (&UAH_REG_D3);

/* Definición de las rutinas de servicio */
_ASMLink_T(int) DO_UAH_pause _ASMLink_P0(void)

        printf("UAH_pause\n");
        _ASMLink_Return(0);
}

_ASMLink_T(int) DO_UAH_exit _ASMLink_P1(int, exitcode)

        printf("UAH_exit\t exitcode = %i\n", _ASM_P exitcode);
        uah_sch_exit(_ASM_P exitcode);
        uah_sch_schedule();
        uah_dispatcher();

        _ASMLink_Return(0);
}

_ASMLink_T(int) DO_UAH_open _ASMLink_P3(const char *,name,int,flag,int,mode)

        printf("UAH_open %s, flag %i, mode %i \n", _ASM_P name, _ASM_P flag, _ASM_P mode);

        _ASMLink_Return(3);

}

_ASMLink_T(int) DO_UAH_close _ASMLink_P1(int,fd)

        printf("UAH_close %i\n", _ASM_P fd);
        _ASMLink_Return(0);

}

_ASMLink_T(int) DO_UAH_create_process _ASMLink_P2(const char*, name, unsigned int, basePriority)
        
        printf("UAH_create_process      %s      BasePriority %d\n",_ASM_P name,_ASM_P basePriority);
        if (uah_sch_create_process(_ASM_P name, _ASM_P basePriority) != 0) {
            uah_dispatcher();
        }
        _ASMLink_Return(0);
}

_ASMLink_T(int) DO_UAH_dev_open _ASMLink_P1(char*,name)
        printf("UAH_dev_open      %s\n",_ASM_P name);
        _ASMLink_Return(uah_dev_open(_ASM_P name));
}

_ASMLink_T(int) DO_UAH_dev_read _ASMLink_P3(int,devDesc,char *,readBuffer,
    unsigned int, maxSize)
        printf("UAH_dev_read     %d\n",_ASM_P devDesc);
        _ASMLink_Return (uah_dev_read(_ASM_P devDesc, _ASM_P readBuffer, _ASM_P maxSize));
}

_ASMLink_T(int) DO_UAH_dev_write _ASMLink_P3(int,devDesc,char *,writeBuffer,
    unsigned int, size)
        printf("UAH_dev_write     %d\n",_ASM_P devDesc);
        _ASMLink_Return (uah_dev_write(_ASM_P devDesc, _ASM_P writeBuffer, _ASM_P size));
}

_ASMLink_T(int) DO_UAH_dev_close _ASMLink_P1(int,devDesc)
        printf("UAH_dev_close     %d\n",_ASM_P devDesc);
        _ASMLink_Return (uah_dev_close(_ASM_P devDesc));
}

_ASMLink_T(int) DO_UAH_sleep _ASMLink_P1(int,ms)
        printf("UAH_dev_sleep     %d\n",_ASM_P ms);
        _ASMLink_Return (uah_timing_sleep(_ASM_P ms));
}

/* LLAMADAS AL SISTEMA */

#define __NR_num_sys_calls 2
    typedef void (*_EMU_SYS_CALLS_VECTOR[_EMU_IRQ_VECTOR_LENGHT]) (void);

/* CREACIÓN E INICIALIZACIÓN DE LA ESTRUCTURA */
_EMU_SYS_CALLS_VECTOR _UAH_SYS_CALLS_TABLE = {
    DO_UAH_pause,
    DO_UAH_exit,
    DO_UAH_open,
    DO_UAH_close,
    DO_UAH_create_process,
    DO_UAH_dev_open,
    DO_UAH_dev_read,
    DO_UAH_dev_write,
    DO_UAH_dev_close,
    DO_UAH_sleep
};

void do_sys_call_manager (void){
    printf("SYS_CALL  %ld: ",UAH_REG_D0);
    _UAH_SYS_CALLS_TABLE[UAH_REG_D0]();
}

void uah_init_traps (void){
    /* Configuramos _EMU_IRQ_VECTOR_TABLE para instalar
        do_sys_call_manager como el manejador del trap 0
     */
    _EMU_IRQ_VECTOR_TABLE[_EMU_IRQ_VECTOR_TRAP0] = do_sys_call_manager;
}