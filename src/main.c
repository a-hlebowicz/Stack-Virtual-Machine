#include "vm.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    const char *source = "int x = 6; if (x + 7 == 13) { print(x); } else { print(0); } //fajny kod";
    Token *tokens = lex(source);
    print_tokens(tokens, source);
    free(tokens);


    initVM();
    Instr instr[] = {
        {OP_PUSH, 6},
        {OP_LOAD_LOCAL, 0},
        {OP_PUSH, 7},
        {OP_ADD, 0},
        {OP_PUSH, 13},
        {OP_EQ, 0},
        {OP_JMP_IF_FALSE,3},
        {OP_LOAD_LOCAL,0},
        {OP_PRINT,0},
        {OP_JMP,2},
        {OP_PUSH, 0},
        {OP_PRINT,0},
        {OP_STOP,0}
    };
    run_vm(instr);
    freeVM();

    return 0;
}