#include "syntax_tree.h"
#include "../Lex_and_Yacc/lexical_analyzer.h"
#include <stdio.h>
#include <string.h>

void showSyntaxTree(SyntaxTree * syntaxtree, int ident_num){
    SyntaxTree * temp = syntaxtree;
    int i = ident_num;
    while(i>0){
        printf("  ");
        i--;
    }
    if(temp != NULL){
        if(temp->nodeType == IF_TYPE){
            printf("IF\n");
        }
        else if(temp->nodeType == REPEAT_TYPE){
            printf("REPEAT\n");
        }    
        else if(temp->nodeType == ASSIGN_TYPE){
            printf("ASSIGN: %s\n", temp->str_value);
        }
        else if(temp->nodeType == READ_TYPE){
            printf("READ:%s\n",temp->str_value);
        }
        else if(temp->nodeType == WRITE_TYPE){
            printf("WRITE:\n");
        }
        else if(temp->nodeType == ID_TYPE){
            printf("ID:%s\n",temp->str_value);
        }
        else if(temp->nodeType == CONST_TYPE){
            printf("CONST: %d\n",temp->value);
        }
        else{
            printf("OPERATION: ");
            switch (temp->opType) {
                case PLUS_OP:
                    printf("+\n");
                    break;
                case SUB_OP:
                    printf("-\n");
                    break;
                case MULT_OP:
                    printf("*\n");
                    break;
                case DIV_OP:
                    printf("/\n");
                    break;
                case EQUAL_OP:
                    printf("=\n");
                    break;
                case LESST_OP:
                    printf("<\n");
                    break;
                case MORET_OP:
                    printf(">\n");
                    break;
                case EQMORET_OP:
                    printf(">=\n");
                    break;
                case EQLESST_OP:
                    printf("<=\n");
                    break;
            }
        }
        if(temp->leftChild != NULL){
            i = ident_num;
            while(i>0){
                printf("  ");
                i--;
            }
            printf("LC:\n");
            showSyntaxTree(temp->leftChild,ident_num+1);
        }
        if(temp->centerChild != NULL){
            i = ident_num;
            while(i>0){
                printf("  ");
                i--;
            }
            printf("CC:\n");
            showSyntaxTree(temp->centerChild,ident_num+1);
        }
        if(temp->rightChild != NULL){
            i = ident_num;
            while(i>0){
                printf("  ");
                i--;
            }
            printf("RC:\n");
            showSyntaxTree(temp->rightChild,ident_num+1);
        }
        if(temp->nextStmt !=NULL){
            i = ident_num;
            while(i>0){
                printf("  ");
                i--;
            }
            printf("NEXT STMT:\n");
            showSyntaxTree(temp->nextStmt,ident_num);
        }

    }
}

SyntaxTree * create_node(NodeType nodetype){
    SyntaxTree * node = (SyntaxTree *) malloc(sizeof(SyntaxTree));
    node->nextStmt = NULL;
    node->leftChild = NULL;
    node->centerChild = NULL;
    node->rightChild = NULL;
    node->nodeType = nodetype;
    node->str_value = (char *) malloc(TOKENLENGTH*sizeof(char));
    return node;
}