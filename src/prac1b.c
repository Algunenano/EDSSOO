/*
 * File:   prac1b.c
 * Author: Algunenano
 *
 * Created on April 22, 2011, 3:15 AM
 */

#include "uah_set_up.h"
#include "uah_sys_calls.h"

_UAH_API_sys_call0(int, UAH_pause)
_UAH_API_sys_call1(int, UAH_exit,int,exitcode)
_UAH_API_sys_call3(int, UAH_open,const char*, name, int, flag, int, mode)
_UAH_API_sys_call1(int, UAH_close, int, fd)

int main (void){
    int fd;
    uah_set_up();

    UAH_pause();
    fd=UAH_open("MIFICHERO.txt",3,4);
    UAH_close(fd);
    UAH_exit(0);
    return (0);
}

