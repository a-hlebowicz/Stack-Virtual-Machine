#include "vm.h"
#include <inttypes.h>
#include <stdio.h>

VM vm;

static void resetStack() {
  vm.sp = vm.stack;
}

void initVM(){
    resetStack();
}

void freeVM(){

}

void push(int64_t x){
    *vm.sp = x;
    vm.sp++;
}

int64_t pop(){
    vm.sp--;
    return *vm.sp;
}

void debug_stack(){
    for (int64_t* start = vm.stack; start<vm.sp;start++){
        printf("[ ");
        printf("%" PRId64, *start);
        printf("] ");
    }
}


void run_vm(Instr* instruction){
    Instr* instr=instruction;
    for (;;){
        switch (instr->opCode){
            case OP_NEG: {
                int64_t x = pop();
                push(-x);
                break;
            }
            case OP_PUSH: {
                push(instr->arg);
                break;
            }
            case OP_POP: {
                pop();
                break;
            }
            case OP_PRINT: {
                int64_t x = pop();
                printf("%" PRId64 "\n", x);
                push(x);
                break;
            }
            case OP_STOP:{
                printf("STOP");
                return;
            }
            default: {
                break;
            }
        }
        instr++;
        //printf("%p",vm.ip);
        //printf("\n");
        
    }

}
