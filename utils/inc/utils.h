#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <stdio.h>

#include "../../asmb/inc/asmb.h"
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"

#define COLORED_LINE(COLOR, ...)    \
    printf ("%s", COLOR);           \
    printf (__VA_ARGS__);           \
    printf ("%s", RESET)

#define STDERR_COLORED_LINE(COLOR, ...)      \
    printf ("%s", COLOR);                    \
    fprintf (stderr, __VA_ARGS__);           \
    printf ("%s", RESET)

//---------------------------- Text Editing -----------------------------//

size_t GimmeFileSize (FILE * file);
size_t BufferLinesRefactorer (char * buffer);

//---------------------------- File Reading -----------------------------//

FILE * FileOpener (const char * file_name);
char * BufferCtor (FILE * file, size_t file_size);

//-----------------------------------------------------------------------//

#endif