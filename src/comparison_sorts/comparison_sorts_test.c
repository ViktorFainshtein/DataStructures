#include "comparison_sorts.h"
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*rand qsort*/

void TestBubble();
void TestSelect();
void TestInsert();

void PrintArr(int arr[], size_t size);

/*a cmp function for qsort()*/
int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

/*
in terminal use command: time ./a.out 'char' - for run time data of selected function 
*/

int main(int argc, char **argv)
{
    int arr[5000];
    size_t size = 5000;
    size_t i = 0;

    while(i < size)
    {
        arr[i] = rand()%5000;
        ++i;
    }

    if(argc < 2)
    {
        fprintf(stderr, "Error, less then 2 elements where entered at compilation time.\n");
        exit(1);
    }

    switch (argv[1][0])
    {
    case 'b':
        TestBubble();
        BubbleSort(arr,size);
        PrintArr(arr,size);
        break;
    case 'i':
        TestInsert();
        InsertionSort(arr,size);
        PrintArr(arr,size);
        break;
    case 's':
        TestSelect();
        SelectionSort(arr,size);
        PrintArr(arr,size);
        break;
    case 'q':
        qsort(arr,size,sizeof(int),cmpfunc);
        PrintArr(arr,size);
        break;
    default:
        fprintf(stderr, "No sorting function was found.\n");
        break;
    }

    return 0;
}

void PrintArr(int arr[], size_t size)
{
    size_t i = 0;
    while(i < size)
    {
        printf("%d\t",arr[i]);
        ++i;
    }
    printf("\n");
}

void TestBubble()
{
    int arr[5] = {5,1,4,2,8};
    size_t size = 5;

    printf("Before Bubble Sort:\n");
    PrintArr(arr,size);

    BubbleSort(arr,size);

    printf("After Bubble Sort:\n");
    PrintArr(arr,size);
}

void TestSelect()
{
    int arr[10] = {8,5,2,6,9,3,1,4,0,7};
    size_t size = 10;

    printf("Before Select Sort:\n");
    PrintArr(arr,size);

    SelectionSort(arr,size);

    printf("After Select Sort:\n");
    PrintArr(arr,size);
}

void TestInsert()
{
    int arr[8] = {6,5,3,1,8,7,2,4};
    size_t size = 8;

    printf("Before insertion Sort:\n");
    PrintArr(arr,size);

    InsertionSort(arr,size);

    printf("After insertion Sort:\n");
    PrintArr(arr,size);
}