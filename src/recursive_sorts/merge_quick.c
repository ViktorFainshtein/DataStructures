/*********************************
 * Reviewer: Roy Mantel
 * Author: Viktor Fainshttein
 * File Name: merge_quick.h
 * ******************************/
#include <string.h> /*memcpy*/
#include <stdlib.h> /*malloc free*/
#include "merge_quick.h"

static void Swap(void *element1, 
                void *element2, 
                void *buffer, 
                size_t element_size);
static int MergeSmaller(void *arr_to_sort, 
                        int left, 
                        int right, 
                        size_t elem_size, 
                        int (*is_before)(const void *elem1, const void *elem2));
static int MergeTwoHalfs(void *arr_to_sort, 
                        int left, 
                        int mid, 
                        int right, 
                        size_t elem_size, 
                        int (*is_before)(const void *elem1, const void *elem2));
static int RealQuickSort(void *arr_to_sort, 
                        int left, 
                        int right, 
                        size_t elem_size, 
                        int (*is_before)(const void *elem1, const void *elem2));
static int Partition(void *arr_to_sort, 
                        int left, 
                        int right, 
                        size_t elem_size, 
                        int (*is_before)(const void *elem1, const void *elem2));


int MergeSort(void *arr_to_sort, 
                size_t num_elements, 
                size_t elem_size, 
                int (*is_before)(const void *elem1, const void *elem2))
{
    int left = 0;
    int right = num_elements - 1;

    return MergeSmaller(arr_to_sort, left, right, elem_size, is_before);
}

static int MergeSmaller(void *arr_to_sort, 
                        int left, int right, 
                        size_t elem_size, 
                        int (*is_before)(const void *elem1, const void *elem2))
{
    int mid = 0;
    int res = 0;
    if(left < right)
    {

        mid = left + (right  - left) / 2;

        res += MergeSmaller(arr_to_sort, left, mid, elem_size, is_before);
        res += MergeSmaller(arr_to_sort, mid +1, right, elem_size, is_before);

        res += MergeTwoHalfs(arr_to_sort, left, mid, right, elem_size, is_before);
    }
    return res;
}

static int MergeTwoHalfs(void *arr_to_sort, 
                        int left, 
                        int mid, 
                        int right, 
                        size_t elem_size, 
                        int (*is_before)(const void *elem1, const void *elem2))
{
    int i = 0, j = 0, k = 0;
    int left_size = mid - left + 1;
    int right_size = right - mid;

    char *left_arr = NULL;
    char *right_arr = NULL;

    left_arr = malloc(left_size * elem_size);
    if(!left_arr && left_size != 0)
    {
        return 1;
    }
    right_arr = malloc(right_size * elem_size);
    if(!right_arr && right_size != 0)
    {
        return 1;
    }

    memcpy(left_arr, 
        ((char *)arr_to_sort + (left*elem_size)), 
        (left_size*elem_size));
    memcpy(right_arr, 
        ((char *)arr_to_sort + ((mid+1)*elem_size)), 
        (right_size*elem_size));

    i=0;
    j=0;
    k=left;

    while((i < left_size) && (j < right_size))
    {
        if(is_before((const void *)(left_arr + (i*elem_size)),
                    (const void *)(right_arr + (j*elem_size))))
        {
            memcpy(((char *)arr_to_sort + (k*elem_size)), 
                    (left_arr + (i*elem_size)), elem_size);
            ++i;
        }
        else
        {
            memcpy(((char *)arr_to_sort + (k*elem_size)), 
                    (right_arr + (j*elem_size)), elem_size);
            ++j;
        }
        ++k;
    }

    if(i != left_size)
    {
        memcpy(((char *)arr_to_sort + (k*elem_size)), 
                (left_arr + (i*elem_size)), (left_size-i)*elem_size);
    }
    else
    {
        memcpy(((char *)arr_to_sort + (k*elem_size)), 
                (right_arr + (j*elem_size)), (right_size - j)*elem_size);
    }

    free(left_arr);
    left_arr = NULL;
    free(right_arr);
    right_arr = NULL;

    return 0;
}

int QuickSort(void *arr_to_sort, 
                size_t num_elements, 
                size_t elem_size, 
                int (*is_before)(const void *elem1, const void *elem2))
{
    int left = 0;
    int right = num_elements - 1;
    int res = 0;

    res = RealQuickSort(arr_to_sort, left, right, elem_size, is_before);

    return res;
}

static int RealQuickSort(void *arr_to_sort, 
                        int left, 
                        int right, 
                        size_t elem_size, 
                        int (*is_before)(const void *elem1, const void *elem2))
{
    int pivot = 0;
    int res = 0;
    if(left<right)
    {
        pivot = Partition(arr_to_sort, left, right, elem_size, is_before);
        if(pivot == -1)
        {
            return 1;
        }
        res += RealQuickSort(arr_to_sort, left, pivot-1, elem_size, is_before);
        res += RealQuickSort(arr_to_sort, pivot + 1, right, elem_size, is_before);
    }
    return res;
}

static int Partition(void *arr_to_sort, 
                    int left, int right, 
                    size_t elem_size, 
                    int (*is_before)(const void *elem1, const void *elem2))
{
    void *pivot = ((char *)arr_to_sort + (right*elem_size));
    void *buffer = NULL;
    int i = left - 1;
    int j = 0;

    buffer = malloc(elem_size);
    if(!buffer)
    {
        return -1;
    }

    for(j = left; j <= (right - 1); j++)
    {
        if(is_before(((const void *)((char *)arr_to_sort + (j*elem_size))), 
                    (const void *)pivot))
        {
            ++i;
            Swap(((char *)arr_to_sort + (i*elem_size)), 
                ((char *)arr_to_sort + (j*elem_size)), 
                buffer, 
                elem_size);
        }
    }
    Swap(((char *)arr_to_sort + ((i+1)*elem_size)), 
        ((char *)arr_to_sort + (right*elem_size)), 
        buffer, 
        elem_size);

    free(buffer);
    buffer = NULL;
    
    return (i+1);
}

int IterBinarySearch(int *array, size_t arr_size ,int data_to_find)
{
    int low = 0, high = (int)arr_size,  mid = 0;

    while (low != high)
    {
        mid = (low + high) / 2;
        if(array[mid] == data_to_find)
        {
            return mid;
        }
        else if (array[mid] < data_to_find)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    if(array[low] == data_to_find)
    {
        return low;
    }
    return -1;
}

int RecurBinarySearch(int *array, size_t arr_size ,int data_to_find)
{
    int mid = arr_size / 2;
    int res = 0;
    if(mid == 0 && array[mid] != data_to_find)
    {
        return -1;
    }

    if(array[mid] == data_to_find)
    {
        return mid;
    }
    else if(array[mid] > data_to_find)
    {
        return RecurBinarySearch(array, mid, data_to_find);
    }

    res = RecurBinarySearch((array + mid), (arr_size - mid), data_to_find);
    if(res != -1)
    {
        return mid + res;
    }
    return -1;
}

static void Swap(void *element1, 
                void *element2, 
                void *buffer, 
                size_t element_size)
{
    memcpy(buffer, element1, element_size);
    memcpy(element1, element2, element_size);
    memcpy(element2, buffer, element_size);
}
