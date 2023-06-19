/*********************************
 * Reviewer: 
 * Author: Viktor Fainshtein
 * File Name: queue.c
 * ******************************/
#include "queue.h"
#include "sll.h"
#include <stdlib.h>	/* malloc free */
#include <assert.h>	/* assert */

struct queue
{
   sll_t *slist;
};

queue_t *QueueCreate()
{
	queue_t *new_queue = (queue_t *)malloc(sizeof(queue_t));
	if(new_queue == NULL)
	{
		return NULL;
	}

	new_queue->slist = SLLCreate();
	if(new_queue->slist == NULL)
	{
		return NULL;
	}
	
	return new_queue;
}

void QueueDestroy(queue_t *q)
{
	assert(q);
	SLLDestroy(q->slist);
	q->slist = NULL;
	free(q);
	q = NULL;
}

int QueueEnQueue(queue_t *q, void *element_add)
{	
	assert(q);
	assert(element_add);

	return (SLLInsert(SLLEnd(q->slist), element_add) == SLLEnd(q->slist)) ? 1 : 0;
}

void QueueDeQueue(queue_t *q)
{
	assert(q);
	SLLRemove(SLLBegin(q->slist));
}

void *QueuePeek(const queue_t *q)
{
	assert(q);

	return SLLGet(SLLBegin(q->slist));
}

queue_t *QueueAppend(queue_t *q1, queue_t *q2)
{
	assert(q1);
	assert(q2);
	
	SLLAppend(q1->slist, q2->slist);

	q2->slist = NULL;
	free(q2);
	q2 = NULL;
	
	return q1;
}

size_t QueueSize(const queue_t *q)
{
	assert(q);
	return SLLCount(q->slist);
}

int QueueIsEmpty(const queue_t *q)
{
	assert(q);

	return (SLLBegin(q->slist) == SLLEnd(q->slist)) ? 1 : 0;
}





















