/* 
 * File:   prac2a.c
 * Author: Algunenano
 *
 * Created on April 25, 2011, 4:30 AM
 */

#include "uah_set_up.h"
#include "uah_sys_calls.h"
#include <stdio.h>

_UAH_API_sys_call2(int,UAH_create_process, const char*, name, 
                        unsigned int, basePriority)
_UAH_API_sys_call1(int,UAH_exit,int,exitcode)
        
int main (void){
    uah_set_up();
    
    UAH_create_process("P0",3);
    UAH_create_process("P1",1);
    UAH_create_process("P2",3);
    UAH_create_process("P3",1);
    
    UAH_exit(0);
    UAH_exit(0);
    UAH_exit(0);
    UAH_exit(0);

    printf("END SESSION\n");
    return 1;    
        
}