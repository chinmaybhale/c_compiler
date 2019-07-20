#include "lexer.h"

typedef struct Node
{
    TokenType type;

    union 
    {
        struct Node **node;
        int value;

    } data;
    
} Node;

void initParser(Token*, unsigned int);
Node** parse();
unsigned int getNodeAmt();