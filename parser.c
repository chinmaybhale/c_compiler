#include <stdlib.h>
#include <stdio.h>
#include "headers/parser.h"

#define INIT_ROOT_NODE (Node**)malloc(sizeof(Node*))
#define CREATE_NODE (Node*)malloc(sizeof(Node))

static Node* stmts();
static Node* expr();
static Node* bangeq_eq();
static Node* less_more();
static Node* plusminus();
static Node* muldiv();
static Node* literal();
static Node* swap(Node*, TokenType);
static void eat(Token);

static Token *token_array;
static unsigned int token_array_size;
static unsigned int token_pos = 0;
static Token curr;
static unsigned int node_amt = 0;

void initParser(Token *array, unsigned int size)
{
    token_array = array;
    token_array_size = size;

    curr = token_array[0];
}

Node** parse()
{
    Node **nodes = INIT_ROOT_NODE;

    while(token_pos <= token_array_size)
    {
        nodes[node_amt++] = expr();
    }

    return nodes;
}

unsigned int getNodeAmt()
{
    return node_amt;
}

static Node* expr()
{
    if(curr.type == COND)
    {
        eat(curr);
        return bangeq_eq();
    }

    return plusminus();
}

static Node* bangeq_eq()
{
    Node* node = less_more();

    if(curr.type == BANGEQ)
    {
        //do something
        eat(curr);
        node = swap(node, BINOP);
        node->data.node[0] = CREATE_NODE;
        node->data.node[0]->type = BANGEQ;
        node->data.node[2] = bangeq_eq();
    }
    if(curr.type == EQEQ)
    {
        //do something
        eat(curr);
        node = swap(node, BINOP);
        node->data.node[0] = CREATE_NODE;
        node->data.node[0]->type = EQEQ;
        node->data.node[2] = bangeq_eq();

    }

    return node;
}

static Node* less_more()
{
    Node* node = plusminus();

    if(curr.type == LESSTHAN)
    {
        eat(curr);
        node = swap(node, BINOP);
        node->data.node[0] = CREATE_NODE;
        node->data.node[0]->type = LESSTHAN;
        node->data.node[2] = bangeq_eq();
    }
    if(curr.type == MORETHAN)
    {
        eat(curr);
        node = swap(node, BINOP);
        node->data.node[0] = CREATE_NODE;
        node->data.node[0]->type = MORETHAN;
        node->data.node[2] = bangeq_eq();
    }
    if(curr.type == LESSEQ)
    {
        eat(curr);
        node = swap(node, BINOP);
        node->data.node[0] = CREATE_NODE;
        node->data.node[0]->type = LESSEQ;
        node->data.node[2] = bangeq_eq();
    }
    if(curr.type == MOREEQ)
    {
        eat(curr);
        node = swap(node, BINOP);
        node->data.node[0] = CREATE_NODE;
        node->data.node[0]->type = MOREEQ;
        node->data.node[2] = bangeq_eq();
    }
    

    return node;
}

static Node* plusminus()
{
    Node* node = muldiv();

    if(curr.type == PLUS)
    {
        eat(curr);
        node = swap(node, BINOP);
        node->data.node[0] = CREATE_NODE;
        node->data.node[0]->type = PLUS;
        node->data.node[2] = bangeq_eq();
    }
    if(curr.type == MINUS)
    {
        eat(curr);
        node = swap(node, BINOP);
        node->data.node[0] = CREATE_NODE;
        node->data.node[0]->type = MINUS;
        node->data.node[2] = bangeq_eq();
    }

    return node;
}

static Node* muldiv()
{
    Node *node = literal();

    if(curr.type == MUL)
    {
        eat(curr);
        node = swap(node, BINOP);
        node->data.node[0] = CREATE_NODE;
        node->data.node[0]->type = MUL;
        node->data.node[2] = bangeq_eq();
    }
    if(curr.type == DIV)
    {
        eat(curr);
        node = swap(node, BINOP);
        node->data.node[0] = CREATE_NODE;
        node->data.node[0]->type = DIV;
        node->data.node[2] = bangeq_eq();
    }

    return node;
}

static Node* literal()
{
    Node *node = CREATE_NODE;

    if(curr.type == LIT)
    {
        node->type = LIT;
        node->data.value = curr.data.value;
        eat(curr);
    }
    if(curr.type == LPAREN)
    {
        eat(curr);
        node = bangeq_eq();
        eat(curr);
    }

    return node;
}

static Node* swap(Node* original_node, TokenType type)
{
    Node *new_node = CREATE_NODE;
    new_node->type = type;
    new_node->data.node = INIT_ROOT_NODE;
    new_node->data.node[1] = original_node;

    return new_node;
}

static void eat(Token current)
{
    curr = token_array[++token_pos];
}