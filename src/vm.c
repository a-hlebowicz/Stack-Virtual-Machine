#include "vm.h"
#include <inttypes.h>

VM vm;

static void resetStack() {
  vm.s_pointer = vm.stack;
}

void initVM(){
    resetStack();
}

void freeVM(){

}

void push(int64_t x){
    *vm.s_pointer = x;
    vm.s_pointer++;
}

int64_t pop(){
    vm.s_pointer--;
    return *vm.s_pointer;
}








/*
static InterpretResult run_vm(Instruction* instruction,uint8_t i_pointer ){

    for (;;){
        Instruction* current_instruction=instruction[i_pointer++];
        switch (current_instruction->op_code){
            case PRINT: {
                //printf("%" PRId64 "\n", current_instruction->operand);
                break;
            }
        }
    }

}
*/
