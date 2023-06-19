/*********************************
 * Reviewer: Viktor Fainshtein
 * Author: Irit Ofir
 * File: sorted_list_test.c
 * ******************************/

#include <stdio.h> /*printf*/
#include <string.h> /*strcmp*/
#include "sorted_list.h" 

int CompareStrings(const void *str1, const void *str2)
{
    return strcmp((char *)str2, (char *)str1);
}

int CompareInts(const void *num1, const void *num2)
{
    return (*(int *)num2 - *(int *)num1);
}


int PrintInt(void *list_data, void *data)
{
    printf("%d\n", *(int *)list_data);
    (void)data;
    return 0;
}


void TestCreateDestroy()
{
    sorted_list_iterator_t iter = SortedListIterInit();
    sorted_list_iterator_t iter1 = SortedListIterInit();

    sorted_list_t *list = SortedListCreate(CompareStrings);

    iter = SortedListBegin(list);
    iter1 = SortedListEnd(list);

    if (1 != SortedListIsSameIter(iter, iter1))
    {
        printf("TestCreate failed (IsSame)\n");
    }

    if (1 != SortedListIsEmpty(list))
    {
        printf("TestCreate failed (IsEmpty)\n");
    }

    if (0 != SortedListSize(list))
    {
        printf("TestCreate failed (size)\n");
    }

    SortedListDestroy(list);
}

void TestInsert()
{
    sorted_list_t *list = SortedListCreate(CompareStrings);
    char *str = "123456789";

    SortedListInsert(list, "365");
    SortedListInsert(list, "120");
    SortedListInsert(list, "50");

    if (strcmp("120", (char *) SortedListGetData(SortedListBegin(list))))
    {
        printf("TestInsert failed\n");
    }

    if (strcmp("50", (char *) SortedListGetData(SortedListPrev(SortedListEnd(list)))))
    {
        printf("TestInsert failed\n");
    }

    str = SortedListPopFront(list);

    if (strcmp("120", str))
    {
        printf("TestInsert failed (PopFront)\n");
    }

    if (2 != SortedListSize(list))
    {
        printf("TestInsert failed (Size)\n");
    }

    str = SortedListPopBack(list);

    if (strcmp("50", str))
    {
        printf("TestInsert failed (PopBack)\n");
    }

    SortedListRemove(SortedListBegin(list));

    if (1 != SortedListIsEmpty(list))
    {
        printf("TestInsert failed (IsEmpty)\n");
    }

    SortedListDestroy(list);
}

int AddToInts(void *list_data, void *data)
{
    *(int *)list_data += *(int *)data;
    return 0;
}

int NotEleven(void *list_data, void *data)
{
    if (11 != *(int *)list_data)
    {
        *(int *)data +=1;
        return 0;
    }
    return *(int *)data;
}

void TestForEach()
{
    sorted_list_t *list = SortedListCreate(CompareInts);
    int array[] = {10, 20, 5, 17, -13, 0};
    int param = 1;
    size_t i = 0;
    int index_of_eleven = 0;

    while (sizeof(array) / sizeof(*array) > i)
    {
        SortedListInsert(list, array + i);
        ++i;
    }

    SortedListForEach(
        SortedListBegin(list),
        SortedListEnd(list),
        &param,
        AddToInts);

    if (-13 + param != *(int *)SortedListGetData(SortedListBegin(list)))
    {
        printf("TestForEach failed (AddToInts)\n");
    }

    index_of_eleven = SortedListForEach(
        SortedListBegin(list),
        SortedListEnd(list),
        &index_of_eleven,
        NotEleven);

    if (3 != index_of_eleven)
    {
        printf("TestForEach failed (NotEleven) %d\n", index_of_eleven);
    }

    SortedListDestroy(list);
}

void TestFind()
{
    sorted_list_t *list = SortedListCreate(CompareInts);
    sorted_list_iterator_t iter_from = SortedListIterInit();
    sorted_list_iterator_t iter_to = SortedListIterInit();
    sorted_list_iterator_t iter_test = SortedListIterInit();
    int test1 = 15;
    int test2 = 22;
    int array[] = {10, 20, 5, 17, -13, 0};
    size_t i = 0;

    while (sizeof(array) / sizeof(*array) > i)
    {
        SortedListInsert(list, array + i);
        ++i;
    }

    iter_from = SortedListFind(list, SortedListBegin(list), 
                               SortedListEnd(list), array + 5); 
    iter_to = SortedListFind(list, SortedListBegin(list), 
                             SortedListEnd(list), array + 1);

    /*SortedListForEach(SortedListBegin(list), SortedListEnd(list),
                      &i, PrintInt);*/

    if (0 != *(int *)SortedListGetData(iter_from))
    {
        printf("TestFind failed (find from) %d\n", *(array + 5));
    }

    /*if (20 != *(int *)SortedListGetData(iter_to))
    {
        printf("TestFind failed (find to)\n");
    }*/

    iter_test = SortedListFind(list, iter_from, iter_to, &test1);

    if(17 != *(int *)SortedListGetData(iter_test))
    {
        printf("TestFind failed (test 1)\n");
    }

    iter_test = SortedListFind(list, iter_from, iter_to, &test2);    

    if (!SortedListIsSameIter(iter_test, SortedListEnd(list)))
    {
        printf("TestFind failed (test 2)\n");
    }

    SortedListDestroy(list);
}

int IsGreaterThan(const void *list_data, const void *data)
{
    return (*(int *)list_data > *(int *)data);
}

void TestFindIf()
{
    sorted_list_t *list = SortedListCreate(CompareInts);
    sorted_list_iterator_t iter_from = SortedListIterInit();
    sorted_list_iterator_t iter_to = SortedListIterInit();
    sorted_list_iterator_t iter_test = SortedListIterInit();
    int test1 = 15;
    int test2 = 22;
    int array[] = {10, 20, 5, 17, -13, 0};
    size_t i = 0;

    while (sizeof(array) / sizeof(*array) > i)
    {
        SortedListInsert(list, (array + i));
        ++i;
    }
    
    iter_from = SortedListFind(list, SortedListBegin(list), 
                               SortedListEnd(list), array + 5); 
    iter_to = SortedListFind(list, SortedListBegin(list), 
                             SortedListEnd(list), array + 1);

    iter_test = SortedListFindIf(iter_from, iter_to, &test1, IsGreaterThan);

    if(17 != *(int *)SortedListGetData(iter_test))
    {
        printf("TestFindIf failed (test 1)\n");
    }

    iter_test = SortedListFindIf(iter_from, iter_to, &test2, IsGreaterThan);    

    if (!SortedListIsSameIter(iter_test, iter_to))
    {
        printf("TestFindIf failed (test 2)\n");
    }

    SortedListDestroy(list);
}

void TestMerge()
{
    sorted_list_t *list_src = SortedListCreate(CompareInts);
    sorted_list_t *list_dest = SortedListCreate(CompareInts);
    sorted_list_iterator_t curr = SortedListIterInit();
    int array1[] = {-1, 0, 0, 1, 3, 7, 19, 30};
    int array2[] = {0, 2, 4, 4, 5, 6, 21, 22, 24, 50};
    size_t i = 0;


    while (sizeof(array1) / sizeof(int) > i)
    {
        SortedListInsert(list_src, (array1 + i));
        ++i;
    }

    i = 0;
    while (sizeof(array2) / sizeof(int) > i)
    {
        SortedListInsert(list_dest, (array2 + i));
        ++i;
    }

    SortedListMerge(list_dest, list_src);
    
    curr = SortedListBegin(list_dest);
    while(!SortedListIsSameIter(curr, SortedListEnd(list_dest)))
    {
    	printf("%d\n", *(int *)SortedListGetData(curr));
    	curr = SortedListNext(curr);
    }

    /*SortedListForEach(SortedListBegin(list_dest), SortedListEnd(list_dest),
                      &i, PrintInt);*/

    for (curr = SortedListNext(SortedListBegin(list_dest)); 
         !SortedListIsSameIter(curr, SortedListEnd(list_dest));
         curr = SortedListNext(curr))
    {
        if (0 > CompareInts(SortedListGetData(SortedListPrev(curr)), 
                                           SortedListGetData(curr)))
        {
            printf("TestMerge failed\n");
        }
    }


    SortedListDestroy(list_dest);
    SortedListDestroy(list_src);
}

int main()
{
    TestCreateDestroy();
    TestInsert();
    TestForEach();
    TestFind();
    TestFindIf();
    TestMerge();
    return 0;
}
