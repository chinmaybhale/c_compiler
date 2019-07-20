typedef enum TokenType
{
    //binary operators
    PLUS, MINUS, MUL, DIV, 
    
    //literal
    LIT,

    //other symbols
    LPAREN, RPAREN, LBRACE, RBRACE,

    //operations
    BINOP, UNOP,

    //End-of-file
    E

} TokenType;