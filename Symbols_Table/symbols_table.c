#include "symbols_table.h"

struct symbol sym_table[SYMTABLE_SIZE]; // The symbol table
int nextEmptyPos = 0; // For adding new variables

int getSymbolPosition(char * varName){
    int i;
    for (i=0;i<nextEmptyPos;i++){
        if(strcmp(varName,sym_table[i].varName)==0){
            return i;
        }
    }
    return -1;
}

int addSymbol(char * varName){
    int symbolAdded = 0;
    if(getSymbolPosition(varName)==-1){
        struct symbol aNewSymbol = {0,NULL,varName,0,"NA"}; //NA means Not assigned
        sym_table[nextEmptyPos] = aNewSymbol;
        nextEmptyPos++;
        symbolAdded = 1;
    }
    return symbolAdded;
}

void setValueToSymbol(int aValue, char * varName){
    int i;
    for(i=0;i<nextEmptyPos;i++){
         if(strcmp(varName,sym_table[i].varName)==0){
             sym_table[i].value = aValue;
         }
    }
}

void setSymbolVarType(char * varName, char * varType){
    int i;
    for(i=0;i<nextEmptyPos;i++){
        if(strcmp(varName,sym_table[i].varName)==0){
            strncpy(sym_table[i].var_type,varType,5);
        }
    }
}

char * getSymbolVarType(char * varName){
    int i;
    char *vartype = malloc(5*sizeof(char));
    vartype[0] = '\0';
    for(i=0;i<nextEmptyPos;i++){
        if(strcmp(varName,sym_table[i].varName)==0){
            strncpy(vartype,sym_table[i].var_type,5);
        }
    }
    return vartype;
}

void addLineToSymbol(int lineNo, char * varName){
    int i;
    for(i=0;i<nextEmptyPos;i++){
        if(strcmp(varName,sym_table[i].varName)==0){
            if(sym_table[i].lines == NULL){
                sym_table[i].linesNo++;
                sym_table[i].lines = (int *) malloc(sizeof(int));
                if(sym_table[i].lines == NULL){
                    printf("Error allocating memory\n");
                    exit(EXIT_FAILURE);
                }
                sym_table[i].lines[0] = lineNo;
            }
            else{
                sym_table[i].linesNo++;
                sym_table[i].lines = (int *) realloc(sym_table[i].lines,sizeof(int)*sym_table[i].linesNo);
                if(sym_table[i].lines == NULL){
                    printf("Error allocating memory\n");
                    exit(EXIT_FAILURE);
                }
                sym_table[i].lines[sym_table[i].linesNo-1] = lineNo;
            }
        }
    }
}

void showSymbolTable(){
    printf("Variable Initial Value\tLines\tType\n");
    int i,j;
    for(i=0;i<nextEmptyPos;i++){
        printf("%s\t%d\t\t",sym_table[i].varName,sym_table[i].value);
        for(j=0;j<sym_table[i].linesNo;j++){
            printf("%d,",sym_table[i].lines[j]);
        }
        printf("\t%s",sym_table[i].var_type);
        printf("\n");
    }
}


void buildSymbolsTable(SyntaxTree * st){
    if(st != NULL){
        if(st->nodeType == ASSIGN_TYPE || st->nodeType == READ_TYPE || st->nodeType == ID_TYPE){
            addSymbol(st->str_value);
        }
        buildSymbolsTable(st->leftChild);
        buildSymbolsTable(st->centerChild);
        buildSymbolsTable(st->rightChild);
        buildSymbolsTable(st->nextStmt);
    }
}