#ifndef SPU_H
#define SPU_H

//--------------------------------------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <stdarg.h>

#include "../../utils/inc/stack.h"
#include "../../utils/inc/utils.h"
#include "../../utils/inc/errors.h"

//--------------------------------------------------------//

const int SPU_VERSION = 1;

struct SPU
{
    FILE * file = NULL;
    size_t file_size = 0;
    const char * file_name = NULL;

    char * code = 0;
    size_t lines_amount = 0;

    struct Stack stack = {};

    int ip = 0;
    struct Line * line = NULL;
};

//-------------------------- Preparation Service ----------------------------//

void spuCtor (SPU * spu, const char * file_name);
void spuDtor (SPU * spu);

//--------------------- Collecting the Machine_code Data --------------------//

void CodeSeparator (SPU * spu);

//----------------------------- Code Execution -----------------------------//

void CodeExecution      (SPU * spu);
void LineReader         (const char *input_line, SPU * spu);
void CommandExecution   (SPU * spu, size_t command_num, ...);

//--------------------------------------------------------------------------//

#endif