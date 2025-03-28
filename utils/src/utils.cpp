#ifndef UTILS_CPP
#define UTILS_CPP

#include "../inc/utils.h"

//-----------------------------------------------------------------------//

size_t GimmeFileSize (FILE * file)
{
    struct stat st = {};
    fstat (fileno (file), &st);
    size_t file_size = (size_t) st.st_size;
    assert (file_size != 0);

    return file_size;
}

size_t BufferLinesRefactorer (char * buffer) 
{
    size_t lines = 0;
    for (size_t i = 0; *(buffer + i + 1) != '\0'; i++)
    {
        if ( *(buffer + i) == '\n')
        {
            *(buffer + i) = '\0';
            lines++;
        }
    }
    return lines + 1; 
}

//-----------------------------------------------------------------------//

FILE * FileOpener (const char * file_name)
{
    FILE * file = fopen (file_name, "rb");
    assert (file);

    return file;
}

char * BufferCtor (FILE * file, size_t file_size)
{
    assert (file != 0);
    assert (file_size != 0);

    char * buffer = (char *) calloc ((file_size + 1), sizeof(char));
    assert (buffer);

    size_t ReadStatus = fread (buffer, sizeof(char), file_size, file);
    if (ReadStatus != file_size)
        printf ("Reading status is incorrect!\n");

    *(buffer + file_size) = '\0';

    fclose (file);

    return buffer;
}

char * SPUBufferCtor (FILE * file, size_t file_size)
{
    assert (file != 0);
    assert (file_size != 0);

    char * buffer = (char *) calloc ((file_size + 1), sizeof(char));
    assert (buffer);

    size_t ReadStatus = fread (buffer, sizeof(char), file_size, file);
    if (ReadStatus != file_size)
        printf ("Reading status is incorrect!\n");

    *(buffer + file_size) = '\0';

    fclose (file);

    return buffer;
}

//-----------------------------------------------------------------------//

#endif