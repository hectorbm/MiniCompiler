#include <stdlib.h>
/*
 * Types of statement
 * */

typedef enum{
    IF_TYPE,
    REPEAT_TYPE,
    ASSIGN_TYPE,
    READ_TYPE,
    WRITE_TYPE,
    ID_TYPE,
    CONST_TYPE,
    OPERATION_TYPE
} NodeType;

typedef enum{
    PLUS_OP,
    SUB_OP,
    MULT_OP,
    DIV_OP,
    EQUAL_OP,
    LESST_OP,
    MORET_OP,
    EQMORET_OP,
    EQLESST_OP
}OperationType;

/*
 * Struct for the Syntax_Tree
 * */
typedef struct st_node{
    NodeType nodeType;

    char * str_value;
    int value;
    OperationType opType;
    int lineNo;

    struct st_node *nextStmt;
    struct st_node *leftChild;
    struct st_node *centerChild;
    struct st_node *rightChild;
}SyntaxTree;

SyntaxTree * create_node(NodeType nodetype);

void showSyntaxTree(SyntaxTree * syntaxtree, int ident_num);

SyntaxTree * parseAndGetSyntaxTree();

