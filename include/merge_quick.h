/*********************************
 * Reviewer: 
 * Author: 
 * File Name: merge_quick.h
 * ******************************/
#ifndef __MERGE_QUICK_H__
#define __MERGE_QUICK_H__

#include <stddef.h> /*size_t*/

int MergeSort(void *arr_to_sort, size_t num_elements, size_t elem_size, int(*is_before)(const void *elem1, const void *elem2));

int QuickSort(void *arr_to_sort, size_t num_elements, size_t elem_size, int(*is_before)(const void *elem1, const void *elem2));  

int RecurBinarySearch(int *array, size_t arr_size ,int data_to_find);
/*return value: in success-index in faile- (-1)*/

int IterBinarySearch(int *array, size_t arr_size ,int data_to_find);
/*return value: in success-index in faile- (-1)*/

#endif