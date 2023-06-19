/* *******************************
 * Reviewer: Daniel Natan
 * Author: Viktor Fainshtein
 * File: dll.h
 * ******************************/
#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h>	/* size_t */

typedef struct dll dll_t;
typedef struct dll_node *dll_iterator_t;

typedef int (*action_func_t)(void *list_data, void *param);
typedef int (*is_match_t)(const void *list_data, const void *data);

/* description: creates a new doubley list
   params: 
   return value: pointer to the created list, NULL in case of failure
   undefined behavior:
   complexity: O(1)  */ 
dll_t *DListCreate(void);

/* description: destroy a list
   params: pointer to a list
   undefined behavior: 
   complexity: O(n)  */ 
void DListDestroy(dll_t *dlist);

/* description: retruns the number of nodes in a list 
   params: pointer to a list
   return value: length of the list
   undefined behavior: 
   complexity: O(n)  */ 
size_t DListSize(const dll_t *dlist);

/* description: check if a list is empty
   params: pointer to a list
   return value: 0 in case the list is not empty, none 0 otherwise 
   undefined behavior: 
   complexity: O(1)  */ 
int DListIsEmpty(const dll_t *dlist);

/* description: returns the head of a list
   params: pointer to a list
   return value: the first node in the list, end of list in case of empty list
   undefined behavior: 
   complexity: O(1)  */ 
dll_iterator_t DListBegin(const dll_t *dlist);

/* description: returns the end of a list
   params: pointer to a list
   return value: the end node in the list
   undefined behavior:
   complexity: O(1)  */ 
dll_iterator_t DListEnd(const dll_t *dlist);

/* description: returns the next node 
   params: dll iterator 
   return value: dll iterator to the next node
   undefined behavior:
   complexity: O(1)  */ 
dll_iterator_t DListNext(dll_iterator_t curr);

/* description: returns the previuos node 
   params: dll iterator
   return value: dll iterator to the previus node
   undefined behavior:
   complexity: O(1)  */ 
dll_iterator_t DListPrev(dll_iterator_t curr);

/* description: compares if two iterators are the same
   params: dll iterator first, dll iterator second
   return value: 1 in case of same pointers, 0 otherwise
   undefined behavior:
   complexity: O(1)  */ 
int DListIsSameIter(dll_iterator_t first, dll_iterator_t second);

/* description: returns data of the recived node
   params: dll iterator
   return value: address of the node data
   undefined behavior:	end of list
   complexity: O(1)  */ 
void* DListGetData(dll_iterator_t curr);

/* description: insert a new node to the start of the list
   params: pointer to list, pointer to data
   return value: dll iterator to the inserted node
   undefined behavior:
   complexity: O(1)  */ 
dll_iterator_t DListPushFront(dll_t *dlist, void *data);

/* description: insert a new node before the end of the list
   params: pointer to list, pointer to data
   return value: dll iterator to the inserted node
   undefined behavior:
   complexity: O(1)  */ 
dll_iterator_t DListPushBack(dll_t *dlist, void *data);

/* description: removes the first node in the list
   params: pointer to list
   return value: data of the removed node
   undefined behavior:
   complexity: O(1)  */ 
void *DListPopFront(dll_t *dlist);

/* description: removes the last node in the list
   params: pointer to list
   return value: data of the removed node
   undefined behavior:
   complexity: O(1)  */ 
void *DListPopBack(dll_t *dlist);

/* description: create a new node and insert it into the list before the currnet node
   params: pointer to list, dll iterator, pointer to data
   return value: the inserted node, end of list in case of failure
   undefined behavior:
   complexity: O(1)  */ 
dll_iterator_t DListInsert(dll_t *dlist, dll_iterator_t curr, void *data);

/* description: removes a node from the list
   params: dll iterator
   return value: end of list in case end of list was sent, 
   		 the next node after the removed node otherwise
   undefined behavior:
   complexity: O(1)  */ 
dll_iterator_t DListRemove(dll_iterator_t curr);

/* description: splices from begin to end and concate to where 
   params: dll iterator where, dll iterator begin, dll iterator end
   return value: dll iterator to the previus node of where after splicing
   undefined behavior:
   complexity: O(1)  */ 
dll_iterator_t DListSplice(dll_iterator_t where, dll_iterator_t begin, dll_iterator_t end); 

/* description: apllies the given function to each node in given range(from - to)
   params: dll iterator from, dll iterator to, pointer to param, address of function
   return value: -1 in case matching faild, 0 in case of no match was found , none 0 otherwise
   undefined behavior:
   complexity: O(n)  */ 
int DListForEach(dll_iterator_t from, dll_iterator_t to, void *param, action_func_t func);

/* description: lookes for a node in range(from-to) based on recived function
   params: dll iterator from, dll iterator to, pointer to param, address of function
   return value: dll iterator in case node found, to otherwise
   undefined behavior:
   complexity: O(n)  */ 
dll_iterator_t DListFind(dll_iterator_t from, dll_iterator_t to, const void *data, is_match_t func); 

/* description: look for multiple nodes based of recived function and insert them into recived list
   params: dll iterator from, dll iterator to, pointer to list, pointer to param, address of function
   return value: 0 in case nodes not found, none 0 otherwise, -1 in case of failure
   undefined behavior:
   complexity: O(n)  */ 
int DListMultiFind(dll_iterator_t from, dll_iterator_t to, dll_t *dlist_dest, const void *data, is_match_t func);

#endif
