#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "heap.h"

typedef struct data
{
    int age;
    char name[10];
}data_t;

/* -----------Test Functions-------------*/
int Test1Vector();

/* --------------Utility Functions ----------*/
static int CompareFunc(const void *a_data, const void *b_data, void *user_param);
static data_t *CreateData(int age, char *name);
static void PrintData(void *data);
static int IsSameData(void *data1, void *data2);
static int IsMatch(const void *a_data, const void *b_data, void *user_param);


int main(void)
{
    Test1Vector();
    return 0;
}

int Test1Vector()
{
    heap_t *heap = HeapCreate(CompareFunc, NULL);

    data_t *data1 = CreateData(16, "Daniel");
    data_t *data2 = CreateData(25, "Yizhak");
    data_t *data3 = CreateData(14, "Shlomi");
    data_t *data4 = CreateData(65, "Rivka");
    data_t *data5 = CreateData(31, "Shmliuk");
    data_t *data6 = CreateData(9, "Zahi");

    assert(HeapIsEmpty(heap) == 1);
    assert(HeapSize(heap) == 0);

    assert(HeapPush(heap, data1) == 0);
    assert(HeapPush(heap, data2) == 0);

    assert(HeapSize(heap) == 2);

    assert(HeapPush(heap, data3) == 0);
    assert(HeapPush(heap, data4) == 0);

    assert(IsSameData(HeapPeek(heap), data3) == 1); /*Until this point data3 is the min*/

    assert(HeapPush(heap, data5) == 0);
    assert(HeapPush(heap, data6) == 0);

    assert(IsSameData(HeapPeek(heap), data6) == 1); /*Until this point data6 is the min*/

    HeapPop(heap);

    assert(IsSameData(HeapPeek(heap), data3) == 1); /*after pop data3 is the min*/

    HeapPop(heap);

    assert(IsSameData(HeapPeek(heap), data1) == 1); /*after pop data1 is the min*/

    assert(HeapPush(heap, data3) == 0);
    assert(HeapPush(heap, data6) == 0); /* inserting again data 3,6 now data6 is min */

    HeapRemove(heap, data6, IsMatch, NULL);

    assert(IsSameData(HeapPeek(heap), data3) == 1); /*after remove data6, data3 is the min*/

    HeapRemove(heap, data3, IsMatch, NULL);
    HeapRemove(heap, data4, IsMatch, NULL);
    HeapRemove(heap, data5, IsMatch, NULL);

    HeapRemove(heap, data6, IsMatch, NULL); /* shouldnt find data6 */
    
    HeapRemove(heap, data2, IsMatch, NULL);
    HeapRemove(heap, data1, IsMatch, NULL);

    assert(HeapIsEmpty(heap) == 1);
    assert(HeapSize(heap) == 0);

    HeapDestroy(heap);
    free(data1);
    free(data2);
    free(data3);
    free(data4);
    free(data5);
    free(data6);

    return(0);
}

static int CompareFunc(const void *a_data, const void *b_data, void *user_param)
{
    (void)user_param;
    return( ((data_t*)b_data)->age < ((data_t*)a_data)->age );
}

static data_t *CreateData(int age, char *name)
{
    data_t *data = malloc(sizeof(data_t));
    data->age = age;
    memcpy(data->name, name, strlen(name));
    return(data);
}  

static void PrintData(void *data)
{
    printf("age is: %d\nname is: %s\n", ((data_t*)data)->age, ((data_t*)data)->name);
}

static int IsSameData(void *data1, void *data2)
{
    return(((data_t*)data1)->age == ((data_t*)data2)->age);
}

static int IsMatch(const void *a_data, const void *b_data, void *user_param)
{
    (void)user_param;
    return(IsSameData((void*)a_data, (void*)b_data));
}
