#include "vm.h"
#include <stdio.h>
int main(void)
{
    initVM();
    //printf("obrot \n");
    Instr t10[] = {
    {OP_PUSH, -5},
    {OP_PUSH, -3},
    {OP_ADD, 0},
    {OP_PRINT, 0},
    {OP_STOP, 0},
    };
    run_vm(t10);

    freeVM();
    return 0;
}