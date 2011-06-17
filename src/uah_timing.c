/* 
 * File:   uah_timing.c
 * Author: Algunenano
 *
 * Created on June 11, 2011, 3:01 AM
 */
#include "uah_pcb.h"
#include "uah_scheduler.h"
#include <stdio.h>


#define UAH_MS_PER_TICK 50

struct UAH_PCB *pTimingList = NULL;

/* Inserta el proceso CURRENT en la cola de procesos dormidos
 * - En caso de mismo tiempo de espera se ordena por prioridad
 * - Si se inserta el proceso current se selcciona el siguiente para ejecución
 * - Retorna 0 / 1 en función de si no o sí se ha dormido
 */
int uah_timing_sleep (unsigned long ms){
    unsigned long ticks;
    unsigned char encontrado = 0;
    unsigned char isSleep = 0;
    
    //Puntero auxiliar a la lista
    struct UAH_PCB *pTimListAux;
    
    //Puntero al puntero donde insertar el PCB
    struct UAH_PCB **ppTimListInsert;
    
    ticks = ms / UAH_MS_PER_TICK;
    
    if (ticks>0){
        
       pTimListAux = pTimingList;
       ppTimListInsert = &pTimingList;
       
       while (pTimListAux && (!encontrado)){
           
           //Tiempo de espera
           if (pTimListAux->ticks > ticks){
               encontrado = 1;
           } else if (pTimListAux->ticks == ticks){
                   
                   //Ordenado por prioridad
                   if (pTimingList->basePriority > 
                           UAH_PCB_CURRENT->basePriority)
                       encontrado = 1;
           }
           
           if (!encontrado){              
               //Actualizar intervalo
               ticks -= pTimListAux->ticks;
               
               //Actualizar punteros a la lista
               ppTimListInsert = &(pTimListAux->next);
               pTimListAux = pTimListAux->next;
               
           } else {
               //Corregir ticks
               pTimListAux->ticks -= ticks;
           }
       }
       
       //Insertar en la lista
       *ppTimListInsert = UAH_PCB_CURRENT;
       UAH_PCB_CURRENT->next = pTimListAux;
       
       //Determinar el valor de los ticks
       UAH_PCB_CURRENT->ticks = ticks;
       
       //Seleccionar un nuevo proceso NEXT
       uah_sch_schedule();
       uah_dispatcher();
       
       //el proceso actual está dormido
       isSleep = 1;
       
    }
    
    return (isSleep);
}


int uah_timing_clk_tick(){
    struct UAH_PCB *pPCBFirst, *pPCBLast;
    unsigned char needDispatch = 0;
    
    if (pTimingList){
        pTimingList->ticks--;
        
        if (pTimingList->ticks<=0){
            //Primero de la lista con ticks == 0
            pPCBFirst = pTimingList;
            
            //Seleccionar el último de la lista que tenga ticks == 0
            pPCBLast = pTimingList;
            while (pPCBLast->next && (pPCBLast->next->ticks <= 0))
                pPCBLast = pPCBLast->next;
            
            pTimingList = pPCBLast->next;
            
            //Poner a NULL el último con ticks==0
            pPCBLast->next = NULL;
            
            //Llamar a la función uah_sch_proc_list_ready
            needDispatch = uah_sch_proc_sort_list_ready(pPCBFirst);
        }
    }
    
    return needDispatch;    
}