#include <stdio.h>
#include "priority_queue.h"

int comparando(const void *data1, const void *data2, void *temp)
{
	if((*(int *)data1 > *(int *)data2) && (temp == NULL))
	{
		return 1;
	}
	return 0;
}

int main()
{
	pri_queue_t *q = PQueueCreate(comparando, NULL);
	int data1 = 30;
	int data2 = 20;
	int data3 = 10;
	
	
	PQueueEnQueue(q, &data1);
	printf("peek data: %d\n", *(int *)PQueuePeek(q));
	PQueueEnQueue(q, &data2);
	printf("peek data: %d\n", *(int *)PQueuePeek(q));
	PQueueEnQueue(q, &data3);
	printf("peek data: %d\n", *(int *)PQueuePeek(q));
	
	printf("After 3 EnQueue: %ld\n", PQueueSize(q));

	printf("Is Empty: %d\n", PQueueIsEmpty(q));
	
	PQueueDeQueue(q);
	printf("after Dequeue size: %ld\n", PQueueSize(q));
	
	printf("after Dequeue data: %d\n", *(int *)PQueuePeek(q));
	PQueueDeQueue(q);
	printf("after Dequeue data: %d\n", *(int *)PQueuePeek(q));
	
	PQueueEnQueue(q, &data1);
	PQueueEnQueue(q, &data2);
	PQueueEnQueue(q, &data3);
	
	/*PQueueClear(q);*/
	
	PQueueDestroy(q);	
	
	return 0;
}
