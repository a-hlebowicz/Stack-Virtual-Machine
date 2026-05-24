#include "../src/lexer.h"
#include <stdio.h>
#include <stdlib.h>
void test_lex(const char *name, const char *source, TokenType *expected, int n) {
    Token *tokens = lex(source);
    int ok = 1;
    for (int i = 0; i < n; i++) {
        if (tokens[i].type != expected[i]) { ok = 0; break; }
    }
    printf("[%s] %s\n", ok ? "PASS" : "FAIL", name);
    if (!ok) print_tokens(tokens, source);
    free(tokens);
}

void run_test_lex(){
    TokenType e1[] = {TOK_NUMBER, TOK_PLUS, TOK_NUMBER, TOK_STAR, TOK_NUMBER, TOK_EOF};
    test_lex("arithmetic", "1 + 2 * 3", e1, 6);

    TokenType e2[] = {TOK_EQUAL, TOK_EQUAL_EQUAL, TOK_LESS, TOK_LESS_EQUAL,
                    TOK_GREATER, TOK_GREATER_EQUAL, TOK_BANG_EQUAL, TOK_EOF};
    test_lex("operators", "= == < <= > >= !=", e2, 8);

    TokenType e3[] = {TOK_INT, TOK_IF, TOK_ELSE, TOK_WHILE, TOK_PRINT, TOK_EOF};
    test_lex("keywords", "int if else while print", e3, 6);

    TokenType e4[] = {TOK_IF, TOK_IDENTIFIER, TOK_IDENTIFIER, TOK_IDENTIFIER, TOK_EOF};
    test_lex("keyword vs ident", "if iffy i print2", e4, 5);

    TokenType e5[] = {TOK_NUMBER, TOK_SLASH, TOK_NUMBER, TOK_EOF};
    test_lex("division not comment", "6 / 2", e5, 4);

    TokenType e6[] = {
        TOK_INT, TOK_IDENTIFIER, TOK_EQUAL, TOK_NUMBER, TOK_SEMICOLON,
        TOK_WHILE, TOK_LEFT_PAREN, TOK_IDENTIFIER, TOK_GREATER, TOK_NUMBER, TOK_RIGHT_PAREN,
        TOK_LEFT_BRACE, TOK_PRINT, TOK_LEFT_PAREN, TOK_IDENTIFIER, TOK_RIGHT_PAREN,
        TOK_SEMICOLON, TOK_RIGHT_BRACE, TOK_EOF
    };
    test_lex("full program", "int x = 5; while (x > 0) { print(x); }", e6, 19);
}