/*********************************
 * Reviewer: Roy Mantel		
 * Author: Viktor Fainshtein			
 * File: priority_queue.c					
 * ******************************/
#include <stdlib.h>	/*malloc free*/
#include <assert.h>
#include "priority_queue.h"
#include "heap.h"


struct p_queue
{
    heap_t *heap;
    PQcompare_t is_less;
    void *user_param;
};


typedef struct pq_node					
{
	ilrd_uid_t uid;
	void *data;
}pq_node_t;


static int pq_compare(const void *data1, const void *data2, void *pq)
{
	assert(data1);
	assert(data2);
	
	return ((pri_queue_t *)pq)->is_less(
		((pq_node_t *)data1)->data, 
		((pq_node_t *)data2)->data, 
		((pri_queue_t *)pq)->user_param);
}


pri_queue_t *PQueueCreate(PQcompare_t priority_func, void *user_param)
{
	pri_queue_t *pq = NULL;
	pq = (pri_queue_t *)malloc(sizeof(pri_queue_t));
	
	if(pq == NULL)
	{
		return NULL;
	}
	
	pq->heap = HeapCreate(pq_compare, pq);
	
	if(pq->heap == NULL)
	{
		free(pq);
		pq = NULL;
		return NULL;
	}
	
	pq->is_less = priority_func;
	pq->user_param = user_param;
	
	return pq;
}

void PQueueDestroy(pri_queue_t *pq)
{
	assert(pq);
	PQueueClear(pq);
	HeapDestroy(pq->heap);
	pq->heap = NULL;
	pq->is_less= NULL;
	pq->user_param = NULL;
	free(pq);
	pq = NULL;
}

ilrd_uid_t PQueueEnQueue(pri_queue_t *pq, void *data)				
{
	pq_node_t *node = NULL;
	assert(pq);
	assert(data);
	
	node = (pq_node_t *)malloc(sizeof(pq_node_t));
	if(node == NULL)
	{
		return g_bad_uid;
	}
	node->data = data;
	node->uid = UIDGet();
	
	if(HeapPush(pq->heap, node))
	{
		free(node);
		return g_bad_uid;
	}

	return node->uid;
}

int PQueueReEnQueue(pri_queue_t *pq, void *data, ilrd_uid_t old_uid)
{
	pq_node_t *node = NULL;
	assert(pq);
	assert(data);
	
	node = (pq_node_t *)malloc(sizeof(pq_node_t));
	if(node == NULL)
	{
		return 1;
	}

	node->data = data;
	node->uid = old_uid;

	if(HeapPush(pq->heap, node))
	{
		free(node);
		return 1;
	}

	return 0;
}

ilrd_uid_t PQueueDeQueue(pri_queue_t *pq)
{
	void *node = HeapPeek(pq->heap);
	ilrd_uid_t uid = g_bad_uid;
	
	assert(pq);

	uid = ((pq_node_t *)node)->uid;
	HeapPop(pq->heap);
	free(node);
	
	return uid;					
}

void *PQueuePeek(pri_queue_t *pq)						
{
	pq_node_t *temp = HeapPeek(pq->heap);
	assert(pq);
	
	if(PQueueIsEmpty(pq))
	{
		return NULL;
	}
	
	return temp->data;
}

int PQueueIsEmpty(pri_queue_t *pq)						
{
	assert(pq);
	return HeapIsEmpty(pq->heap);
}

size_t PQueueSize(pri_queue_t *pq)
{
	assert(pq);
	return HeapSize(pq->heap);
}

void PQueueClear(pri_queue_t *pq)
{	
	assert(pq);
	
	while(HeapSize(pq->heap))
	{
		HeapPop(pq->heap);
	}	
}

static int pq_is_match(const void *data1, const void *data2, void *pq)
{
	assert(data1);
	assert(data2);
	return UIDIsSame((*(ilrd_uid_t *)data1), ((pq_node_t *)data2)->uid);
}

void *PQueueErase(pri_queue_t *pq, ilrd_uid_t uid)
{
	pq_node_t *node = NULL;
	void *ret_data = NULL;
	assert(pq);

	node  = HeapRemove(pq->heap, (const void *)&uid , pq_is_match, pq->user_param);
	if(node == NULL)
	{
		return NULL;
	}

	ret_data = node->data;
	node->uid = UIDGetNull();
	node->data = NULL;
	free(node);
	
	return ret_data;
}
























