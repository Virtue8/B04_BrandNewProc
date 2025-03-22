#include "inc/spu.h"

int main (/*int argc, char * argv[]*/)
{
    SPU spu = {};

    spuCtor (&spu, "../sample/machine_code.txt");

    spu.file_size = GimmeFileSize (spu.file);
    
    spu.code = BufferCtor (spu.file, spu.file_size);
    CodeSeparator (&spu);

    CodeExecution (&spu);

    spuDtor (&spu);
}