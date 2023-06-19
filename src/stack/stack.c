/******************************
Reviewer: Irit Ofir 
Author: Viktor Fainshtein
File: stack.c
******************************/
#include <stddef.h>	/* size_t */
#include <stdlib.h>	/* malloc free*/
#include <stdio.h>	/* printf */
#include <assert.h>	/* assert */
#include <string.h>	/* memcpy */
#include "stack.h"	/*functions declarations and typedef of struct stack as stack_t*/

struct stack 
{
    char *stack;
    size_t element_size;
    size_t capacity;
    int size;
};

stack_t *StackCreate(size_t capacity, size_t  element_size)
{
	stack_t *stk = (stack_t *)malloc(sizeof(stack_t));
	if(!stk)
	{
		printf("stack pointer allocation error\n");
		return NULL;
	}
	stk->stack = (char *)malloc(capacity * element_size);
	if(!(stk->stack))
	{
		printf("stack array allocation error\n");
		free(stk);
		return NULL;
	}
	stk->capacity = capacity;
	stk->element_size = element_size;
	stk->size = 0;
	return stk;
}

void StackPush(stack_t *s, void *element_to_push)
{
	assert(s);
	assert(element_to_push);
	memcpy(s->stack + ((s->size) * (s->element_size)), element_to_push, s->element_size);
	s->size = s->size + 1;
}

void StackPop(stack_t *s)
{
	assert(s);
	s->size = s->size -1;
}

void StackPeek(stack_t *s, void *store_element)
{
	assert(s);
	assert(store_element);
	memcpy(store_element, s->stack + ((s->size -1) * (s->element_size)), s->element_size);
}

int StackIsEmpty(stack_t *s)
{	
	assert(s);
	return !(s->size);
}

void StackDestroy(stack_t *s)
{
	assert(s);
	free(s->stack);
	s->stack = NULL;
	free(s);
	s = NULL;
}

size_t StackCapacity(stack_t *s)
{
	assert(s);
	return s->capacity;
}

size_t StackSize(stack_t *s)
{
	assert(s);
	return s->size;
}








