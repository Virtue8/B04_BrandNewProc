#ifndef SPU_CPP
#define SPU_CPP

#include <stdio.h>
#include "../inc/spu.h"
#include "../../utils/inc/utils.h"
#include "../../utils/inc/commands.h"
#include "../../utils/inc/stack.h"

void spuCtor (SPU * spu, const char * file_name)
{
    assert (spu);
    assert (file_name);

    spu->file = fopen (file_name, "rb");

    assert (spu->file);

    StackCtor (&spu->stack);
}

void spuDtor (SPU * spu)
{
    assert (spu != NULL);

    StackDtor (&spu->stack);
    free   (spu->code);
}

void CodeSeparator (SPU * spu)
{
    assert (spu != NULL);

    spu->lines_amount = BufferLinesRefactorer (spu->code);

    spu->line = (Line *) calloc (spu->lines_amount, sizeof(Line));
    assert (spu->line != NULL);

    size_t prev_i_value = 0;
    int k = 0;

    for (size_t i = 0; i < spu->file_size + 1; i++)
    {
        if (spu->code[i] == '\0')
        {
            spu->line[k].len = i - prev_i_value;
            spu->line[k].ptr = spu->code + i - spu->line[k].len;

            prev_i_value = i;
            k += 1;
        }
    }
}

void CodeExecution (SPU * spu)
{
    assert (spu != NULL);

    for (int i = 0; i < (int) spu->lines_amount; i++)
    {
        if (i != 0)
            spu->line[i].ptr++;

        char input_line[20] = "";

        strcpy (input_line, spu->line[i].ptr);

        LineReader (input_line, spu);
    }
}

void LineReader (const char *input_line, SPU * spu) 
{
    assert  (input_line != NULL);
    int command = -1;
    char arg1[10] = "";
    char arg2[10] = "";

    int words_amount = sscanf (input_line, "%d %s %s", &command, arg1, arg2);

    int num1 = 0;
    int num2 = 0;

    if (words_amount >= 2)
    {
        printf ("!!!!!!!\n");
        if (sscanf (arg1, "%d", &num1) != 1) 
        {
            fprintf (stderr, "Error: Invalid argument '%s'\n", arg1);
            abort ();
        }
    }
    
    if (words_amount >= 3) 
    {
        if (sscanf (arg2, "%d", &num2) != 1) 
        {
            fprintf (stderr, "Error: Invalid argument '%s'\n", arg2);
            abort ();
        }
    }

    switch (words_amount) 
    {
        case 1:
            CommandExecution (spu, command);
            break;
        case 2:
            CommandExecution (spu, command, num1);
            break;
        case 3:
            CommandExecution (spu, command, num1, num2);
            break;
        default:
            fprintf (stderr, "Error: Invalid input format\n");
            abort ();
    }
}

void CommandExecution (SPU * spu, size_t command_num, ...)
{
    va_list arg;

    switch (command_num) 
    {
        case HLT:
            exit (0);

        case PUSH:
            va_start (arg, 1);
            StackPush (&spu->stack, va_arg (arg, int));
            break;

        case POP:
            StackPop (&spu->stack);
            break;

        case ADD:
            StackAdd (&spu->stack);
            break;

        case SUB:
            StackSub (&spu->stack);
            break;

        case MUL:
            StackMul (&spu->stack);
            break;

        case DIV:
            StackDiv (&spu->stack);
            break;

        case SQRT:
            StackSqrt (&spu->stack);
            break;

        case SIN:
            StackSin (&spu->stack);
            break;

        case COS:
            StackCos (&spu->stack);
            break;

        default:
            fprintf (stderr, "Error! Unidentified command.");
            break;
    }
}


#endif