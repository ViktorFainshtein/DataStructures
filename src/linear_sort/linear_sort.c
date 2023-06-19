/* *******************************
 * Reviewer: Yohai Azoulai
 * Author: Viktor Fainshtein		
 * File: linear_sort.c
 * ******************************/
 
#include <assert.h>
#include "linear_sort.h"

#define RANGE 100
#define SIZE 5000

#define RADIX_RANGE 10

static int Find_Max(int arr[], size_t size);
/*static int Find_Min(int arr[], size_t size);*/
static void RadixCountingSort(int arr[], size_t size, size_t mod);

void CountingSort(int arr[], size_t size)
{
    size_t i = 0, j = 0;
    size_t max_val = 0;
    /*size_t min_val = 0;*/
    int LUT[RANGE] = {0};   /*since RANGE is known before the function use we can use static arrays*/
    int output[SIZE] = {0};
	
	assert(arr);
	
    max_val = Find_Max(arr, size);

    /*count the instenses of a number in the arr and put the result in LUT in the corresponding index*/
    while(i < size)
    {
        LUT[arr[i]] += 1;
        ++i;
    }

    i = 1;
    /*adjust the values of the LUT to the correct indexes*/
    
    while(i <= max_val)
    {
        LUT[i] += LUT[i-1];
        ++i;
    }

    /*put the correct order in the output arr*/
    for(i = 0; i < size; ++i)
    {
        output[LUT[arr[i]]] = arr[i];
        LUT[arr[i]] -= 1;
    }

    /*fix the recived arr*/
    for(i=0, j=1; i < size; ++i, ++j)
    {
        arr[i] = output[j];
    }
}

void RadixSort(int arr[], size_t size)
{
    size_t i = 0;
    size_t mod = 1;
    size_t max_digits = 0;

    int max = Find_Max(arr, size);

    while(max)
    {
        max_digits += 1;
        max /= 10;
    }

    for ( i = 0; i < max_digits; i++)
    {
        RadixCountingSort(arr,size,mod);
        mod *= 10;
    }
}

static void RadixCountingSort(int arr[], size_t size, size_t mod)
{
    size_t i = 0, j = 0;

    int LUT[RADIX_RANGE] = {0};
    int output[SIZE] = {0};

    /*count the instenses of a number in the arr and put the result in LUT in the corresponding index*/
    while(i < size)
    {
        LUT[(arr[i] / mod) % 10] += 1;
        ++i;
    }

    i = 1;
    /*adjust the values of the LUT to the correct indexes*/
    while(i < RADIX_RANGE)
    {
        LUT[i] += LUT[i-1];
        ++i;
    }

    /*put the correct order in the output arr*/
    for(i = size-1; (int)i >= 0; --i)
    {
        output[LUT[(arr[i] / mod) % 10]] = arr[i];
        LUT[(arr[i] / mod) % 10] -= 1;
    }

    /*fix the recived arr*/
    for(i = 0, j = 1; i < size; ++i, ++j)
    {
        arr[i] = output[j];
    }
}

static int Find_Max(int arr[], size_t size)
{
    size_t i = 0;
    int max = 0;
    while (i < size)
    {
        if(arr[i] > max)
        {   
            max = arr[i];
        }
        ++i;
    }
    return max;
}
/* for advance question
static int Find_Min(int arr[], size_t size)
{
    size_t i = 0;
    int min = 0;
    while (i < size)
    {
        if(arr[i] < min)
        {   
            min = arr[i];
        }
        ++i;
    }
    return min;
}
*/
