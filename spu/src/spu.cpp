#ifndef SPU_CPP
#define SPU_CPP

#include <stdio.h>
#include "../inc/spu.h"
#include "../../utils/inc/utils.h"
#include "../../utils/inc/commands.h"
#include "../../utils/inc/stack.h"

void spuCtor(SPU* spu, const char* file_name) 
{
    assert (spu);
    assert (file_name);

    spu->file = fopen (file_name, "r");
    assert (spu->file);

    spu->file_size = GimmeFileSize (spu->file);

    spu->code = (spuElem_t*) calloc (spu->file_size + 1, sizeof(spuElem_t));
    if (!spu->code) 
    {
        fclose (spu->file);
        ErrorReport (MEM_ALLOC_FAILED);
    }

    size_t pos = 0;
    spuElem_t value;

    while (fscanf (spu->file, "%d", &value) == 1) 
    {
        spu->code [pos++] = value;
    }

    spu->file_size = pos;
    fclose (spu->file);
    
    StackCtor (&spu->stack);
}

void spuDtor (SPU * spu)
{
    assert (spu != NULL);

    StackDtor (&spu->stack);
    free   (spu->code);
}

void CodeExecution (SPU * spu)
{
    assert (spu != NULL);

    for (spu->ip = 0; spu->ip < (int) spu->file_size; spu->ip++)
    {    
        CommandSeek (spu->code[spu->ip], spu);
    }

}

void CommandSeek (spuElem_t command, SPU * spu) 
{
    int args_amount = 0;

    for (int i = 0; i != COMMANDS_AMOUNT; i++)
    {
        if (Commands[i].number == command) 
            args_amount = Commands[i].args_amount;
    }

    spuElem_t arg1 = 0;
    spuElem_t arg2 = 0;

    switch (args_amount) 
    {
        case 0:
            CommandExecution (spu, command);
            break;
        case 1:
            spu->ip++;
            arg1 = spu->code[spu->ip];
            CommandExecution (spu, command, arg1);
            break;
        case 2:
            spu->ip++;
            arg1 = spu->code[spu->ip];
            spu->ip++;
            arg2 = spu->code[spu->ip];
            CommandExecution (spu, command, arg1, arg2);
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
            fprintf (stderr, "Error! Unidentified command.\n");
            break;
    }
}


#endif