#include <stdio.h>
#include <stdlib.h>
#include "CodeGenerator/code_generator.h"

extern FILE * yyin;

int main(int argc, char * argv []){
    SyntaxTree * syntaxTree;

    if(argc!=2){
        printf("Input file is missing!\n");
        exit(EXIT_FAILURE);
    }

    char * fileName = argv[1];
    FILE * code = NULL;

    if((code = fopen(fileName,"r"))==NULL){
        exit(EXIT_FAILURE);
    }
    //Set code as input
    yyin = code;
    //Create syntax tree
    syntaxTree = parse();

    //Show syntax tree
    printf("\nSyntax Tree:\n");
    showSyntaxTree(syntaxTree,0);

    //Build symbols table
    buildSymtab(syntaxTree);
    
    //Check typos
    printf("Checking typos: ");
    typeCheck(syntaxTree);
    printf("Typos OK\n");

    //Show symbols table
    printf("Symbols table:\n");
    showSymbolTable();

    //Generate code
    codeGen(syntaxTree,strcat(fileName,".vm"));
    
}

