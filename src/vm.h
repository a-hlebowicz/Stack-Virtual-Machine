#ifndef vm.h
#include <stdint.h>
#define STACK_SIZE 256

typedef enum {
    PUSH,
    POP,
    ADD,
    SUB,
    PRINT
} OpCode;

typedef struct {
    OpCode op_code;
    int64_t operand;

} Instruction;

typedef struct {
    Instruction* instruction;
    uint8_t* i_pointer;
    int64_t stack[STACK_SIZE];
    uint8_t* s_pointer;
} VM;
/*
typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;
*/
void initVM();
void freeVM();
//InterpretResult interpret(Instruction* instruction[]);
void push(int64_t x);
int64_t pop();

#endif