/*Lexical analyzer*/
%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
#include "lexical_analyzer.h"
%}
%option noyywrap
digit   [0-9]
letter  [a-zA-Z]
number {digit}+
identifier {letter}+
newline \n
whitespace [\t ]+


%%
if {return IF;}
then {return THEN;}
else {return ELSE;}
repeat {return REPEAT;}
until {return UNTIL;}
read {return READ;}
write {return WRITE;}
end {return END;}
"+" {return PLUS;}
"-" {return SUB;}
"*" {return MULT;}
"/" {return DIV;}
"=" {return EQUAL;}
":=" {return ASSIGN;}
"<" {return LESST;}
">" {return MORET;}
">=" {return EQMORET;}
"<=" {return EQLESST;}
";" {return SEMIC;}
"(" {return LPAREN;}
")" {return RPAREN;}
{number} {return NUM;}
{identifier} {return ID;}
{newline} {lineNo++;}
{whitespace} {/*Skip whitespace*/}
"{" { char c;
      do{
            c = input();
            if (c=='\n') {
                  lineNo++;
            }
      }while(c!='}' && c!=0);
      if (c==0){
            return ERROR;
      }
      }

%%

void printToken(int aToken){
      switch(aToken){
            // Reserved words
            case IF:
            case ELSE:
            case THEN:
            case REPEAT:
            case UNTIL:
            case READ:
            case WRITE:     
            case END:
                  printf("Line:%d ,Reserved word:%s\n", lineNo, token_str);
                  break;

            // Number or variable identifier
            case NUM: 
                  printf("Line:%d ,Number:%s\n", lineNo, token_str);
                  break;
            case ID:
                  printf("Line:%d ,Identifier:\'%s\'\n", lineNo, token_str);
                  break;

            // Special symbols 
            case PLUS:
            case SUB:
            case MULT:
            case DIV:
            case EQUAL:
            case EQLESST:
            case EQMORET:
            case ASSIGN:
            case LESST:
            case MORET:
            case SEMIC:
            case RPAREN:
            case LPAREN:
                  printf("Line:%d ,symbol:\'%s\'\n", lineNo, token_str);
                  break;
      }

}

int getToken(){
      static int firstLine = 1;
      if (firstLine){
        firstLine = 0;
        lineNo = 1;
      }
      int aToken;
      aToken = yylex();
      strncpy(token_str, yytext,TOKENLENGTH);
      printToken(aToken);
      return aToken;
}