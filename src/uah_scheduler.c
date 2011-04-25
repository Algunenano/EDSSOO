/* 
 * File:   uah_scheduler.c
 * Author: Algunenano
 *
 * Created on April 25, 2011, 5:08 AM
 */

#include "uah_scheduler.h"
#include "uah_pcb.h"

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
#define UAH_PCB_Queues_Number 8
struct UAH_PCB_Queue UAH_PCB_Ready_Queues_TABLE[UAH_PCB_Queues_Number];