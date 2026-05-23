#include "vm.h"
#include <stdio.h>
int main(void)
{
    initVM();
    //printf("obrot \n");
    Instr t10[] = {
    {OP_PUSH, 7},          // 0: ta wartość ma "przetrwać"
    {OP_PUSH, 0},          // 1: warunek (false)
    {OP_JMP_IF_FALSE, 2},  // 2: popuje 0, skacze do 5
    {OP_PUSH, 99},         // 3: pominięte
    {OP_STOP, 0},          // 4: pominięte
    {OP_PRINT, 0},         // 5: wypisz top stosu
    {OP_STOP, 0},          // 6
    };
    
    run_vm(t10);

    freeVM();
    return 0;
}