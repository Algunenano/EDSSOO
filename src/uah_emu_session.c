/* 
 * File:   uah_emu_session.c
 * Author: Algunenano
 *
 * Created on April 25, 2011, 6:35 PM
 */

#include <stdio.h>
#include <string.h>

#include "uah_pcb.h"
#include "uah_scheduler.h"

extern struct UAH_PCB *UAH_PCB_CURRENT;
extern unsigned int UAH_current_prio;

extern struct UAH_PCB_Queue UAH_PCB_Ready_Queues_TABLE[8];

void EMU_Session_Show_State (void){
    struct UAH_PCB *UAH_PCB_Aux;
    int auxCount;
    
    printf ("\nSTATE\n\n");
    printf ("\tCURRENT->\t%s \t PID \t%i \tDPRIO \t%i\tBPRIO\t%i\n\n",
                UAH_PCB_CURRENT->name,
                UAH_PCB_CURRENT->pid,
                UAH_current_prio,
                UAH_PCB_CURRENT->basePriority);
    
    for (auxCount=0; auxCount<UAH_PCB_Queues_Number;auxCount++){
        UAH_PCB_Aux = UAH_PCB_Ready_Queues_TABLE[auxCount].head;
        
        printf("\tPCBQueue[%d]->",auxCount);
        
        while (UAH_PCB_Aux != NULL){
            printf("\t%s \tPID\t%i \tBPRIO \t%i \n\t\t->",
                    UAH_PCB_Aux->name,
                    UAH_PCB_Aux->pid,
                    UAH_PCB_Aux->basePriority);
            UAH_PCB_Aux = UAH_PCB_Aux->next;
        }
        printf("\tNULL\n");
    }
    printf("\n\n");
    getchar();   
    
}