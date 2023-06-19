/*********************************
 * Reviewer: 
 * Author: 
 * File Name: merge_quick.h
 * ******************************/

#include <stdio.h>  /*printf*/

#include "merge_quick.h"

int CompareInts(const void *data1, const void *data2)
{
    if(*(int *)data1 <= *(int *)data2)
    {
        return 1;
    }
    return 0;
}

int QuickCompareInts(const void *data1, const void *data2)
{
    if(*(int *)data1 < *(int *)data2)
    {
        return 1;
    }
    return 0;
}


int main()
{
    int arr[9] = {1,2,3,4,5,6,7,8,9};
    int arr_to_sort[9] = {2,6,4,-5,7,-1,-500,9,500};
    int arr_to_quick_sort[8] = {4,1,2,7,5,3,8,100};
    size_t size = 9;
    int data = 9;
    int res = 0;
    int i = 0;
    res = IterBinarySearch(arr, size, data);
    printf("res: %d\n", res);

    res = RecurBinarySearch(arr, size, data);
    printf("res: %d\n", res);

    res = MergeSort(arr_to_sort, size, sizeof(int), CompareInts);
    printf("res Merge: %d\n", res);
    for(i = 0; i < 9; ++i)
    {
        printf("%d\t", arr_to_sort[i]);
    }
    printf("\n");

    res = QuickSort(arr_to_quick_sort, 8, sizeof(int), QuickCompareInts);
    printf("res: %d\n", res);
    
    for(i = 0; i < 8; ++i)
    {
        printf("%d\t", arr_to_quick_sort[i]);
    }
    printf("\n");

    return 0;
}