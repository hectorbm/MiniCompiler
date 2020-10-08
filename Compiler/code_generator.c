#include "code_generator.h"

CodeGenVM generateCode(SyntaxTree * st,FILE * vm_code,int initialTempReg,int nextLineNo,int branchLengthCheckMode){
    int r1, r2,r3;
    CodeGenVM instructionRetVal = {-1,-1};
    CodeGenVM aux;
    int len_if_Part = 0, len_else_part = 0, repeat_initial_pos = 0;

    if(st!=NULL){
        switch (st->nodeType){
            case IF_TYPE:
                aux = generateCode(st->leftChild,vm_code,initialTempReg,nextLineNo,branchLengthCheckMode);
                r1 = aux.destinationRegister;
                nextLineNo = aux.lastLineOfCode + 1;

                //Check length of if-part
                aux = generateCode(st->centerChild,vm_code,initialTempReg,nextLineNo+1,1);
                len_if_Part = aux.lastLineOfCode;

                //Check len of else-part
                if(st->rightChild !=NULL){
                    aux = generateCode(st->rightChild,vm_code,initialTempReg,len_if_Part+2,1);
                    len_else_part = aux.lastLineOfCode;
                }
                //Write instructions for if-only 
                if(st->rightChild !=NULL){
                    if(!branchLengthCheckMode){
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
                    aux = generateCode(st->centerChild,vm_code,initialTempReg,nextLineNo,branchLengthCheckMode);
                    nextLineNo = aux.lastLineOfCode + 1;
                    if(!branchLengthCheckMode)
                        fprintf(vm_code,"JUMP,%d\n",len_else_part+1);
                    nextLineNo++;
                    aux = generateCode(st->rightChild,vm_code,initialTempReg,nextLineNo,branchLengthCheckMode);
                    nextLineNo = aux.lastLineOfCode + 1;
                }
                // Write instructions for if-else
                else{
                    if(!branchLengthCheckMode){
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
                    aux = generateCode(st->centerChild,vm_code,initialTempReg,nextLineNo,branchLengthCheckMode);
                    nextLineNo = aux.lastLineOfCode + 1;
                }

                if(st->nextStmt != NULL){
                    aux = generateCode(st->nextStmt,vm_code,initialTempReg,nextLineNo,branchLengthCheckMode);
                    instructionRetVal.lastLineOfCode = aux.lastLineOfCode;
                }
                else{
                    instructionRetVal.lastLineOfCode = aux.lastLineOfCode;
                }

                break;


            case REPEAT_TYPE:
                repeat_initial_pos = nextLineNo;
                aux = generateCode(st->leftChild,vm_code,initialTempReg,nextLineNo,branchLengthCheckMode);
                nextLineNo = aux.lastLineOfCode+1;
                aux = generateCode(st->centerChild,vm_code,initialTempReg,nextLineNo,branchLengthCheckMode);
                r1 = aux.destinationRegister;
                nextLineNo = aux.lastLineOfCode+1;

                if (!branchLengthCheckMode){
                    switch (st->centerChild->opType) {
                        case EQUAL_OP:
                            fprintf(vm_code,"BNE,%d,0,%d\n",r1,repeat_initial_pos);
                            break;
                        case LESST_OP:
                            fprintf(vm_code,"BGEZ,%d,%d\n",r1,repeat_initial_pos);
                            break;
                        case MORET_OP:
                            fprintf(vm_code,"BLEZ,%d,%d\n",r1,repeat_initial_pos);
                            break;
                        case EQMORET_OP:
                            fprintf(vm_code,"BLTZ,%d,%d\n",r1,repeat_initial_pos);
                            break;
                        case EQLESST_OP:
                            fprintf(vm_code,"BGTZ,%d,%d\n",r1,repeat_initial_pos);
                            break;

                    }
                }
                nextLineNo++;
                if(st->nextStmt != NULL){
                    aux = generateCode(st->nextStmt,vm_code,initialTempReg,nextLineNo,branchLengthCheckMode);
                    instructionRetVal.lastLineOfCode = aux.lastLineOfCode;
                }
                else{
                    instructionRetVal.lastLineOfCode = aux.lastLineOfCode + 1;
                }

                break;

            case ASSIGN_TYPE:
                aux = generateCode(st->leftChild,vm_code,initialTempReg,nextLineNo,branchLengthCheckMode);
                r1 = aux.destinationRegister;
                nextLineNo = aux.lastLineOfCode + 1;
                if(!branchLengthCheckMode)
                    fprintf(vm_code,"SW,%d,%d\n",r1,getSymbolMemoryPosition(st->str_value));

                instructionRetVal.lastLineOfCode = nextLineNo;

                if(st->nextStmt != NULL){
                    aux = generateCode(st->nextStmt,vm_code,initialTempReg,nextLineNo+1,branchLengthCheckMode);
                    instructionRetVal = aux;
                }
                break;

            case READ_TYPE:
                r1 = initialTempReg;
                if(!branchLengthCheckMode) {
                    fprintf(vm_code, "READ,%d\n", r1);
                    fprintf(vm_code, "SW,%d,%d\n", r1, getSymbolMemoryPosition(st->str_value));
                }
                instructionRetVal.destinationRegister = r1;
                instructionRetVal.lastLineOfCode = nextLineNo+1;

                if(st->nextStmt != NULL){
                    aux = generateCode(st->nextStmt,vm_code,initialTempReg,nextLineNo+2,branchLengthCheckMode);
                    instructionRetVal = aux;
                }
                break;

            case WRITE_TYPE:
                aux = generateCode(st->leftChild,vm_code,initialTempReg,nextLineNo,branchLengthCheckMode);
                nextLineNo = aux.lastLineOfCode + 1;
                r1 = aux.destinationRegister;
                if(!branchLengthCheckMode)
                    fprintf(vm_code,"WRITE,%d\n",r1);

                instructionRetVal.destinationRegister = initialTempReg;
                instructionRetVal.lastLineOfCode = nextLineNo;

                if(st->nextStmt != NULL){
                    aux = generateCode(st->nextStmt,vm_code,initialTempReg,nextLineNo+1,branchLengthCheckMode);
                    instructionRetVal = aux;
                }
                break;
            case ID_TYPE:
                r1 = initialTempReg;
                if(!branchLengthCheckMode)
                    fprintf(vm_code,"LW,%d,%d\n",r1,getSymbolMemoryPosition(st->str_value));
                instructionRetVal.destinationRegister = r1;
                instructionRetVal.lastLineOfCode = nextLineNo;
                break;

            case CONST_TYPE:
                r1 = initialTempReg;
                if(!branchLengthCheckMode)
                    fprintf(vm_code,"ADDI,%d,0,%d\n",r1,st->value);
                instructionRetVal.destinationRegister = r1;
                instructionRetVal.lastLineOfCode = nextLineNo;
                break;

            case OPERATION_TYPE:
                aux = generateCode(st->leftChild,vm_code,initialTempReg+1,nextLineNo,branchLengthCheckMode);
                r1 = aux.destinationRegister;
                nextLineNo = aux.lastLineOfCode + 1;
                aux = generateCode(st->centerChild,vm_code,initialTempReg+2,nextLineNo,branchLengthCheckMode);
                r2 = aux.destinationRegister;
                nextLineNo = aux.lastLineOfCode + 1;
                r3 = initialTempReg;

                if(!branchLengthCheckMode){
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

                instructionRetVal.destinationRegister = r3;
                instructionRetVal.lastLineOfCode = nextLineNo;

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