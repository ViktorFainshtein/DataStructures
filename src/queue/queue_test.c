/*********************************
 * Reviewer: 
 * Author: Viktor Fainshtein
 * File Name: queue_test.c
 * ******************************/
#include "queue.h"
#include <stdio.h>	/* printf */
#include <stdlib.h>	/* free */

void GeneralTest();

void TestAppend();

void TestEnQueue();

void TestDeQueue();

int main()
{
	GeneralTest();

	TestAppend();

	TestEnQueue();

	TestDeQueue();
	
	return 0;
}

void GeneralTest()
{
	size_t data1 = 3;
	size_t data2 = 6;
	size_t data3 = 9;
	queue_t *queue = QueueCreate();
	
	QueueEnQueue(queue, &data1);
	printf("%ld\n", *(size_t *)QueuePeek(queue));
	QueueDeQueue(queue);
	QueueEnQueue(queue, &data2);
	printf("%ld\n", *(size_t *)QueuePeek(queue));
	QueueDeQueue(queue);
	QueueEnQueue(queue, &data3);
	printf("%ld\n", *(size_t *)QueuePeek(queue));
	QueueDeQueue(queue);
	
	QueueEnQueue(queue, &data1);
	QueueEnQueue(queue, &data2);
	QueueEnQueue(queue, &data3);
	
	if(QueueIsEmpty(queue) == 1)
	{
		printf("Queue is empty\n");
	}
	else
	{
		printf("Queue is not empty\n");
	}
	
	printf("Queue len is: %ld\n", QueueSize(queue));
	
	QueueDestroy(queue);
}

void TestAppend()
{
	queue_t *queue1 = QueueCreate();
	queue_t *queue2 = QueueCreate();
	queue_t *temp = NULL;
	size_t data1 = 3;
	size_t data2 = 6;
	size_t data3 = 9;
	
	QueueEnQueue(queue1, &data1);
	QueueEnQueue(queue1, &data2);
	QueueEnQueue(queue1, &data3);

	QueueEnQueue(queue2, &data3);
	QueueEnQueue(queue2, &data2);
	QueueEnQueue(queue2, &data1);
	
	temp = QueueAppend(queue1, queue2);
	
	printf("%ld\n", *(size_t *)QueuePeek(temp));
	QueueDeQueue(temp);
	printf("%ld\n", *(size_t *)QueuePeek(temp));
	QueueDeQueue(temp);
	printf("%ld\n", *(size_t *)QueuePeek(temp));
	QueueDeQueue(temp);
	printf("%ld\n", *(size_t *)QueuePeek(temp));
	QueueDeQueue(temp);
	printf("%ld\n", *(size_t *)QueuePeek(temp));
	QueueDeQueue(temp);
	printf("%ld\n", *(size_t *)QueuePeek(temp));
	QueueDeQueue(queue1);
	
	QueueDestroy(queue1);
	temp = NULL;
}

void TestEnQueue()
{
	size_t data1 = 3;
	size_t data2 = 6;
	size_t data3 = 9;
	queue_t *queue = QueueCreate();
	
	QueueEnQueue(queue, &data1);
	QueueEnQueue(queue, &data2);
	QueueEnQueue(queue, &data3);

	if(QueueIsEmpty(queue) == 1)
	{
		printf("Queue is empty\n");
	}
	else
	{
		printf("Queue is not empty\n");
	}
	
	printf("Queue len is: %ld\n", QueueSize(queue));
	
	QueueDestroy(queue);
}

void TestDeQueue()
{
	size_t data1 = 3;
	size_t data2 = 6;
	size_t data3 = 9;
	queue_t *queue = QueueCreate();
	
	QueueEnQueue(queue, &data1);
	QueueEnQueue(queue, &data2);
	QueueEnQueue(queue, &data3);
	
	printf("Queue len after Enqueue is: %ld\n", QueueSize(queue));
	
	QueueDeQueue(queue);
	QueueDeQueue(queue);
	QueueDeQueue(queue);
	
	printf("Queue len after Dequeue is: %ld\n", QueueSize(queue));
	
	QueueDestroy(queue);
}



















