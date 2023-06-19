#include <stdio.h>  /*printf*/
#include "linear_sort.h"
#include <stdlib.h> /*rand qsort*/

void TestCountingSort();
void TestRadixSort();

void PrintArr(int arr[], size_t size);

int main(int argc, char **argv)
{
    int arr[5000] = {0};
    size_t size = 5000;
    size_t i = 0;

    if(argc < 2)
    {
        fprintf(stderr, "Error, less then 2 elements where entered at compilation time.\n");
        exit(1);
    }

    switch (argv[1][0])
    {
    case 'c':
        while(i < size)
        {
            arr[i] = ((rand()%100) +1);
            ++i;
        }
        TestCountingSort();
        CountingSort(arr,size);
        PrintArr(arr,size);
        break;
    case 'r':
        while(i < size)
        {
            arr[i] = (rand()%(10000000-1));
            ++i;
        }
        TestRadixSort();
        RadixSort(arr, size);
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
    printf("\n\n");
}

void TestCountingSort()
{
    int arr[7] = {1,4,1,2,7,5,2};
    size_t size = 7;

    CountingSort(arr,size);

    PrintArr(arr,size);
}

void TestRadixSort()
{
    int arr[8] = {170,45,75,90,802,24,2,66};
    size_t size = 8;

    RadixSort(arr,size);

    PrintArr(arr,size);
}