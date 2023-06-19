/******************************
Reviewer: Daniel Natan
Author: Viktor Fainshtein
File: vector.h
******************************/
#include <stdio.h>	/* printf */
#include "vector.h"	/* VectorCreate  */

void TestCreateDiffrentVectors();
void TestDiffrentVectorPush();
void TestDiffrentCapacityUpdate();
void TestDiffrentVectorPop();
void TestDiffrentIsEmpty();
void TestDiffrentGetAccess();
void TestDiffrentShrinkToFit();
void TestDiffrentVectorReserve();

int main()
{
	TestCreateDiffrentVectors();
	
	TestDiffrentVectorPush();

	TestDiffrentCapacityUpdate();
	
	TestDiffrentVectorPop();
	
	TestDiffrentIsEmpty();
	
	TestDiffrentGetAccess();
	
	TestDiffrentShrinkToFit();
	
	TestDiffrentVectorReserve();
	
	return 0;
}

void TestCreateDiffrentVectors()
{
	vector_t *vec_int = VectorCreate(5, sizeof(int));
	vector_t *vec_char = VectorCreate(5, sizeof(char));
	vector_t *vec_double = VectorCreate(5, sizeof(double));
	
	if(vec_int == NULL)
	{
		printf("Failed to create vector of int type.\n");
	}
	if(vec_char == NULL)
	{
		printf("Failed to create vector of char type.\n");
	}
	if(vec_double == NULL)
	{
		printf("Failed to create vector of double type.\n");
	}
	
	VectorDestroy(vec_int);
	VectorDestroy(vec_char);
	VectorDestroy(vec_double);
}

void TestDiffrentVectorPush()
{
	int i = 0;
	int size = 5;
	vector_t *vec_int = VectorCreate(size, sizeof(int));
	vector_t *vec_char = VectorCreate(size, sizeof(char));
	vector_t *vec_double = VectorCreate(size, sizeof(double));
	int *v_i = NULL;
	char *v_c = NULL;
	double *v_d = NULL;
	int push_i_val = 1;
	char  push_c_val = 'a';
	double push_d_val = 12.3;
	
	while(++i != size-2)
	{
		VectorPush(vec_int, &push_i_val);
	}
	v_i = VectorGetAccess(vec_int, VectorSize(vec_int)-1);
	printf("Top vector is: %d\nCapacity is: %ld\nNumber of Elements: %ld\n", *v_i, VectorCapacity(vec_int), VectorSize(vec_int));
	
	i = 0;
	while(++i != size-2)
	{
		VectorPush(vec_char, &push_c_val);
	}
	v_c = VectorGetAccess(vec_char, VectorSize(vec_char)-1);
	printf("Top vector is: %c\nCapacity is: %ld\nNumber of Elements: %ld\n", *v_c, VectorCapacity(vec_char), VectorSize(vec_char));
	
	i = 0;
	while(++i != size-2)
	{
		VectorPush(vec_double, &push_d_val);
	}
	v_d = VectorGetAccess(vec_double, VectorSize(vec_double)-1);
	printf("Top vector is: %f\nCapacity is: %ld\nNumber of Elements: %ld\n", *v_d, VectorCapacity(vec_double), VectorSize(vec_double));

	VectorDestroy(vec_int);
	VectorDestroy(vec_char);
	VectorDestroy(vec_double);
}

void TestDiffrentCapacityUpdate()
{	
	int size = 3;
	int i = 0;
	vector_t *vec_int = VectorCreate(size, sizeof(int));
	vector_t *vec_char = VectorCreate(size, sizeof(char));
	vector_t *vec_double = VectorCreate(size, sizeof(double));
	int push_i_val = 1;
	char  push_c_val = 'a';
	double push_d_val = 12.3;
	
	printf("Int vector capacity before max push: %ld\n", VectorCapacity(vec_int));
	while(i++<size)
	{
		VectorPush(vec_int, &push_i_val);
	}
	printf("Int vector capacity after max push: %ld\n", VectorCapacity(vec_int));
	
	i = 0;
	printf("Int vector capacity before max push: %ld\n", VectorCapacity(vec_char));
	while(i++<size)
	{
		VectorPush(vec_char, &push_c_val);
	}
	printf("Char vector capacity after max push: %ld\n", VectorCapacity(vec_char));
	
	i = 0;
	printf("Int vector capacity before max push: %ld\n", VectorCapacity(vec_double));
	while(i++<size)
	{
		VectorPush(vec_double, &push_d_val);
	}
	printf("Double vector capacity after max push: %ld\n", VectorCapacity(vec_double));

	VectorDestroy(vec_int);
	VectorDestroy(vec_char);
	VectorDestroy(vec_double);
}

void TestDiffrentVectorPop()
{
	vector_t *vec_int = VectorCreate(1, sizeof(int));
	vector_t *vec_char = VectorCreate(1, sizeof(char));
	vector_t *vec_double = VectorCreate(1, sizeof(double));
	int push_i_val = 1;
	char  push_c_val = 'a';
	double push_d_val = 12.3;
	
	VectorPush(vec_int, &push_i_val);
	VectorPush(vec_char, &push_c_val);
	VectorPush(vec_double, &push_d_val);
	
	printf("Before Pop:\nvector int size: %ld\tvector char size: %ld\tvector double size: %ld\n", VectorSize(vec_int), VectorSize(vec_char), VectorSize(vec_double));
	
	VectorPop(vec_int);
	VectorPop(vec_char);
	VectorPop(vec_double);
	
	printf("After Pop:\nvector int size: %ld\tvector char size: %ld\tvector double size: %ld\n", VectorSize(vec_int), VectorSize(vec_char), VectorSize(vec_double));
	
	VectorDestroy(vec_int);
	VectorDestroy(vec_char);
	VectorDestroy(vec_double);
}

void TestDiffrentIsEmpty()
{
	int size = 3;
	int i = 0;
	vector_t *vec_int = VectorCreate(size, sizeof(int));
	vector_t *vec_char = VectorCreate(size, sizeof(char));
	vector_t *vec_double = VectorCreate(size, sizeof(double));
	int push_i_val = 1;
	char  push_c_val = 'a';
	double push_d_val = 12.3;
	
	while(2 != i)
	{
	VectorPush(vec_int, &push_i_val);
	VectorPush(vec_char, &push_c_val);
	VectorPush(vec_double, &push_d_val);
	i++;
	}
	
	printf("Before Push:\n");
	printf("Int vector size: %ld\tIs empty: %d\n", VectorSize(vec_int), VectorIsEmpty(vec_int));
	printf("Char vector size: %ld\tIs empty: %d\n", VectorSize(vec_char), VectorIsEmpty(vec_char));
	printf("Double vector size: %ld\tIs empty: %d\n", VectorSize(vec_double), VectorIsEmpty(vec_double));
	
	while(0 != i)
	{
		VectorPop(vec_int);
		VectorPop(vec_char);
		VectorPop(vec_double);
		i--;
	}
	
	printf("After Pop:\n");
	printf("Int vector size: %ld\tIs empty: %d\n", VectorSize(vec_int), VectorIsEmpty(vec_int));
	printf("Char vector size: %ld\tIs empty: %d\n", VectorSize(vec_char), VectorIsEmpty(vec_char));
	printf("Double vector size: %ld\tIs empty: %d\n", VectorSize(vec_double), VectorIsEmpty(vec_double));
	
	VectorDestroy(vec_int);
	VectorDestroy(vec_char);
	VectorDestroy(vec_double);	
}

void TestDiffrentGetAccess()
{
	int i = 0;
	int size = 3;
	int *v_i = NULL;
	char *v_c = NULL;
	double *v_d = NULL;
	vector_t *vec_int = VectorCreate(size, sizeof(int));
	vector_t *vec_char = VectorCreate(size, sizeof(char));
	vector_t *vec_double = VectorCreate(size, sizeof(double));
	int push_i_val = 1;
	char  push_c_val = 'a';
	double push_d_val = 12.3;
	
	while(3 != i)
	{
		VectorPush(vec_int, &push_i_val);
		VectorPush(vec_char, &push_c_val);
		VectorPush(vec_double, &push_d_val);
		i++;
	}

	v_i = VectorGetAccess(vec_int, 0);
	v_c = VectorGetAccess(vec_char, 1);
	v_d = VectorGetAccess(vec_double, 2);
	
	printf("int vec from index 0 is: %d\nint vec size is: %ld\n", *v_i, VectorSize(vec_int));
	printf("char vec from index 1 is: %c\nchar vec size is: %ld\n", *v_c, VectorSize(vec_char));
	printf("double vec from index 2 is: %f\ndouble vec size is: %ld\n", *v_d, VectorSize(vec_double));

	VectorDestroy(vec_int);
	VectorDestroy(vec_char);
	VectorDestroy(vec_double);
}

void TestDiffrentShrinkToFit()
{
	int i = 0;
	int size = 5;
	vector_t *vec_int = VectorCreate(size, sizeof(int));
	vector_t *vec_char = VectorCreate(size, sizeof(char));
	vector_t *vec_double = VectorCreate(size, sizeof(double));
	int push_i_val = 1;
	char  push_c_val = 'a';
	double push_d_val = 12.3;
	
	while(3 != i)
	{
		VectorPush(vec_int, &push_i_val);
		VectorPush(vec_char, &push_c_val);
		VectorPush(vec_double, &push_d_val);
		i++;
	}
	
	printf("Int vector size before shrink: %ld\nInt vector capacity before shrink: %ld\n", VectorSize(vec_int), VectorCapacity(vec_int));
	printf("Char vector size before shrink: %ld\nChar vector capacity before shrink: %ld\n", VectorSize(vec_char), VectorCapacity(vec_char));
	printf("Double vector size before shrink: %ld\nDouble vector capacity before shrink: %ld\n", VectorSize(vec_double), VectorCapacity(vec_double));
	
	VectorShrinkToFit(vec_int);
	VectorShrinkToFit(vec_char);
	VectorShrinkToFit(vec_double);
	
	printf("Int vector size after shrink: %ld\nInt vector capacity after shrink: %ld\n", VectorSize(vec_int), VectorCapacity(vec_int));
	printf("Char vector size after shrink: %ld\nChar vector capacity after shrink: %ld\n", VectorSize(vec_char), VectorCapacity(vec_char));
	printf("Double vector size after shrink: %ld\nDouble vector capacity after shrink: %ld\n", VectorSize(vec_double), VectorCapacity(vec_double));
	
	VectorDestroy(vec_int);
	VectorDestroy(vec_char);
	VectorDestroy(vec_double);
}

void TestDiffrentVectorReserve()
{
	int size = 3;
	vector_t *vec_int = VectorCreate(size, sizeof(int));
	vector_t *vec_char = VectorCreate(size, sizeof(char));
	vector_t *vec_double = VectorCreate(size, sizeof(double));

	printf("Int vector capacity before Reserve(size %d): %ld\n", size, VectorCapacity(vec_int));
	printf("Int vector capacity before Reserve(size %d): %ld\n", size, VectorCapacity(vec_char));
	printf("Int vector capacity before Reserve(size %d): %ld\n", size, VectorCapacity(vec_double));
	
	size = 8;
	VectorReserve(vec_int, (size_t)size);
	VectorReserve(vec_char, (size_t)size);
	VectorReserve(vec_double, (size_t)size);
	
	printf("Int vector capacity after Reserve(new size %d): %ld\n", size, VectorCapacity(vec_int));
	printf("Int vector capacity after Reserve(new size %d): %ld\n", size, VectorCapacity(vec_char));
	printf("Int vector capacity after Reserve(new size %d): %ld\n", size, VectorCapacity(vec_double));
	
	VectorDestroy(vec_int);
	VectorDestroy(vec_char);
	VectorDestroy(vec_double);
}


































