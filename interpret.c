#include <stdio.h>
#include "headers/interpret.h"

static int solveNodes(Node*);
static int binop(Node**);

void interpret(Node **parsed_nodes, unsigned int node_amt)
{
    int i, result = 0;

    for(i = 0; i <= node_amt; i++)
    {
        result += solveNodes(parsed_nodes[i]);
    }

    printf("%d\n", result);

}

static int solveNodes(Node* node)
{
    switch(node->type)
    {
        case BINOP : return binop(node->data.node);

        case LIT : return node->data.value;
    }
}

static int binop(Node** node)
{
    int result = 0;

    switch(node[0]->type)
    {
        case PLUS: result = solveNodes(node[1]) + solveNodes(node[2]); break;
        case MINUS: result = solveNodes(node[1]) - solveNodes(node[2]); break;
        case MUL: result = solveNodes(node[1]) * solveNodes(node[2]); break;
        case DIV: result = solveNodes(node[1]) / solveNodes(node[2]); break;
    }

    return result;
}

