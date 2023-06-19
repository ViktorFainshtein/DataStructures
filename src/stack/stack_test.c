/******************************
Reviewer: Irit Ofir
Author: Viktor Fainshtein
File: test.c
******************************/

#include <stdio.h>	/* printf */
#include "stack.h"	/*StackCreate StackPush StackPop StackPeek StackIsEmpty StackDestroy StackCapacity StackSize*/

void TestCreateByType();
	
void TestFillTheStack();
	
void TestEmptyTheStuck();

void TestPushDiffrentTypes();

void TestPopDiffrentTypes();
	
void TestIsEmptyDiffrentTypes();

int main()
{
	TestCreateByType();
	
	TestFillTheStack();
	
	TestEmptyTheStuck();
	
	TestPushDiffrentTypes();
	
	TestPopDiffrentTypes();
	
	TestIsEmptyDiffrentTypes();
	
	return 0;
}


void TestCreateByType()
{
	int size1 = sizeof(int);
	char size2 = sizeof(char);
	float size3 = sizeof(float);
	double size4 = sizeof(double);
	
	stack_t *stack1 = StackCreate(1, size1);
	stack_t *stack2 = StackCreate(1, size2);
	stack_t *stack3 = StackCreate(1, size3);
	stack_t *stack4 = StackCreate(1, size4);
	
	if(stack1 == NULL)
	{
		printf("Failed to create int type stack\n");
	}
	if(stack2 == NULL)
	{
		printf("Failed to create char type stack\n");
	}
	if(stack3 == NULL)
	{
		printf("Failed to create float type stack\n");
	}
	if(stack4 == NULL)
	{
		printf("Failed to create double type stack\n");
	}
	
	StackDestroy(stack1);
	StackDestroy(stack2);
	StackDestroy(stack3);
	StackDestroy(stack4);
}

void TestFillTheStack()
{
	int size = sizeof(int);
	stack_t *s = StackCreate(5, size);
	int push_number = 1;
	int num_of_elements = StackCapacity(s);
	printf("Stack size before Fill: %ld\n", StackSize(s));
	while(num_of_elements)
	{
		StackPush(s, &push_number);
		--num_of_elements;
		++push_number;
	}
	printf("Stack size after Fill: %ld\n", StackSize(s));
	StackDestroy(s);
}

void TestEmptyTheStuck()
{
	int size = sizeof(int);
	stack_t *s = StackCreate(5, size);
	int push_number = 1;
	int num_of_elements = StackCapacity(s);
	while(num_of_elements)
	{
		StackPush(s, &push_number);
		--num_of_elements;
		++push_number;
	}
	printf("Stack size before Empty: %ld\n", StackSize(s));
	num_of_elements = StackCapacity(s);
	while(num_of_elements)
	{
		StackPop(s);
		--num_of_elements;
	}
	printf("Stack size after Empty: %ld\n", StackSize(s));
	StackDestroy(s);
}

void TestPushDiffrentTypes()
{
	int size1 = sizeof(int);
	char size2 = sizeof(char);
	double size3 = sizeof(double);
	stack_t *s1 = StackCreate(5, size1);
	stack_t *s2 = StackCreate(5, size2);
	stack_t *s3 = StackCreate(5, size3);
	int number = 1;
	char element = 'a';
	double real_num = 2.3;
	StackPush(s1, &number);
	StackPeek(s1, &number);
	printf("int was added to the stack, stack top is: %d\nStack size after push: %ld\n", number, StackSize(s1));
	StackPush(s2, &element);
	StackPeek(s2, &number);
	printf("char was added to the stack, stack top is: %c\nStack size after push: %ld\n", element, StackSize(s2));
	StackPush(s3, &real_num);
	StackPeek(s3, &number);
	printf("double was added to the stack, stack top is: %f\nStack size after push: %ld\n", real_num, StackSize(s3));
	StackDestroy(s1);
	StackDestroy(s2);
	StackDestroy(s3);
}

void TestPopDiffrentTypes()
{
	int size1 = sizeof(int);
	char size2 = sizeof(char);
	double size3 = sizeof(double);
	stack_t *s1 = StackCreate(5, size1);
	stack_t *s2 = StackCreate(5, size2);
	stack_t *s3 = StackCreate(5, size3);
	int number = 1;
	char element = 'a';
	double real_num = 2.3;
	StackPush(s1, &number);
	StackPush(s2, &element);
	StackPush(s3, &real_num);
	StackPop(s1);
	StackPop(s2);
	StackPop(s3);
	printf("Int Stack IsEmpty After Pop: %d\nInt Stack Size After Pop: %ld\n", StackIsEmpty(s1), StackSize(s1));
	printf("Char Stack IsEmpty After Pop: %d\nChar Stack Size After Pop: %ld\n", StackIsEmpty(s2), StackSize(s2));
	printf("Double Stack IsEmpty After Pop: %d\nDouble Stack Size After Pop: %ld\n", StackIsEmpty(s3), StackSize(s3));
	StackDestroy(s1);
	StackDestroy(s2);
	StackDestroy(s3);
}

void TestIsEmptyDiffrentTypes()
{	
	int size1 = sizeof(int);
	char size2 = sizeof(char);
	double size3 = sizeof(double);
	stack_t *s1 = StackCreate(5, size1);
	stack_t *s2 = StackCreate(5, size2);
	stack_t *s3 = StackCreate(5, size3);
	int number = 1;
	char element = 'a';
	double real_num = 2.3;
	printf("Before Push:\n");
	printf("Is Int Stack Empty: %d\n", StackIsEmpty(s1));
	printf("Is Char Stack Empty: %d\n", StackIsEmpty(s2));
	printf("Is Double Stack Empty: %d\n", StackIsEmpty(s3));
	StackPush(s1, &number);
	StackPush(s2, &element);
	StackPush(s3, &real_num);
	printf("After Push:\n");
	printf("Is Int Stack Empty: %d\n", StackIsEmpty(s1));
	printf("Is Char Stack Empty: %d\n", StackIsEmpty(s2));
	printf("Is Double Stack Empty: %d\n", StackIsEmpty(s3));
	StackDestroy(s1);
	StackDestroy(s2);
	StackDestroy(s3);
}








