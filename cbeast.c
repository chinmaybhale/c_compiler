#include <stdlib.h>
#include <stdio.h>
#include "headers/cbeast.h"

#define CHUNK 1024

char* readFile(char*);
int shell();

int main(int argc, char** argv)
{
    printf("cbeast v0.1\n");

    if(argc != 2)
    {
        printf("Filename not specified... running on shell\n");
        while(shell());
        return 0;
    }

    char *source = readFile(argv[1]);

    initLexer(source, 'a');
    initParser(getTokens(), get_tokens_size());
    interpret(parse(), getNodeAmt());

    free(source);
    return 0;
}

int shell()
{
    char *source = (char*)malloc(CHUNK);
    printf(">");
    fgets(source, CHUNK, stdin);
    source[CHUNK - 1] = '\0';
    initLexer(source, 'a');
    initParser(getTokens(), get_tokens_size());
    interpret(parse(), getNodeAmt());
    free(source);

    return 0;
}

char* readFile(char *filename)
{
    char *source = (char*)malloc(CHUNK);
    FILE *file = fopen(filename, "r");

    if(!file)
    {
        printf("file not found!/file not open!");
        exit(0);
    }

    while(fread(source, 1, CHUNK, file));

    source[CHUNK - 1] = '\0';
    
    fclose(file);
    return source;
}