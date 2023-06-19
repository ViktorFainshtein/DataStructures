/*********************************
 * Reviewer: Roy Mantel		
 * Author: Viktor Fainshtein			
 * File: priority_queue.c					
 * ******************************/
#include <stdlib.h>	/*malloc free*/
#include <assert.h>
#include "priority_queue.h"
#include "sorted_list.h"


struct p_queue
{
    sorted_list_t *slist;
    PQcompare_t compare_func;
    void *user_param;
};


typedef struct pq_node								
{
	ilrd_uid_t uid;
	void *data;
}pq_node_t;

static int pq_compare(const void *data1, const void *data2, void *pq)
{
	pq_node_t t_data1 = *(pq_node_t *)data1;
	pq_node_t t_data2 = *(pq_node_t *)data2;
	
	assert(data1);
	assert(data2);
	
	return ((pri_queue_t *)pq)->compare_func(
		t_data1.data, 
		t_data2.data, 
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
	
	pq->slist = SortedListCreate(pq_compare, pq);
	
	if(pq->slist == NULL)
	{
		free(pq);
		pq = NULL;
		return NULL;
	}
	
	pq->compare_func = priority_func;
	pq->user_param = user_param;
	
	return pq;
}

void PQueueDestroy(pri_queue_t *pq)
{
	assert(pq);
	PQueueClear(pq);
	SortedListDestroy(pq->slist);
	pq->slist = NULL;
	pq->compare_func = NULL;
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
	if(SortedListIsSameIter(
		SortedListInsert(pq->slist, node),
		SortedListEnd(pq->slist)))
	{
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
	if(SortedListIsSameIter(
		SortedListInsert(pq->slist, node),
		SortedListEnd(pq->slist)))
	{
		return 1;
	}
	return 0;
}

ilrd_uid_t PQueueDeQueue(pri_queue_t *pq)
{
	/*sorted_list_iterator_t from = SortedListBegin(pq->slist);
	ilrd_uid_t uid = (*(pq_node_t *)SortedListGetData(from)).uid;
	assert(pq);
	
	(*(pq_node_t *)SortedListGetData(from)).uid = g_bad_uid;*/
	/*free(SortedListGetData(from));
	SortedListRemove(from);*/
	void *node = SortedListPopFront(pq->slist);
	ilrd_uid_t uid = ((pq_node_t *)node)->uid;
	free(node);
	
	return uid;					
}

void *PQueuePeek(pri_queue_t *pq)						
{
	pq_node_t *temp = SortedListGetData(SortedListBegin(pq->slist));
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
	return SortedListIsEmpty(pq->slist);
}

size_t PQueueSize(pri_queue_t *pq)
{
	assert(pq);
	return SortedListSize(pq->slist);
}

void PQueueClear(pri_queue_t *pq)
{
	sorted_list_iterator_t from = SortedListBegin(pq->slist);
	sorted_list_iterator_t to = SortedListEnd(pq->slist);
	
	assert(pq);
	
	while(!SortedListIsSameIter(from,to))
	{
		free(SortedListGetData(from));
		SortedListRemove(from);
		from = SortedListBegin(pq->slist);
	}	
}

void *PQueueErase(pri_queue_t *pq, ilrd_uid_t uid)
{
	sorted_list_iterator_t from = SortedListBegin(pq->slist);
	sorted_list_iterator_t to = SortedListEnd(pq->slist);
	pq_node_t *data = NULL;
	
	assert(pq);
	
	while(!SortedListIsSameIter(from,to))
	{
		if(UIDIsSame((*(pq_node_t *)SortedListGetData(from)).uid, uid))
		{
			data = ((pq_node_t *)SortedListGetData(from))->data;
			free(SortedListGetData(from));
			SortedListRemove(from);
			return data;
		}
		from = SortedListNext(from);
	}
	return data;
}
























