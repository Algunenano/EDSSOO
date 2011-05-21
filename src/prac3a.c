/* 
 * File:   prac3a.c
 * Author: Algunenano
 *
 * Created on May 21, 2011, 4:11 AM
 */

#include "prac3a.h"
#include "uah_emu_session.h"
#include "uah_arch_ps.h"
#include "uah_sys_calls.h"
#include "uah_set_up.h"
#include <stdio.h>

_UAH_API_sys_call2(int, UAH_create_process, const char*, name,
                        unsigned int, basePriority)
_UAH_API_sys_call1(int, UAH_exit, int, exitcode) 


int main (void){
    unsigned int cont;
    
    uah_set_up();
    
    UAH_create_process("P0",3);
    UAH_create_process("P1",1);
    UAH_create_process("P2",3);
    UAH_create_process("P3",1);
    
    EMU_Session_Show_State();
    
    for (cont=0; cont<4; cont++){
        _EMU_HW_IRQ(0);
        EMU_Session_Show_State();
    }
    
    UAH_exit(0);
    UAH_exit(0);
    UAH_exit(0);
    UAH_exit(0);
    
    EMU_Session_Show_State();
    
    printf("END SESSION\n");
    
    return 1;    
}
