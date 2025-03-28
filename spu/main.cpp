#include "inc/spu.h"

int main (/*int argc, char * argv[]*/)
{
    SPU spu = {};

    spuCtor (&spu, "../sample/machine_code.txt");
    
    CodeExecution (&spu);

    spuDtor (&spu);
}