%{
#include "../Syntax_Tree/syntax_tree.h"  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexical_analyzer.h"
#define YYSTYPE YYSTYPE
typedef SyntaxTree *YYSTYPE;

static char var_name[TOKENLENGTH];
static int curLineNo;
int yyerror(char *errmsg);
static SyntaxTree * syntaxTree;
static int yylex(void);
%}

%start program

%token IF THEN ELSE REPEAT UNTIL READ WRITE END
%token PLUS SUB MULT DIV EQUAL LESST MORET EQMORET EQLESST SEMIC LPAREN RPAREN
%token ID NUM ASSIGN 
%token ERROR

%%
program : stmt_seq
          {syntaxTree = $1;}
          ;

stmt_seq : stmt_seq stmt
           { 
             SyntaxTree * temp = $1;
             if(temp != NULL){ 
               while (temp->nextStmt != NULL){
                 temp = temp->nextStmt;
               }
             temp->nextStmt = $2;
             $$ = $1; 
             }
             else {
              $$ = $2;
             }
           }
           | stmt
           { 
             $$ = $1;
           }
           ;

stmt : if_stmt { $$ = $1;  }
       | repeat_stmt SEMIC{ $$ = $1; }
       | assign_stmt SEMIC{ $$ = $1; }
       | read_stmt SEMIC{ $$ = $1; }
       | write_stmt SEMIC{ $$ = $1; }
       ;

if_stmt : IF exp THEN stmt_seq END
          { $$ = create_node(IF_TYPE);
            $$->leftChild = $2;
            $$->centerChild = $4;
          }
          | IF exp THEN stmt_seq ELSE stmt_seq END
          { 
            $$ = create_node(IF_TYPE);
            $$->leftChild = $2;
            $$->centerChild = $4;
            $$->rightChild = $6;
          }
          ;

repeat_stmt : REPEAT stmt_seq UNTIL exp
              { $$ = create_node(REPEAT_TYPE);
                $$->leftChild = $2;
                $$->centerChild = $4;
                $$->lineNo = lineNo;
              }
              ;

assign_stmt : ID
	      {
                strncpy(var_name, token_str,TOKENLENGTH);
                curLineNo = lineNo;}
	      ASSIGN exp
              { $$ = create_node(ASSIGN_TYPE);
              	strncpy($$->str_value, var_name,TOKENLENGTH);
                $$->leftChild = $4;
                $$->lineNo = curLineNo;
              }

read_stmt : READ ID
            { $$ = create_node(READ_TYPE);
              $$->lineNo = lineNo;
              strncpy($$->str_value, token_str,TOKENLENGTH);
            }
            ;

write_stmt : WRITE exp
             { $$ = create_node(WRITE_TYPE);
               $$->lineNo = lineNo;
               $$->leftChild = $2;
             }
             ;

exp : simple_exp LESST simple_exp
      { 
        $$ = create_node(OPERATION_TYPE);
        $$->leftChild = $1;
        $$->centerChild = $3;
        $$->opType = LESST_OP;
        $$->lineNo = lineNo;
      }
      | simple_exp MORET simple_exp
      { 
        $$ = create_node(OPERATION_TYPE);
        $$->leftChild = $1;
        $$->centerChild = $3;
        $$->opType = MORET_OP;
        $$->lineNo = lineNo;
      }
      | simple_exp EQUAL simple_exp
      { 
        $$ = create_node(OPERATION_TYPE);
        $$->leftChild = $1;
        $$->centerChild = $3;
        $$->opType = EQUAL_OP;
        $$->lineNo = lineNo;
      }
      | simple_exp EQLESST simple_exp
      { 
        $$ = create_node(OPERATION_TYPE);
        $$->leftChild = $1;
        $$->centerChild = $3;
        $$->opType = EQLESST_OP;
        $$->lineNo = lineNo;
      }
      | simple_exp EQMORET simple_exp
      { 
        $$ = create_node(OPERATION_TYPE);
        $$->leftChild = $1;
        $$->centerChild = $3;
        $$->opType = EQMORET_OP;
        $$->lineNo = lineNo;
      }
      | simple_exp
      { 
        $$ = $1;
      }
      ;

simple_exp : simple_exp PLUS term
      { $$ = create_node(OPERATION_TYPE);
        $$->leftChild = $1;
        $$->centerChild = $3;
        $$->opType = PLUS_OP;
        $$->lineNo = lineNo;
      }
      | simple_exp SUB term
      {
        $$ = create_node(OPERATION_TYPE);
        $$->leftChild = $1;
        $$->centerChild = $3;
        $$->opType = SUB_OP;
        $$->lineNo = lineNo;
      }
      | term { $$ = $1; }
      ;

term : term MULT factor
       { $$ = create_node(OPERATION_TYPE);
         $$->leftChild = $1;
         $$->centerChild = $3;
         $$->opType = MULT_OP;
         $$->lineNo = lineNo;
       }
       | term DIV factor
       { $$ = create_node(OPERATION_TYPE);
         $$->leftChild = $1;
         $$->centerChild = $3;
         $$->opType = DIV_OP;
         $$->lineNo = lineNo;
       }
      | factor { $$ = $1; }
      ;

factor : LPAREN exp RPAREN
         { $$ = $2; }
         | NUM
         { $$ = create_node(CONST_TYPE);
           $$->value = atoi(token_str);
         }
         | ID
         { $$ = create_node(ID_TYPE);
           strncpy($$->str_value, token_str,TOKENLENGTH);
           $$->lineNo = lineNo;
         }
         | error 
         {
           $$ = NULL;
         }
         ;
%%

int yyerror(char *errmsg){
  printf("\nSyntax error at line: %d", lineNo);
  if(strlen(token_str)!=0)
    printf(", unexpected token:%s\n", token_str);
  else 
    printf("\n");
  exit(EXIT_FAILURE);
  return -1;
}

static int yylex(void){
  return getToken();
}

SyntaxTree * parseAndGetSyntaxTree(){
  yyparse();
  return syntaxTree;
}