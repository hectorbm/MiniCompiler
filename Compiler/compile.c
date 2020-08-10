#include <stdio.h>
#include <stdlib.h>
#include "code_generator.h"

extern FILE * yyin;

int main(int argc, char * argv []){
    SyntaxTree * st;

    if(argc!=2){
        exit(EXIT_FAILURE);
    }

    char * fileName = argv[1];
    FILE * code = NULL;

    if((code = fopen(fileName,"r"))==NULL){
        exit(EXIT_FAILURE);
    }
    //Set code as Lex input
    yyin = code;
    //Create syntax tree
    st = parseAndGetSyntaxTree();

    //Show syntax tree
    printf("\nSyntax Tree:\n");
    showSyntaxTree(st,0);

    //Build symbols table
    buildSymbolsTable(st);

    //Check typos
    printf("Checking typos: ");
    check_typos(st);
    printf("Typos OK\n");

    //Show symbols table
    printf("Symbol table:\n");
    showSymbolTable();

    //Generate code
    codeGenerator(st,strcat(fileName,".vm"));

}

