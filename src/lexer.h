#pragma once 
#include <stdint.h>

typedef enum {
    // single character
    TOK_LEFT_PAREN, TOK_RIGHT_PAREN,
    TOK_LEFT_BRACE, TOK_RIGHT_BRACE,
    TOK_MINUS, TOK_PLUS, TOK_SEMICOLON,
    TOK_SLASH, TOK_STAR,
    // one or two character
    TOK_BANG_EQUAL,                       
    TOK_EQUAL, TOK_EQUAL_EQUAL,         
    TOK_GREATER, TOK_GREATER_EQUAL,      
    TOK_LESS, TOK_LESS_EQUAL,          
    // literals
    TOK_IDENTIFIER, TOK_NUMBER,
    // keywords
    TOK_INT, TOK_IF, TOK_ELSE, TOK_WHILE, TOK_PRINT,
    // special
    TOK_EOF, TOK_ERROR
} TokenType;

typedef struct {
    TokenType type;
    int64_t value;
    int start;
    int length;
} Token;


Token* lex(const char source[]);


void print_tokens(Token* tokens, const char *source);

