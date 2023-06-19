/* *******************************
 * Reviewer: Irit Ofir
 * Author: Viktor Fainshtein
 * File: sorted_list.c
 * ******************************/

#include <stdlib.h>	/* malloc free */
#include <assert.h>	/* assert */
#include "sorted_list.h"

struct sorted_list
{
	dll_t *list;
	void *user_param;
	sorted_list_compare_func_t compare_func;
};

sorted_list_iterator_t SortedListIterInit(void)
{
	sorted_list_iterator_t iter;
	iter.iter = NULL;
	return iter;
}

sorted_list_t *SortedListCreate(sorted_list_compare_func_t compare_func, void *user_param)
{
	sorted_list_t *list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	if(list == NULL)
	{
		return NULL;
	}
	
	list->list = DListCreate();
	if(list->list == NULL)
	{
		free(list);
		return NULL;
	}
	
	list->compare_func = compare_func;
	list->user_param = user_param;

	return list;
}

void SortedListDestroy(sorted_list_t *list)
{
	assert(list);
	DListDestroy(list->list);
	list->list = NULL;
	list->compare_func = NULL;
	free(list);
	list = NULL;
}
				
size_t SortedListSize(const sorted_list_t *list)
{
	assert(list);
	return DListSize(list->list);
}
				
int SortedListIsEmpty(const sorted_list_t *list)
{
	assert(list);
	return DListIsEmpty(list->list);
}			

sorted_list_iterator_t SortedListBegin(const sorted_list_t *list)
{
	sorted_list_iterator_t iter;
	assert(list);
	iter.iter = DListBegin(list->list);
	
	#ifndef NDEBUG
    	iter.list = (sorted_list_t *)list;
    	#endif 
	
	return iter;
}
	
sorted_list_iterator_t SortedListEnd(const sorted_list_t *list)
{
	sorted_list_iterator_t iter;
	assert(list);
	iter.iter = DListEnd(list->list);

	#ifndef NDEBUG
    	iter.list = (sorted_list_t *)list;
    	#endif 
	
	return iter;
}	

sorted_list_iterator_t SortedListNext(sorted_list_iterator_t iter)
{
	iter.iter = DListNext(iter.iter);
	return iter;
}	
		
sorted_list_iterator_t SortedListPrev(sorted_list_iterator_t iter)
{
	iter.iter = DListPrev(iter.iter);
	return iter;
}			

int SortedListIsSameIter(sorted_list_iterator_t iter1, sorted_list_iterator_t iter2)
{
	if(iter1.iter == iter2.iter)
	{
		return 1;
	}
	
	return 0;
}

void *SortedListGetData(sorted_list_iterator_t iter)
{
	return (DListGetData(iter.iter));
}					

sorted_list_iterator_t SortedListInsert(sorted_list_t *list, void *data)
{
	sorted_list_iterator_t curr = SortedListBegin(list);
	sorted_list_iterator_t last = SortedListEnd(list);
	int res = 0;
	assert(list);
	
	if(SortedListIsEmpty(list))
	{
		curr.iter = DListInsert(list->list, curr.iter, data);
		return curr;
	}
	
	res = list->compare_func(SortedListGetData(curr), data, list->user_param);
	while(!(SortedListIsSameIter(curr, last)) && (res > 0))
	{
		curr.iter = DListNext(curr.iter);
		if(SortedListIsSameIter(curr, last))
		{
			break;
		}
		res = list->compare_func(SortedListGetData(curr), data, list->user_param);
	}
	
	curr.iter = DListInsert(list->list, curr.iter, data);
	return curr;
}

void *SortedListPopFront(sorted_list_t *list)
{
	assert(list);
	return DListPopFront(list->list);
}				


void *SortedListPopBack(sorted_list_t *list)
{
	assert(list);
	return DListPopBack(list->list);
}

sorted_list_iterator_t SortedListRemove(sorted_list_iterator_t curr)
{
	curr.iter = DListRemove(curr.iter);
	return curr;
}

int SortedListForEach(sorted_list_iterator_t from, sorted_list_iterator_t to, void *param, action_func_t action_func)
{
	size_t res = 0;
	int action = 0;
	
	assert(param);
	while(!SortedListIsSameIter(from, to))
	{
		action = action_func(SortedListGetData(from), param);
		if(action != 0) 
		{
			return action;
		}
		++res;
	}
	
	return 0; 
}		

void SortedListMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
	sorted_list_iterator_t iter_dest = SortedListBegin(dest_list);
	sorted_list_iterator_t iter_from = SortedListBegin(src_list);
	sorted_list_iterator_t iter_to = SortedListBegin(src_list);
	int res = 0;
	assert(dest_list && src_list);
	
	while((!SortedListIsSameIter(iter_dest, SortedListEnd(dest_list))) || (!SortedListIsSameIter(iter_from, SortedListEnd(src_list))))
	{
		res = dest_list->compare_func(SortedListGetData(iter_dest), SortedListGetData(iter_from), NULL);
		if(res <= 0)
		{	
			while((res <= 0) && (!SortedListIsSameIter(iter_to, SortedListEnd(src_list))))
			{
				iter_to = SortedListNext(iter_to);
				res = dest_list->compare_func(SortedListGetData(iter_dest), SortedListGetData(iter_to), NULL);
			}
			DListSplice(iter_dest.iter, iter_from.iter, iter_to.iter);
			iter_dest = SortedListNext(iter_dest);
		}
		else if(res > 0)
		{
			iter_dest = SortedListNext(iter_dest);
		}
		iter_from = SortedListBegin(src_list);
		iter_to = SortedListBegin(src_list);
	}
} 	

sorted_list_iterator_t SortedListFind(sorted_list_t *list, sorted_list_iterator_t from, sorted_list_iterator_t to, const void *data)
{
	assert(list);
	while(!SortedListIsSameIter(from, to))
	{
		if(list->compare_func(SortedListGetData(from), data, list->user_param) < 0)
		{
			return from;
		}
		from = SortedListNext(from);
	}
	
	return SortedListEnd(list);
}

sorted_list_iterator_t SortedListFindIf(sorted_list_iterator_t from, sorted_list_iterator_t to, const void *data, sorted_list_is_match_func_t is_match_func)
{
	while(!SortedListIsSameIter(from, to))
	{
		if(is_match_func(SortedListGetData(from), data) == 1)
		{
			return from;
		}
		from = SortedListNext(from);
	}
	
	return to;
}






















