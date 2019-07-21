#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "headers/lexer.h"

#define ALLOC_SIZE 20
#define INIT_TOKEN (Token*)malloc(sizeof(Token))

static Token makeToken(TokenType);
static Token make_logic_token(TokenType);
static Token digit();

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

//TODO: add new symbols
Token getToken()
{
    switch(source[pos])
    {
        case ' ' : pos++; return getToken();
        case '+' : return makeToken(PLUS);
        case '-' : return makeToken(MINUS);
        case '*' : return makeToken(MUL);
        case '/' : return makeToken(DIV);

        case '(' : return makeToken(LPAREN);
        case ')' : return makeToken(RPAREN);
        case '{' : return makeToken(LBRACE);
        case '}' : return makeToken(RBRACE);

        case '?' : return makeToken(COND);
        case '<' : return make_logic_token(LESSTHAN);
        case '>' : return make_logic_token(MORETHAN);
        case '=' : return make_logic_token(EQUAL);
        case '!' : return make_logic_token(BANG); 
        default :
            if(isdigit(source[pos]))
                return digit();
            else
                return makeToken(E);
    }
}

//TODO: rename to make_token
static Token makeToken(TokenType type)
{
    Token *token = INIT_TOKEN;
    token->type = type;

    token->data.str = NULL;

    pos++;

    return *token;   
}

static Token make_logic_token(TokenType type)
{
    Token *token = INIT_TOKEN;

    if(source[pos + 1] == '=')
    {
        switch(source[pos])
        {
            case '<' : type = LESSEQ; break;
            case '>' : type = MOREEQ; break;
            case '=' : type = EQEQ; break;
            case '!' : type = BANGEQ; break;
        }

        pos++;
    }
    
    return makeToken(type);
}

//TODO: rename to make_lit_token
static Token digit()
{
    Token *token = INIT_TOKEN;
    int value = 0;

    while(isdigit(source[pos]))
    {
        value *= 10;
        value += source[pos] - '0';
        pos++;
    }

    token->type = LIT;
    token->data.value = value;
    
    return *token;
}

void printToken(Token token)
{
    switch(token.type)
    {
        case LIT: printf("< %s, %d >\n", "LIT", token.data.value); break;
        case PLUS: printf("< %s >\n", "PLUS"); break;
        case MINUS: printf("< %s >\n", "MINUS"); break;
        case MUL: printf("< %s >\n", "MUL"); break;
        case DIV: printf("< %s >\n", "DIV"); break;
        case COND: printf("< %s >\n", "COND"); break;
        case IF: printf("< %s >\n", "IF"); break;
        case AND: printf("< %s >\n", "AND"); break;
        case OR: printf("< %s >\n", "OR"); break;
        case WHILE: printf("< %s >\n", "WHILE"); break;
        case VAR_I: printf("< %s, %s >\n", "VAR_I", token.data.str); break;
        case VAR_S: printf("< %s, %s >\n", "VAR_S", token.data.str); break;
        case PRINT: printf("< %s >\n", "PRINT"); break;
    }
}