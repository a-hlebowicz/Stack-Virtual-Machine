#include "lexer.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

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
    token.start = s.start;
    token.length = s.current - s.start;
    token.value = 0;
    return token;
}
static bool isAtEnd(){
    return s.source[s.current] == '\0';
}
static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}
static bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
          c == '_';
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

static Token scan_number(){
    int64_t value = s.source[s.start] -'0';    
    while(isDigit(s.source[s.current])){
        value = value*10 + s.source[s.current] - '0';
        s.current++;
    }
    Token t = makeToken(TOK_NUMBER);
    t.value = value;
    return t;
}
static TokenType check_keyword(int start, int length, const char *rest, TokenType type) {
    if (s.current - s.start == start + length &&                      
        memcmp(&s.source[s.start + start], rest, length) == 0) {      
        return type;                                                  
    }
    return TOK_IDENTIFIER;
}
static TokenType identifier_type(){
    switch (s.source[s.start]){
        case 'e': return check_keyword(1, 3, "lse", TOK_ELSE);
        case 'i': {
            if (s.current - s.start > 1) {
                switch (s.source[s.start + 1]) {
                    case 'f': return check_keyword(2, 0, "",  TOK_IF);
                    case 'n': return check_keyword(2, 1, "t", TOK_INT);
                }
            }
            break; 
        }
        case 'p': return check_keyword(1, 4, "rint", TOK_PRINT);
        case 'w': return check_keyword(1, 4, "hile", TOK_WHILE);
    }
    return TOK_IDENTIFIER; 
}
static Token scan_identifier(){
    while (isAlpha(s.source[s.current]) || isDigit(s.source[s.current]))  s.current++;
    return makeToken(identifier_type());
    
}
static Token scan(){
    skipWhitespace();
    s.start = s.current;
    if (isAtEnd()) return makeToken(TOK_EOF);
    char c = s.source[s.current++];
    if (isDigit(c)) return scan_number();
    if (isAlpha(c)) return scan_identifier();
    switch (c){
        //single
        case '(': return makeToken(TOK_LEFT_PAREN);
        case ')': return makeToken(TOK_RIGHT_PAREN);
        case '{': return makeToken(TOK_LEFT_BRACE);
        case '}': return makeToken(TOK_RIGHT_BRACE);
        case '/': return makeToken(TOK_SLASH);
        case '*': return makeToken(TOK_STAR);
        case '-': return makeToken(TOK_MINUS);
        case '+': return makeToken(TOK_PLUS);
        case ';': return makeToken(TOK_SEMICOLON);
        
        //double
        case '!': {
            if (match('='))return makeToken(TOK_BANG_EQUAL);
            else return makeToken(TOK_ERROR);
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

    for(;;) {
        Token t = scan();

        if (count+1 >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, capacity * sizeof(Token));
        }

        tokens[count++] = t;

        if (t.type == TOK_EOF) break;
    }

    return tokens;
}

const char* tokenTypeToString(TokenType type) {
    static const char* names[] = {
    "TOK_LEFT_PAREN", "TOK_RIGHT_PAREN",
    "TOK_LEFT_BRACE", "TOK_RIGHT_BRACE",
    "TOK_MINUS", "TOK_PLUS", "TOK_SEMICOLON",
    "TOK_SLASH", "TOK_STAR",
    "TOK_BANG_EQUAL",
    "TOK_EQUAL", "TOK_EQUAL_EQUAL",
    "TOK_GREATER", "TOK_GREATER_EQUAL",
    "TOK_LESS", "TOK_LESS_EQUAL",
    "TOK_IDENTIFIER", "TOK_NUMBER",
    "TOK_INT", "TOK_IF", "TOK_ELSE", "TOK_WHILE", "TOK_PRINT",
    "TOK_EOF", "TOK_ERROR"
};

    return names[type];
}
void print_tokens(Token* tokens, const char *source){
    for (int i=0;true;i++){
        Token t=tokens[i];
        printf("type = %s",tokenTypeToString(t.type));
        if (t.type == TOK_NUMBER)printf(", value = %" PRId64, t.value);
        if (t.type == TOK_IDENTIFIER){
            printf(", value = ");
            for (int j=t.start;t.start+t.length>j;j++){
                printf("%c", source[j]);
            }
        }

        printf("\n");
        if (t.type == TOK_EOF) return;
    }
}

