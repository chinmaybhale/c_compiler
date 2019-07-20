#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "headers/lexer.h"

#define ALLOC_SIZE 20

static Token makeToken(TokenType);
static int digit();

static const char *source;
static int pos;
static Token *tokens;
static unsigned int token_array_size;

void initLexer(const char *src, const char type)
{
    source = src;
    pos = 0;

    if(type == 'a')
    {
        tokens = (Token*)malloc(sizeof(Token) * ALLOC_SIZE);
        token_array_size = 0;
    }
}

Token* getTokens()
{
    Token token = getToken();
    int multiplier = 1;
    
    while (token.type != E)
    {
        if(token_array_size > ALLOC_SIZE * multiplier)
        {
            tokens = (Token*)realloc(tokens, ALLOC_SIZE * ++multiplier);
        }

        tokens[token_array_size++] = token;
        token = getToken();
    }
    
    if(token_array_size > ALLOC_SIZE * multiplier)
    {
        tokens = (Token*)realloc(tokens, ++token_array_size);
    }

    tokens[token_array_size++] = token;

    return tokens;
}

unsigned int get_tokens_size()
{
    return token_array_size;
}

Token getToken()
{
    switch(source[pos])
    {
        case ' ' : pos++; return getToken();
        case '+' : return makeToken(PLUS);
        case '-' : return makeToken(MINUS);
        case '*' : return makeToken(MUL);
        case '/' : return makeToken(DIV);
        default :
            if(isdigit(source[pos]))
                return makeToken(LIT);
            else
                return makeToken(E);
    }
}

static Token makeToken(TokenType type)
{
    Token *token = (Token*)malloc(sizeof(Token));
    token->type = type;

    if(type == LIT)
    {    
        token->value = malloc(sizeof(int));
        *(token->value) = digit();
        return *token;
    }
    else
        token->value = NULL;

    pos++;

    return *token;   
}

static int digit()
{
    int value = 0;

    while(isdigit(source[pos]))
    {
        value *= 10;
        value += source[pos] - '0';
        pos++;
    }

    return value;
}

void printToken(Token token)
{
    switch(token.type)
    {
        case LIT: printf("< %s, %d >\n", "LIT", *(token.value)); break;
        case PLUS: printf("< %s >\n", "PLUS"); break;
        case MINUS: printf("< %s >\n", "MINUS"); break;
        case MUL: printf("< %s >\n", "MUL"); break;
        case DIV: printf("< %s >\n", "DIV"); break;
    }
}