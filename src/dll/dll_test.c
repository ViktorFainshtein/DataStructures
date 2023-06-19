/* *******************************
 * Reviewer: Daniel Natan
 * Author: Viktor Fainshtein		
 * File: dll_test.c
 * ******************************/

#include "dll.h"
#include <stdio.h>	/* printf */


int IsEqualToParam(const void *list_data,const void *data)
{
	if(list_data == data)
	{
		return 1;
	}
	return 0;
}

int Add(void *list_data, void *data)					
{
	size_t ld = *(size_t *)list_data;
	size_t d = *(size_t *)data;

	if(list_data == NULL && data)
	{
		return 0;
	}
	*((size_t *)list_data) = ld +d;
	return 1;
}

void TestCreate();
void TestSize();
void TestIsEmpty();
void TestBegin();
void TestEnd();
void TestNextPrev();
void TestIsSameIter();
void TestForEach();
void TestFind();
void TestMultiFind();
void TestRemove();
void TestPushFront();
void TestPushBack();
void TestPopFront();
void TestPopBack();
void TestSplice();

int main()
{
	TestCreate();
	TestSize();
	TestIsEmpty();
	TestBegin();
	TestEnd();
	TestNextPrev();
	TestIsSameIter();
	TestForEach();
	TestFind();
	TestMultiFind();
	TestRemove();
	TestPushFront();
	TestPushBack();
	TestPopFront();
	TestPopBack();
	TestSplice();

	return 0;
}

void TestCreate()
{
	dll_t *list = DListCreate();
	dll_iterator_t begin = DListBegin(list);
	dll_iterator_t end = DListEnd(list);
	
	if(list == NULL || begin == NULL || end == NULL)
	{
		printf("Faild creating a list\n");
	}
	
	if(begin != end)
	{
		printf("List created incorrectly\n");
	}
	
	DListDestroy(list);
	begin = NULL;
	end = NULL;	
}

void TestSize()
{
	dll_t *list = DListCreate();	
	dll_iterator_t begin = DListBegin(list);
	size_t num_1 = 1;
	size_t num_2 = 2;
	size_t num_3 = 3;
	
	if(0 != DListSize(list))
	{
		printf("Error, size was not 0\n");
	}
	
	begin = DListInsert(list, begin, &num_1);
	begin = DListInsert(list, begin, &num_2);
	begin = DListInsert(list, begin, &num_3);
	
	if(3 != DListSize(list))
	{
		printf("Error, size was not 3\n");
	}
	
	DListDestroy(list);
	begin = NULL;
}

void TestIsEmpty()
{
	dll_t *list = DListCreate();	
	dll_iterator_t begin = DListBegin(list);
	size_t num_1 = 1;
	size_t num_2 = 2;
	size_t num_3 = 3;
	
	if(0 != DListSize(list))
	{
		printf("Error, list was not empty(size check)\n");
	}
	
	if(!DListIsEmpty(list))
	{
		printf("Error, list was not empty(isEmpty check)\n");
	}
	
	begin = DListInsert(list, begin, &num_1);
	begin = DListInsert(list, begin, &num_2);
	begin = DListInsert(list, begin, &num_3);
	
	if(0 == DListSize(list))
	{
		printf("Error, list was empty(size check)\n");
	}
	
	if(DListIsEmpty(list))
	{
		printf("Error, list was empty(isEmpty check)\n");
	}
	
	DListDestroy(list);
	begin = NULL;
}

void TestBegin()
{
	dll_t *list = DListCreate();	
	dll_iterator_t begin = DListBegin(list);
	size_t num_1 = 1;
	size_t num_2 = 2;
	size_t num_3 = 3;
	
	if(begin != DListEnd(list))
	{
		printf("Begin is not the same as tail\n");
	}
	
	DListInsert(list, begin, &num_1);
	DListInsert(list, begin, &num_2);
	DListInsert(list, begin, &num_3);
	
	begin = DListBegin(list);
	
	if(num_1 != *(size_t *)DListGetData(begin))
	{
		printf("Begin is not the start of the list(after Insert)\n");
	}
	
	DListPushFront(list, &num_3);
	begin = DListBegin(list);
	
	if(num_3 != *(size_t *)DListGetData(begin))
	{
		printf("Begin is not the start of the list(after pusAfter)\n");
	}
	
	DListDestroy(list);
	begin = NULL;
}

void TestEnd()
{
	dll_t *list = DListCreate();	
	dll_iterator_t end = DListEnd(list);
	size_t num_1 = 1;
	size_t num_2 = 2;
	size_t num_3 = 3;
	
	if(end != DListBegin(list))
	{
		printf("End is not the same as tail\n");
	}
	
	DListInsert(list, end, &num_1);
	DListInsert(list, end, &num_2);
	DListInsert(list, end, &num_3);
	
	end = DListEnd(list);
	
	if(num_3 == *(size_t *)DListGetData(end))
	{
		printf("End is not the end of the list(after Insert)\n");
	}
	
	DListPushBack(list, &num_1);
	end = DListEnd(list);
	
	if(num_1 == *(size_t *)DListGetData(end))
	{
		printf("End is not the end of the list(after pusBack)\n");
	}
	
	DListDestroy(list);
	end = NULL;
}

void TestNextPrev()
{
	dll_t *list = DListCreate();	
	dll_iterator_t begin = DListBegin(list);
	dll_iterator_t end = DListEnd(list);
	size_t num_1 = 1;
	size_t num_2 = 2;
	
	DListInsert(list, begin, &num_1);
	DListInsert(list, begin, &num_2);

	begin = DListBegin(list);
	begin = DListNext(begin);

	if(*(size_t *)DListGetData(begin) != num_2)
	{
		printf("Error, next failed to move to the correct node\n");
	}
	
	end = DListPrev(end);
	
	if(*(size_t *)DListGetData(end) != num_2)
	{
		printf("Error, prev failed to move to the correct node\n");
	}
	
	if(begin != end)
	{
		printf("begin and prev do not point to the same node\n");
	}

	DListDestroy(list);
	begin = NULL;
	end = NULL;
}

void TestIsSameIter()
{
	dll_t *list = DListCreate();	
	dll_iterator_t begin = DListBegin(list);
	dll_iterator_t end = DListEnd(list);
	size_t num_1 = 1;
	size_t num_2 = 2;
	
	if(DListIsSameIter(begin, end) == 0)
	{
		printf("Not the same iterators(on empty list)\n");
	}
	
	DListInsert(list, begin, &num_1);
	DListInsert(list, begin, &num_2);
	
	begin = DListBegin(list);	
	end = DListEnd(list);
	
	if(DListIsSameIter(begin, end))
	{
		printf("begin and end were found as same iter after inserts\n");
	}
	
	begin = DListNext(begin);
	end = DListPrev(end);
		
	if(DListIsSameIter(begin, end) == 0)
	{
		printf("Same iterators were found as diffrent iterators\n");
	}
	
	DListDestroy(list);
	begin = NULL;
	end = NULL;	
}

void TestForEach()
{
	dll_t *list = DListCreate();	
	dll_iterator_t begin = DListBegin(list);
	dll_iterator_t end = DListEnd(list);
	size_t num_1 = 1;
	size_t num_2 = 2;

	DListInsert(list, begin, &num_1);
	DListInsert(list, begin, &num_2);
	
	DListForEach(DListBegin(list), DListEnd(list), &num_1, Add);
	
	end = DListPrev(end);
	begin = DListBegin(list);
	
	if(*(size_t *)DListGetData(begin) != 2)
	{
		printf("For each didnt change the data correctly for the fist element\n");
	}
	
	if(*(size_t *)DListGetData(end) != 4)
	{
		printf("For each didnt change the data correctly for the last element\n");
	}


	DListDestroy(list);
	begin = NULL;
	end = NULL;
}

void TestFind()
{
	dll_t *list = DListCreate();	
	dll_iterator_t iter = NULL;
	size_t num_1 = 1;
	size_t num_2 = 2;

	DListInsert(list, DListBegin(list), &num_1);
	DListInsert(list, DListEnd(list), &num_2);
	
	iter = DListFind(DListBegin(list), DListEnd(list), &num_2, IsEqualToParam);

	if(iter != DListPrev(DListEnd(list)))
	{
		printf("Error, did not found 2 in the list\n");
	}
	
	DListDestroy(list);
	iter = NULL;
}

void TestMultiFind()
{
	dll_t *list = DListCreate();
	dll_t *dest = DListCreate();
	size_t res = 0;	
	size_t num_1 = 1;
	size_t num_2 = 2;

	DListInsert(list, DListBegin(list), &num_1);
	DListInsert(list, DListEnd(list), &num_2);
	DListInsert(list, DListEnd(list), &num_1);
	
	res = DListMultiFind(DListBegin(list), DListEnd(list), dest, &num_1, IsEqualToParam);

	if(res != 2)
	{
		printf("Error, multiFind was supposed to find 2 nodes\n");
	}
	
	DListDestroy(list);
	DListDestroy(dest);
		
}

void TestRemove()
{
	dll_t *list = DListCreate();
	dll_iterator_t iter1 = NULL;
	dll_iterator_t iter2 = NULL;	
	size_t num_1 = 1;
	size_t num_2 = 2;	
	
	DListInsert(list, DListBegin(list), &num_1);
	DListInsert(list, DListEnd(list), &num_2);
	DListInsert(list, DListEnd(list), &num_1);	
	
	iter1 = DListEnd(list);
	iter2 = DListRemove(DListPrev(DListEnd(list)));
	
	if(iter1 != iter2)
	{
		printf("Faild to remove the node before the end of the list\n");
	}
	
	if(2 != DListSize(list))
	{
		printf("size is not equal to 2 after removig 1 node: %ld \n", DListSize(list));
	}
	
	
	DListDestroy(list);
	iter1 = NULL;
	iter2 = NULL;	
}

void TestPushFront()
{
	dll_t *list = DListCreate();
	dll_iterator_t iter1 = NULL;
	dll_iterator_t iter2 = NULL;
	size_t num_1 = 1;
	size_t num_2 = 2;
	size_t num_3 = 3;
		
	iter2 = DListPushFront(list, &num_1);
	iter2 = DListPushFront(list, &num_2);
	iter2 = DListPushFront(list, &num_3);
	
	iter1 = DListBegin(list);
	
	if(*(size_t *)DListGetData(iter1) != 3)
	{
		printf("Push front failed to insert the data in correct order\n");
	}
	
	if(iter1 != iter2)
	{
		printf("Push front failed, not the same iterators\n");
	}
	
	DListDestroy(list);
	iter1 = NULL;	
	iter2 = NULL;
}

void TestPushBack()
{
	dll_t *list = DListCreate();
	dll_iterator_t iter1 = NULL;
	dll_iterator_t iter2 = NULL;
	size_t num_1 = 1;
	size_t num_2 = 2;
	size_t num_3 = 3;
	
		
	iter2 = DListPushBack(list, &num_1);
	iter2 = DListPushBack(list, &num_2);
	iter2 = DListPushBack(list, &num_3);
	
	iter1 = DListPrev(DListEnd(list));
	
	if(*(size_t *)DListGetData(iter1) != 3)
	{
		printf("Push back failed to insert the data in correct order\n");
	}
	
	if(iter1 != iter2)
	{
		printf("Push front failed, not the same iterators\n");
	}
	
	DListDestroy(list);
	iter1 = NULL;	
	iter2 = NULL;
}

void TestPopFront()
{
	dll_t *list = DListCreate();
	size_t num_1 = 1;
	size_t num_2 = 2;
	size_t num_3 = 3;
	size_t res = 0;
		
	DListPushFront(list, &num_1);
	DListPushFront(list, &num_2);
	DListPushFront(list, &num_3);
	
	res = *(size_t *)DListPopFront(list);
	
	if(res != 3)
	{
		printf("Poped the incorrect node(bad return value)\n");
	}
	
	if(2 != DListSize(list))
	{
		printf("Faild to pop the first node\n");
	}
	
	DListDestroy(list);	
}

void TestPopBack()
{
	dll_t *list = DListCreate();
	size_t num_1 = 1;
	size_t num_2 = 2;
	size_t num_3 = 3;
	size_t res = 0;
		
	DListPushFront(list, &num_1);
	DListPushFront(list, &num_2);
	DListPushFront(list, &num_3);
	
	res = *(size_t *)DListPopBack(list);
	
	if(res != 1)
	{
		printf("Poped the incorrect node(bad return value)\n");
	}
	
	if(2 != DListSize(list))
	{
		printf("Faild to pop the last node\n");
	}
	
	DListDestroy(list);
}

void TestSplice()
{
	dll_t *list = DListCreate();
	dll_t *dest = DListCreate();
	dll_iterator_t begin = DListBegin(list);
	size_t num_ins = 2;
	size_t num_front = 1;
	size_t num_back = 3;
	
	begin = DListInsert(list, begin, &num_ins);
	DListPushFront(list, &num_front);
	DListPushBack(list, &num_back);
	
	begin = DListBegin(list);
	
	while(begin != DListEnd(list))
	{
		printf("value at list before splice: %ld\n", *(size_t *)DListGetData(begin));
		begin = DListNext(begin);
	}
	
	begin = DListBegin(list);
	begin = DListNext(begin);
	
	DListSplice(DListEnd(dest) ,begin, DListEnd(list));
	
	begin = DListBegin(dest);
	
	while(begin != DListEnd(dest))
	{
		printf("value at dest after: %ld\n", *(size_t *)DListGetData(begin));
		begin = DListNext(begin);
	}
	
	begin = DListBegin(list);
	
	while(begin != DListEnd(list))
	{
		printf("value at list after: %ld\n", *(size_t *)DListGetData(begin));
		begin = DListNext(begin);
	}
	
	DListDestroy(list);
	DListDestroy(dest);
	begin = NULL;
}





