/*********************************
 * Reviewer: Daniel Binyamin
 * Author: Viktor Fainshtein
 * File Name: circular_buffer_test.c
 * ******************************/
#include "circular_buffer.h"
#include <stdio.h>	/* printf */
#include <stdlib.h>	/* free malloc */

void TestCreate();

void TestDestroy();

void TestFreeSpace();

void TestBufSiz();

void TestIsEmpty();

void TestReadWrite();

int main()
{
	TestCreate();

	TestDestroy();

	TestFreeSpace();

	TestBufSiz();

	TestIsEmpty();

	TestReadWrite();
	
	return 0;
}

void TestCreate()
{
	size_t capacity = 10;
	circ_buff_t *c_buff = NULL;
	c_buff = CircBuffCreate(capacity);
	
	if(c_buff == NULL)
	{
		printf("Failed to create Buffer\n");
	}
	
	if(CircBuffFreeSpace(c_buff) != capacity)
	{
		printf("Buffer free space is less then allocated\n");
	}
	
	if(CircBuffBufSiz(c_buff) != capacity)
	{
		printf("Buffer capacity is diffrent then the initial capacity\n");
	}
	
	if(CircBuffIsEmpty(c_buff) == 0)
	{
		printf("Buffer not empty after creation\n");
	}
	
	CircBuffDestroy(c_buff);
	c_buff = NULL;
}

void TestDestroy()
{
	size_t capacity = 10;
	circ_buff_t *c_buff = NULL;
	c_buff = CircBuffCreate(capacity);

	CircBuffDestroy(c_buff);	
	c_buff = NULL;
}

void TestFreeSpace()
{
	size_t capacity = 10;
	circ_buff_t *c_buff = NULL;
	char *write_arr = (char *)malloc(11);
	int i = 0;
	c_buff = CircBuffCreate(capacity);

	
	while(10 != i)
	{
		*(write_arr+i) = 'a'+i;	
		++i;
	}
	
	CircBuffWrite(c_buff, write_arr, 5);
	
	if(CircBuffFreeSpace(c_buff) != 5)
	{
		printf("After writing 5 bytes, only %ld byten were writen\n",
			 CircBuffFreeSpace(c_buff));
	}
	
	CircBuffWrite(c_buff, write_arr+5, 5);
	
	if(CircBuffFreeSpace(c_buff) != 0)
	{
		printf("After writing 5 more bytes, only %ld byten were writen\n"
			, CircBuffFreeSpace(c_buff));
	}
	
	CircBuffWrite(c_buff, write_arr, 5);
	
	if(CircBuffFreeSpace(c_buff) != 0)
	{
		printf("Wrote into a full buffer\n");
	}
	
	CircBuffDestroy(c_buff);
	free(write_arr);
	c_buff = NULL;
	write_arr = NULL;
}

void TestBufSiz()
{
	size_t capacity = 10;
	circ_buff_t *c_buff = NULL;
	c_buff = CircBuffCreate(capacity);
	
	if(CircBuffBufSiz(c_buff) != capacity)
	{
		printf("Buffer capacity is diffrent then the initial capacity\n");
	}
	
	CircBuffDestroy(c_buff);
	c_buff = NULL;
}

void TestIsEmpty()
{
	size_t capacity = 10;
	circ_buff_t *c_buff = NULL;
	char *write_arr = (char *)malloc(11);
	int i = 0;
	c_buff = CircBuffCreate(capacity);
	
	if(CircBuffIsEmpty(c_buff) == 0)
	{
		printf("Buffer is not empty\n");
	}
	
	while(10 != i)
	{
		*(write_arr+i) = 'a'+i;	
		++i;
	}
	
	CircBuffWrite(c_buff, write_arr, 5);
	
	if(CircBuffIsEmpty(c_buff) == 1)
	{
		printf("Buffer is empty after writing\n");
	}
	
	CircBuffDestroy(c_buff);
	free(write_arr);
	c_buff = NULL;
	write_arr = NULL;
}

void TestReadWrite()
{
	size_t capacity = 10;
	circ_buff_t *c_buff = CircBuffCreate(capacity);
	char *read_arr = (char *)malloc(11);
	char *write_arr = (char *)malloc(11);
	int i = 0;
	
	while(10 != i)
	{
		*(write_arr + i) = 'a' + i;
		*(read_arr + i) = '0' + i;
		++i;
	}
	*(write_arr+i) = '\0';
	*(read_arr+i) = '\0';
	
	CircBuffWrite(c_buff, write_arr, 10);
	CircBuffRead(c_buff, read_arr, 10);
	printf("%s\n", read_arr);
	
	i = 0;
	while(10 != i)
	{
		*(write_arr+i) = '0'+i;	
		++i;
	}
	
	CircBuffWrite(c_buff, write_arr, 10);
	CircBuffRead(c_buff, read_arr, 3);
	printf("%s\n", read_arr);
	
	CircBuffWrite(c_buff, write_arr+3, 3);
	CircBuffRead(c_buff, read_arr, 8);
	printf("%s\n", read_arr);		
	
	CircBuffDestroy(c_buff);
	free(read_arr);
	free(write_arr);
	c_buff = NULL;
	read_arr = NULL;
	write_arr = NULL;
}






