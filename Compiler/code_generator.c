#include "code_generator.h"

CodeGenVM generateCode(SyntaxTree * st,FILE * vm_code,int initialTempReg,int nextLineNo,int lenCheckMode){
    int r1, r2,r3;
    CodeGenVM instructionRetVal={-1,-1},aux;
    int len_if_Part = 0, len_else_part = 0, repeat_ini=0;
    if(st!=NULL){
        switch (st->nodeType){
            case IF_TYPE:
                aux = generateCode(st->leftChild,vm_code,initialTempReg,nextLineNo,lenCheckMode);
                r1 = aux.destreg;
                nextLineNo = aux.endCodeLine + 1;

                //Check length of if-part
                aux = generateCode(st->centerChild,vm_code,initialTempReg,nextLineNo+1,1);
                len_if_Part = aux.endCodeLine;

                //Check len of else-part
                if(st->rightChild !=NULL){
                    aux = generateCode(st->rightChild,vm_code,initialTempReg,len_if_Part+2,1);
                    len_else_part = aux.endCodeLine;
                }

                if(st->rightChild !=NULL){
                    if(!lenCheckMode){
                        switch (st->leftChild->opType){
                            case EQUAL_OP:
                                fprintf(vm_code,"BNE,%d,0,%d\n",r1,len_if_Part+2);
                                break;
                            case LESST_OP:
                                fprintf(vm_code,"BGEZ,%d,%d\n",r1,len_if_Part+2);
                                break;

                            case MORET_OP:
                                fprintf(vm_code,"BLEZ,%d,%d\n",r1,len_if_Part+2);
                                break;

                            case EQMORET_OP:
                                fprintf(vm_code,"BLTZ,%d,%d\n",r1,len_if_Part+2);
                                break;
                            case EQLESST_OP:
                                fprintf(vm_code,"BGTZ,%d,%d\n",r1,len_if_Part+2);
                                break;
                        }

                    }

                    nextLineNo++;
                    aux = generateCode(st->centerChild,vm_code,initialTempReg,nextLineNo,lenCheckMode);
                    nextLineNo = aux.endCodeLine + 1;
                    if(!lenCheckMode)
                        fprintf(vm_code,"JUMP,%d\n",len_else_part+1);
                    nextLineNo++;
                    aux = generateCode(st->rightChild,vm_code,initialTempReg,nextLineNo,lenCheckMode);
                    nextLineNo = aux.endCodeLine + 1;
                }
                else{
                    if(!lenCheckMode){
                        switch (st->leftChild->opType){
                            case EQUAL_OP:
                                fprintf(vm_code,"BNE,%d,0,%d\n",r1,len_if_Part+1);
                                break;
                            case LESST_OP:
                                fprintf(vm_code,"BGEZ,%d,%d\n",r1,len_if_Part+1);
                                break;

                            case MORET_OP:
                                fprintf(vm_code,"BLEZ,%d,%d\n",r1,len_if_Part+1);
                                break;

                            case EQMORET_OP:
                                fprintf(vm_code,"BLTZ,%d,%d\n",r1,len_if_Part+1);
                                break;
                            case EQLESST_OP:
                                fprintf(vm_code,"BGTZ,%d,%d\n",r1,len_if_Part+1);
                                break;
                        }

                    }

                    nextLineNo++;
                    aux = generateCode(st->centerChild,vm_code,initialTempReg,nextLineNo,lenCheckMode);
                    nextLineNo = aux.endCodeLine + 1;
                }

                if(st->nextStmt != NULL){
                    aux = generateCode(st->nextStmt,vm_code,initialTempReg,nextLineNo,lenCheckMode);
                    instructionRetVal.endCodeLine = aux.endCodeLine;
                }
                else{
                    instructionRetVal.endCodeLine = aux.endCodeLine;
                }

                break;


            case REPEAT_TYPE:
                repeat_ini = nextLineNo;
                aux = generateCode(st->leftChild,vm_code,initialTempReg,nextLineNo,lenCheckMode);
                nextLineNo = aux.endCodeLine+1;
                aux = generateCode(st->centerChild,vm_code,initialTempReg,nextLineNo,lenCheckMode);
                r1 = aux.destreg;
                nextLineNo = aux.endCodeLine+1;

                if (!lenCheckMode){
                    switch (st->centerChild->opType) {
                        case EQUAL_OP:
                            fprintf(vm_code,"BNE,%d,0,%d\n",r1,repeat_ini);
                            break;
                        case LESST_OP:
                            fprintf(vm_code,"BGEZ,%d,%d\n",r1,repeat_ini);
                            break;
                        case MORET_OP:
                            fprintf(vm_code,"BLEZ,%d,%d\n",r1,repeat_ini);
                            break;
                        case EQMORET_OP:
                            fprintf(vm_code,"BLTZ,%d,%d\n",r1,repeat_ini);
                            break;
                        case EQLESST_OP:
                            fprintf(vm_code,"BGTZ,%d,%d\n",r1,repeat_ini);
                            break;

                    }
                }
                nextLineNo++;
                if(st->nextStmt != NULL){
                    aux = generateCode(st->nextStmt,vm_code,initialTempReg,nextLineNo,lenCheckMode);
                    instructionRetVal.endCodeLine = aux.endCodeLine;
                }
                else{
                    instructionRetVal.endCodeLine = aux.endCodeLine + 1;
                }

                break;

            case ASSIGN_TYPE:
                aux = generateCode(st->leftChild,vm_code,initialTempReg,nextLineNo,lenCheckMode);
                r1 = aux.destreg;
                nextLineNo = aux.endCodeLine + 1;
                if(!lenCheckMode)
                    fprintf(vm_code,"SW,%d,%d\n",r1,getSymbolPosition(st->str_value));

                instructionRetVal.endCodeLine = nextLineNo;

                if(st->nextStmt != NULL){
                    aux = generateCode(st->nextStmt,vm_code,initialTempReg,nextLineNo+1,lenCheckMode);
                    instructionRetVal = aux;
                }
                break;

            case READ_TYPE:
                r1 = initialTempReg;
                if(!lenCheckMode) {
                    fprintf(vm_code, "READ,%d\n", r1);
                    fprintf(vm_code, "SW,%d,%d\n", r1, getSymbolPosition(st->str_value));
                }
                instructionRetVal.destreg = r1;
                instructionRetVal.endCodeLine = nextLineNo+1;

                if(st->nextStmt != NULL){
                    aux = generateCode(st->nextStmt,vm_code,initialTempReg,nextLineNo+2,lenCheckMode);
                    instructionRetVal = aux;
                }
                break;

            case WRITE_TYPE:
                aux = generateCode(st->leftChild,vm_code,initialTempReg,nextLineNo,lenCheckMode);
                nextLineNo = aux.endCodeLine + 1;
                r1 = aux.destreg;
                if(!lenCheckMode)
                    fprintf(vm_code,"WRITE,%d\n",r1);

                instructionRetVal.destreg = initialTempReg;
                instructionRetVal.endCodeLine = nextLineNo;

                if(st->nextStmt != NULL){
                    aux = generateCode(st->nextStmt,vm_code,initialTempReg,nextLineNo+1,lenCheckMode);
                    instructionRetVal = aux;
                }
                break;
            case ID_TYPE:
                r1 = initialTempReg;
                if(!lenCheckMode)
                    fprintf(vm_code,"LW,%d,%d\n",r1,getSymbolPosition(st->str_value));
                instructionRetVal.destreg = r1;
                instructionRetVal.endCodeLine = nextLineNo;
                break;

            case CONST_TYPE:
                r1 = initialTempReg;
                if(!lenCheckMode)
                    fprintf(vm_code,"ADDI,%d,0,%d\n",r1,st->value);
                instructionRetVal.destreg = r1;
                instructionRetVal.endCodeLine = nextLineNo;
                break;

            case OPERATION_TYPE:
                aux = generateCode(st->leftChild,vm_code,initialTempReg+1,nextLineNo,lenCheckMode);
                r1 = aux.destreg;
                nextLineNo = aux.endCodeLine + 1;
                aux = generateCode(st->centerChild,vm_code,initialTempReg+2,nextLineNo,lenCheckMode);
                r2 = aux.destreg;
                nextLineNo = aux.endCodeLine + 1;
                r3 = initialTempReg;

                if(!lenCheckMode){
                    switch (st->opType) {
                        case PLUS_OP:
                            fprintf(vm_code,"ADD,%d,%d,%d\n",r3,r1,r2);
                            break;

                        case SUB_OP:
                            fprintf(vm_code,"SUB,%d,%d,%d\n",r3,r1,r2);
                            break;
                        case MULT_OP:
                            fprintf(vm_code,"MULT,%d,%d,%d\n",r3,r1,r2);
                            break;

                        case DIV_OP:
                            fprintf(vm_code,"DIV,%d,%d,%d\n",r3,r1,r2);
                            break;

                        case EQUAL_OP:
                            fprintf(vm_code,"SUB,%d,%d,%d\n",r3,r1,r2);
                            break;

                        case LESST_OP:
                            fprintf(vm_code,"SUB,%d,%d,%d\n",r3,r1,r2);
                            break;

                        case MORET_OP:
                            fprintf(vm_code,"SUB,%d,%d,%d\n",r3,r1,r2);
                            break;

                        case EQMORET_OP:
                            fprintf(vm_code,"SUB,%d,%d,%d\n",r3,r1,r2);
                            break;
                        case EQLESST_OP:
                            fprintf(vm_code,"SUB,%d,%d,%d\n",r3,r1,r2);
                            break;
                    }
                }

                instructionRetVal.destreg = r3;
                instructionRetVal.endCodeLine = nextLineNo;

                break;


        }
        return instructionRetVal;
    }
}

// InitialTempReg is 1, $0 is constant, using VM MIPS type register.
void codeGenerator(SyntaxTree * st,char * destFile){
    FILE * vm_code = NULL;
    if((vm_code=fopen(destFile,"w"))==NULL){
        printf("Unable to create destination file");
        exit(EXIT_FAILURE);
    }
    generateCode(st,vm_code,1,0,0);
    fprintf(vm_code,"HALT");
    fclose(vm_code);
}