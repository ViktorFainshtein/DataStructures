/*********************************
 * Reviewer: Sarah Toledano
 * Author: Viktor Fainshtein
 * File Name: task.c
 * ******************************/
#include <stdlib.h>	/*malloc free*/
#include <assert.h>	/*assert*/
#include "task.h"

struct task                    
{
	time_t exec_time_in_sec;
	task_action_t action_func;
	size_t time_interval;
	void *arg;
};

task_t *TaskCreate(size_t interval, void *arg, task_action_t action_func)
{
	task_t *task = NULL;
	task = (task_t *)malloc(sizeof(task_t));
	
	if(task == NULL)
	{
		return NULL;
	}
	
	task->time_interval = interval;
	task->exec_time_in_sec = time(NULL) + interval;
	task->action_func = action_func;
	task->arg = arg;
	
	return task;
}

void TaskDestroy(task_t *task)
{
	assert(task);
	
	task->exec_time_in_sec = 0;
	task->action_func = NULL;
	task->arg = NULL;
	free(task);
	task = NULL;
}

time_t TaskGetExecTime(task_t *task)
{
	assert(task);
	return task->exec_time_in_sec;
}

size_t TaskGetIntervalTime(task_t *task)
{
	assert(task);
	return task->time_interval;
}

void TaskSetExecTime(task_t *task, time_t new_time)
{
	assert(task);
	task->exec_time_in_sec = new_time + task->time_interval;
}

void TaskSetIntervalTime(task_t *task, size_t new_interval_in_seconds)
{
	assert(task);
	task->time_interval = new_interval_in_seconds;
}

int TaskExec(task_t *task)
{
	assert(task);
	return task->action_func(task->arg);
}

