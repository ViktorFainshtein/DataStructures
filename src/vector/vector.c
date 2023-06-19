/******************************
Reviewer: Daniel Natan
Author: Viktor Fainshtein
File: vector.h
******************************/
#include <stdio.h>	/* printf */
#include <stddef.h>	/* size_t */
#include <stdlib.h>	/* realloc free*/
#include <assert.h>	/* assert */
#include <string.h>	/* memcpy */
#include "vector.h"	/* typedef of struct vector and functions declaration*/

enum RetVal { SUCCESS, FAIL};

struct vector
{
    char* vector;
    size_t element_size;
    size_t capacity;
    int size;
};

static int Resize(vector_t *vec)
{
	vec->capacity *= 2;
	vec->vector = (char *)realloc(vec->vector, (vec->capacity * vec->element_size));
	if(vec->vector == NULL)
	{
		return FAIL;
	}
	return SUCCESS;
}

vector_t *VectorCreate(size_t capacity, size_t element_size)
{
	vector_t *vec = (vector_t *)malloc(sizeof(vector_t));
	if(!vec)
	{
		printf("vector pointer allocation error\n");
		return NULL;
	}
	vec->vector = (char *)malloc(capacity * element_size);
	if(!(vec->vector))
	{
		printf("vector array allocation error\n");
		free(vec);
		return NULL;
	}
	vec->capacity = capacity;
	vec->element_size = element_size;
	vec->size = 0;
	
	return vec;
}

void VectorDestroy(vector_t *vector)
{
	assert(vector);
	assert(vector->vector);
	free(vector->vector);
	vector->vector = NULL;
	free(vector);
	vector = NULL;
}

int VectorPush(vector_t *vector, void *element_to_push)
{
	int res = 0;
	assert(vector);
	assert(vector->vector);
	assert(element_to_push); 
	memcpy(vector->vector + ((vector->size) * (vector->element_size)), element_to_push, vector->element_size);
	vector->size = vector->size + 1;
	if((size_t)vector->size == vector->capacity)
	{
		res = Resize(vector);
	}
	return res;
}

void VectorPop(vector_t *vector)
{
	assert(vector);
	--vector->size;
}

int VectorIsEmpty(vector_t *vector)
{
	assert(vector);
	return !(vector->size);
}

size_t VectorSize(vector_t *vector)
{
	assert(vector);
	return vector->size;
}

size_t VectorCapacity(vector_t *vector)
{
	assert(vector);
	return vector->capacity;
}

void *VectorGetAccess(vector_t *vector, int index)
{
	assert(vector);
	return (vector->vector + (index * vector->element_size));
}

int VectorShrinkToFit(vector_t *vector)
{
	assert(vector);
	vector->vector = (char *)realloc(vector->vector,(vector->size * vector->element_size)+1);
	if(vector->vector == NULL)
	{
		return FAIL;
	}
	vector->capacity = vector->size+1;
	return SUCCESS;
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	assert(vector);
	vector->vector = (char *)realloc(vector->vector,(new_capacity * vector->element_size));
	if(vector->vector == NULL)
	{
		return FAIL;
	}
	vector->capacity = new_capacity;
	return SUCCESS;
}



































