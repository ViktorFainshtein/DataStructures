/*********************************
 * Reviewer: Yohai Azoulai
 * Author: Viktor Fainshtein		
 * File: sll_test.c
 * ******************************/
#include <stdio.h>	/* printf */
#include <assert.h>	/* assert */
#include "sll.h"

int IsEqualToParam(sll_iterator curr,void *param);

int AddOne(sll_iterator curr, void *param);

void TestInsert();

void TestRemove();

void TestDestroy();

void TestIsEqual();

void TestFind();

void TestForEach();

void TestNodeCount();

int main()
{
	TestInsert();
	TestRemove();
	TestDestroy();
	TestIsEqual();
	TestFind();
	TestForEach();
	TestNodeCount();

	return 0;
}

int IsEqualToParam(sll_iterator curr,void *param)
{
	if(SLLGet(curr) == param)
	{
		return 1;
	}
	return 0;
}

int AddOne(sll_iterator curr, void *param)					
{
	size_t res = 0;
	if(SLLGet(curr) == NULL && param)
	{
		return 0;
	}
	res = (size_t)SLLGet(curr) + (size_t)param;
	SLLSetData(curr, &res);
	return 1;
}

void TestInsert()
{
	sll_t *list = SLLCreate();
	sll_iterator curr = SLLBegin(list);
	size_t data1 = 8;
	size_t data2 = 10;
	size_t data3 = 12;
	
	printf("Before Inserting Into list 3 nodes, size of list = %ld\n", SLLCount(list));
	
	curr = SLLInsert(curr,&data1);
	curr = SLLInsert(curr,&data2);
	curr = SLLInsert(curr,&data3);
	
	printf("After Inserting Into list 3 nodes, size of list = %ld\n", SLLCount(list));

	SLLDestroy(list);
}

void TestRemove()
{
	sll_t *list = SLLCreate();
	sll_iterator curr = SLLBegin(list);
	size_t data1 = 8;
	size_t data2 = 10;
	size_t data3 = 12;
	
	curr = SLLInsert(curr,&data1);
	curr = SLLInsert(curr,&data2);
	curr = SLLInsert(curr,&data3);
	printf("Befor Remove, num of elements in the list is: %ld\n", SLLCount(list));
	curr = SLLNext(curr);
	curr = SLLNext(curr);
	curr = SLLRemove(curr);
	printf("After removing the last element, num of element is: %ld\n", SLLCount(list));
	
	SLLDestroy(list);
}

void TestDestroy()
{
	sll_t *list = SLLCreate();
	sll_iterator curr = SLLBegin(list);
	size_t data1 = 8;
	size_t data2 = 10;

	curr = SLLInsert(curr,&data1);
	curr = SLLInsert(curr,&data2);
	
	SLLDestroy(list);
}

void TestIsEqual()								
{
	sll_t *list = SLLCreate();
	sll_iterator curr1 = SLLBegin(list);
	sll_iterator curr2 = SLLBegin(list);
	size_t data1 = 8;
	size_t data2 = 8;
	size_t res = 0;
	
	res = SLLIteratorsIsEqual(curr1, curr2);
	if(1 == res)
	{
		printf("both iterators point to the same node in the list\n");
	}
	else
	{
		printf("both iterators point to a diffrent node in the list\n");
	}
	
	curr1 = SLLInsert(curr1,&data1);
	curr1 = SLLInsert(curr1,&data2);
	curr2 = SLLNext(curr2);
	
	res = SLLIteratorsIsEqual(curr1, curr2);
	if(1 == res)
	{
		printf("both iterators point to the same node in the list\n");
	}
	else
	{
		printf("both iterators point to a diffrent node in the list\n");
	}
	
	SLLDestroy(list);
}

void TestFind()
{
	sll_t *list = SLLCreate();
	sll_iterator from = SLLBegin(list);
	sll_iterator to = SLLBegin(list);
	size_t insert1 = 8;
	size_t insert2 = 10;
	size_t insert3 = 12;
	size_t insert4 = 20;
	
	from = SLLInsert(from,&insert1);
	from = SLLInsert(from,&insert2);
	from = SLLInsert(from,&insert3);
	from = SLLInsert(from,&insert4);
	
	to = SLLEnd(list);
	
	from = SLLFind(from,to,&insert4,IsEqualToParam);
	printf("Looking for value 20 in list.\n");
	if(insert4 == *(size_t *)SLLGet(from))
	{
		printf("Node with the same value was found\n");	
	}
	else
	{
		printf("Node was not found\n");
	}
	
	SLLDestroy(list);
}

void TestForEach()
{
	sll_t *list = SLLCreate();
	sll_iterator from = SLLBegin(list);
	sll_iterator to = SLLBegin(list);
	size_t res = 0;
	size_t add = 1;
	size_t insert1 = 8;
	size_t insert2 = 10;
	size_t insert3 = 12;
	
	from = SLLInsert(from,&insert1);
	from = SLLInsert(from,&insert2);
	from = SLLInsert(from,&insert3);
	
	to = SLLEnd(list);
	
	res = SLLForEach(from, to, &add, AddOne);
	
	if(0 == res)
	{
		printf("ForEach Failed\n");
	}

	SLLDestroy(list);
}

void TestNodeCount()
{
	sll_t *list = SLLCreate();
	sll_iterator from = SLLBegin(list);
	size_t res = 0;
	size_t insert1 = 8;
	size_t insert2 = 10;
	size_t insert3 = 12;
	
	from = SLLInsert(from,&insert1);
	from = SLLInsert(from,&insert2);
	from = SLLInsert(from,&insert3);
	
	res = SLLCount(list);
	if(3 != res)
	{
		printf("Error: Number of nodes counted is %ld insted of 3\n", res);
	}
	
	SLLDestroy(list);
}

















