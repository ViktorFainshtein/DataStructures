/*********************************
 * Reviewer: 
 * Author: Viktor Fainshtein
 * File Name: comparison_sorts.c
 * ******************************/
#include <assert.h>
#include "comparison_sorts.h"

void BubbleSort(int arr[], size_t size)
{
    size_t i = 0, j = 0;
    int swap = 0;   /*can remove the swap var and insted do mathematical swap*/

    assert(arr);

    for(i = 0; i < size; ++i)
    {
        for(j = 0; j < (size - 1); ++j)
        {
            if(arr[j] > arr[j+1])
            {
                swap = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = swap;
            }
        }
    }
}

void SelectionSort(int arr[], size_t size)
{
    size_t i = 0, j = 0;
    int min_index = 0;
    int min_value = 0;

    assert(arr);

    for(i = 0; i < size; ++i)
    {
        min_index = i;
        min_value = arr[i];

        for(j = i; j < size; ++j)
        {
            if(arr[j] < arr[i])
            {
                if(min_value > arr[j])
                {
                    min_value = arr[j];
                    min_index = j;
                }
            }
        }

        arr[min_index] = arr[i];
        arr[i] = min_value;
    }
}

void InsertionSort(int arr[], size_t size)
{
    size_t i = 0, j = 0;
    int swap = 0;

    assert(arr);

    for(i = 1; i < size; ++i)
    {
        for(j = i; j > 0; --j)
        {
            if(arr[j] < arr[j-1])
            {
                swap = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = swap;
            }
        }
    }
}