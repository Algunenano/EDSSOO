/* 
 * File:   prac2b.c
 * Author: Algunenano
 *
 * Created on April 25, 2011, 6:47 PM
 */

#include "prac2b.h"
#include "uah_emu_session.h"
#include "uah_arch_ps.h"
#include "uah_sys_calls.h"
#include "uah_set_up.h"
#include <stdio.h>

_UAH_API_sys_call2(int, UAH_create_process, const char*, name,
                        unsigned int, basePriority)
_UAH_API_sys_call1(int, UAH_exit, int, exitcode)        

int main (void){
    uah_set_up();
    EMU_Session_Show_State();
    
    UAH_create_process("P0",3);
    EMU_Session_Show_State();
    
    UAH_create_process("P1",1);
    EMU_Session_Show_State();
    
    UAH_create_process("P2",3);
    EMU_Session_Show_State();
    
    UAH_create_process("P3",1);
    EMU_Session_Show_State();
    
    UAH_exit(0);
    EMU_Session_Show_State();
    
    UAH_exit(0);
    EMU_Session_Show_State();
    
    UAH_exit(0);
    EMU_Session_Show_State();
    
    UAH_exit(0);
    EMU_Session_Show_State();
    
    printf("END SESSION\n");
    return 1;    
}
