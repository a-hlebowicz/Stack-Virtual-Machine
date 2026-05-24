#include "vm.h"
#include "lexer.h"
#include <stdio.h>
int main(void)
{
    const char *source = "+ == = //komentarz +";
    Token *tokens = lex(source);
    print_tokens(tokens);
    //free(tokens);
    return 0;
}