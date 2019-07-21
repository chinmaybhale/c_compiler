#include "tokentypeEnum.h"

//TODO: fix the hell created by this
typedef struct Token
{
    TokenType type;
    union
    {
        int value;
        char *str;
    } data;
    

} Token;

void initLexer(const char*, const char);
Token* getTokens();
unsigned int get_tokens_size();
Token getToken();
void printToken(Token);