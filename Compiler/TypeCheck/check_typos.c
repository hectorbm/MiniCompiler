#include "check_typos.h"

char * typeCheck(SyntaxTree *st){
    char aux[MAXTYPELEN],aux2[MAXTYPELEN];
    char *typo=NULL;
    if(st != NULL){
        switch (st->nodeType) {
            case IF_TYPE:
                strncpy(aux,typeCheck(st->leftChild),MAXTYPELEN);
                if(strcmp(aux,BOOL)!=0){
                    printf("Type error in if: %s instead of bool at line:%d\n",aux,st->leftChild->lineNo);
                    exit(EXIT_FAILURE);
                }
                typeCheck(st->centerChild);
                typeCheck(st->rightChild);
                typeCheck(st->nextStmt);
                break;

            case REPEAT_TYPE:
                strncpy(aux,typeCheck(st->centerChild),MAXTYPELEN);
                if(strcmp(aux,BOOL)!=0){
                    printf("Type error in repeat: %s instead of bool at line:%d\n",aux,st->lineNo);
                    exit(EXIT_FAILURE);
                }
                typeCheck(st->leftChild);
                typeCheck(st->nextStmt);
                break;

            case ASSIGN_TYPE:
                strncpy(aux,typeCheck(st->leftChild),MAXTYPELEN);
                if(strcmp(aux,INT)!=0){
                    printf("Type error in assignment: %s instead of int at line:%d\n",aux,st->lineNo);
                    exit(EXIT_FAILURE);
                }
                if(strcmp(getSymbolVarType(st->str_value),NA)==0){
                    setSymbolVarType(st->str_value,aux);
                }
                typeCheck(st->nextStmt);
                break;

            case READ_TYPE:
                setSymbolVarType(st->str_value,INT);
                typeCheck(st->nextStmt);
                break;

            case WRITE_TYPE:
                strncpy(aux,typeCheck(st->leftChild),MAXTYPELEN);
                if(strcmp(aux,INT)!=0){
                    printf("Type error in write: %s instead of int at line:%d\n",aux,st->lineNo);
                    exit(EXIT_FAILURE);
                }
                typeCheck(st->nextStmt);
                break;

            case ID_TYPE:
                typo = getSymbolVarType(st->str_value);
                break;

            case CONST_TYPE:
                typo = INT;
                break;

            case OPERATION_TYPE:
                switch (st->opType) {
                    case PLUS_OP:
                    case SUB_OP:
                    case MULT_OP:
                    case DIV_OP:
                        strncpy(aux,typeCheck(st->leftChild),MAXTYPELEN);
                        strncpy(aux2,typeCheck(st->centerChild),MAXTYPELEN);
                        if(strcmp(aux,INT)!=0){
                            printf("Type error in operation: %s instead of int at line:%d\n",aux,st->lineNo);
                            exit(EXIT_FAILURE);
                        }
                        else if(strcmp(aux2,INT)!=0){
                            printf("Type error in operation: %s instead of int at line:%d\n",aux2,st->lineNo);
                            exit(EXIT_FAILURE);
                        }
                        else{
                            typo = INT;
                        }
                        break;

                    case EQUAL_OP:
                    case LESST_OP:
                    case MORET_OP:
                    case EQMORET_OP:
                    case EQLESST_OP:
                        strncpy(aux,typeCheck(st->leftChild),MAXTYPELEN);
                        strncpy(aux2,typeCheck(st->centerChild),MAXTYPELEN);
                        if(strcmp(aux,INT)!=0){
                            printf("Type error in comparison: %s instead of int at line:%d\n",aux,st->lineNo);
                            exit(EXIT_FAILURE);
                        }
                        else if(strcmp(aux2,INT)!=0){
                            printf("Type error in comparison: %s instead of int at line:%d\n",aux2,st->lineNo);
                            exit(EXIT_FAILURE);
                        }
                        else{
                            typo = BOOL;
                        }
                        break;
                }
                break;
                
        }
    }
    return typo;
}