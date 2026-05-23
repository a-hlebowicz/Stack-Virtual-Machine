#ifndef VM_H
#define VM_H
#include <stdint.h>
#define STACK_SIZE 256

typedef enum {
    OP_PUSH,
    OP_POP,
    OP_ADD,
    OP_SUB,
    OP_PRINT,
    OP_NEG,
    OP_MUL,
    OP_DIV,
    OP_STOP,
    OP_STORE_LOCAL,
    OP_LOAD_LOCAL,
    OP_JMP_IF_FALSE,
} OpCode;

typedef struct {
    OpCode opCode;
    int64_t arg;

} Instr;

typedef struct {
    //Instr* instr;
    //Instr *ip;                  //instruction pointer
    int64_t stack[STACK_SIZE];
    int64_t* sp;                //stack pointer
} VM;
/*
typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;
*/
void initVM(void);
void freeVM(void);
//InterpretResult interpret(Instruction* instruction[]);
void push(int64_t x);
int64_t pop(void);
void debug_stack();
void run_vm();

#endif