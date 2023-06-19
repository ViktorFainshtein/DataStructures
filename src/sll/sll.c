/*********************************
 * Reviewer: 
 * Author: Viktor Fainshtein		
 * File: sll.c
 * ******************************/
#include <stdlib.h>	/* free mallloc*/
#include <assert.h>	/* assert */
#include "sll.h"

struct node
{
	void *data;
	struct node *next;
};

struct sll
{
	node_t *head;
	node_t *tail;
};

static int NotDummy(sll_iterator curr, void *param)
{
	assert(curr);
	if(curr->next != NULL && param)
	{
		return 1;
	}
	return 0;
}

sll_iterator SLLBegin(sll_t *slist)
{	
	assert(slist);
	return slist->head;
}

sll_iterator SLLEnd(sll_t *slist)
{
	assert(slist);
	return slist->tail;
}

sll_iterator SLLNext(sll_iterator curr)
{
	assert(curr);
	if(curr->next != NULL)			
	{
		return curr->next;
	}
	return curr;
}

void *SLLGet(sll_iterator curr)
{
	assert(curr);
	return curr->data;
}

void SLLSetData(sll_iterator curr, void *data)
{
	assert(curr);
	curr->data = data;
}

int SLLIteratorsIsEqual(sll_iterator iter1, sll_iterator iter2)
{
	assert(iter1 && iter2);
	if(iter1 == iter2)
	{
		return 1;
	}
	return 0;
}

sll_t *SLLCreate()
{
	sll_t *list = (sll_t *)malloc(sizeof(sll_t));
	if(list == NULL)
	{
		return NULL;
	}
	
	list->tail = (node_t *)malloc(sizeof(node_t));
	if(list->tail == NULL)
	{
		return NULL;
	}	
						
	list->tail->next = NULL;
	list->tail->data = (sll_t *)list;
	list->head = list->tail;

	return list;
}

sll_iterator SLLInsert(sll_iterator curr, void *new_data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	if(new_node == NULL)
	{
		return curr;
	}	
			
	assert(curr);
	new_node->next = curr->next;
	new_node->data = curr->data;
	curr->next = new_node;
	curr->data = new_data;
	
	if(new_node->next == NULL)
	{
		((sll_t *)new_node->data)->tail = new_node;
	}
	
	return curr;
}

sll_iterator SLLRemove(sll_iterator curr)					
{
	node_t *temp = curr->next;
	assert(curr);	
	if(curr->next == NULL)
	{
		return curr;
	}
	
	if((curr->next)->next == NULL)
	{
		((sll_t *)curr->next->data)->tail = curr;

	}
	
	curr->next = temp->next;
	curr->data = temp->data;
	temp->next = NULL;
	temp->data = NULL;
	free(temp);
		
	return curr;
}

size_t SLLCount(const sll_t *slist)
{
	int res = 1;
	assert(slist);
	return SLLForEach(slist->head, slist->tail, &res, NotDummy);
}

sll_iterator SLLFind(sll_iterator from, sll_iterator to,void *param, int (*match)(sll_iterator curr,void *param))
{
	assert(from && to);
	while(from != to)
	{
		if(match(from,param) == 1)
		{
			return from;
		}
		from = from->next;
	}
	
	return to;
}

int SLLForEach(sll_iterator from, sll_iterator to, void *param, int (*action)(sll_iterator curr,void *param))
{
	int res = 0;
	assert(from && to);	
	while(from!=to)
	{
		if(0 == action(from, param))
		{
			return 0;
		}
		++res;
		from = from->next;
	}
	
	return res;
}

void SLLDestroy(sll_t *slist)
{
	sll_iterator curr = slist->head;
	sll_iterator temp = curr;
	assert(slist);	
	while(curr != slist->tail)
	{
		curr->data = NULL;
		curr = curr->next;
		free(temp);
		temp = curr;
	}
	free(slist->tail);
	slist->tail = NULL;
	free(slist);
	slist = NULL;
	curr = NULL;
	temp = NULL;
}

sll_t *SLLAppend(sll_t *list1, sll_t *list2)
{
	if(list1->head == list1->tail && list2->head == list2->tail)
	{
		return NULL;
	}
	else if(list2->head == list2->tail)
	{
		return list1;
	}
	else if(list1->head == list1->tail)
	{
		return list2;
	}
	
	list1->tail->data = SLLGet(list2->head);
	list1->tail->next = list2->head->next;
	list1->tail = list2->tail; 
	list2->tail->data = list1;
	
	free(list2->head);
	list2->head = NULL;
	free(list2);
	list2 = NULL;
	
	return list1;
}




