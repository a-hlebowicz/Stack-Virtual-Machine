#include "vm.h"
#include "lexer.h"
#include <stdio.h>
int main(void)
{
    const char *source = "xd + y = else //fajny kod";
    Token *tokens = lex(source);
    print_tokens(tokens, source);
    //free(tokens);
    return 0;
}