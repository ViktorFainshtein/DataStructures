/*********************************
 * Reviewer: 
 * Author: 
 * File Name: heap.h
 * ******************************/

#include <stdio.h>  /*printf*/

#include "heap.h"


typedef struct tuple
{
    int key;
    int value;
}tuple_t;


int MaxCmp(const void *a_data, const void *b_data, void *user_param)
{
    if(((tuple_t *)a_data)->key < ((tuple_t *)b_data)->key)
    {
        return 0;
    }
    return 1;
}

int MinCmp(const void *a_data, const void *b_data, void *user_param)
{
    if(((tuple_t *)a_data)->key > ((tuple_t *)b_data)->key)
    {
        return 0;
    }
    return 1;
}

int IsMatch(const void *a_data, const void *b_data, void *user_param)
{
    if(((tuple_t *)a_data)->key == ((tuple_t *)b_data)->key)
    {
        return 1;
    }
    return 0;
}

int main()
{
    heap_t *heap = NULL;
    tuple_t t[] = { {1,100}, {2, 100}, {3, 100}, {4, 100}, {5, 100} };
    tuple_t t1 = {-1, 100};
    int i = 0;

    heap = HeapCreate(MaxCmp, NULL);
    if(!heap)
    {
        printf("Create heap failed\n");
    }


    printf("size: %ld\n", HeapSize(heap));
    printf("is empty: %d\n", HeapIsEmpty(heap));

    for(i = 0; i<5; i++)
    {
        HeapPush(heap, &t[i]);
    }
    HeapPush(heap, &t1);

    printf("Peek at top: %d\n", ((tuple_t*)HeapPeek(heap))->key);

    HeapPop(heap);

    printf("Peek at top after POP: %d\n", ((tuple_t*)HeapPeek(heap))->key);
    
    HeapRemove(heap, &t[2], IsMatch, NULL);
    
    printf("Peek at top after Remove: %d\n", ((tuple_t*)HeapPeek(heap))->key);

    HeapDestroy(heap);

    return 0;
}