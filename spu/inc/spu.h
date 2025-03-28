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

const int SPU_VERSION = 2;

typedef int spuElem_t;

struct SPU
{
    FILE * file = NULL;
    size_t file_size = 0;
    const char * file_name = NULL;

    spuElem_t * code = 0;
    struct Stack stack = {};
    int ip = 0;

    int reg_values[4] = {};
};

//-------------------------- Preparation Service ----------------------------//

void spuCtor (SPU * spu, const char * file_name);
void spuDtor (SPU * spu);

//----------------------------- Code Execution -----------------------------//

void CodeExecution      (SPU * spu);
void CommandSeek (spuElem_t command, SPU * spu);
void CommandExecution   (SPU * spu, size_t command_num, ...);

//--------------------------------------------------------------------------//

#endif