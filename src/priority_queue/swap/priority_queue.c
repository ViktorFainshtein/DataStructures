#include <stdlib.h>	/*malloc free*/
#include <assert.h>
#include "priority_queue.h"
#include "sorted_list.h"


struct p_queue
{
    sorted_list_t *slist;
    pq_compare_t compare_func;
    void *user_param;
};


typedef struct pq_node								
{
	ilrd_uid_t uid;
	void *data;
}pq_node_t;

static int pq_compare(const void *data1, const void *data2, const void *pq)
{
	pq_node_t t_data1 = *(pq_node_t *)data1;
	pq_node_t t_data2 = *(pq_node_t *)data2;
	
	assert(data1);
	assert(data2);
	
	return ((pri_queue_t *)pq)->compare_func(t_data1.data, t_data2.data, ((pri_queue_t *)pq)->user_param);
}

pri_queue_t *PQueueCreate(pq_compare_t priority_func, void *user_param)
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
		return UIDGetNull();
	}
	node->data = data;
	node->uid = UIDGet();
	SortedListInsert(pq->slist, node);
	return node->uid;
}

void PQueueDeQueue(pri_queue_t *pq)
{
	sorted_list_iterator_t from = SortedListBegin(pq->slist);
	assert(pq);
	
	free(SortedListGetData(from));
	SortedListPopFront(pq->slist);						
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

void PQueueErase(pri_queue_t *pq, ilrd_uid_t uid)
{
	sorted_list_iterator_t from = SortedListBegin(pq->slist);
	sorted_list_iterator_t to = SortedListEnd(pq->slist);
	
	assert(pq);
	
	while(!SortedListIsSameIter(from,to))
	{
		if(UIDIsSame((*(pq_node_t *)SortedListGetData(from)).uid, uid))
		{
			SortedListRemove(from);
			break;
		}
		from = SortedListNext(from);
	}
}























