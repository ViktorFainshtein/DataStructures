/*********************************
 * Reviewer: Avigail Millatiner
 * Author:  Viktor Fainshtein
 * File: bst.c
 * ******************************/

#include <stdlib.h> /*malloc free*/
#include <assert.h>
#include "bst.h"

typedef struct bst_node
{
    void *data;
    struct bst_node *parent;
    struct bst_node *child[2];
}bst_node_t;

struct bst
{
    void *user_param;
    bst_node_t *root;
    bst_compare_func_t cmp_fun;
};

static void RemoveNode(bst_iterator_t iter);

static int IsLeaf(bst_iterator_t iter);
static int IsNodeWithRightChild(bst_iterator_t iter);
static int IsNodeWithLeftChild(bst_iterator_t iter);

bst_iterator_t BSTIterInit(void);

/*create a node and init with the data recived from the user */
static bst_node_t *CreatNode(const void *data)
{
    bst_node_t *new_node = NULL;
    
    new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
    if(!new_node)
    {
    	return NULL;
    }
    
    new_node->data = (void *)data;
    new_node->parent = NULL;
    new_node->child[0] = NULL;
    new_node->child[1] = NULL;
    
    return new_node;
}

bst_t *BSTCreate(bst_compare_func_t compare_func, void *user_param)
{
    bst_t *bst = NULL;

    assert(compare_func);

    bst = (bst_t *)malloc(sizeof(bst_t));
    if(!bst)
    {
        return NULL;
    }
    
    bst->cmp_fun = compare_func;
    bst->user_param = user_param;
    
    /*create dummy node and set it as root*/
    bst->root = (bst_node_t *)malloc(sizeof(bst_node_t));           
    if(bst->root == NULL)
    {
    	free(bst);
    	bst = NULL;
        return NULL;
    }

    (bst->root)->data = NULL;
    (bst->root)->parent = NULL;
    (bst->root)->child[0] = NULL;
    (bst->root)->child[1] = NULL;
    return bst;
}

void BSTDestroy(bst_t *bst)
{
    bst_iterator_t curr;
    bst_iterator_t end;

    assert(bst);

    curr = BSTBegin(bst);
    end = BSTEnd(bst);

    while(!BSTIsSameIter(curr,end))
    {
        BSTRemove(curr);
        curr = BSTBegin(bst);
        end = BSTEnd(bst);
    }
    RemoveNode(curr);
    
    bst->cmp_fun = NULL;
    bst->user_param = NULL;
    bst->root = NULL;
    free(bst);
    bst = NULL;
}

size_t BSTSize(bst_t *bst)
{
    bst_iterator_t curr = BSTIterInit();
    size_t size = 0;

    assert(bst);

    curr = BSTBegin(bst);

    while(!BSTIsSameIter(curr,BSTEnd(bst)))
    {
        ++size;
        curr = BSTNext(curr);
    }

    return size;
}

int BSTIsEmpty(bst_t *bst)
{
    assert(bst);
    /*in case of dummy node*/
    if((bst->root)->data == NULL)
    {
        return 1;
    }
    return 0;
}

bst_iterator_t BSTInsert(bst_t *bst, const void *data)  
{
    bst_iterator_t curr = BSTIterInit();
    bst_node_t *new_node = NULL;
    int res = 0;
    size_t index = 0;

    assert(bst);
    assert(data);

    curr.bst_node = bst->root;

    /*if tree is empty - set the node as root*/
    if(BSTIsEmpty(bst))     
    {
        new_node = CreatNode(data);
        if(!new_node)
        {
            return BSTEnd(bst);
        }
        
        (bst->root)->child[1] = new_node;
        bst->root->data = new_node->data;
        new_node->data = NULL;
        new_node->parent = bst->root;
        
        return curr;
    }

    /*if the tree is not empty*/
    while(curr.bst_node != NULL || (curr.bst_node)->data != NULL)
    {
        res = bst->cmp_fun((curr.bst_node)->data, data, bst->user_param);
        /*if key alredy exists in the tree*/
        if(0 == res)
        {
            return BSTEnd(bst);
        }
        /*smaller - insert to the left*/
        if(res < 0)
        {
            if((curr.bst_node->child[0] == NULL))                      /*if no left child exist - insert*/
            {
                new_node = CreatNode(data);
                (curr.bst_node)->child[0] = new_node;
                new_node->parent = curr.bst_node;
                curr.bst_node = (curr.bst_node)->child[0];
                return curr;
            }
            curr.bst_node = (curr.bst_node)->child[0];
        }
        /*bigger - insert to the right*/
        else if(res > 0)
        {
            if((curr.bst_node)->child[1] == NULL)                       /*if no right child exist - insert*/
            {
                new_node = CreatNode(data);
                (curr.bst_node)->child[1] = new_node;
                new_node->parent = curr.bst_node;
                curr.bst_node = (curr.bst_node)->child[1];
                return curr;
            }
            else if(((curr.bst_node)->child[1])->data == NULL)          /*if its a dummy switch dummy with new_node*/              
            {
                new_node = CreatNode(data);
                ((curr.bst_node)->child[1])->parent = new_node;         /*set the dummis parent to be new node*/
                new_node->child[1] = ((curr.bst_node)->child[1]);       /*set new nodes right child to be dummy*/
                new_node->parent = curr.bst_node;                       /*set currents node parent to be dummys parent*/
                (curr.bst_node)->child[1] = new_node;                   /*set dummys parent child to be current node*/
                curr.bst_node = (curr.bst_node)->child[1];
                return curr;
            }
            curr.bst_node = (curr.bst_node)->child[1];                  /*go right*/
        }
    }

    return curr;
}

void BSTRemove(bst_iterator_t iter)
{
    bst_iterator_t curr;
    bst_iterator_t parent;

    assert(iter.bst_node);

    curr.bst_node = iter.bst_node;
    parent.bst_node = (iter.bst_node)->parent;
    
    /*1: remove leaf that is not a dummy*/
    if(IsLeaf(iter) && ((iter.bst_node)->data != NULL))
    {
        /*update parent pointers*/
        /*if its the left leaf*/
        if((parent.bst_node)->child[0] == iter.bst_node)
        {
            (parent.bst_node)->child[0] = NULL;
        }
        /*if its the right leaf*/
        else
        {
            (parent.bst_node)->child[1] = NULL;
        }
        RemoveNode(iter);
    }
    /*2: remove a node with 1 child*/
    else if(IsNodeWithLeftChild(iter))
    {
        /*if iter is the left child*/
        if((parent.bst_node)->child[0] == iter.bst_node)
        {
            /*set the child of the parent of the current node*/
            (parent.bst_node)->child[0] = (iter.bst_node)->child[0];            
            /*set the parent of the current child*/
            ((iter.bst_node)->child[0])->parent = parent.bst_node;              
 
        }
        /*if iter is the right child*/
        else
        {
            (parent.bst_node)->child[1] = iter.bst_node->child[0];
            ((iter.bst_node)->child[0])->parent = parent.bst_node;

        }
        RemoveNode(iter);
    }
    else if(IsNodeWithRightChild(iter))
    {
        /*if root*/
        if((iter.bst_node)->parent == NULL)   
        {
            curr.bst_node = iter.bst_node->child[1];    
            iter.bst_node->data = curr.bst_node->data;  
            iter.bst_node->child[0] = curr.bst_node->child[0];
            iter.bst_node->child[1] = curr.bst_node->child[1];
            if(curr.bst_node->child[0])
            {
                curr.bst_node->child[0]->parent = iter.bst_node;
            }
            if(curr.bst_node->child[1])
            {
                curr.bst_node->child[1]->parent = iter.bst_node;
            }
            RemoveNode(curr);
        }
        else if((parent.bst_node)->child[0] == iter.bst_node)
        {
            (parent.bst_node)->child[0] = (iter.bst_node)->child[1];            /*set the child of the parent of the current node*/
            ((iter.bst_node)->child[1])->parent = parent.bst_node;              /*set the parent of the current child*/
            RemoveNode(iter);
        }
        else
        {
            (parent.bst_node)->child[1] = iter.bst_node->child[1];
            ((iter.bst_node)->child[1])->parent = parent.bst_node;
            RemoveNode(iter);
        } 
    }
    /*3: remove a node with 2 or more children*/
    else if(((iter.bst_node)->child[0] != NULL) && ((iter.bst_node)->child[1] != NULL) && (((iter.bst_node)->child[1])->data != NULL))
    {
        curr = BSTNext(iter);

        /*switcheru current nodes child*/
        if(curr.bst_node->child[1] != NULL)
        {
            ((curr.bst_node)->parent)->child[0] = (curr.bst_node)->child[1];
            ((curr.bst_node)->child[1])->parent = (curr.bst_node)->parent;
            (curr.bst_node)->child[1] = NULL;
            (curr.bst_node)->parent = NULL;
        }

        /*if root - switch current data with root data and free current node*/
        if((iter.bst_node)->parent == NULL)
        {
            iter.bst_node->data = curr.bst_node->data;
            RemoveNode(curr);
        }
        /*if not root - check if its parents left child and switch*/
        else if((parent.bst_node)->child[0] == iter.bst_node)
        {
            if((curr.bst_node)->child[1] != NULL)
            {
                ((curr.bst_node)->child[1])->parent = curr.bst_node->parent;
            }
            ((curr.bst_node)->parent)->child[0] = curr.bst_node->child[1];

            (curr.bst_node)->child[0] = (iter.bst_node)->child[0];
            (curr.bst_node)->child[1] = (iter.bst_node)->child[1];

            ((iter.bst_node)->child[0])->parent = curr.bst_node;
            ((iter.bst_node)->child[1])->parent = curr.bst_node;

            (parent.bst_node)->child[0] = curr.bst_node;
            (curr.bst_node)->parent = parent.bst_node;
            
            RemoveNode(iter);
        }
        /*if not root - check if its parents right child and switch*/
        else
        {
            ((curr.bst_node)->child[1])->parent = curr.bst_node->parent;
            ((curr.bst_node)->parent)->child[0] = curr.bst_node->child[1];

            (curr.bst_node)->child[0] = (iter.bst_node)->child[0];
            (curr.bst_node)->child[1] = (iter.bst_node)->child[1];

            ((iter.bst_node)->child[0])->parent = curr.bst_node;
            ((iter.bst_node)->child[1])->parent = curr.bst_node;

            (parent.bst_node)->child[1] = curr.bst_node;
            (curr.bst_node)->parent = parent.bst_node;
            RemoveNode(iter);
        }
    }
    /*left exists and right is dummy*/
    else 
    {
        curr.bst_node = (iter.bst_node)->child[0];            

        while((curr.bst_node)->child[1] != NULL)
        {
            curr.bst_node = (curr.bst_node)->child[1];
        }
        if(curr.bst_node->child[0] != NULL)
        {
            ((curr.bst_node)->child[0])->parent = (curr.bst_node)->parent;
            ((curr.bst_node)->parent)->child[1] = (curr.bst_node)->child[0];
            curr.bst_node->child[0] = NULL;
            curr.bst_node->parent = NULL;
        }
        parent.bst_node->child[1] = curr.bst_node;
        curr.bst_node->parent = parent.bst_node;

        if(curr.bst_node != iter.bst_node->child[0])
        {
            ((iter.bst_node)->child[0])->parent = curr.bst_node;
            (curr.bst_node)->child[0] = (iter.bst_node)->child[0];
        }
        
        ((iter.bst_node)->child[1])->parent = curr.bst_node;
        (curr.bst_node)->child[1] = (iter.bst_node)->child[1];

        RemoveNode(iter);

    }
}

static void RemoveNode(bst_iterator_t iter)
{
    iter.bst_node->data = NULL;
    iter.bst_node->parent = NULL;
    iter.bst_node->child[0] = NULL;
    iter.bst_node->child[1] = NULL;
    free(iter.bst_node);
    iter.bst_node = NULL;
}

bst_iterator_t BSTBegin(bst_t *bst)
{
    bst_iterator_t curr = BSTIterInit();

    assert(bst);

    curr.bst_node = bst->root;

    while((curr.bst_node)->child[0] != NULL)
    {
        curr.bst_node = (curr.bst_node)->child[0];
    }

    return curr;
}

bst_iterator_t BSTEnd(bst_t *bst)
{
    bst_iterator_t curr = BSTIterInit();

    assert(bst);

    curr.bst_node = bst->root;

    while((curr.bst_node)->data != NULL)      
    {
        curr.bst_node = (curr.bst_node)->child[1];
    }

    return curr;
}

bst_iterator_t BSTNext(bst_iterator_t iter)
{
    bst_iterator_t curr = BSTIterInit();
    bst_iterator_t parent = BSTIterInit();

    assert(iter.bst_node);

    curr.bst_node = iter.bst_node;
    /*check right*/
    if((curr.bst_node)->child[1] != NULL)   
    {
        curr.bst_node = iter.bst_node->child[1];

        while(curr.bst_node->child[0] != NULL)
        {
            curr.bst_node = curr.bst_node->child[0];
        }

        return curr;
    }
    /*check up - if you are the right node go up until you are the left node*/
    else if ((iter.bst_node)->child[1] == NULL)   
    {
        curr.bst_node = iter.bst_node;
        parent.bst_node = (curr.bst_node)->parent;

        while(((curr.bst_node)->parent)->child[0] != curr.bst_node)
        {  
            parent.bst_node = (parent.bst_node)->parent;
            curr.bst_node = curr.bst_node->parent;
        }

        return parent;
    }

    else
    {
        curr.bst_node = curr.bst_node->parent;
    }

    return curr;
}

bst_iterator_t BSTPrev(bst_iterator_t iter)
{
    bst_iterator_t curr = BSTIterInit();
    bst_iterator_t parent = BSTIterInit();

    assert(iter.bst_node);

    curr.bst_node = iter.bst_node;
    /*check left*/
    if((iter.bst_node)->child[0] != NULL)   
    {
        curr.bst_node = iter.bst_node->child[0];

        while(curr.bst_node->child[1] != NULL)
        {
            curr.bst_node = curr.bst_node->child[1];
        }

        return curr;
    }
    /*check up - if you are the left node go up until you are the right node*/
    else 
    {
        curr.bst_node = iter.bst_node;
        parent.bst_node = (curr.bst_node)->parent;

        while(parent.bst_node->child[1] != curr.bst_node)
        {
            parent.bst_node = (parent.bst_node)->parent;
            curr.bst_node = curr.bst_node->parent;
        }

        return parent;
    }
}

int BSTIsSameIter(bst_iterator_t f_iter, bst_iterator_t s_iter)
{
    assert(f_iter.bst_node);
    assert(s_iter.bst_node);

    return (f_iter.bst_node == s_iter.bst_node);
}

void *BSTGetData(bst_iterator_t iter)
{
    assert(iter.bst_node);
    return iter.bst_node->data;
}

bst_iterator_t BSTFind(bst_t *bst, const void *data)
{
    bst_iterator_t first;
    bst_iterator_t last;
    int res = 0;

    assert(bst);
    assert(data);

    first = BSTBegin(bst);
    last = BSTEnd(bst);

    /*while not dummy - will return dummy if data not found*/
    while(!BSTIsSameIter(first,last))        
    {
        res = bst->cmp_fun(BSTGetData(first), data, bst->user_param);
        if(0 == res)
        {
            return first;
        }
        first = BSTNext(first);
    }

    return first;
}

int BSTForEach(bst_t *bst, bst_action_func_t action_func, void *data)
{
    /*from begin to end - activate the action func*/
    bst_iterator_t first = BSTIterInit();
    bst_iterator_t last = BSTIterInit();

    assert(action_func);
    assert(bst);

    first = BSTBegin(bst);
    last = BSTEnd(bst);

    while(!BSTIsSameIter(first,last))
    {
        if(1 == action_func((first.bst_node)->data, data))    /*if the function faild return 1 to indicate failure*/
        {
            return 1;
        }
        first = BSTNext(first);
    }
    return 0;
}

bst_iterator_t BSTIterInit(void)
{
    bst_iterator_t iter = {NULL};
    return iter;
}

static int IsLeaf(bst_iterator_t iter)
{
    if(((iter.bst_node)->child[0] == NULL) && ((iter.bst_node)->child[1] == NULL))
    {
        return 1;
    }
    return 0;
}

static int IsNodeWithRightChild(bst_iterator_t iter)
{
    if(((iter.bst_node)->child[1] != NULL) && ((iter.bst_node)->child[0] == NULL))
    {
        return 1;
    }
    return 0;
}
static int IsNodeWithLeftChild(bst_iterator_t iter)
{
    if(((iter.bst_node)->child[0] != NULL) && ((iter.bst_node)->child[1] == NULL))
    {
        return 1;
    }
    return 0;
}