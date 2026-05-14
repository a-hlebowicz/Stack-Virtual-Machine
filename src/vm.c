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

void debug_stack(){
    for (int64_t* start = vm.stack; start<vm.s_pointer;start++){
        printf("[ ");
        printf("%" PRId64, *start);
        printf("] ");
    }
}


static void run_vm(Instruction* instruction){
    uint8_t* i_pointer=instruction;
    for (;;){
        Instruction* current_instruction=i_pointer;
        switch (current_instruction->op_code){
            case OP_NEG: {
                int64_t x = pop();
                push(-x);
                break;
            }
        }
    }

}
