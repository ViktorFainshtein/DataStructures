/*********************************
 * Reviewer: 
 * Author: 
 * File Name: heap.h
 * ******************************/
#include <stdlib.h> /*malloc free*/
#include <string.h> /*memcpy*/
#include "heap.h"
#include "vector.h"

struct heap
{
    vector_t *arr;
    heap_is_less_func_t is_less;
    void *usr_param;
};

static void HeapifyUp(heap_t *heap, size_t index);
static void HeapifyDown(heap_t *heap, size_t index);
static void Swap(void **var1, void **var2);


/*max number of nodes at each level is 2^level*/
/*(void **) will be saved at each index*/
/*use GetAccess to the last element with size*/

/*
get access give you an access to all of the vector
since the address are linear
*/

heap_t *HeapCreate(heap_is_less_func_t comp_ptr, void *param)
{
    heap_t *heap = NULL;

    heap = malloc(sizeof(heap_t));
    if(!heap)
    {
        return NULL;
    }
    heap->arr = VectorCreate(sizeof(void *),sizeof(void *));
    if(!heap->arr)
    {
        free(heap);
        heap = NULL;
        return NULL;
    }
    heap->is_less = comp_ptr;
    heap->usr_param = param;
    
    return heap;
}

void HeapDestroy(heap_t *heap)
{
    VectorDestroy(heap->arr);
    heap->is_less = NULL;
    heap->usr_param = NULL;
    free(heap);
    heap = NULL;
}

int HeapPush(heap_t *heap, const void *data)
{
    if(VectorPush(heap->arr, &data))
    {
        return 1;
    }

    HeapifyUp(heap, (VectorSize(heap->arr)-1));
    
    return 0;
}

/*pop the root*/
void HeapPop(heap_t *heap)
{
    void **root = NULL;
    void **leaf = NULL;

    root = VectorGetAccess(heap->arr, 0);
    leaf = VectorGetAccess(heap->arr, (VectorSize(heap->arr)-1));

    Swap(root, leaf);
    VectorPop(heap->arr);
    HeapifyDown(heap, 0);
}

void *HeapRemove(heap_t *heap, const void *data, heap_is_match_func_t is_match, void *param)
{
    void **curr = NULL;
    void *ret_data = NULL;
    size_t last_index = VectorSize(heap->arr)-1;
    size_t i = 0;

    for(i = 0; i < last_index+1; i++)
    {
        curr = VectorGetAccess(heap->arr, i);
        if(is_match(data, *curr, heap->usr_param))
        {
            ret_data = *curr;
            Swap(curr, VectorGetAccess(heap->arr, last_index));
            /*remove last index*/
            VectorPop(heap->arr);
            HeapifyDown(heap, i);
            return ret_data;
        }
    }
    return NULL;
}

size_t HeapSize(heap_t *heap)
{
    return VectorSize(heap->arr);
}

int HeapIsEmpty(heap_t *heap)
{
    return VectorIsEmpty(heap->arr);
}

void *HeapPeek(heap_t *heap)
{
    void **temp = NULL;
    temp = VectorGetAccess(heap->arr, 0);
    return *temp;
}

static void HeapifyUp(heap_t *heap, size_t index)
{
    void **temp = NULL;
    void **min_max = NULL;
    size_t i = 0;
    size_t parent = 0;

    for(i = index; i > 0; i = parent)
    {
        parent = (i-1)/2;
        temp = VectorGetAccess(heap->arr, i);
        min_max = VectorGetAccess(heap->arr, parent);
        if(heap->is_less(*temp, *min_max, heap->usr_param))
        {
            Swap(temp, min_max);
        }
        else
        {
            break;
        }
    }
}

/*swap the node with its children until it is a leaf and then heapifyUP*/
static void HeapifyDown(heap_t *heap, size_t index)
{
    void **temp = NULL;
    void **left = NULL;
    void **right = NULL;
    size_t i = 0;
    size_t left_index = 0;
    size_t right_index = 0;

    for(i = index; i < VectorSize(heap->arr);)
    {
        left_index = 2*i +1;
        right_index = 2*i +2;

        temp = VectorGetAccess(heap->arr, i);

        if(right_index > (VectorSize(heap->arr) -1))
        {
            break;
        }
        
        left = VectorGetAccess(heap->arr, left_index);
        right = VectorGetAccess(heap->arr, right_index);

        if(heap->is_less(*left, *right, heap->usr_param))
        {
            Swap(temp, left);
            i = (2*i) + 1;
        }
        else
        {
            Swap(temp, right);
            i = (2*i) +2;
        }
    }

    left_index = 2*i +1;
    if(left_index == VectorSize(heap->arr)-1)
    {
        left = VectorGetAccess(heap->arr, left_index);
        Swap(temp, left);
        i = left_index;
    }

    HeapifyUp(heap, i);
}

static void Swap(void **var1, void **var2)
{
    void *temp = *var1;
    *var1 = *var2;
    *var2 = temp;
}