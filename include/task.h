/*********************************
 * Reviewer: Sarah Toledano
 * Author: Viktor Fainshtein
 * File Name: task.h
 * ******************************/
#ifndef __TASK_H__
#define __TASK_H__

#include <time.h>	/*time_t*/

typedef int (*task_action_t)(void *arg);
typedef struct task task_t;

task_t *TaskCreate(size_t interval, void *arg, task_action_t action_func);
/*
Descreption: create a new task
Return val: pointer to task, if fails NULL ptr
Complexity: O(1)
*/

void TaskDestroy(task_t *task);
/*
Descreption: destroy/remove task
Return val: 
Complexity: O(1)
*/

time_t TaskGetExecTime(task_t *task);
/*
Descreption: gives the exe time of the task
param: ptr to task
Return val: time_t exe_time
Complexity:
*/

size_t TaskGetIntervalTime(task_t *task);
/*
Descreption: gives the interval time of the task
param: ptr to task
Return val: time_t exe_time
Complexity:
*/

void TaskSetExecTime(task_t *task, time_t new_exec_time);
/*
Descreption: change the exec time of the task
param: ptr to task, new exec
Return val: non
Complexity:
*/

void TaskSetIntervalTime(task_t *task, size_t new_interval_in_seconds);
/*
Descreption: change the interval time of the task
param: ptr to task, new interval time
Return val: non
Complexity:
*/

int TaskExec(task_t *task);
/*
Descreption: execute task func
Return val: zero if success, non-zero integer when fails.
Complexity: O(1)
*/

#endif
