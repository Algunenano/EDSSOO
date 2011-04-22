/*
 * File:   prac1b.c
 * Author: Algunenano
 *
 * Created on April 22, 2011, 3:15 AM
 */

#include "uah_set_up.h"
#include "uah_sys_calls.h"

_UAH_API_sys_call0(int, UAH_pause)
_UAH_API_sys_call1(int,UAH_exit,int,exitcode)

int main (void){
    uah_set_up();
    UAH_pause();
    UAH_exit(0);
    return (0);
}

