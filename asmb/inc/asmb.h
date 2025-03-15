#ifndef ASMB_H
#define ASMB_H

//--------------------------------------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/param.h>

#include "../../utils/inc/stack.h"
#include "../../utils/inc/utils.h"

//--------------------------------------------------------//


typedef unsigned long int ProcElem_t;

static const int COMMANDS_AMOUNT = 26;

struct Command
{
    int number;
    const char * name[10];
};

Command Commands[COMMANDS_AMOUNT] = 
{
    {0,  "HLT"},
    {10, "PUSH"},
    {11, "PUSHR"},
    {12, "PUSHM"},
    {13, "PUSHRM"},
    {20, "POP"},
    {21, "POPM"},
    {30, "JMP"},
    {31, "JA"},
    {32, "JAE"},
    {33, "JB"},
    {34, "JBE"},
    {35, "JE"},
    {36, "JNE"},
    {40, "ADD"},
    {41, "SUB"},
    {42, "MUL"},
    {43, "DIV"},
    {44, "SQRT"},
    {45, "POW"},
    {46, "LN"},
    {47, "SIN"},
    {48, "COS"},
    {5,  "CALL"},
    {6,  "RET"},
    {7,  "OUT"}
};


enum Registers
{
    AX = 1,
    BX,
    CX,
    DX
};

const int ASMB_VERSION = 1;

struct Assembler
{
    FILE * file = NULL;
    FILE * output_file = NULL;
    size_t file_size = 0;

    const char * file_name = NULL;
    const char * output_file_name = NULL;

    char * code = 0;
    size_t lines_amount = 0;

    int ip = 0;
    struct Line * line = NULL;
};

struct Line
{
    size_t len = 0;
    char * ptr = 0;
};

//-------------------------- Assembling Service ----------------------------//

void asmbCtor (Assembler * asmb, const char * input_file_name, const char * output_file_name);
void asmbDtor (Assembler * asmb);

//--------------------- Collecting the sample_code Data --------------------//

void CodeSeparator (Assembler * asmb);

//--------------------- Reworking and Analyzing the Code -------------------//

int GetCommandNumber (const char * command);
int GetRegisterValue (const char *reg);
void LineIdentifier (const char * input_line, char * output_line, Assembler * asmb);
void CodeAssemble (Assembler * asmb);
void MachineCodeWriter(Assembler * asmb, const char *output_code);

//--------------------------------------------------------//

#endif