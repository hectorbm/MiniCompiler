/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    THEN = 259,
    ELSE = 260,
    REPEAT = 261,
    UNTIL = 262,
    READ = 263,
    WRITE = 264,
    END = 265,
    PLUS = 266,
    SUB = 267,
    MULT = 268,
    DIV = 269,
    EQUAL = 270,
    LESST = 271,
    MORET = 272,
    EQMORET = 273,
    EQLESST = 274,
    SEMIC = 275,
    LPAREN = 276,
    RPAREN = 277,
    ID = 278,
    NUM = 279,
    ASSIGN = 280
  };
#endif
/* Tokens.  */
#define IF 258
#define THEN 259
#define ELSE 260
#define REPEAT 261
#define UNTIL 262
#define READ 263
#define WRITE 264
#define END 265
#define PLUS 266
#define SUB 267
#define MULT 268
#define DIV 269
#define EQUAL 270
#define LESST 271
#define MORET 272
#define EQMORET 273
#define EQLESST 274
#define SEMIC 275
#define LPAREN 276
#define RPAREN 277
#define ID 278
#define NUM 279
#define ASSIGN 280

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 12 "syntax_analyzer.y"
struct st_node * syntax_tree;

#line 110 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
