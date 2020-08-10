#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SYMTABLE_SIZE 15
#include "../Syntax_Tree/syntax_tree.h"

struct symbol{
    int linesNo; //Number of lines the symbol appears
    int * lines; //Dynamic array with the line number of each appearance
    char * varName; //Symbol name in the program
    int value; // Value of the symbol (This language only allows integers)
    char var_type[5];
};

int getSymbolPosition(char * varName);
int addSymbol(char * varName);
void setValueToSymbol(int aValue, char * varName);
void addLineToSymbol(int lineNo, char * varName);
void showSymbolTable();
void buildSymbolsTable(SyntaxTree * st);
void setSymbolVarType(char * varName, char * varType);
char * getSymbolVarType(char * varName);