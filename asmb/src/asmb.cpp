#ifndef ASMB_CPP
#define ASMB_CPP

#include <stdio.h>
#include "../inc/asmb.h"
#include "../../utils/inc/utils.h"
#include "../../utils/inc/commands.h"
#include "../../utils/inc/errors.h"

void asmbCtor (Assembler * asmb, const char * input_file_name, const char * output_file_name)
{
    if (input_file_name == NULL)
        ErrorReport (INVALID_PATH);
    if (input_file_name == NULL)
        ErrorReport (INVALID_PATH);

    asmb->file = fopen (input_file_name, "rb");                         
    asmb->output_file = fopen (output_file_name, "w");                  

    if (asmb->file == NULL)
        ErrorReport (FILE_OPENING_FAILED);
    if (asmb->output_file == NULL)
        ErrorReport (FILE_OPENING_FAILED);
}

void asmbDtor (Assembler * asmb)
{
    if (asmb == NULL)
        ErrorReport (NULL_STRUCTURE);

    free   (asmb->code);
    fclose (asmb->output_file);
}

void CodeSeparator (Assembler * asmb)
{
    assert (asmb != NULL);

    asmb->lines_amount = BufferLinesRefactorer (asmb->code);

    asmb->line = (Line *) calloc (asmb->lines_amount, sizeof(Line));
    assert (asmb->line != NULL);

    size_t prev_i_value = 0;
    int k = 0;

    for (size_t i = 0; i < asmb->file_size + 1; i++)
    {
        if (asmb->code[i] == '\0')
        {
            asmb->line[k].len = i - prev_i_value;
            asmb->line[k].ptr = asmb->code + i - asmb->line[k].len;

            prev_i_value = i;
            k += 1;
        }
    }
}

int GetCommandNumber (const char * command) 
{
    assert (command != NULL);

    for (int k = 0; k < COMMANDS_AMOUNT; k++)
    {
        if (strcmp (command, *Commands[k].name) == 0)
            return Commands[k].number;
    }

    return -1;
}

int GetRegister (const char * reg) 
{
    if (strcmp (reg, "AX") == 0) return AX;
    if (strcmp (reg, "BX") == 0) return BX;
    if (strcmp (reg, "CX") == 0) return CX;
    if (strcmp (reg, "DX") == 0) return DX;

    return -1;
}


void LineIdentifier (const char *input_line, char *output_line, Assembler * asmb) 
{
    assert  (input_line != NULL);
    assert  (output_line != NULL);

    char command[10] = "";
    char arg1[10] = "";
    char arg2[10] = "";

    int words_amount = sscanf (input_line, "%s %s %s", command, arg1, arg2);

    int command_number = GetCommandNumber (command);
    if (command_number == -1) 
    {
        fprintf (stderr, "Error: Unknown command '%s'\n", command);
        strcpy (output_line, "ERROR");
        return;
    }

    int num1 = 0;
    int num2 = 0;

    if (words_amount >= 2)
    {
        num1 = GetRegister (arg1);
        if (num1 == -1) 
        {
            if (sscanf (arg1, "%d", &num1) != 1) 
            {
                fprintf (stderr, "Error: Invalid argument '%s'\n", arg1);
                strcpy (output_line, "ERROR");
                return;
            }
        }
    }

    if (words_amount >= 3) 
    {
        num2 = GetRegister (arg2);
        if (num2 == -1) 
        {
            if (sscanf (arg2, "%d", &num2) != 1) {
                fprintf (stderr, "Error: Invalid argument '%s'\n", arg2);
                strcpy (output_line, "ERROR");
                return;
            }
        }
    }

    switch (words_amount) 
    {
        case 1:
            sprintf (output_line, "%d\n", command_number);
            break;
        case 2:
            sprintf (output_line, "%d %d\n", command_number, num1);
            break;
        case 3:
            sprintf (output_line, "%d %d %d\n", command_number, num1, num2);
            break;
        default:
            fprintf (stderr, "Error: Invalid input format\n");
            strcpy (output_line, "ERROR");
    }
}

void CodeAssemble (Assembler * asmb)
{
    assert (asmb != NULL);

    for (int i = 0; i < (int) asmb->lines_amount; i++)
    {
        char input_line[30] = "";
        char output_line[10] = "";
        
        if (i != 0)
            asmb->line[i].ptr++;

        strcpy (input_line, asmb->line[i].ptr);

        LineIdentifier (input_line, output_line, asmb);
        MachineCodeWriter (asmb, output_line);
    }
}

void MachineCodeWriter (Assembler * asmb, const char * output_code) 
{
    assert (asmb != NULL);

    if (asmb->output_file == NULL || output_code == NULL) 
    {
        fprintf (stderr, "Error: Invalid file pointer or buffer\n");
        return;
    }

    size_t write_state = fwrite (output_code, sizeof (char), strlen (output_code), asmb->output_file);

    if (write_state < strlen (output_code)) 
    {
        fprintf (stderr, "Error: Failed to write complete data to file\n");
    }
}


#endif