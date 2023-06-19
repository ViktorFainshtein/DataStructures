#include <stdio.h>  /*printf*/
#include <string.h> /*strcmp*/
#include "hash_table.h"

typedef struct tuple
{
    char name[10];
    int grade;
}tuple_t;

int HashActionFunction(void *hash_data, void *param)
{
    if(hash_data == NULL)
    {
        return 0;
    }
    
    ((tuple_t*)hash_data)->grade += 1;
    
    return 1;
}

int HashCompare(const void *a_data, const void *b_data)
{
    if(strcmp(((tuple_t *)(a_data))->name, ((tuple_t *)(b_data))->name) == 0)
    {
        return 1;
    }
    return 0;
}

int HashFunction(void *key)
{
    int res = 0;
    char *str = ((tuple_t *)key)->name;
    while(*str != '\0')
    {
        res += *str;
        ++str;
    }
    return res;
}

int main()
{
    hash_t *table = NULL;
    size_t res = 100;

    tuple_t key1 = {"irit", 99};
    tuple_t key2 = {"roy", 99};
    tuple_t key3 = {"daniel", 99};
    tuple_t key4 = {"nofar", 99};
    
    table = HashCreate(HashCompare, HashFunction, 4);
    if(!table)
    {
        printf("faild to create hash table\n");
    }

    res = HashSize(table);
    if(res != 0)
    {
        printf("incorect hash table size on empty table\n");
    }
    if(!HashIsEmpty(table))
    {
        printf("hash table faild on IsEmpty on empty table\n");
    }

    if(HashInsert(table, &key1) != 0)
    {
        printf("faild to insert first element\n");
    }
    if(HashInsert(table, &key2) != 0)
    {
        printf("faild to insert second element\n");
    }
    if(HashInsert(table, &key3) != 0)
    {
        printf("faild to insert third element\n");
    }
    if(HashInsert(table, &key4) != 0)
    {
        printf("faild to insert forth element\n");
    }

    res = HashSize(table);
    if(res != 4)
    {
        printf("incorect hash table size on inserted table\n");
    }

    if(HashIsEmpty(table))
    {
        printf("hash table faild on IsEmpty on inserted table\n");
    }

    HashRemove(table, &key2);

    res = HashSize(table);
    if(res != 3)
    {
        printf("incorect hash table size after remove\n");
    }
    if(HashIsEmpty(table))
    {
        printf("hash table faild on IsEmpty after one remove\n");
    }

    if(strcmp(((tuple_t *)HashFind(table, &key3))->name, "daniel") != 0)
    {
        printf("faild to find the correct name\n");
    }

    HashForEach(table, HashActionFunction, &res);

    if(((tuple_t *)HashFind(table, &key1))->grade != 100)
    {
        printf("for each faild to add 1 to the grade\n");
        printf("%s\n", ((tuple_t *)HashFind(table, &key1))->name);
        printf("%d\n", ((tuple_t *)HashFind(table, &key1))->grade);
    }
    if(((tuple_t *)HashFind(table, &key3))->grade != 100)
    {
        printf("for each faild to add 1 to the grade\n");
        printf("%s\n", ((tuple_t *)HashFind(table, &key3))->name);
        printf("%d\n", ((tuple_t *)HashFind(table, &key3))->grade);
    }
    if(((tuple_t *)HashFind(table, &key4))->grade != 100)
    {
        printf("for each faild to add 1 to the grade\n");
        printf("%s\n", ((tuple_t *)HashFind(table, &key4))->name);
        printf("%d\n", ((tuple_t *)HashFind(table, &key4))->grade);
    }


    

    HashDestroy(table);

    return 0;
}