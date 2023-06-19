/*********************************
 * Reviewer: Daniel Binyamin
 * Author: Viktor Fainshtein
 * File Name: circular_buffer.c
 * ******************************/
#include "circular_buffer.h"
#include <stdlib.h>	/* free malloc */
#include <assert.h>	/* assert */

struct circular_buffer
{
	size_t capacity;
	size_t size;
	size_t head;
	char *buffer;	
};

circ_buff_t *CircBuffCreate(size_t capacity)
{
	circ_buff_t *c_buff = (circ_buff_t *)malloc(sizeof(circ_buff_t) + capacity);
	if(!c_buff)
	{
		return NULL;
	}
	c_buff->capacity = capacity;
	c_buff->size = 0;
	c_buff->head = 0;
	c_buff->buffer = (char *)c_buff + sizeof(circ_buff_t);
	
	return c_buff;
}

void CircBuffDestroy(circ_buff_t *c_buff)
{
	assert(c_buff);
	c_buff->capacity = 0;
	c_buff->size = 0;
	c_buff->head = 0;
	c_buff->buffer = NULL;
	free(c_buff);
	c_buff = NULL;
}

size_t CircBuffFreeSpace(const circ_buff_t *c_buff)
{
	assert(c_buff);
	return (c_buff->capacity - c_buff->size);
}

size_t CircBuffBufSiz(const circ_buff_t *c_buff)
{
	assert(c_buff);
	return c_buff->capacity;
}

int CircBuffIsEmpty(const circ_buff_t *c_buff)
{
	assert(c_buff);
	if(0 == c_buff->size)
	{
		return 1;
	}
	
	return 0;
}

ssize_t CircBuffRead(circ_buff_t *c_buff, void *stream, size_t count)
{
	size_t i = 0;
	assert(c_buff);
	assert(stream);
	while(count && c_buff->size)
	{
		*((char *)stream + i) = *(c_buff->buffer + c_buff->head);
		++i;
		--count;
		--c_buff->size;
		++c_buff->head;
		c_buff->head %= c_buff->capacity;
	}
	
	return i;
}

ssize_t CircBuffWrite(circ_buff_t *c_buff, const void *stream, size_t count)
{
	size_t i = 0;
	assert(c_buff);
	assert(stream);
	while(count && CircBuffFreeSpace(c_buff))
	{
		*(c_buff->buffer + ((c_buff->head + c_buff->size) % c_buff->capacity)) = *((char *)stream + i);
		++i;
		--count;
		++c_buff->size;
	}
	
	return i;
}




