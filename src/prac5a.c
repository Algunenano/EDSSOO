/* 
 * File:   prac5a.c
 * Author: Algunenano
 *
 * Created on June 17, 2011, 3:00 AM
 */

#include "prac5a.h"
#include "uah_arch_ps.h"
#include "uah_set_up.h"
#include "uah_emu_session.h"
#include "uah_sys_calls.h"
#include "uah_dev_manager.h"
#include <stdio.h>
#include <string.h>


_UAH_API_sys_call0(int,UAH_pause);
_UAH_API_sys_call1(int,UAH_exit,int,exitcode);
_UAH_API_sys_call3(int,UAH_open,const char*,name,int,flag,int,mode);
_UAH_API_sys_call1(int,UAH_close,int,fd);
_UAH_API_sys_call2(int,UAH_create_process,const char*,name,int,basePriority);
_UAH_API_sys_call1(int,UAH_dev_open,char*,name);
_UAH_API_sys_call3(int,UAH_dev_read,int,devDesc,char*,readBuffer,unsigned int,maxSize);
_UAH_API_sys_call3(int,UAH_dev_write,int,devDesc,char*,writeBuffer,unsigned int,size);
_UAH_API_sys_call1(int,UAH_dev_close,int,devDesc);
_UAH_API_sys_call1(int,UAH_sleep,int,ms)

int main (void){
    uah_set_up();
    
    EMU_Session_Show_State();
    
    UAH_create_process("P0",3);
    EMU_Session_Show_State();
    
    UAH_create_process("P1",1);
    EMU_Session_Show_State();
    
    UAH_create_process("P2",2);
    EMU_Session_Show_State();
    
    UAH_create_process("P3",4);
    EMU_Session_Show_State();
    
    UAH_sleep(100);
    EMU_Session_Show_State();
    
    _EMU_HW_IRQ(0);
    EMU_Session_Show_State();
    
    UAH_sleep(200);
    EMU_Session_Show_State();
    
    _EMU_HW_IRQ(0);
    EMU_Session_Show_State();
    
    UAH_sleep(150);
    EMU_Session_Show_State();
    
    _EMU_HW_IRQ(0);
    EMU_Session_Show_State();
    
    UAH_sleep(100);
    EMU_Session_Show_State();
    
    _EMU_HW_IRQ(0);
    EMU_Session_Show_State();
    
    _EMU_HW_IRQ(0);
    EMU_Session_Show_State();

    UAH_exit(0);

    UAH_exit(0);

    UAH_exit(0);
   
    UAH_exit(0);

    EMU_Session_Show_State();
    
    printf("END SESSION\n");
    
    return 0;
}