/*********************************
 * Reviewer: Sarah Toledano
 * Author: Viktor Fainshtein
 * File Name: scheduler.h
 * ******************************/
#include <stddef.h>	/*size_t*/
#include "uid.h"	/*ilrd_uid_t*/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

typedef struct scheduler scheduler_t;
typedef int (* scheduler_action_t)(void *arg);

scheduler_t *SchedulerCreate(void); 

void SchedulerDestroy(scheduler_t *scdlr);

ilrd_uid_t SchedulerAddTask(scheduler_t *scdlr,  
            scheduler_action_t action_func,
            void *arg,
            size_t time_interval);/*absolute time in seconds (relative to epoch)*/
/*
Descreption:
Return val: new task uid, returns bad uid if fails 
Complexity:
*/

int SchedulerRemoveTask(scheduler_t *scdlr, ilrd_uid_t uid);

void SchedulerClearAll(scheduler_t *scdlr);

int SchedulerIsEmpty(scheduler_t *scdlr);

size_t SchedulerSize(scheduler_t *scdlr);

int SchedulerRun(scheduler_t *scdlr);
/* -1 in fail, zero in success, any other number for user func fails */

void SchedulerStop(scheduler_t *scdlr);

#endif










