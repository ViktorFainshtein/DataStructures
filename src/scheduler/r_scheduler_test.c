/*********************************
 * Reviewer: Daniel Natan
 * Author: Roy Mantel
 * File Name: scheduler_test.c
 * ******************************/

#include <stdio.h>	/*printf*/
#include <time.h>	/*ctime*/
#include "scheduler.h"
#include "uid.h"

void CreateAddDestroy(void);
void TestSchedulerBasics(scheduler_t *scdlr);
void TestSchedulerAdvanced(scheduler_t *scdlr);

int PrintName(void *name)
{
	static int count = 0;
	while(count < 7)
	{
		printf("%s, Count = %d\n", (char *)name, count);
		++count;
		return 0;
	}

	return 1;
}

int PrintTime(void *time)
{
	static int count = 0;
	while(count < 5)
	{
		printf("The Test Started at: %sCount = %d\n", ctime((time_t*)time), count);
		++count;
		return 0;
	}
	return 1;
}

int PrintSentenceAndStop(void *arg)
{
	SchedulerStop((scheduler_t*)arg);
	printf("Now I Will Stop\n");
	return 1;
}

int main(void)
{
	scheduler_t *scdlr = NULL;
	/* CreateAddDestroy(); */

	TestSchedulerBasics(scdlr);
	if(scdlr)
	{
		printf("Error 0: SchedulerDestroy\n");
	}

	scdlr = SchedulerCreate();
	TestSchedulerAdvanced(scdlr);

	SchedulerDestroy(scdlr);

	return 0;
}

void TestSchedulerBasics(scheduler_t *scdlr)
{
	ilrd_uid_t uid = UIDGetNull();
	scdlr = SchedulerCreate();

	if(!SchedulerIsEmpty(scdlr))
	{
		printf("Error 1: Created Scheduler is not empty\n");
	}

	if(SchedulerSize(scdlr))
	{
		printf("Error 2: Created Scheduler size is not zero\n");
	}

	uid = SchedulerAddTask(scdlr, PrintName, "Roy", 5);
	if(UIDIsSame(g_bad_uid, uid))
	{
		printf("BAD UID\n");
	}

	if(UIDIsSame(g_bad_uid, SchedulerAddTask(scdlr, PrintName, "RoyRoy", 3)))
	{
		printf("BAD UID\n");
	}

	if(UIDIsSame(g_bad_uid, SchedulerAddTask(scdlr, PrintName, "Yor", 8)))
	{
		printf("BAD UID\n");
	}

	if(SchedulerIsEmpty(scdlr))
	{
		printf("Error 3: Scheduler still empty after adding tasks\n");
	}

	if(3 != SchedulerSize(scdlr))
	{
		printf("Error 4: Scheduler size is not correct\n");
	}

	SchedulerRemoveTask(scdlr, uid);
	if(2 != SchedulerSize(scdlr))
	{
		printf("Error 5: Scheduler size is not correct after RemoveTask\n");
	}

	SchedulerClearAll(scdlr);
	if(!SchedulerIsEmpty(scdlr))
	{
		printf("Error 6: Cleared Scheduler is not empty\n");
	}

	if(SchedulerSize(scdlr))
	{
		printf("Error 7: Cleared Scheduler size is not zero\n");
	}

	SchedulerDestroy(scdlr);
}

void CreateAddDestroy(void)
{
	scheduler_t *scdlr = NULL;
	scdlr = SchedulerCreate();
	SchedulerAddTask(scdlr, PrintName, "Roy", 5);
	SchedulerDestroy(scdlr);
}

void TestSchedulerAdvanced(scheduler_t *scdlr)
{
	time_t test_time = time(NULL);
	SchedulerAddTask(scdlr, PrintTime, &test_time, 7);
	SchedulerAddTask(scdlr, PrintName, "Advanced Test", 3);
	/*the next line inserts a Stop task, to test if Scheduler stops by it's own
		make it a comment*/
	SchedulerAddTask(scdlr, PrintSentenceAndStop, scdlr, 17);
	SchedulerRun(scdlr);
}