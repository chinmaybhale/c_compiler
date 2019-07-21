typedef enum TokenType
{
    //keywords
    IF, AND, OR, WHILE, VAR_I, VAR_S, PRINT,

    //binary operators
    PLUS, MINUS, MUL, DIV, 
    LESSTHAN, MORETHAN, LESSEQ, MOREEQ, EQEQ,
    EQUAL, BANG, BANGEQ, COND,
    
    //literal
    LIT,

    //other symbols
    LPAREN, RPAREN, LBRACE, RBRACE,

    //operations
    BINOP, UNOP,

    //End-of-file
    E

} TokenType;