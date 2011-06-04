/* 
 * File:   uah_scheduler.c
 * Author: Algunenano
 *
 * Created on April 25, 2011, 5:08 AM
 */

#include "uah_scheduler.h"
#include "uah_pcb.h"
#include <stdio.h>
#include <stdlib.h>

/* Variable auxiliar empleada para asignar un identificador a cada proceso */
int UAH_countPID;

/* Puntero al PCB del proceso que posee actualmente la CPU */
struct UAH_PCB *UAH_PCB_CURRENT;

/* Puntero al PCB del proceso que pasará a ser CURRENT
   tras la acción del dispatcher */
struct UAH_PCB *UAH_PCB_NEXT;

/* Prioridad dinámica del proceso que actualmente posee la CPU */
unsigned int UAH_current_prio;

/* Prioridad del proceso que pasará a ser CURRENT 
   tras la acción del dispatcher */
unsigned int UAH_next_prio;

/* PCB del proceso P_IDLE que se ejecuta cuando no hay ningún otro proceso listo*/
struct UAH_PCB P_IDLE;

/* PCB del proceso P_INIT que constituye el primer proceso de usuario */
struct UAH_PCB P_INIT;

/* Tabla de colas de procesos listos: Una cola por prioridad */
struct UAH_PCB_Queue UAH_PCB_Ready_Queues_TABLE[UAH_PCB_Queues_Number];

unsigned int UAH_countTicks; /* Implementa un contador de ticks */

#define UAH_Quantum 2 /* Determina el valor del Quantum */

/* Manejo del incremento de prioridad de los procesos */
#define UAH_burst_ticks 2
unsigned int UAH_count_burst_ticks;


/* Inicialización de campos del PCB */
void uah_sch_init_PCB (struct UAH_PCB *p_pcb, const char *name, 
                unsigned int pid, unsigned int basePriority){
    p_pcb->name = name;
    p_pcb->pid = pid;
    p_pcb->basePriority = basePriority;
    p_pcb->openDeviceCounter = 0;
    p_pcb->openDeviceListBitMap = 0;
}

/* Inicializa los PCBs de P_IDLE y P_INIT, el PID y las colas de procesos*/
void uah_sch_init (void){
    unsigned int i;
    uah_sch_init_PCB(&P_IDLE,"P_IDLE",0,7);
    uah_sch_init_PCB(&P_INIT,"P_INIT",1,6);
    UAH_countPID=2;
    
    for (i=0; i<UAH_PCB_Queues_Number; i++){
        UAH_PCB_Ready_Queues_TABLE[i].head = NULL;
        UAH_PCB_Ready_Queues_TABLE[i].tail = NULL;        
    }
    
    uah_pcb_insert_queue_tail(&P_IDLE,&UAH_PCB_Ready_Queues_TABLE[7]);
    
    UAH_current_prio = 6;
    UAH_PCB_CURRENT = &P_INIT;
    UAH_countTicks = 0;
    UAH_count_burst_ticks = 0;
}

/* Seleccionar el proceso a ejecutar */
int uah_sch_schedule (void){
    unsigned int i = 0;
    struct UAH_PCB *p_pcb = NULL;
    
    
    /* Extraemos el proceso de mayor prioridad */
    while ((i< UAH_PCB_Queues_Number) && (p_pcb == NULL)){
        uah_pcb_extract_queue_head(&p_pcb,&UAH_PCB_Ready_Queues_TABLE[i]);
        i++;
    }
    
    if (i != UAH_PCB_Queues_Number){
        UAH_PCB_NEXT = p_pcb;
        UAH_next_prio = i-1;
        return 0;
    }
    
    return -1;
}

/* Se ejecuta cuando un proceso pasa al estado Ready*/
int uah_sch_proc_ready (struct UAH_PCB *pPCB, unsigned int priority){
    if (priority < UAH_current_prio){
        uah_pcb_insert_queue_head(UAH_PCB_CURRENT,
                                &UAH_PCB_Ready_Queues_TABLE[UAH_current_prio]);
        UAH_PCB_NEXT = pPCB;
        UAH_next_prio = priority;
        return 1;
    }
    
    uah_pcb_insert_queue_tail(pPCB,&UAH_PCB_Ready_Queues_TABLE[priority]);
    return 0;
}

/* Crear un proceso (su PCB y añadirlo a las colas )*/
int uah_sch_create_process (const char *name, unsigned int basePriority){
    struct UAH_PCB *pPCB = malloc (sizeof (struct UAH_PCB));
    if (!pPCB) return -1;
    uah_sch_init_PCB (pPCB, name, UAH_countPID++, basePriority);
    return uah_sch_proc_ready (pPCB, basePriority);
}

/* Cerrar el proceso actual */
int uah_sch_exit (int exitcode){
    free (UAH_PCB_CURRENT);
    return 0;
}

/* Emula el cambio de contexto */
void uah_dispatcher (void) {
    UAH_countTicks = 0;
    if (UAH_PCB_CURRENT != UAH_PCB_NEXT){
        UAH_PCB_CURRENT = UAH_PCB_NEXT;
        UAH_current_prio = UAH_next_prio;
    }
}


void uah_sch_burst_user_process (void){
    struct UAH_PCB *pPCB;
    int i = UAH_current_prio > 1 ? UAH_current_prio : 2;
    
    /* No llegamos al proceso de IDLE */
    for (;i<UAH_PCB_Queues_Number-1;i++){
        uah_pcb_extract_queue_head(&pPCB,&UAH_PCB_Ready_Queues_TABLE[i]);
        while (pPCB != NULL){
            uah_pcb_insert_queue_tail(pPCB,&UAH_PCB_Ready_Queues_TABLE[i-1]);
            uah_pcb_extract_queue_head(&pPCB,&UAH_PCB_Ready_Queues_TABLE[i]);
        }
    }
}

void uah_sch_round_robin (void) {
    UAH_countTicks++;
    
    if (UAH_countTicks == UAH_Quantum){
        /* Insertar el proceso current al final de la cola de 
         * su prioridad base 
         */
        uah_pcb_insert_queue_tail(UAH_PCB_CURRENT,
                &UAH_PCB_Ready_Queues_TABLE[UAH_PCB_CURRENT->basePriority]);
        
        /* Llama a uah_sch_schedule para seleccionar un nuevo proceso */
        uah_sch_schedule();
        
        /* Llama al dispatcher */
        uah_dispatcher();
    } else {
        /* No se realiza cuando se ejecuta un proceso del sistema */
        if (UAH_current_prio!=0){
            UAH_count_burst_ticks++;
            
            if (UAH_count_burst_ticks == UAH_burst_ticks){
                UAH_count_burst_ticks = 0;
                uah_sch_burst_user_process();
            }
        }
    }
    
}