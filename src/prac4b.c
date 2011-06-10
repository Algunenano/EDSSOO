/* 
 * File:   prac4b.c
 * Author: Algunenano
 *
 * Created on June 11, 2011, 12:52 AM
 */

#include "prac4b.h"
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

int main (void){
    unsigned int cont;
    unsigned int devDescP0_DEV0;
    unsigned int devDescP0_DEV1;
    unsigned int devDescP1_DEV1;
    char *bufferP0 = "Hello!";
    char bufferP1[4];
    
    uah_set_up();
    
    UAH_create_process("P0",3);
    devDescP0_DEV0 = UAH_dev_open("DEV0");
    devDescP0_DEV1 = UAH_dev_open("DEV1");
    EMU_Session_Show_State();
    
    UAH_create_process("P1",1);
    devDescP1_DEV1 = UAH_dev_open("DEV1");
    EMU_Session_Show_State();
    
    
    UAH_dev_read(devDescP1_DEV1,bufferP1,4);
    EMU_Session_Show_State();
    
    UAH_dev_write(devDescP0_DEV0,bufferP0,strlen(bufferP0));
    EMU_Session_Show_State();
    
    _EMU_HW_IRQ(38);
    EMU_Session_Show_State();
    
    _EMU_HW_IRQ(40);
    EMU_Session_Show_State();
    
    
    UAH_dev_close(devDescP1_DEV1);
    EMU_Session_Show_State();
    
    UAH_exit(0);
    EMU_Session_Show_State();
    
    UAH_dev_close(devDescP0_DEV0);
    EMU_Session_Show_State();
    
    UAH_dev_close(devDescP0_DEV1);
    EMU_Session_Show_State();
    
    UAH_exit(0);
    EMU_Session_Show_State();
    
    printf("END SESSION\n");
    
    return 1;    
}

