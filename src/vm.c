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
                //push(x);
                break;
            }
            case OP_STOP:{
                printf("STOP");
                return;
            }
            case OP_NEG: {
                int64_t x = pop();
                push(-x);
                break;
            }
            case OP_ADD: {
                int64_t y = pop();
                int64_t x = pop();
                push(x+y);
                break;
            }
            case OP_SUB: {
                int64_t y = pop();
                int64_t x = pop();
                push(x-y);
                break;
            }
            case OP_MUL: {
                int64_t y = pop();
                int64_t x = pop();
                push(x*y);
                break;
            }
            case OP_DIV: {
                int64_t y = pop();
                int64_t x = pop();
                if (y==0){
                    printf("Division by zero\n");
                    return;
                }
                push(x/y);
                break;
            }
            case OP_STORE_LOCAL:{
                int x = instr->arg;         //arg store_local to miejsce na stosie w ktorym jest zmienna
                vm.stack[x] = pop();    
                break;
            }
            case OP_LOAD_LOCAL: {
                int x = instr->arg;
                push(vm.stack[x]);       
                break;
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
