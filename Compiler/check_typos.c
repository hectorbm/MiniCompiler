#include "check_typos.h"

char * check_typos(SyntaxTree *st){
    char aux[MAXTYPELEN],aux2[MAXTYPELEN];
    if(st != NULL){
        switch (st->nodeType) {
            case IF_TYPE:
                strncpy(aux,check_typos(st->leftChild),MAXTYPELEN);
                if(strcmp(aux,BOOL)!=0){
                    printf("Type error: %s instead of bool\n",aux);
                    exit(EXIT_FAILURE);
                }
                check_typos(st->centerChild);
                check_typos(st->rightChild);
                check_typos(st->nextStmt);
                break;

            case REPEAT_TYPE:
                strncpy(aux,check_typos(st->centerChild),MAXTYPELEN);
                if(strcmp(aux,BOOL)!=0){
                    printf("Type error: %s instead of bool\n",aux);
                    exit(EXIT_FAILURE);
                }
                check_typos(st->leftChild);
                check_typos(st->nextStmt);
                break;

            case ASSIGN_TYPE:
                strncpy(aux,check_typos(st->leftChild),MAXTYPELEN);
                if(strcmp(aux,INT)!=0){
                    printf("Type error: %s instead of int\n",aux);
                    exit(EXIT_FAILURE);
                }
                if(strcmp(getSymbolVarType(st->str_value),NA)==0){
                    setSymbolVarType(st->str_value,aux);
                }
                check_typos(st->nextStmt);
                break;

            case READ_TYPE:
                setSymbolVarType(st->str_value,INT);
                check_typos(st->nextStmt);
                break;

            case WRITE_TYPE:
                strncpy(aux,check_typos(st->leftChild),MAXTYPELEN);
                if(strcmp(aux,INT)!=0){
                    printf("Type error: %s instead of int\n",aux);
                    exit(EXIT_FAILURE);
                }
                check_typos(st->nextStmt);
                break;

            case ID_TYPE:
                strncpy(st->varType,getSymbolVarType(st->str_value),5);
                return st->varType;

            case CONST_TYPE:
                strncpy(st->varType,INT,5);
                return st->varType;

            case OPERATION_TYPE:
                switch (st->opType) {
                    case PLUS_OP:
                        strncpy(aux,check_typos(st->leftChild),MAXTYPELEN);
                        strncpy(aux2,check_typos(st->centerChild),MAXTYPELEN);
                        if(strcmp(aux,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }
                        if(strcmp(aux2,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }

                        return INT;
                    case SUB_OP:
                        strncpy(aux,check_typos(st->leftChild),MAXTYPELEN);
                        strncpy(aux2,check_typos(st->centerChild),MAXTYPELEN);
                        if(strcmp(aux,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }
                        if(strcmp(aux2,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }

                        return INT;
                    case MULT_OP:
                        strncpy(aux,check_typos(st->leftChild),MAXTYPELEN);
                        strncpy(aux2,check_typos(st->centerChild),MAXTYPELEN);
                        if(strcmp(aux,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }
                        if(strcmp(aux2,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }

                        return INT;
                    case DIV_OP:
                        strncpy(aux,check_typos(st->leftChild),MAXTYPELEN);
                        strncpy(aux2,check_typos(st->centerChild),MAXTYPELEN);
                        if(strcmp(aux,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }
                        if(strcmp(aux2,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }

                        return INT;
                    case EQUAL_OP:
                        strncpy(aux,check_typos(st->leftChild),MAXTYPELEN);
                        strncpy(aux2,check_typos(st->centerChild),MAXTYPELEN);
                        if(strcmp(aux,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }
                        if(strcmp(aux2,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }

                        return BOOL;
                    case LESST_OP:
                        strncpy(aux,check_typos(st->leftChild),MAXTYPELEN);
                        strncpy(aux2,check_typos(st->centerChild),MAXTYPELEN);
                        if(strcmp(aux,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }
                        if(strcmp(aux2,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }

                        return BOOL;
                    case MORET_OP:
                        strncpy(aux,check_typos(st->leftChild),MAXTYPELEN);
                        strncpy(aux2,check_typos(st->centerChild),MAXTYPELEN);
                        if(strcmp(aux,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }
                        if(strcmp(aux2,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }

                        return BOOL;
                    case EQMORET_OP:
                        strncpy(aux,check_typos(st->leftChild),MAXTYPELEN);
                        strncpy(aux2,check_typos(st->centerChild),MAXTYPELEN);
                        if(strcmp(aux,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }
                        if(strcmp(aux2,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }

                        return BOOL;
                    case EQLESST_OP:
                        strncpy(aux,check_typos(st->leftChild),MAXTYPELEN);
                        strncpy(aux2,check_typos(st->centerChild),MAXTYPELEN);
                        if(strcmp(aux,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }
                        if(strcmp(aux2,INT)!=0){
                            printf("Type error: %s instead of int\n",aux);
                            exit(EXIT_FAILURE);
                        }

                        return BOOL;
                }
                break;
        }
    }
    return NULL;
}