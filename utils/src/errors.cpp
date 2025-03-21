#ifndef ERRORS_CPP
#define ERRORS_CPP

#include "../inc/errors.h"

void ErrorReport (int error_code)
{
    COLORED_STDERR ("\nERROR!!! Code %d: ", error_code);
    
    switch (error_code)
    {
        case FILE_OPENING_FAILED :
            COLORED_STDERR ("File opening failed!");
            break;
        case FILE_CLOSING_FAILED :
            COLORED_STDERR ("File closing failed!");
            break;
        case NULL_FILE :
            COLORED_STDERR ("Something went wrong with your file!");
            break;
        case NULL_STRUCTURE :
            COLORED_STDERR ("The structure you want to use is null!");
            break;
        case INVALID_PATH :
            COLORED_STDERR ("Invalid file name or path!");
            break;
        default:
            COLORED_STDERR ("Unknown error.");
            break;
    }

    printf ("\n\n");
    abort ();
}

#endif