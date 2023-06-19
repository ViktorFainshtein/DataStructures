#include <stdio.h>
#include "scheduler.h"


int Blues(void *arg)
{
	if(arg == NULL)
	{
		printf("Nani! cinamon.\n");
	}
	
	return 0;
}

int Rock(void *arg)
{
	if(arg == NULL)
	{
		printf("thats a sharp dress my man!\n");
	}

	return 0;
}

int Classic(void *arg)
{
	if(arg == NULL)
	{
		printf("its For not four and elise isn't a season\n");
	}

	return 0;
}

int Pop1(void *arg)
{
	if(arg == NULL)
	{
		printf("You've been hit by...\n");
	}

	return 0;
}

int Pop2(void *arg)
{
	if(arg == NULL)
	{
		printf("You've been struck by...\n");
	}

	return 0;
}

int Pop3(void *arg)
{
	if(arg == NULL)
	{
		printf("A Smooth Scheduler!\n");
	}

	return 0;
}

int Electro(void *arg)
{
	if(arg == NULL)
	{
		printf("BzzBzzBzz\n");
	}

	return 0;
}

int Stop(void *arg)
{
	SchedulerStop(arg);
	return 1;
}


int main()
{
	scheduler_t *sr = NULL;
	
	void *arg1 = NULL;
	void *arg2 = NULL;
	void *arg3 = NULL;
	void *arg4 = NULL;
	void *arg5 = NULL;
	
	ilrd_uid_t t1 = UIDGetNull();
	ilrd_uid_t t2 = UIDGetNull();
	ilrd_uid_t t3 = UIDGetNull();
	ilrd_uid_t t4 = UIDGetNull();
	ilrd_uid_t t5 = UIDGetNull();
	ilrd_uid_t t6 = UIDGetNull();
	ilrd_uid_t t7 = UIDGetNull();
	ilrd_uid_t t8 = UIDGetNull();
	
	sr = SchedulerCreate();
	
	t1 = SchedulerAddTask(sr, Blues, arg1, 2);
	t2 = SchedulerAddTask(sr, Rock, arg2, 5);
	t3 = SchedulerAddTask(sr, Classic, arg3, 3);
	t4 = SchedulerAddTask(sr, Pop1, arg4, 7);
	t5 = SchedulerAddTask(sr, Pop2, arg4, 8);
	t6 = SchedulerAddTask(sr, Pop3, arg4, 9);
	t7 = SchedulerAddTask(sr, Electro, arg5, 10);
	t8 = SchedulerAddTask(sr, Stop, sr, 11);
	
	if(UIDIsSame(t1,t2) || UIDIsSame(t2,t3) || UIDIsSame(t3,t4) || 
		UIDIsSame(t4,t5) || UIDIsSame(t5,t6) || 
		UIDIsSame(t6,t7) || UIDIsSame(t7,t8))
	{
		printf("ERROR\n");
	}
	
	printf("%d\n", SchedulerIsEmpty(sr));
	
	printf("%ld\n", SchedulerSize(sr));

	SchedulerRemoveTask(sr, t7);
	
	printf("%ld\n", SchedulerSize(sr));
	
	SchedulerRun(sr);
	
	printf("%d\n", SchedulerIsEmpty(sr));
	
	SchedulerDestroy(sr);
	sr = NULL;
	
	return 0;
}
