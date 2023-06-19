/* *******************************
 * Reviewer: Irit Ofir
 * Author: Viktor Fainshtein
 * File: sorted_list.h
 * ******************************/
 
#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include "dll.h"
#include <stddef.h>	/* size_t */

/*
positiv if data2 should be before, negative if data1 should be before, zero if equal - the new data should be before. 
O(1)
*/
typedef int(*sorted_list_compare_func_t)(const void *data1, const void *data2, void *user_param);		
/*
non_zero if match, zero otherwise 
O(1)
*/
typedef int(*sorted_list_is_match_func_t)(const void *list_data, const void *data);	 
/*
user comparison function for creating a list
O(1)
*/
typedef int(*sorted_list_action_func_t)(void *list_data, void *data);

typedef struct sorted_list sorted_list_t;
typedef struct sorted_list_iterator sorted_list_iterator_t;

/* description: create a new sort list
   params: compare function
   return value: pointer to created sort list
   undefined behavior:
   complexity: O(1)  */ 
sorted_list_t *SortedListCreate(sorted_list_compare_func_t compare_func, void *user_param); 

/* description: set the sort list iterator to default
   return value: the set sort list iterator
   undefined behavior:
   complexity: O(1)  */ 
sorted_list_iterator_t SortedListIterInit();			

/* description: Destroys sorted list
   params: pointer to sorted list
   undefined behavior:
   complexity: O(n)  */ 
void SortedListDestroy(sorted_list_t *list);

/* description: count the number of nodes in sorted list
   params: pointer to sorted list
   return value: number of nodes in sorted list
   undefined behavior:
   complexity: O(n)  */ 
size_t SortedListSize(const sorted_list_t *list); 				

/* description: check if list is empty
   params: pointer to sorted list
   return value: 0 in case the list is not empty, non 0 otherwise
   undefined behavior:
   complexity: O(1)  */ 
int SortedListIsEmpty(const sorted_list_t *list); 				

/* description: return the first node in the sorted list
   params: pointer to sorted list
   return value: iterator to the first node
   undefined behavior:
   complexity: O(1)  */ 
sorted_list_iterator_t SortedListBegin(const sorted_list_t *list);			

/* description: return the end of the sorted list
   params: pointer to sorted list
   return value: iterator to end of list
   undefined behavior:
   complexity: O(1)  */ 
sorted_list_iterator_t SortedListEnd(const sorted_list_t *list);		

/* description: return iterator to the next node in sorted list
   params: iterator iter
   return value: iterator to next node
   undefined behavior:
   complexity: O(1)  */ 
sorted_list_iterator_t SortedListNext(sorted_list_iterator_t iter);	

/* description: return iterator to the previuse node in sorted list
   params: iterator iter
   return value: iterator to previuse
   undefined behavior:
   complexity: O(1)  */ 
sorted_list_iterator_t SortedListPrev(sorted_list_iterator_t iter);			

/* description: check if two iterators point to the same node in sorted list
   params: iterator iter1, iterator iter2
   return value: 0 in case they point to diffrent nodes, non 0 otherwise
   undefined behavior:
   complexity: O(1)  */ 
int SortedListIsSameIter(sorted_list_iterator_t iter1, sorted_list_iterator_t iter2);

/* description: return the data stored in the node
   params: iterator iter
   return value: poionter to the data
   undefined behavior:
   complexity: O(1)  */ 
void *SortedListGetData(sorted_list_iterator_t iter); 

/* description: create a new node with recived data and insert it into the list 
		in the correct place based on lists function
   params: pointer to sorted list, pointer to data
   return value: iterator to the inserted node
   undefined behavior:
   complexity: O(n)  */ 
sorted_list_iterator_t SortedListInsert(sorted_list_t *list, void *data); 

/* description: remove the first node
   params: pointer to sorted list
   return value: data of the removed node
   undefined behavior:
   complexity: O(1)  */ 
void *SortedListPopFront(sorted_list_t *list);					

/* description: remove the last node
   params: pointer to sorted list
   return value: data of the removed node
   undefined behavior:
   complexity: O(1)  */ 
void *SortedListPopBack(sorted_list_t *list);

/* description: remove the sent node from list
   params: iterator to the sorted list
   return value: iterator to the next node in sorted list
   undefined behavior:
   complexity: O(1)  */ 
sorted_list_iterator_t SortedListRemove(sorted_list_iterator_t curr);

/* description: for each node preform the recived function
   params: iterator from, iterator to, pointer to data, address to action function
   return value: 0 in case of success, a number of the node that the function failed (non 0)
   undefined behavior:
   complexity: O(n)  */ 
int SortedListForEach(sorted_list_iterator_t from, sorted_list_iterator_t to, void *param, action_func_t action_func);	

/* description: merge two list into one
   params: destenation list, source list
   return value: destenation list
   undefined behavior:
   complexity: O(n+m)  */ 
void SortedListMerge(sorted_list_t *dest_list, sorted_list_t *src_list); 

/* description: look for the node in the list via comparison function by comparing with data
   params: pointer to sorted list, iterator from, iterator to, pointer to data
   return value: End of list in case data was not found, iterator to the data otherwise
   undefined behavior:
   complexity: O(n)  */ 
sorted_list_iterator_t SortedListFind(sorted_list_t *list, sorted_list_iterator_t from, sorted_list_iterator_t to, const void *data);

/* description: look for the node in the list via recived function by comparing with data
   params: iterator from, iterator to, pointer to data, pointer to is_match_func
   return value: iterator to in case none found, iterator from otherwise
   undefined behavior:
   complexity: O(n)  */ 
sorted_list_iterator_t SortedListFindIf(sorted_list_iterator_t from, sorted_list_iterator_t to, const void *data, sorted_list_is_match_func_t is_match_func);

struct sorted_list_iterator
{
	dll_iterator_t iter;
	#ifndef NDEBUG
	sorted_list_t *list;
	#endif
};


#endif
