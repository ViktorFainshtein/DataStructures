/*********************************
 * Reviewer: Sarah Toledano
 * Author: Viktor Fainshtein
 * File Name: scheduler.c
 * ******************************/
#include <stdlib.h>	/*malloc free*/
#include <unistd.h>	/*sleep*/
#include <assert.h>	/*assert*/
#include "scheduler.h"
#include "priority_queue.h"
#include "task.h"

struct scheduler
{
	pri_queue_t *pq;
	task_t *curr_task;
	size_t is_running;
};

static int TaskTimeCmp(const void *task1, const void *task2, void *arg)
{
	task_t *t1 = (task_t *)task1;
	task_t *t2 = (task_t *)task2;
	 
	return (TaskGetExecTime(t1) < TaskGetExecTime(t2));
}

scheduler_t *SchedulerCreate(void)
{
	scheduler_t *scdlr = NULL;
	scdlr = (scheduler_t *)malloc(sizeof(scheduler_t));
	
	if(scdlr == NULL)
	{
		return NULL;
	}
	
	scdlr->pq = PQueueCreate(TaskTimeCmp, NULL);
		
	if(scdlr->pq == NULL)
	{
		free(scdlr);
		scdlr = NULL;
		return NULL;
	}
	
	scdlr->is_running = 0;
	scdlr->curr_task = NULL;
	
	return scdlr;
}

void SchedulerDestroy(scheduler_t *scdlr)
{
	assert(scdlr);
	
	SchedulerClearAll(scdlr);
	PQueueDestroy(scdlr->pq);

	scdlr->pq = NULL;
	scdlr->curr_task = NULL;

	free(scdlr);
	scdlr = NULL;
}

ilrd_uid_t SchedulerAddTask(scheduler_t *scdlr,  
            scheduler_action_t action_func,
            void *arg,
            size_t time_interval)
{
	task_t *task = NULL;
	assert(scdlr);

	task = TaskCreate(time_interval, arg, action_func);
	if(task == NULL)
	{
		return g_bad_uid;
	}
	
	return PQueueEnQueue(scdlr->pq, task);
}

int SchedulerRemoveTask(scheduler_t *scdlr, ilrd_uid_t uid)
{
	void *task = NULL;
	assert(scdlr);

	task = PQueueErase(scdlr->pq, uid);

	if(task)
	{
		TaskDestroy(task);
		task = NULL;
	}

	return 0;
}

void SchedulerClearAll(scheduler_t *scdlr)
{
	assert(scdlr);
	while(!SchedulerIsEmpty(scdlr))
	{
		TaskDestroy(PQueuePeek(scdlr->pq));
		PQueueDeQueue(scdlr->pq);
	}
}

int SchedulerIsEmpty(scheduler_t *scdlr)
{
	assert(scdlr);
	return (PQueueIsEmpty(scdlr->pq) && !scdlr->curr_task);
}

size_t SchedulerSize(scheduler_t *scdlr)
{
	assert(scdlr);
	return (PQueueSize(scdlr->pq) + !!(scdlr->curr_task));
}

int SchedulerRun(scheduler_t *scdlr)
{
	int res = 0;
	int enq_res = 0;
	time_t time_to_exec = 0;
	ilrd_uid_t uid = UIDGetNull();
	
	assert(scdlr);

	scdlr->is_running = 1;
	
	while(!SchedulerIsEmpty(scdlr) && scdlr->is_running && !enq_res)
	{	
		scdlr->curr_task = PQueuePeek(scdlr->pq);
		time_to_exec = difftime(TaskGetExecTime(scdlr->curr_task), time(NULL));

		while (0 < time_to_exec)
		{
			time_to_exec = sleep(time_to_exec);	
		}
		
		uid = PQueueDeQueue(scdlr->pq);
		res = TaskExec(scdlr->curr_task);
		
		if(0 == res)
		{
			TaskSetExecTime(scdlr->curr_task, time(NULL));
			enq_res = PQueueReEnQueue(scdlr->pq, scdlr->curr_task, uid);
		}
		else
		{
			TaskDestroy(scdlr->curr_task);
		}
	}
	
	if(enq_res)
	{
		TaskDestroy(scdlr->curr_task);
	}
	
	scdlr->is_running = 0;
	scdlr->curr_task = NULL;

	return enq_res;
}

void SchedulerStop(scheduler_t *scdlr)
{
	assert(scdlr);
	scdlr->is_running = 0;
}
