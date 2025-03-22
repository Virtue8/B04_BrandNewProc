#ifndef STACKFUNCS_CPP
#define STACKFUNCS_CPP

#include "../inc/stack.h"

//--------------------------------------------------------//

StackElem_t StackAdd (struct Stack * stk)
{
    StackCheck (stk);

    StackElem_t a = StackPop (stk);
    StackElem_t b = StackPop (stk);
    return StackPush (stk, b + a);
    
    StackCheck (stk);
}

StackElem_t StackSub (struct Stack * stk)
{
    StackCheck (stk);

    StackElem_t a = StackPop (stk);
    StackElem_t b = StackPop (stk);
    return StackPush (stk, b - a);
}

StackElem_t StackMul (struct Stack * stk)
{
    StackCheck (stk);

    StackElem_t a = StackPop (stk);
    StackElem_t b = StackPop (stk);
    return StackPush (stk, b * a);
}

StackElem_t StackDiv (struct Stack * stk)
{
    StackCheck (stk);

    StackElem_t a = StackPop (stk);
    StackElem_t b = StackPop (stk);
    return StackPush (stk, b / a);
}

StackElem_t StackSqrt (struct Stack * stk)
{
    StackCheck (stk);

    StackElem_t a = StackPop (stk);
    return StackPush (stk, sqrt (a));;
}

StackElem_t StackSin (struct Stack * stk)
{
    StackCheck (stk);
    
    StackElem_t a = StackPop (stk);
    return StackPush (stk, sin (a));
}

StackElem_t StackCos (struct Stack * stk)
{
    StackCheck (stk);

    StackElem_t a = StackPop (stk);
    return StackPush (stk, cos (a));
}

//--------------------------------------------------------//

void StackCtor (struct Stack * stk)
{
    stk->Size = 0;
    stk->Capacity = 1;

    stk->Data = (StackElem_t *) calloc (stk->Capacity + 2, sizeof(StackElem_t));
    if (stk->Data == NULL) 
        stk->ErrorCode = ERR;

    stk->Data++;
    *(stk->Data - 1) = CANARY_VALUE;
    *(stk->Data + stk->Capacity) = CANARY_VALUE;

    stk->LeftCanary = CANARY_VALUE;
    stk->RightCanary = CANARY_VALUE;
}

//--------------------------------------------------------//

StackElem_t StackPush (struct Stack * stk, StackElem_t unit)
{
    StackCheck (stk);

    if (stk->Size == stk->Capacity)
        StackRealloc (stk, RM_PUSH);

    stk->Data[stk->Size++] = unit;
    return unit;
}

//--------------------------------------------------------//

StackElem_t StackPop (struct Stack * stk)
{
    StackCheck (stk);

    if (stk->Capacity == 0 || stk->Size == 0)
    {
        stk->ErrorCode = POP_ERR;
        StackDump (stk);
    }

    stk->Size--;

    StackElem_t unit = stk->Data[stk->Size];

    if (stk->Capacity > 2 * stk->Size + 1)
        StackRealloc (stk, RM_POP);

    return unit;
}

//--------------------------------------------------------//

void StackDtor (struct Stack * stk)
{
    StackCheck (stk);

    free (stk->Data);
    stk->Data = NULL;

    stk->Capacity = 0;
    stk->Size = 0;
    stk->ErrorCode = 0;
}

//--------------------------------------------------------//

void StackRealloc (struct Stack * stk, int MODE)
{
    StackCheck (stk);

    *(stk->Data + stk->Capacity) = 0;
    stk->Data--;
    
    if (MODE == RM_POP)
        stk->Capacity = stk->Size + 1;

    else if (MODE == RM_PUSH)
        stk->Capacity = stk->Size * 2 + 1;
    
    stk->Data = (StackElem_t *) realloc (stk->Data, sizeof(StackElem_t)*(stk->Capacity + 2));
    if (stk->Data == NULL) 
        stk->ErrorCode = REALLOC_ERR;

    stk->Data++;
    *(stk->Data + stk->Capacity) = CANARY_VALUE;
}

//--------------------------------------------------------//

int StackCheck (struct Stack * stk)
{
    if (stk == NULL)
        stk->ErrorCode = NULL_STRUCT_POINTER;

    else if ((stk->Data == NULL))
        stk->ErrorCode = NULL_DATA_POINTER;

    else if (stk->Size > stk->Capacity && stk->Capacity != 0)
        stk->ErrorCode = STACK_OVERFLOW;

    else if (*(stk->Data - 1) != CANARY_VALUE)
        stk->ErrorCode = LEFT_CANARY_DEATH;

    else if (*(stk->Data + stk->Capacity) != CANARY_VALUE)
        stk->ErrorCode = RIGHT_CANARY_DEATH;

    else if (!isfinite(stk->Size))
        stk->ErrorCode = SIZE_ERR;

    else if (!isfinite(stk->Capacity))
        stk->ErrorCode = CAPACITY_ERR;

    if (stk->ErrorCode)
    {    
        StackDump (stk);
        exit (1);
    }

    return 0;
}

//--------------------------------------------------------//

int StackDump (struct Stack * stk)
{
    if (stk == 0)
    {
        COLORED_LINE (RED, "Zero Stack Pointer!!!\n");
    } 
    else
    {
        printf ("\n\n");
        printf ("----------------------\n"
                "| Stack State Report |\n"
                "----------------------\n\n");

        printf ("----------------------\n");
        printf ("| Data Size:    %lu\n", stk->Size);
        printf ("| Capacity:     %lu\n", stk->Capacity);
        printf ("----------------------\n\n");

        if (stk->Data == 0)
        {
            COLORED_LINE (RED, "Zero Data Pointer!!!\n");
        }  
        else
        {
            printf ("%ld current\n%ld required left canary value\n\n", *(stk->Data - 1), CANARY_VALUE);
            printf ("%ld current\n%ld required right canary value\n\n", *(stk->Data + stk->Capacity), CANARY_VALUE);

            printf ("Data pointer: %p\n", stk->Data);

            if (stk->ErrorCode != POP_ERR && isfinite(stk->Size) && isfinite(stk->Capacity)) 
            {
                printf ("\n------------------");
                for (size_t i = 0; i != stk->Size; i++)
                    printf ("------");
                printf ("\n");

                printf ("| Stack Data:    ");
                for (size_t i = 0; i < stk->Size; i++)
                    printf ("%ld    ", stk->Data[i]);
                printf ("|\n");

                printf ("------------------");
                for (size_t i = 0; i != stk->Size; i++)
                    printf ("------");
                printf ("\n\n");
            }

        MemDump (stk);

        if (stk->ErrorCode != 0)
        {
            COLORED_LINE (RED, "\nWe got some issues!\n");
            printf ("%s", ErrorMessages[stk->ErrorCode]);
            exit(1);
        }
        }
    }

    return 0;
}

void MemDump (struct Stack * stk)
{
    COLORED_LINE (GREEN, "MEMORY DUMP\n");
    size_t cell = 0;
    for (size_t i = 0; i != stk->Capacity + 6; i++)
    {
        cell = ((StackElem_t)stk->Data - 1 + i) - ((StackElem_t)stk->Data - 1 + i)/100*100;
        printf ("%ld: | %ld |", cell, *(stk->Data - 2 + i));
        if (*(stk->Data - 2 + i) == CANARY_VALUE)
            printf ("    <----- Canary");
        if (i == 2)
            printf ("    <----- stk->Data");
        printf ("\n");
    }
    COLORED_LINE (GREEN, "OVER\n\n");
}

bool CompareTwo (double k1, double k2)
{
    return (fabs (k1 - k2) <= EPSILON);
}

#endif