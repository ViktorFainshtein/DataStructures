

#include <stdlib.h> /*malloc free strtod */
#include <string.h> /*strlen*/

#include "stack.h"
#include "calculator.h"

stack_t *operators, *output;

static char PeekWrapper(stack_t *operators)
{
    char operator = '0';
    StackPeek(operators, &operator);
    return operator;
}

typedef void (*action_func_t)();

static action_func_t Handler[58];

static action_func_t Execute[48];

int pres_LUT[128] = {0};

static void InitHandler(void);
static void InitPresLUT(void);
static void InitExecute(void);
static void HandleOperand(char **exp);
static void HandleSpace(char **exp);
static void HandleOperator(char **exp);
static int PrecedenceLessEqual(char currOper , char oper);
static void AddTwoNums();
static void SubTwoNums();
static void MultTwoNums();
static void DivTwoNums();
static void HandleOpenBracket(char **exp);
static void HandleCloseBracket(char **exp);

double Calculate(const char* expression)
{
    double res = 0;
    char *exp_ptr = NULL;
    char **temp_add_ptr = NULL;
    exp_ptr = (char*)expression;
    /*Create:*/
    operators = StackCreate(strlen(expression),sizeof(char));
    output = StackCreate(strlen(expression),sizeof(double));
    /*Init:*/
    InitHandler();
    InitPresLUT();
    InitExecute();
    /*Execute:*/
    while('\0' != *exp_ptr)
    {
        temp_add_ptr = &exp_ptr;
        Handler[(int)(*(exp_ptr))](temp_add_ptr);
    }
    while (!StackIsEmpty(operators))
    {
        Execute[(int)PeekWrapper(operators)]();
    }
    /*Clean-Up:*/
    StackPeek(output, &res);
    StackDestroy(output);
    StackDestroy(operators);

    return res;
}

static void InitHandler(void)
{
    Handler['0'] = HandleOperand;
    Handler['1'] = HandleOperand;
    Handler['2'] = HandleOperand;
    Handler['3'] = HandleOperand;
    Handler['4'] = HandleOperand;
    Handler['5'] = HandleOperand;
    Handler['6'] = HandleOperand;
    Handler['7'] = HandleOperand;
    Handler['8'] = HandleOperand;
    Handler['9'] = HandleOperand;

    Handler[' '] = HandleSpace;
    Handler['+'] = HandleOperator;
    Handler['-'] = HandleOperator;
    Handler['*'] = HandleOperator;
    Handler['/'] = HandleOperator;
    Handler['('] = HandleOpenBracket;
    Handler[')'] = HandleCloseBracket;
}

static void InitPresLUT(void)
{
    pres_LUT['('] = 0;
    pres_LUT['+'] = 1;
    pres_LUT['-'] = 1;
    pres_LUT['*'] = 2;
    pres_LUT['/'] = 2;
    pres_LUT[')'] = 3;
}

static void InitExecute(void)
{
    Execute['+'] = AddTwoNums; 
    Execute['-'] = SubTwoNums;
    Execute['*'] = MultTwoNums;
    Execute['/'] = DivTwoNums;
}

static void HandleOperand(char **exp)
{
    double num = 0;
    num = strtod(*exp, exp); 
    StackPush(output, &num);
}

static void HandleSpace(char **exp)
{
    ++*exp;
}


static void HandleOperator(char **exp)
{
    while ((!StackIsEmpty(operators)) && (PrecedenceLessEqual(**exp , PeekWrapper(operators)) <= 0))
    {
        Execute[(int)PeekWrapper(operators)]();
    }
    StackPush(operators, *exp);
    ++*exp;
}

static void HandleOpenBracket(char **exp)
{
    StackPush(operators, *exp);
    ++*exp;
}

static void HandleCloseBracket(char **exp)
{
    while (0 != PrecedenceLessEqual('(', PeekWrapper(operators)))
    {
        Execute[(int)PeekWrapper(operators)]();
    }
    StackPop(operators);
    ++*exp;
}

static int PrecedenceLessEqual(char currOper , char oper)
{
    return (pres_LUT[(int)currOper] - pres_LUT[(int)oper]);
}

static void AddTwoNums()
{
    double first = 0;
    double sec = 0;
    double res = 0;

    StackPop(operators);
    StackPeek(output, &first);
    StackPop(output);
    StackPeek(output, &sec);
    StackPop(output);

    res = sec + first;
    StackPush(output, &res);
}

static void SubTwoNums()
{
    double first = 0;
    double sec = 0;
    double res = 0;

    StackPop(operators);
    StackPeek(output, &first);
    StackPop(output);
    StackPeek(output, &sec);
    StackPop(output);

    res = sec - first;
    StackPush(output, &res);
}

static void MultTwoNums()
{
    double first = 0;
    double sec = 0;
    double res = 0;

    StackPop(operators);
    StackPeek(output, &first);
    StackPop(output);
    StackPeek(output, &sec);
    StackPop(output);

    res = sec * first;
    StackPush(output, &res);
}

static void DivTwoNums()
{
    double first = 0;
    double sec = 0;
    double res = 0;

    StackPop(operators);
    StackPeek(output, &first);
    StackPop(output);
    StackPeek(output, &sec);
    StackPop(output);

    res = sec / first;
    StackPush(output, &res);
}