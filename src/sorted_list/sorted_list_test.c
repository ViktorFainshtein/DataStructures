/* *******************************
 * Reviewer: Irit Ofir
 * Author: Viktor Fainshtein
 * File: sorted_list_test.c
 * ******************************/

#include "sorted_list.h"
#include <stdio.h>	/* printf */


/* positive if data2 should be before data1, 
   negative if data1 should be before data2, 
   zero if equal - the new data should be before. */
/*int CompareMax(const void *data1, const void *data2)
{
	if(*(size_t *)data1 > *(size_t *)data2)
	{
		return 1;
	}
	else if(*(size_t *)data1 < *(size_t *)data2)
	{
		return -1;
	}
	
	return 0;
}*/

/* positiv if data2 should be before data1, 
   negative if data1 should be before data2, 
   zero if equal - the new data should be before. */
/*int CompareMin(const void *data1, const void *data2)
{
	if(*(size_t *)data1 < *(size_t *)data2)
	{
		return 1;
	}
	else if(*(size_t *)data1 > *(size_t *)data2)
	{
		return -1;
	}
	
	return 0;
}*/
/*
int Action(void *list_data, void *data)
{
	if(list_data == NULL || data == NULL)
	{
		return 1;
	}

	*((size_t *)list_data) = *(size_t *)list_data + *(size_t *)data;

	return 0;
}

int IsEqual(const void *list_data, const void *data)
{
	if(*(size_t *)list_data == *(size_t *)data)
	{
		return 1;
	}
	
	return 0;
}
*/
/*
void TestCreate();
void TestDestroy();
void TestSize();
void TestListBegin();
void TestEnd();
void TestListNext();
void TestListPrev();
void TestIsSameIter();
void TestGetData();
void TestPopFront();
void TestPopBack();
void TestIsEmpty();
void TestInsert();
void TestRemove();
void TestForEach();
void TestMerge();
void TestFind();
void TestFindIf();
*/
int main()
{	
	/*TestCreate();
	TestDestroy();
	TestSize();
	TestListBegin();
	TestEnd();
	TestListNext();
	TestListPrev();
	TestIsSameIter();
	TestGetData();
	TestPopFront();
	TestPopBack();
	TestIsEmpty();
	TestInsert();
	TestRemove();	
	TestForEach();
	TestMerge();
	TestFind();
	TestFindIf();*/
	
	return 0;
}
/*
void TestCreate()
{
	sorted_list_t *list = SortedListCreate(CompareMin);	

	if(list == NULL)
	{
		printf("Faild to create a list!\n");
	}


	SortedListDestroy(list);
}

void TestDestroy()
{
	sorted_list_t *list = SortedListCreate(CompareMin);	
	size_t num1 = 8;
	size_t num2 = 6;
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);	

	SortedListDestroy(list);
}

void TestSize()
{
	sorted_list_t *list = SortedListCreate(CompareMin);	
	size_t num1 = 8;
	size_t num2 = 6;
	
	if(0 != SortedListSize(list))
	{
		printf("Wrong list size(not 0)!\n");
	}	
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);	

	if(2 != SortedListSize(list))
	{
		printf("Wrong list size(not 2)!\n");
	}	

	SortedListDestroy(list);
}

void TestListBegin()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	size_t num1 = 8;
	size_t num2 = 6;
	
	if(SortedListBegin(list).iter != SortedListEnd(list).iter)
	{
		printf("Begin was not set correctly(diffrent then end on empty list)\n");
	}	
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);
	
	if(SortedListBegin(list).iter == SortedListEnd(list).iter)
	{
		printf("Begin was not set correctly(same as end)\n");
	}	

	SortedListDestroy(list);
}

void TestEnd()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	size_t num1 = 8;
	size_t num2 = 6;
	
	if(SortedListBegin(list).iter != SortedListEnd(list).iter)
	{
		printf("End was not set correctly(diffrent then head on empty list)\n");
	}	
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);
	
	if(SortedListBegin(list).iter == SortedListEnd(list).iter)
	{
		printf("End was not set correctly(same as head)\n");
	}	

	SortedListDestroy(list);
}

void TestListNext()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	sorted_list_iterator_t iter_head = SortedListIterInit();
	sorted_list_iterator_t iter_tail = SortedListIterInit();
	size_t num1 = 8;
	size_t num2 = 6;
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);
	
	iter_head = SortedListBegin(list);
	iter_tail = SortedListEnd(list);
	
	iter_head = SortedListNext(iter_head);
	iter_head = SortedListNext(iter_head);
	
	if(iter_head.iter != iter_tail.iter)
	{
		printf("Next failed to reach end\n");
	}

	SortedListDestroy(list);
}

void TestListPrev()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	sorted_list_iterator_t iter_head = SortedListIterInit();
	sorted_list_iterator_t iter_tail = SortedListIterInit();
	size_t num1 = 8;
	size_t num2 = 6;
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);
	
	iter_head = SortedListBegin(list);
	iter_tail = SortedListEnd(list);
	
	iter_tail = SortedListPrev(iter_tail);
	iter_tail = SortedListPrev(iter_tail);
	
	if(iter_head.iter != iter_tail.iter)
	{
		printf("Prev failed to reach Start\n");
	}

	SortedListDestroy(list);
}

void TestIsSameIter()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	sorted_list_iterator_t iter_head = SortedListIterInit();
	sorted_list_iterator_t iter_tail = SortedListIterInit();
	size_t num1 = 8;
	size_t num2 = 6;

	iter_head = SortedListBegin(list);
	iter_tail = SortedListEnd(list);

	if(iter_head.iter != iter_tail.iter)
	{
		printf("Was supposed to point to the same address on empty list\n");
	}
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);
	
	iter_head = SortedListBegin(list);
	iter_tail = SortedListEnd(list);
	
	iter_tail = SortedListPrev(iter_tail);
	
	if(iter_head.iter == iter_tail.iter)
	{
		printf("Was supposed to point to diffrent location after insertion\n");
	}
	
	iter_tail = SortedListPrev(iter_tail);
	
	if(iter_head.iter != iter_tail.iter)
	{
		printf("Was supposed to point to same location after insertion\n");
	}

	SortedListDestroy(list);
}

void TestGetData()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	sorted_list_iterator_t iter_head = SortedListIterInit();
	size_t num1 = 8;
	size_t num2 = 6;
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);
	
	iter_head = SortedListBegin(list);
	
	if(*(size_t *)SortedListGetData(iter_head) == 8)
	{
		printf("Wrong value was found at first node\n");
	}
	
	iter_head = SortedListNext(iter_head);
	
	if(*(size_t *)SortedListGetData(iter_head) == 6)
	{
		printf("Wrong value was found at second node\n");
	}
	
	SortedListDestroy(list);
}

void TestPopFront()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	size_t num1 = 8;
	size_t num2 = 6;
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);
	
	if(*(size_t *)SortedListPopFront(list) != 6)
	{
		printf("Wrong value was poped at first pop\n");
	}
	
	if(*(size_t *)SortedListPopFront(list) != 8)
	{
		printf("Wrong value was poped at second pop\n");
	}
	
	if(SortedListSize(list) != 0)
	{
		printf("list not size is not 0 after 2 pops\n");
	}
	
	SortedListDestroy(list);
}

void TestPopBack()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	size_t num1 = 8;
	size_t num2 = 6;
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);
	
	if(*(size_t *)SortedListPopBack(list) != 8)
	{
		printf("Wrong value was poped from the back(not 8)\n");
	}
	
	if(*(size_t *)SortedListPopBack(list) != 6)
	{
		printf("Wrong value was poped from the back(not 6)\n");
	}
	
	if(SortedListSize(list) != 0)
	{
		printf("list not size is not 0 after 2 pops\n");
	}
	
	SortedListDestroy(list);
}

void TestIsEmpty()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	sorted_list_iterator_t iter_head = SortedListIterInit();
	sorted_list_iterator_t iter_tail = SortedListIterInit();
	size_t num1 = 8;
	size_t num2 = 6;

	iter_head = SortedListBegin(list);
	iter_tail = SortedListEnd(list);

	if(iter_head.iter != iter_tail.iter)
	{
		printf("list is not empty on empty list based on pointers\n");
	}
	
	if(SortedListIsEmpty(list) != 1)
	{
		printf("list is not empy\n");
	}
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);
	
	if(SortedListSize(list) == 0)
	{
		printf("list was not supposed to be empty by size\n");
	}
	
	if(SortedListIsEmpty(list))
	{
		printf("list was not supposed to be empty\n");
	}

	SortedListDestroy(list);
}

void TestInsert()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	sorted_list_iterator_t iter_head = SortedListIterInit();
	sorted_list_iterator_t iter_tail = SortedListIterInit();
	size_t num1 = 8;
	size_t num2 = 6;
	
	SortedListInsert(list, &num1);
	iter_head = SortedListBegin(list);

	if(*(size_t *)SortedListGetData(iter_head) != 8)
	{
		printf("first node is not 8\n");
	}
	
	if(SortedListSize(list) != 1)
	{
		printf("list size is not 1 after one insertion\n");
	}

	SortedListInsert(list, &num2);
	iter_head = SortedListBegin(list);

	if(*(size_t *)SortedListGetData(iter_head) != 6)
	{
		printf("first node is not 6\n");
	}

	iter_tail = SortedListEnd(list);
	iter_tail = SortedListPrev(iter_tail);

	if(*(size_t *)SortedListGetData(iter_tail) != 8)
	{
		printf("last node is not 8\n");
	}

	if(SortedListSize(list) != 2)
	{
		printf("list size is not 2 after second insertion\n");
	}

	SortedListDestroy(list);
}

void TestRemove()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	sorted_list_iterator_t iter_head = SortedListIterInit();
	size_t num1 = 8;
	size_t num2 = 6;
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);	
	
	iter_head = SortedListBegin(list);
	iter_head = SortedListRemove(iter_head);
	
	if(*(size_t *)SortedListGetData(iter_head) != 8)
	{
		printf("Removed the wrong node\n");
	}
	
	if(SortedListSize(list) != 1)
	{
		printf("did not remove a node\n");
	}
	
	iter_head = SortedListRemove(iter_head);
	
	if(SortedListSize(list) != 0)
	{
		printf("did not remove a node(list size not 0)\n");
	}
	
	if(SortedListIsEmpty(list)!= 1)
	{
		printf("did not remove a node(list not empty)\n");
	}
	
	
	SortedListDestroy(list);
}

void TestForEach()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	sorted_list_iterator_t iter_head = SortedListIterInit();
	sorted_list_iterator_t iter_tail = SortedListIterInit();
	size_t num1 = 8;
	size_t num2 = 6;
	size_t num_action = 1;
	int res = 0;

	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);

	iter_head = SortedListBegin(list);
	iter_tail = SortedListEnd(list);
	
	res = SortedListForEach(iter_head, iter_tail, &num_action, Action);
	
	if(res != 0)
	{
		printf("ForEach Faild at point: %d\n", res);
	}
	
	iter_head = SortedListBegin(list);
	
	if(*(size_t *)SortedListGetData(iter_head) != 7)
	{
		printf("ForEach did not work correctly(first node not 7)\n");
	}
	
	iter_head = SortedListNext(iter_head);
	
	if(*(size_t *)SortedListGetData(iter_head) != 9)
	{
		printf("ForEach did not work correctly(first node not 9)\n");
	}
	
	
	SortedListDestroy(list);	
}

void TestMerge()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	sorted_list_t *src_list = SortedListCreate(CompareMin);
	sorted_list_iterator_t iter_head = SortedListIterInit();
	size_t num1 = 8;
	size_t num2 = 6;
	size_t num3 = 7;
	size_t num4 = 8;
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);

	SortedListInsert(src_list, &num3);
	SortedListInsert(src_list, &num4);
	
	SortedListMerge(list, src_list);
	
	if(SortedListSize(list) != 4 || SortedListSize(src_list) != 0)
	{
		printf("Merge size is incorrect\n");
	}
	
	iter_head = SortedListBegin(list);

	if(*(size_t *)SortedListGetData(iter_head) != 6)
	{
		printf("first node value is incorrect(not 6)\n");
	}
	
	iter_head = SortedListNext(iter_head);

	if(*(size_t *)SortedListGetData(iter_head) != 7)
	{
		printf("second node value is incorrect(not 7)\n");
	}
	
	iter_head = SortedListNext(iter_head);

	if(*(size_t *)SortedListGetData(iter_head) != 8)
	{
		printf("third node value is incorrect(not 8)\n");
	}
	
	iter_head = SortedListNext(iter_head);

	if(*(size_t *)SortedListGetData(iter_head) != 8)
	{
		printf("forth node value is incorrect(not 8)\n");
	}
	
	
	SortedListDestroy(list);	
	SortedListDestroy(src_list);		
}

void TestFind()
{
	sorted_list_t *list = SortedListCreate(CompareMin);
	sorted_list_iterator_t iter = SortedListIterInit();
	size_t num1 = 8;
	size_t num2 = 6;
	size_t num3 = 1;
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);
	SortedListInsert(list, &num3);		
	
	iter = SortedListFind(list, SortedListBegin(list), SortedListEnd(list), &num2);
	
	if(*(size_t *)SortedListGetData(iter) != 8)
	{
		printf("iter value was supposed to be 8\n");
	}
	
	SortedListDestroy(list);	
}

void TestFindIf()
{
	sorted_list_t *list = SortedListCreate(CompareMin);	
	sorted_list_iterator_t iter_head = SortedListIterInit();
	sorted_list_iterator_t iter_tail = SortedListIterInit();
	
	size_t num1 = 8;
	size_t num2 = 6;	
	size_t num_find = 8;
	size_t num_lost = 10;
	
	SortedListInsert(list, &num1);
	SortedListInsert(list, &num2);

	iter_head = SortedListBegin(list);
	iter_tail = SortedListEnd(list);
	
	iter_head = SortedListFindIf(iter_head, iter_tail, &num_find, IsEqual);
	
	if(*(size_t *)SortedListGetData(iter_head) != 8)
	{
		printf("Did not found the node\n");
	}
	
	iter_head = SortedListFindIf(iter_head, iter_tail, &num_lost, IsEqual);
	iter_tail = SortedListEnd(list);
	
	if(iter_head.iter != iter_tail.iter)
	{
		printf("Returned the Wrong node\n");
	}
	
	SortedListDestroy(list);	
}
*/

























