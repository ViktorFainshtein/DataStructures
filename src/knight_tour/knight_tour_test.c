

#include <stdio.h>
#include <stdlib.h> /*malloc free*/
#include "knight_tour.h"

void PrintBoard(int *res);

int main()
{
    position_t pos = {3,5};
    int *res = NULL;
    res = (int *)malloc(sizeof(int) * 64);

    KnightTour(pos, res);
    PrintBoard(res);

    free(res);

    return 0;
}

void PrintBoard(int *res)
{
    int i = 0;
    printf("the path of the mighty knight is:\n");
    for(i=0;i<64;i++)
    {
        if(i % 8 == 0)
        {
            printf("\n");
        }
        printf("%d\t", *(res+i));
    }
    printf("\n");
}