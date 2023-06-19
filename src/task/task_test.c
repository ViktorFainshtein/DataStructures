#include <stdio.h>
#include "task.h"

int IsSameNumbroAsEight(void *arg)
{
	if(8 == *(int *)arg)
	{
		return 1;
	}
	return 0;
}


int main()
{
	task_t *task = NULL;
	task_t *task_b = NULL;
	size_t time = 100;
	int eight = 8;
	int not_eight = 10;
	
	task = TaskCreate(time, &eight, IsSameNumbroAsEight);
	
	printf("Get time: %ld\n", TaskGetExecTime(task));
	
	TaskSetIntervalTime(task, 150);
	printf("time after set: %ld\n", TaskGetIntervalTime(task));
	
	printf("task exec: %d\n", TaskExec(task));

	task_b = TaskCreate(time, &not_eight, IsSameNumbroAsEight);
	printf("task_b exec: %d\n", TaskExec(task_b));
	
	TaskDestroy(task);
	TaskDestroy(task_b);

	return 0;
}
