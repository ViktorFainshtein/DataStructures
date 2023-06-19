/*********************************
 * Reviewer: 
 * Author:  Viktor Fainshtein
 * File: bst.h
 * ******************************/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc free */
#include "bst.h"

/*user struct - void *data */
typedef struct tuple
{
    int key;
    int value;
}tuple_t;

/*a is current data, b is recived data from func*/
int CompareFunction(const void *a_data, const void *b_data, void *user_param)
{
    if(((tuple_t *)a_data)->key > ((tuple_t *)b_data)->key)
    {
        return -1;
    }

    else if (((tuple_t *)a_data)->key < ((tuple_t *)b_data)->key)
    {
        return 1;
    }

    return 0;
}

static void PrintData(tuple_t *data);

void Test();

int main()
{
    /*bst_t *bst = BSTCreate(CompareFunction, NULL);
    bst_iterator_t iter;
    bst_iterator_t other_iter;
    tuple_t *t1 = malloc(sizeof(tuple_t));
    tuple_t *t2 = malloc(sizeof(tuple_t));
    tuple_t *t3 = malloc(sizeof(tuple_t));
    tuple_t *t4 = malloc(sizeof(tuple_t));
    
    
    t1->key = 8;    
    t1->value = 100;
    t2->key = 5;    
    t2->value = 100;
    t3->key = 10;   
    t3->value = 100;
    t4->key = 15;   
    t4->value = 100;*/
    
    Test();

  /*  printf("is empty?: %d\n", BSTIsEmpty(bst));

    printf("size: %ld\n", BSTSize(bst));
*/
    /*iter = BSTInsert(bst, t1);*/
    /*PrintData(BSTGetData(iter));*/
    /*iter = BSTInsert(bst, t2);*/
    /*PrintData(BSTGetData(iter));*/
    /*iter = BSTInsert(bst, t3);*/
    /*PrintData(BSTGetData(iter));*/
/*
    iter = BSTBegin(bst);
    PrintData(BSTGetData(iter));
    
    iter = BSTNext(iter);
    PrintData(BSTGetData(iter));
    
    iter = BSTNext(iter);
    PrintData(BSTGetData(iter));

    iter = BSTPrev(iter);
    PrintData(BSTGetData(iter));

    iter = BSTPrev(iter);
    PrintData(BSTGetData(iter));

    iter = BSTEnd(bst);
    printf("iter data:\n");
    PrintData(BSTGetData(iter));

    other_iter = BSTBegin(bst);
    printf("other_iter data:\n");
    PrintData(BSTGetData(iter));

    printf("Is Same Iter?: %d\n", BSTIsSameIter(iter, other_iter));

    other_iter = BSTEnd(bst);

    printf("Is Same Iter?: %d\n", BSTIsSameIter(iter, other_iter));

    printf("is empty?: %d\n", BSTIsEmpty(bst));

    printf("size: %ld\n", BSTSize(bst));

    iter = BSTFind(bst, t4);
    PrintData(BSTGetData(iter));
    
    BSTDestroy(bst);*/
    /*see if any nodes left after destroy*/
/*
    free(t1);
    free(t2);
    free(t3);
    free(t4);
*/
    return 0;
}

static void PrintData(tuple_t *tuple)
{
    if(tuple == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("key is: %d\n", tuple->key);
    	printf("value is: %d\n", tuple->value);
    }
}

void Test()
{
    bst_t *bst = BSTCreate(CompareFunction, NULL);
    bst_iterator_t iter;
    bst_iterator_t other_iter;  
    /*15 node:*/
    tuple_t *t1 = malloc(sizeof(tuple_t));
    tuple_t *t2 = malloc(sizeof(tuple_t));
    tuple_t *t3 = malloc(sizeof(tuple_t));
    tuple_t *t4 = malloc(sizeof(tuple_t));
    tuple_t *t5 = malloc(sizeof(tuple_t));
    tuple_t *t6 = malloc(sizeof(tuple_t));
    tuple_t *t7 = malloc(sizeof(tuple_t));
    tuple_t *t8 = malloc(sizeof(tuple_t));
    tuple_t *t9 = malloc(sizeof(tuple_t));
    tuple_t *t10 = malloc(sizeof(tuple_t));
    tuple_t *t11 = malloc(sizeof(tuple_t));
    tuple_t *t12 = malloc(sizeof(tuple_t));
    tuple_t *t13 = malloc(sizeof(tuple_t));
    tuple_t *t14 = malloc(sizeof(tuple_t));
    tuple_t *t15 = malloc(sizeof(tuple_t));
    
    t1->key = 5;    /*root*/
    t1->value = 100;
    t2->key = 2;    /*left to root*/
    t2->value = 100;
    t3->key = 1;   
    t3->value = 100;
    t4->key = 3;   
    t4->value = 100;   
    t5->key = 4;
    t5->value = 100;
    t6->key = 8;     /*right to root*/
    t6->value = 100;
    t7->key = 6;
    t7->value = 100;
    t8->key = 7;
    t8->value = 100;
    t9->key = 10;
    t9->value = 100;
    t10->key = 9;
    t10->value = 100;
    t11->key = 80;
    t11->value = 100;
    t12->key = 40;
    t12->value = 100;
    t13->key = 50;
    t13->value = 100;
    t14->key = 20;
    t14->value = 100;
    t15->key = 15;
    t15->value = 100;

    iter = BSTInsert(bst, t1);
    iter = BSTInsert(bst, t2);
    iter = BSTInsert(bst, t3);
    iter = BSTInsert(bst, t4);
    iter = BSTInsert(bst, t5);
    iter = BSTInsert(bst, t6);
    iter = BSTInsert(bst, t7);
    iter = BSTInsert(bst, t8);
    iter = BSTInsert(bst, t9);
    iter = BSTInsert(bst, t10);
    iter = BSTInsert(bst, t11);
    iter = BSTInsert(bst, t12);
    iter = BSTInsert(bst, t13);
    iter = BSTInsert(bst, t14);
    iter = BSTInsert(bst, t15);

    iter = BSTBegin(bst);
    PrintData(BSTGetData(iter));

    iter = BSTEnd(bst);
    iter = BSTPrev(iter);
    PrintData(BSTGetData(iter));

    iter = BSTBegin(bst);

    while(!BSTIsSameIter(iter,BSTEnd(bst)))
    {
        PrintData(BSTGetData(iter));
        iter = BSTNext(iter);
    }

    BSTDestroy(bst);

    free(t1);
    free(t2);
    free(t3);
    free(t4);
    free(t5);
    free(t6);
    free(t7);
    free(t8);
    free(t9);
    free(t10);
    free(t11);
    free(t12);
    free(t13);
    free(t14);
    free(t15);
}