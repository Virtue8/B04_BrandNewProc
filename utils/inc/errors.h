#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#include "utils.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"

#define COLORED_STDERR(...)        \
    fprintf (stderr, "%s", RED);   \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "%s", RESET)

enum ErrorCodes 
{
    FILE_OPENING_FAILED = 1,
    FILE_CLOSING_FAILED = 2,
    NULL_FILE           = 3,
    NULL_STRUCTURE      = 4,
    INVALID_PATH        = 5,
    MEM_ALLOC_FAILED    = 6,
};

void ErrorReport (int error_code);

#endif
