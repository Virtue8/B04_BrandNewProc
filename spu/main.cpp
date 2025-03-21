#include "inc/spu.h"

int main ()
{
    SPU spu = {};

    spuCtor (&spu, "../sample/machine_code.txt");

    spu.file_size = GimmeFileSize (spu.file);
    
    spu.code = BufferCtor (spu.file, spu.file_size);
    CodeSeparator (&spu);

    CommandIdentifier (10);
    CommandIdentifier (3);

    spuDtor (&spu);
}