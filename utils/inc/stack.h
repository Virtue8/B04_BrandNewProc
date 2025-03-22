#ifndef STACK_H
#define STACK_H

//--------------------------------------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

const int STACK_VERSION = 1;

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"

#define COLORED_LINE(COLOR, ...)    \
    printf ("%s", COLOR);           \
    printf (__VA_ARGS__);           \
    printf ("%s", RESET)

typedef long int StackElem_t;
const StackElem_t CANARY_VALUE = 0xC0110CF00;

//--------------------------------------------------------//

struct Stack
{
    StackElem_t LeftCanary  = CANARY_VALUE;

    StackElem_t * Data      = NULL;
    size_t Size             = 0;
    size_t Capacity         = 0;

    int ErrorCode           = 0;
    
    StackElem_t RightCanary = CANARY_VALUE;
};

enum StackErrorCodes 
{
    ERR                     = 0,
    STACK_OVERFLOW          = 1,
    NULL_DATA_POINTER       = 2,
    NULL_STRUCT_POINTER     = 3,
    LEFT_CANARY_DEATH       = 4,
    RIGHT_CANARY_DEATH      = 5,
    SIZE_ERR                = 6,
    CAPACITY_ERR            = 7,
    REALLOC_ERR             = 8,
    POP_ERR                 = 9,
};

enum ReallocMode 
{
    RM_POP,
    RM_PUSH
};

const double EPSILON = pow (10, -6);

const char ErrorMessages[12][50] = {"Construction error\n", 
                                    "Stack is overflowed\n", 
                                    "NULL data pointer\n",
                                    "NULL struct pointer\n",
                                    "Data destruction from left side\n",
                                    "Data destruction from right side\n",
                                    "Size error\n",
                                    "Capacity error\n",
                                    "Reallocation error\n",
                                    "StackPop error: minimum size limit\n"};

//--------------------------------------------------------//

StackElem_t StackPush   (struct Stack * stk, StackElem_t unit);
StackElem_t StackPop    (struct Stack * stk);

StackElem_t StackAdd    (struct Stack * stk);
StackElem_t StackSub    (struct Stack * stk);
StackElem_t StackMul    (struct Stack * stk);
StackElem_t StackDiv    (struct Stack * stk);
StackElem_t StackSqrt   (struct Stack * stk);
StackElem_t StackSin    (struct Stack * stk);
StackElem_t StackCos    (struct Stack * stk);

void StackCtor   (struct Stack * stk);
void StackDtor   (struct Stack * stk);
void StackRealloc (struct Stack * stk, int MODE);

int StackDump   (struct Stack * stk);
int StackCheck  (struct Stack * stk);

bool CompareTwo (double k1, double k2);
void MemDump (struct Stack * stk);

#endif