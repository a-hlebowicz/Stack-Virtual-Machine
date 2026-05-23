#include "vm.h"
#include "lexer.h"
#include <stdio.h>
int main(void)
{
    initVM();
    //printf("obrot \n");
    Instr t10[] = {
    {OP_PUSH, 7},          
    {OP_PUSH, 0},          
    {OP_JMP_IF_FALSE, 2},  
    {OP_PUSH, 99},         
    {OP_STOP, 0},          
    {OP_PRINT, 0},         
    {OP_STOP, 0},          
    };
    
    run_vm(t10);

    freeVM();
    return 0;
}