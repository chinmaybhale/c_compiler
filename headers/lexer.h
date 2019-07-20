#include "tokentypeEnum.h"

typedef struct Token
{
    TokenType type;
    int *value;

} Token;

void initLexer(const char*, const char);
Token* getTokens();
unsigned int get_tokens_size();
Token getToken();
void printToken(Token);