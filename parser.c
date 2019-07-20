#include <stdlib.h>
#include <stdio.h>
#include "headers/parser.h"

#define INIT_ROOT_NODE (Node**)malloc(sizeof(Node*))
#define CREATE_NODE (Node*)malloc(sizeof(Node))

static Node* muldiv();
static Node* literal();
static Node* swap(Node*, TokenType);
static void eat(Token);

static Token *token_array;
static unsigned int token_array_size;
static unsigned int token_pos = 0;
static Token curr, prev;
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
        nodes[node_amt++] = muldiv();
    }

    return nodes;
}

unsigned int getNodeAmt()
{
    return node_amt;
}

// Node* plusminus()
// {
//     node = muldiv();
//     return node;
// }

static Node* muldiv()
{
    Node *node = literal();

    if(curr.type == MUL)
    {
        eat(curr);
        node = swap(node, BINOP);
        node->data.node[0] = CREATE_NODE;
        node->data.node[0]->type = MUL;
        node->data.node[2] = muldiv();
    }
    if(curr.type == DIV)
    {
        eat(curr);
        node = swap(node, BINOP);
        node->data.node[0] = CREATE_NODE;
        node->data.node[0]->type = DIV;
        node->data.node[2] = muldiv();
    }

    return node;
}

static Node* literal()
{
    Node *node = CREATE_NODE;

    if(curr.type == LIT)
    {
        node->type = LIT;
        node->data.value = *(curr.value);
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