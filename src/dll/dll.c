/* *******************************
 * Reviewer: Daniel Natan
 * Author: Viktor Fainshtein		
 * File: dll.c
 * ******************************/

#include "dll.h"
#include <assert.h>	/* assert */
#include <stdlib.h>	/* malloc free */

struct dll
{
	struct dll_node *head;
	struct dll_node *tail;
};

struct dll_node
{
	void *data;
	struct dll_node *next;
	struct dll_node *prev;
};

static int AddOne(void *list_data, void *param)
{
	int p = *(size_t *)param;
	assert(list_data && param);
	if(list_data == NULL || param == NULL)
	{
		return 0;
	}
	*((int *)param) = p + 1;
	return 1;
}

 
dll_t *DListCreate(void)
{
	dll_t *list = (dll_t *)malloc(sizeof(dll_t));
	if(list == NULL)
	{
		return NULL;
	}
	
	list->tail = (struct dll_node *)malloc(sizeof(struct dll_node));
	if(list->tail == NULL)
	{
		free(list);
		return NULL;
	}
	
	list->head = (struct dll_node *)malloc(sizeof(struct dll_node));
	if(list->head == NULL)
	{
		free(list);
		return NULL;
	}	
						
	list->tail->next = NULL;
	list->tail->prev = list->head;
	list->head->next = list->tail;
	list->head->prev = NULL;
	
	list->tail->data = (dll_t *)list;
	list->head->data = (dll_t *)list;

	return list;
}

void DListDestroy(dll_t *dlist)
{
	dll_iterator_t curr = dlist->head;
	dll_iterator_t temp = curr;
	assert(dlist);	
	while(curr != dlist->tail)
	{
		curr->data = NULL;
		curr->prev = NULL;
		curr = curr->next;
		free(temp);
		temp = curr;
	}
	free(dlist->tail);
	dlist->tail = NULL;
	free(dlist);
	dlist = NULL;
	curr = NULL;
}

size_t DListSize(const dll_t *dlist)
{
	int res = 0;
	assert(dlist);
	if(DListForEach(DListBegin(dlist), DListEnd(dlist), &res, AddOne) == res)
	{
		return res;
	}
	return 0;
}

int DListIsEmpty(const dll_t *dlist)
{
	assert(dlist);
	return ((dlist->head)->next == dlist->tail);
}

dll_iterator_t DListBegin(const dll_t *dlist)
{
	assert(dlist);
	return ((dlist->head)->next);
}

dll_iterator_t DListEnd(const dll_t *dlist)
{
	assert(dlist);
	return dlist->tail;
}

dll_iterator_t DListNext(dll_iterator_t curr)
{
	return curr->next;
}

dll_iterator_t DListPrev(dll_iterator_t curr)
{	
	return curr->prev;
}

int DListIsSameIter(dll_iterator_t first, dll_iterator_t second)
{
	assert(first && second);
	return (first == second);
}

void* DListGetData(dll_iterator_t curr)
{
	assert(curr);
	return curr->data;
}

dll_iterator_t DListPushFront(dll_t *dlist, void *data)
{
	assert(dlist);
	return DListInsert(dlist, (dlist->head)->next, data);

}

dll_iterator_t DListPushBack(dll_t *dlist, void *data)
{
	assert(dlist);
	return DListInsert(dlist, dlist->tail, data);
}

void *DListPopFront(dll_t *dlist)
{
	void *temp = DListGetData((dlist->head)->next);
	assert(dlist);
	DListRemove((dlist->head)->next);
	return temp;
}

void *DListPopBack(dll_t *dlist)
{
	void *temp = DListGetData((dlist->tail)->prev);
	assert(dlist);
	DListRemove((dlist->tail)->prev);
	return temp;
}

dll_iterator_t DListInsert(dll_t *dlist, dll_iterator_t curr, void *data)
{
	struct dll_node *new_node = (struct dll_node *)malloc(sizeof(struct dll_node));
	if(new_node == NULL)
	{
		return dlist->tail;
	}	
	
	assert(dlist);
	assert(curr);
	assert(data);
	
	new_node->next = curr;
	new_node->prev = curr->prev;
	new_node->data = data;
	(curr->prev)->next = new_node;
	curr->prev = new_node;
	
	return new_node;
}

dll_iterator_t DListRemove(dll_iterator_t curr)
{
	dll_iterator_t temp = curr->next;
	assert(curr);	
	
	(curr->next)->prev = curr->prev;
	(curr->prev)->next = curr->next;
	curr->data = NULL;
	curr->next = NULL;
	curr->prev = NULL;
	free(curr);
	curr = NULL;
		
	return temp;
}

dll_iterator_t DListSplice(dll_iterator_t where, dll_iterator_t begin, dll_iterator_t end)
{
	dll_iterator_t p_from = begin->prev;
	dll_iterator_t p_where = where->prev;
	
	assert(where);
	assert(begin);
	assert(end);
	
	p_where->next = begin;
	where->prev = end->prev;
	(end->prev)->next = where;
	end->prev = p_from;
	p_from->next = end;
	begin->prev = p_where;
	
	p_from = NULL;
	p_where = NULL;
	
	return where->prev;
}


int DListForEach(dll_iterator_t from, dll_iterator_t to, void *param, action_func_t func)
{
	int res = 0;
	assert(from && to);
	assert(param);	
	while(from!=to)
	{
		if(0 == func(DListGetData(from), param))
		{
			return -1;
		}
		else
		{
			++res;
		}
		from = from->next;
	}
	
	return res;
}

dll_iterator_t DListFind(dll_iterator_t from, dll_iterator_t to, const void *data, is_match_t func)
{
	assert(from && to);
	assert(data);
	while(from != to)
	{
		if(func(DListGetData(from),data) == 1)
		{
			return from;
		}
		from = from->next;
	}
	
	return to;
}

int DListMultiFind(dll_iterator_t from, dll_iterator_t to, dll_t *dlist_dest, const void *data, is_match_t func)
{
	int res = 0;
	assert(from && to);
	assert(data);
	while(from != to)
	{
		if(func(DListGetData(from),data) == 1)
		{
			if(DListPushBack(dlist_dest, DListGetData(from)) == NULL)
			{
				return -1;
			}
			++res;
		}
		from = from->next;
	}
	
	return res;
}
  

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
