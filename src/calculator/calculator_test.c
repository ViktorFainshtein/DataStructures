#include <stdlib.h> /*malloc free strtod */
#include <stdio.h>  /*printf*/

#include "calculator.h"



int main()
{
    double res = 0;
    char str[50] = {"2*(3+5)*8/2"};   /*2*(3+5)*8/2*/
    char str2[100] = {"412+3+2-5+7-4+( (3.25 + 2.17) * 45.87 + 5.2 /2*4 - (8 + 9) ) / 7"};    
    res = Calculate(str);
    printf("res: %f\n", res);

    res = Calculate(str2);
    printf("res: %f\n", res);

    return 0;
}