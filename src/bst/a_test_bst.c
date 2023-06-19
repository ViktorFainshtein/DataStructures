/*********************************
 * Reviewer: Nofar Melamed
 * Author: Avigail Millatiner		
 * File: test_bst.c
 * ******************************/
#include <stdio.h>/*size_t*/
#include <string.h>/*strcpy*/
#include "bst.h"


static int count_func(void *bst_data, void *counter);

/*tests func*/
void TestCreate();
void TestIntPrevNext2();
void ForEachTest();

int main ()
{
    TestCreate();
	TestIntPrevNext2();
	ForEachTest();

	printf("the end ~(˘▾˘~)\n");
    return 0;
}

/*service func*/

static int IntCompare(const void *num1 , const void *num2, void* param)
{
    (void )param;
    return *(int *)num2 - *(int *)num1;
}


/*tests func*/

void TestCreate()
{
    bst_t *bst = NULL;

    printf("___ TestCreate ___\n");
    bst = BSTCreate(IntCompare, NULL);
    BSTDestroy(bst);
    return ;
}


void TestIntPrevNext2()
{
    bst_t *bst = NULL;
    bst_iterator_t iter;
    int arr[]={11,9,6,45,3,8};
    int brr[]={3,6,8,9,11,45};
    int val=0, i=0;

    printf("___ TestIntPrevNext2 ___\n");

    bst = BSTCreate(IntCompare, NULL);

	for(i=0;i<6;++i)
	{
	   BSTInsert(bst,&arr[i]);
	}
	
	iter=BSTBegin(bst);
	for(i=0;i<6;++i)
	{
		val=*(int*)BSTGetData(iter);
		if(val != brr[i])
		{
			printf("error, got %d, expected %d\n", val, brr[i]);
		}
		iter=BSTNext(iter);
	}  
    BSTDestroy(bst);
    return ;
}


void ForEachTest()
{
	bst_t *bst = NULL;
    int arr[]={11,9,27,45,7,8};
    int counter=0,size=0, i=0;

    printf("___ ForEachTest ___\n");

    bst = BSTCreate(IntCompare, NULL);

	if(0 != size)
	{
		printf("size error, expected 0 got %d\n",size);
	}

	for(i=0;i<6;++i)
	{
	   BSTInsert(bst,&arr[i]);
	}
	BSTForEach(bst,count_func,&counter);
	if(6 != counter)
	{
		printf("count error, expected 6, got %d\n",counter);
	}

	size=BSTSize(bst);
	if(6 != size)
	{
		printf("size error, expected 6, got %d\n",size);
	}
    BSTDestroy(bst);
    return ;
}

static int count_func(void *bst_data, void *counter)
{
	(void)bst_data;
	*(int*)counter=*(int*)counter+1;
	return 0;
}


















