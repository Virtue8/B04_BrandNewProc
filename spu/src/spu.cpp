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
    }
}

void LineReader (SPU * spu)
{
    
}

void CommandIdentifier (SPU * spu, size_t command_num, ...)
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
        default:
            fprintf (stderr, "Error! Unidentified command.");
            break;
    }
}

//#define CommandIdentifier (com_number, ...)

void CommandExecution (SPU * spu)
{
    
}

#endif