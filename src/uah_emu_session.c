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
    int auxCount = 0, auxCount2 = 0;
    
    printf ("\nSTATE\n\n");
    printf ("\tCURRENT->\t%s \t PID \t%i \tDPRIO \t%i\tBPRIO\t%i\n",
                UAH_PCB_CURRENT->name,
                UAH_PCB_CURRENT->pid,
                UAH_current_prio,
                UAH_PCB_CURRENT->basePriority);
    
    if (UAH_PCB_CURRENT->openDeviceCounter){
        printf("\t\t\tDevice List:\n");
        
        while (auxCount < UAH_MAX_NUM_OPEN_DEVICES){
            if ((UAH_PCB_CURRENT->openDeviceListBitMap >> auxCount) & 0x1){
                printf("\t\t\t-> DESC \t%i, NAME \t\"%s\"\n",
                        auxCount,
                        UAH_PCB_CURRENT->openDeviceList[auxCount]->name
                        );
            }
            auxCount++;
        }
    }
    
    printf("\n");
    
    for (auxCount=0; auxCount<UAH_PCB_Queues_Number;auxCount++){
        UAH_PCB_Aux = UAH_PCB_Ready_Queues_TABLE[auxCount].head;
        
        printf("\tPCBQueue[%d]->",auxCount);
        
        while (UAH_PCB_Aux != NULL){
            printf("\t%s \tPID\t%i \tBPRIO \t%i \n",
                    UAH_PCB_Aux->name,
                    UAH_PCB_Aux->pid,
                    UAH_PCB_Aux->basePriority);
            
            if (UAH_PCB_Aux->openDeviceCounter){
                printf("\t\t\tDevice List:\n");
                auxCount2 = 0;
                while (auxCount2 < UAH_MAX_NUM_OPEN_DEVICES){
                    if ((UAH_PCB_Aux->openDeviceListBitMap >> auxCount2) & 0x1){
                        printf("\t\t\t-> DESC \t%i, NAME \t\"%s\"\n",
                            auxCount2,
                            UAH_PCB_Aux->openDeviceList[auxCount2]->name
                            );
                    }
                    auxCount2++;
                }
                printf("\n");
            }
            
            
            UAH_PCB_Aux = UAH_PCB_Aux->next;
            printf("\t\t->");
        }
        printf("\tNULL\n");
    }
    printf("\n\n");
    getchar();   
    
}