/*********************************
 * Reviewer: Yohai 				
 * Author: Daniel Binyamin			
 * File: pq_heap_test.c				
 * ******************************/

#include <stdlib.h>/*malloc , free*/
#include <stdio.h>/*printf*/

#include "uid.h"  
#include "priority_queue.h"


typedef struct
{
	void* data;
	char* name; 

}person_t; 

void *param ="";

int pq_compare_func(const void *data1, const void *data2, void *user_param)
{
	
	person_t* p1 = (person_t*)data1;
	person_t* p2 = (person_t*)data2;
	(void)user_param;
	
	return (*(int*)p1 ->data > *(int*)p2 ->data );
}

void CheckCreateDestroy()
{
	pri_queue_t *pq = NULL;
	person_t* p1 = {0};
	person_t* p2 = {0};
	int a = 1 ,b =2;
	
	p1 = (person_t *)malloc(sizeof(person_t));
	p2 = (person_t *)malloc(sizeof(person_t));
	pq = PQueueCreate(pq_compare_func ,param);
	p1 -> data = (void*)&a;
	p2 -> data = (void*)&b;
	PQueueEnQueue(pq,p1);
	PQueueEnQueue(pq,p2);
	
	PQueueDestroy(pq);
	free(p1);
	free(p2);
}

void checkEnDeQueue()
{
	ilrd_uid_t uid1 = UIDGetNull();
	ilrd_uid_t uid2 = UIDGetNull();
	person_t* p1 = {0};
	person_t* p2 = {0};
	pri_queue_t *pq = NULL;
	int a = 1 ,b =2;
	
	p1 = (person_t *)malloc(sizeof(person_t));
	p2 = (person_t *)malloc(sizeof(person_t));
	pq = PQueueCreate(pq_compare_func ,param);
	
	p1 -> data = (void*)&a;
	p2 -> data = (void*)&b;
	
	uid1 = PQueueEnQueue(pq,p1);
	uid2 = PQueueEnQueue(pq,p2);
	
	if(2 != PQueueSize(pq))
	{
		printf("ENQ (1) Error\n");
	
	}
	PQueueDeQueue(pq);
	PQueueDeQueue(pq);
	
	if(0 != PQueueSize(pq))
	{
		printf("DEQ Error\n");
	
	}
	
	free(p1);
	free(p2);
	
	(void)uid1;
	(void)uid2;

	PQueueDestroy(pq);

}

void checkPeekSizeIsEmptyClear()
{

	ilrd_uid_t uid1 = UIDGetNull(),
		   uid2 = UIDGetNull(),
	           uid3 = UIDGetNull(),
		   uid4 = UIDGetNull();
	
	person_t* p1 = {0}, *p2 = {0}, *p3 = {0}, *p4 = {0};
	pri_queue_t *pq = NULL;
	int a = 1 ,b =2 , c=3 ,d = 4;
	
	p1 = (person_t *)malloc(sizeof(person_t));
	p2 = (person_t *)malloc(sizeof(person_t));
	p3 = (person_t *)malloc(sizeof(person_t));
	p4 = (person_t *)malloc(sizeof(person_t));
	
	pq = PQueueCreate(pq_compare_func ,param);
	
	if(1 != PQueueIsEmpty(pq))
	{
		printf("IsEmpty (1) Error\n");
	
	}
	
	p1 -> data = (void*)&a;
	p2 -> data = (void*)&b;
	p3 -> data = (void*)&c;
	p4 -> data = (void*)&d;
	
	uid1 = PQueueEnQueue(pq,p1);
	uid2 = PQueueEnQueue(pq,p2);
	uid3 = PQueueEnQueue(pq,p3);
	uid4 = PQueueEnQueue(pq,p4);
	
	if(4 != PQueueSize(pq))
	{
		printf("Size (1) Error\n");
	
	}
	if(0 != PQueueIsEmpty(pq))
	{
		printf("IsEmpty (2) Error\n");
	
	}
	
	PQueueClear(pq);
	free(p1);
	free(p2);
	free(p3);
	free(p4);
	if(0 != PQueueSize(pq))
	{
		printf("Size  or clear(2) Error\n");
	
	}
	(void)uid1;
	(void)uid2;
	(void)uid3;
	(void)uid4;
	
	PQueueDestroy(pq);
}

void checkErase()
{
	ilrd_uid_t uid1 = UIDGetNull(),
		   uid2 = UIDGetNull(),
	           uid3 = UIDGetNull(),
		   uid4 = UIDGetNull(),
		   uid_test = UIDGetNull();
	
	person_t* p1 = {0}, *p2 = {0}, *p3 = {0}, *p4 = {0};
	pri_queue_t *pq = NULL;
	int a = 7 ,b =5 , c=3 ,d = 4;
	char a_n = 'a', b_n = 'b' , c_n = 'c' , d_n = 'd';
	 
	p1 = (person_t *)malloc(sizeof(person_t));
	p2 = (person_t *)malloc(sizeof(person_t));
	p3 = (person_t *)malloc(sizeof(person_t));
	p4 = (person_t *)malloc(sizeof(person_t));
	
	pq = PQueueCreate(pq_compare_func ,param);
	
	p1 -> data = (void*)&a;
	p1 -> name = &a_n;
	p2 -> data = (void*)&b;
	p2 -> name = &b_n;
	p3 -> data = (void*)&c;
	p3 -> name = &c_n;
	p4 -> data = (void*)&d;
	p4 -> name = &d_n;
	
	uid1 = PQueueEnQueue(pq,p1);
	uid2 = PQueueEnQueue(pq,p2);
	uid3 = PQueueEnQueue(pq,p3);
	uid4 = PQueueEnQueue(pq,p4);

	if('a' != *((person_t*)PQueuePeek(pq))-> name)
	{
		printf("Peek Error\n");
	}
	PQueueErase(pq,uid1);
	
	if('b' != *((person_t*)PQueuePeek(pq))-> name)
	{
		printf("Peek (2) / Erase (1) Error\n");
	}

	PQueueErase(pq,g_bad_uid);
	if('b' != *((person_t*)PQueuePeek(pq))-> name)
	{
		printf("Peek (2) / Erase (1) Error\n");
	}

	PQueueErase(pq,uid3);
	if(2 != PQueueSize(pq))
	{
		printf("Erase (1) Error\n");
	}
	
	if('b' != *((person_t*)PQueuePeek(pq))-> name)
	{
		printf("Erase (2) Error\n");
	}
	uid_test = PQueueDeQueue(pq);
	if(!UIDIsSame(uid_test , uid2))
	{
		printf("DEQ UID_test Error\n");	
	
	}
	if('d' != *((person_t*)PQueuePeek(pq))-> name)
	{
		printf("Erase (3) Error\n");
	}
	PQueueDeQueue(pq);
	if(1 != PQueueIsEmpty(pq))
	{
		printf("Erase (4) Error\n");
	
	}

	free(p1);
	free(p2);
	free(p3);
	free(p4);
	
	(void)uid1;
	(void)uid2;
	(void)uid3;
	(void)uid4;
	
	PQueueDestroy(pq);

}

int main()
{
    CheckCreateDestroy();
   	checkEnDeQueue();
	checkPeekSizeIsEmptyClear();
	checkErase();

	return 0;
}
