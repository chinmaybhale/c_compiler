typedef enum TokenType
{
    //binary operators
    PLUS, MINUS, MUL, DIV,
    
    //literal
    LIT,

    //operations
    BINOP, UNOP,

    //End-of-file
    E

} TokenType;