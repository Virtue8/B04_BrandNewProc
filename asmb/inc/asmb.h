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
#include "../../utils/inc/errors.h"

//--------------------------------------------------------//

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