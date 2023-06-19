/*********************************
 * Reviewer: Nodfar Melamed
 * Author: Viktor Fainshtein
 * File Name: hash_table.c
 * ******************************/
#include <stdlib.h> /*malloc free*/
#include <assert.h>
#include <stdio.h>  /*printf for remove - in case the element user wanted to removed does not exist*/
#include "hash_table.h"
#include "dll.h"

typedef struct hash
{
    size_t size;
    hash_func_t encode;
    hash_is_match_t cmp_func;
    void **arr;
};

static int CalcIndex(hash_t *hash, void *data); 

hash_t *HashCreate(hash_is_match_t compare_func, hash_func_t hash_func ,size_t table_size)
{
    hash_t *h_table = NULL;
    size_t i = 0;
    size_t j = 0;
    h_table = (hash_t *)malloc(sizeof(hash_t));
    if(!h_table)
    {
        return NULL;
    }

    h_table->arr = (void *)malloc(sizeof(void *) * table_size);
    if(!h_table->arr)
    {
        free(h_table);
        return NULL;
    }

    for(i=0; i<table_size; ++i)
    {
        h_table->arr[i] = DListCreate();
        if(h_table->arr[i] == NULL)
        {
            break;
        }
    }
    /*in case faild to create a list at a certaine index*/
    if(i != table_size)
    {
        for(j=0; j<i;++j)
        {
            DListDestroy(h_table->arr[j]);
        }
        free(h_table->arr);
        free(h_table);
        return NULL;
    }

    h_table->size = table_size;
    h_table->cmp_func = compare_func;
    h_table->encode = hash_func;

    return h_table;
}

void HashDestroy(hash_t *hash)
{
    size_t i = 0;

    assert(hash);
    assert(hash->arr);

    for(i=0; i< hash->size; ++i)
    {
        DListDestroy(hash->arr[i]);
    }
    free(hash->arr);
    hash->arr = NULL;

    hash->size = 0;
    hash->encode = NULL;
    hash->cmp_func = NULL;
    free(hash);
    hash = NULL;
}

size_t HashSize(hash_t *hash)
{
    size_t i = 0;
    size_t res = 0;

    for(i=0; i< hash->size; ++i)
    {
        res += DListSize(hash->arr[i]);
    }
    return res;
}

int HashIsEmpty(hash_t *hash)
{
    size_t i = 0;

    for(i=0; i< hash->size; ++i)
    {
        if(DListIsEmpty(hash->arr[i]) != 1)
        {
            return 0;
        }
    }
	return 1;
}

int HashInsert(hash_t *hash, const void *data)
{
    int index = -1;
    dll_iterator_t node = NULL;
    
    assert(hash);
    assert(data);

    index = CalcIndex(hash, (void *)data);

    node = DListInsert(hash->arr[index], DListBegin(hash->arr[index]), (void *)data);
    if(DListIsSameIter(node, DListEnd(hash->arr[index])))
    {
        return 1;
    }
    return 0;
}

void HashRemove(hash_t *hash, void *data)
{
    int index = -1;
    dll_iterator_t node = NULL;

    assert(hash);
    assert(data);

    index = CalcIndex(hash, (void *)data);

    node = DListFind(DListBegin(hash->arr[index]),DListEnd(hash->arr[index]), data, hash->cmp_func);
    if(DListIsSameIter(node, DListEnd(hash->arr[index])))
    {
        printf("\nFaild to find\n\n");
    }
    else
    {
        DListRemove(node);
    }
}

void *HashFind(hash_t *hash, const void *data)
{
    int index = -1;
    dll_iterator_t node = NULL;

    assert(hash);
    assert(data);

    index = CalcIndex(hash, (void *)data);
    node = DListFind(DListBegin(hash->arr[index]),DListEnd(hash->arr[index]), data, hash->cmp_func);

    if(DListIsSameIter(node, DListEnd(hash->arr[index])))
    {
        return NULL;
    }
    return DListGetData(node);
}

int HashForEach(hash_t *hash, hash_action_func_t action_func, void *param)
{
    size_t i = 0;
    int res = 0;
    for(i=0; i < hash->size; ++i)
    {
        if(DListIsEmpty(hash->arr[i]))
        {
            continue;
        }
        res = DListForEach(DListBegin(hash->arr[i]) ,DListEnd(hash->arr[i]), param, action_func);
        /*if for each faild*/
        if(res == -1)
        {
            return 1;
        }
    }
    
    return 0;
}

static int CalcIndex(hash_t *hash, void *data)
{
    int index = -1;
    index = hash->encode(data);
    index %= hash->size; 
    return index;
}
