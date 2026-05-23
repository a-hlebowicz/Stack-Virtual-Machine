#include "lexer.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    const char *source;
    int start;
    int current;
    int line;
} Scanner;

Scanner s;

static Token makeToken(TokenType type){
    Token token;
    token.type = type;
    return token;
}
static bool isAtEnd(){
    return s.source[s.current] == '\0';
}
static char peek_next(void) {
    if (isAtEnd()) return '\0';
    return s.source[s.current + 1];
}
static bool match(char expected){
    if (isAtEnd())return false;
    if (s.source[s.current]!= expected) return false;
    s.current++;
    return true;
}
static void skipWhitespace(void) {
    for (;;) {
        char c = s.source[s.current];
        switch (c) {
            case ' ':
            case '\t':
            case '\r':
                s.current++;
                break;
            case '\n':
                s.line++;
                s.current++;
                break;
            case '/':
                if (peek_next() == '/') {
                    while (!isAtEnd() && s.source[s.current] != '\n') s.current++;
                } else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

static Token scan(){
    skipWhitespace();
    if (isAtEnd()) return makeToken(TOK_EOF);
    char c = s.source[s.current++];
    switch (c){
        //single
        case '(': return makeToken(TOK_LEFT_PAREN);
        case ')': return makeToken(TOK_RIGHT_PAREN);
        case '{': return makeToken(TOK_LEFT_BRACE);
        case '}': return makeToken(TOK_RIGHT_BRACE);
        case ',': return makeToken(TOK_COMMA);
        case '.': return makeToken(TOK_DOT);
        case '-': return makeToken(TOK_MINUS);
        case '+': return makeToken(TOK_PLUS);
        case ';': return makeToken(TOK_SEMICOLON);
        
        //double
        case '!': {
            if (match('='))return makeToken(TOK_BANG_EQUAL);
            else return makeToken(TOK_BANG);
        }
        case '=': {
            if (match('='))return makeToken(TOK_EQUAL_EQUAL);
            else return makeToken(TOK_EQUAL);
        }
        case '<': {
            if (match('='))return makeToken(TOK_LESS_EQUAL);
            else return makeToken(TOK_LESS);
        }
        case '>': {
            if (match('='))return makeToken(TOK_GREATER_EQUAL);
            else return makeToken(TOK_GREATER);
        }


        default:
            printf("Unexpected character.");
            return makeToken(TOK_ERROR);
    }
}


Token* lex(char source[]){
    int capacity = 8;
    int count = 0;
    Token *tokens = malloc(capacity * sizeof(Token));

    //scanerinit()
    s.source = source;
    s.start = 0;
    s.current = 0;
    s.line = 1;

    while (!isAtEnd()) {
        s.start = s.current;

        Token t = scan();
        
        if (t.type == TOK_EOF) break;

        if (count+1 >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, capacity * sizeof(Token));
        }

        tokens[count++] = t;
    }

    //TOK_EOF

    return tokens;
}

const char* tokenTypeToString(TokenType type) {
    static const char* names[] = {
        "TOK_LEFT_PAREN",
        "TOK_RIGHT_PAREN",
        "TOK_LEFT_BRACE",
        "TOK_RIGHT_BRACE",
        "TOK_COMMA",
        "TOK_DOT",
        "TOK_MINUS",
        "TOK_PLUS",
        "TOK_SEMICOLON",
        "TOK_SLASH",
        "STAR",

        "TOK_BANG",
        "TOK_BANG_EQUAL",
        "TOK_EQUAL",
        "TOK_EQUAL_EQUAL",
        "TOK_GREATER",
        "TOK_GREATER_EQUAL",
        "TOK_LESS",
        "TOK_LESS_EQUAL",

        "TOK_IDENTIFIER",
        "TOK_STRING",
        "TOK_NUMBER",

        "TOK_AND",
        "TOK_CLASS",
        "TOK_ELSE",
        "TOK_FALSE",
        "TOK_FUN",
        "TOK_FOR",
        "TOK_IF",
        "TOK_NIL",
        "TOK_OR",

        "TOK_PRINT",
        "TOK_RETURN",
        "TOK_SUPER",
        "TOK_THIS",
        "TOK_TRUE",
        "TOK_VAR",
        "TOK_WHILE",

        "TOK_EOF",
        "TOK_ERROR"
    };

    return names[type];
}
void print_tokens(Token* tokens){
    for (int i=0;true;i++){
        printf("type = %s \n",tokenTypeToString(tokens[i].type));
        if (tokens[i].type == TOK_EOF) return;
    }
}

