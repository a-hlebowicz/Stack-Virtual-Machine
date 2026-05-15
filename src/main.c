#include "vm.h"
#include <stdio.h>
int main(void)
{
    initVM();
    //printf("obrot \n");

    static Instr instruction[] = {
        {OP_PUSH, 5},
        {OP_NEG, 0},
        {OP_PRINT, 0},
        {OP_STOP, 0},
    };
    run_vm(instruction);

    freeVM();
    return 0;
}