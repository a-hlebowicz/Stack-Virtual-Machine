#pragma once 
#include <stdint.h>

typedef enum {
    TOK_INT
} TokenType;

typedef struct {
    TokenType type;
    int64_t value;
} Token;