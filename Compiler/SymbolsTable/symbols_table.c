#include "symbols_table.h"

struct symbol sym_table[SYMTABLE_SIZE]; // The symbol table
int nextEmptyPos = 0; // For adding new variables

int getSymbolMemoryPosition(char * varName){
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
    if(getSymbolMemoryPosition(varName)==-1){
        struct symbol aNewSymbol = {0,NULL,varName,"NA"}; //NA means Not assigned
        sym_table[nextEmptyPos] = aNewSymbol;
        nextEmptyPos++;
        symbolAdded = 1;
    }
    return symbolAdded;
}

void setSymbolVarType(char * varName, char * varType){
    int i;
    for(i=0;i<nextEmptyPos;i++){
        if(strcmp(varName,sym_table[i].varName)==0){
            strncpy(sym_table[i].var_type,varType,MAXLEN_VARTYPE);
        }
    }
}

char * getSymbolVarType(char * varName){
    int i;
    char *vartype = malloc(MAXLEN_VARTYPE*sizeof(char));
    vartype[0] = '\0';
    for(i=0;i<nextEmptyPos;i++){
        if(strcmp(varName,sym_table[i].varName)==0){
            strncpy(vartype,sym_table[i].var_type,MAXLEN_VARTYPE);
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
                    printf("Error allocating memory for symbols table\n");
                    exit(EXIT_FAILURE);
                }
                sym_table[i].lines[0] = lineNo;
            }
            else{
                sym_table[i].linesNo++;
                sym_table[i].lines = (int *) realloc(sym_table[i].lines,sizeof(int)*sym_table[i].linesNo);
                if(sym_table[i].lines == NULL){
                    printf("Error allocating memory for symbols table\n");
                    exit(EXIT_FAILURE);
                }
                sym_table[i].lines[sym_table[i].linesNo-1] = lineNo;
            }
        }
    }
}

void showSymbolTable(){
    printf("Variable\tLines\t\tType\tLocation\n");
    int i,j;
    for(i=0;i<nextEmptyPos;i++){
        printf("%s\t\t",sym_table[i].varName);
        for(j=0;j<sym_table[i].linesNo;j++){
            printf("%d,",sym_table[i].lines[j]);
        }
        printf("\t%s\t%d",sym_table[i].var_type,i);
        printf("\n");
    }
}


void buildSymtab(SyntaxTree * st){
    if(st != NULL){
        if(st->nodeType == ASSIGN_TYPE || st->nodeType == READ_TYPE || st->nodeType == ID_TYPE){
            addSymbol(st->str_value);
            addLineToSymbol(st->lineNo,st->str_value);
        }
        buildSymtab(st->leftChild);
        buildSymtab(st->centerChild);
        buildSymtab(st->rightChild);
        buildSymtab(st->nextStmt);
    }
}