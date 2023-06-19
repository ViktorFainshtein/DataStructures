/*********************************
 * Reviewer: Daniel Natan
 * Author: Viktor Fainshttein
 * File Name: recursion.c
 * ******************************/
#include <stdio.h>  /*printf*/
#include <string.h> /*strcmp*/
#include "../../include/stack.h"

typedef struct Node Node_t;

struct Node
{
    int data;
    Node_t *next;
};

void CheckFibo();
int RecFibonacci(int element_index);
int Fibonacci(int element_index);

void CheckFlip();
Node_t* FlipList(Node_t* node);

void CheckSortStuck();
stack_t *SortStack(stack_t *stack);
void SortedInsert(stack_t *stack, int elem);

void CheckStrFunctions();
size_t StrLen(const char *str);
int StrCmp (const char* str1, const char* str2);
char* StrCpy(char* destination, const char* source);
char *StrCat(char *destination, const char *source);
char *StrStr(const char *haystack, const char *needle);

int main()
{
    /*CheckFibo();*/
    CheckFlip();
    /*CheckStrFunctions();*/
    /*CheckSortStuck();*/

    return 0;
}

void CheckFibo()
{
    int res = 0;
    
    res = Fibonacci(6);
    printf("res = %d\n", res);
    
    res = RecFibonacci(6);
    printf("res = %d\n", res);
}

int RecFibonacci(int element_index)
{
    if(element_index == 0)
    {
        return 0;
    }
    else if (element_index == 1)
    {
        return 1;
    }
    return  RecFibonacci(element_index-1) + RecFibonacci(element_index-2);
}

int Fibonacci(int element_index)
{
    int curr = 0;
    int next = 1;
    int res = 0;

    --element_index;

    while (element_index)
    {
        res = curr + next;
        curr = next;
        next = res;
        --element_index;
    }
    return res;
}

void CheckFlip()
{
    Node_t node1 = {1, NULL};
    Node_t node2 = {2, NULL};
    Node_t node3 = {3, NULL};
    Node_t node4 = {4, NULL};

    Node_t *iter1 = NULL;

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;

    iter1 = &node1;

    while (iter1 != NULL)
    {
        printf("data: %d\n", iter1->data);
        iter1 = iter1->next;
    }

    iter1 = FlipList(&node1);

    while (iter1 != NULL)
    {
        printf("data: %d\n", iter1->data);
        iter1 = iter1->next;
    }

}

Node_t* FlipList(Node_t* node)
{
    Node_t *temp = NULL;
    
    if(node->next == NULL)
    {
        return node;
    }
    temp = FlipList(node->next);
    node->next->next = node;
    node->next = NULL;
    
    return temp;
}

void CheckSortStuck()
{
    stack_t *stack = StackCreate(10, sizeof(int));
    int num1 = 9;
    int num2 = 4;
    int num3 = 6;
    int num4 = 1;
    int num5 = 2;
    int num6 = 5;
    int num7 = 3;
    int num8 = 8;
    int num9 = 7;

    StackPush(stack,&num1);
    StackPush(stack,&num2);
    StackPush(stack,&num3);
    StackPush(stack,&num4);
    StackPush(stack,&num5);
    StackPush(stack,&num6);
    StackPush(stack,&num7);
    StackPush(stack,&num8);
    StackPush(stack,&num9);

    stack = SortStack(stack);

    while(!StackIsEmpty(stack))
    {
        StackPeek(stack, &num1);
        printf("data: %d\n", num1);
        StackPop(stack);
    }

}

/*extract all elements from the struct and insert them back in order*/
stack_t *SortStack(stack_t *stack)
{
    int elem;
    if (StackSize(stack) > 1)
    {
        StackPeek(stack, &elem);
        StackPop(stack);
        SortStack(stack);
        SortedInsert(stack, elem);
    }
    return stack;
}


void SortedInsert(stack_t *stack, int elem)
{
    int temp_num = 0;
    StackPeek(stack, &temp_num);
    if(StackIsEmpty(stack) || elem > temp_num)
    {
        StackPush(stack, &elem);
        return;
    }
    StackPop(stack);
    SortedInsert(stack, elem);

    StackPush(stack, &temp_num);
}

void CheckStrFunctions()
{
    char str_len[50] = {" this is a string"};
    char str_a[50] = {"this is also a string"};
    char str_b[50] = {"this is also a string"};
    char str_c[50] = {"this string is not like the others"};
    
    char *temp = NULL;

    printf("string length: %ld\n", StrLen(str_len));
    
    printf("string compare a & b: %d\n", StrCmp(str_a, str_b));
    printf("string compare a & c: %d\n", StrCmp(str_a, str_c));

    temp = StrCpy(str_c,str_a);
    printf("string copy a to c: %s\n", temp);

    temp = StrCat(str_b, str_len);
    printf("string concate len to b: %s\n", temp);

    printf("string strstr b & len: %s\n", StrStr(str_b, str_len));
}

size_t StrLen(const char *str)
{
    if(*str == '\0')
    {
        return 0;
    }
    return (1 + StrLen(str+1));
}

int StrCmp(const char* str1, const char* str2)
{
    if(*str1 == '\0' && *str2 == '\0')
    {
        return 0;
    }
    else if(*str1 != *str2)
    {
        return (*str1 - *str2);
    }
    return StrCmp(str1+1, str2+1);
}

char* StrCpy(char* destination, const char* source)
{
    if(*source == '\0')
    {
        *destination = *source;
        return destination;
    }

    *destination = *source;
    
    return StrCpy(destination+1, source+1) -1;
}

char *StrCat(char *destination, const char *source)
{
    if(*destination != '\0')
    {
        return StrCat(destination+1, source) -1; 
    }
    if(*source == '\0')
    {
        *destination = '\0';
        return destination;
    }
    *destination = *source;
    
    return StrCat(destination+1, source+1) -1;
}

char *StrStr(const char *haystack, const char *needle)
{
    if(*haystack == '\0')
    {
        return NULL;
    }
    if(strncmp(haystack,needle,StrLen(needle)) == 0)
    {
        return (char *)needle;
    }

    return StrStr(haystack+1, needle);
}