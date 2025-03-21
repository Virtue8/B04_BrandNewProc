#include "inc/asmb.h"

int main () // FIXME argc argv
{
    Assembler asmb = {}; // memset(0)

    asmbCtor (&asmb, "../sample/sample_code.txt", "../sample/machine_code.txt");

    asmb.file_size = GimmeFileSize (asmb.file);
    
    asmb.code = BufferCtor (asmb.file, asmb.file_size);

    CodeSeparator (&asmb);                                                  //separating the code into lines

    CodeAssemble (&asmb);                                                   //assembling the machine_code_buffer

    asmbDtor (&asmb);                                                       //freeing the space and removing excess data
}