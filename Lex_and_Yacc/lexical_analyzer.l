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
whitespace [\t]+

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
{newline} {/*Skip newline*/}
{whitespace} {/*Skip whitespace*/}
"{" { char c;
      do{
      c = input();
      if(c==EOF) break;
      }while(c!='}');
      }

%%

int getToken(){
      int aToken;
      aToken = yylex();
      strncpy(token_str, yytext,TOKENLENGTH);
      return aToken;
}