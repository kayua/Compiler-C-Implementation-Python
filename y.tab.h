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
    WORD = 258,
    SEMICOLON = 259,
    OPENPARENTS = 260,
    CLOSEPARENTS = 261,
    OR = 262,
    AND = 263,
    NOT = 264,
    OPEN_BRACKETS = 265,
    CLOSE_BRACKETS = 266,
    EQUAL = 267,
    NOT_EQUAL = 268,
    GREATER = 269,
    LESS = 270,
    GREATER_OR_EQUAL = 271,
    LESS_OR_EQUAL = 272,
    IF = 273,
    FOR = 274,
    WHILE = 275,
    DO = 276,
    SUM = 277,
    SUB = 278,
    MUL = 279,
    DIV = 280,
    MOD = 281,
    EXP = 282,
    ASSIGN = 283,
    INT = 284,
    FLOAT = 285,
    CHAR = 286,
    BOOL = 287,
    DOUBLE = 288,
    IMPORT = 289,
    DEFINE = 290,
    VALUE_INT = 291,
    TRY = 292,
    CATCH = 293,
    EXCEPT = 294,
    TRUE = 295,
    FALSE = 296
  };
#endif
/* Tokens.  */
#define WORD 258
#define SEMICOLON 259
#define OPENPARENTS 260
#define CLOSEPARENTS 261
#define OR 262
#define AND 263
#define NOT 264
#define OPEN_BRACKETS 265
#define CLOSE_BRACKETS 266
#define EQUAL 267
#define NOT_EQUAL 268
#define GREATER 269
#define LESS 270
#define GREATER_OR_EQUAL 271
#define LESS_OR_EQUAL 272
#define IF 273
#define FOR 274
#define WHILE 275
#define DO 276
#define SUM 277
#define SUB 278
#define MUL 279
#define DIV 280
#define MOD 281
#define EXP 282
#define ASSIGN 283
#define INT 284
#define FLOAT 285
#define CHAR 286
#define BOOL 287
#define DOUBLE 288
#define IMPORT 289
#define DEFINE 290
#define VALUE_INT 291
#define TRY 292
#define CATCH 293
#define EXCEPT 294
#define TRUE 295
#define FALSE 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 12 "syntax.y"
 char* cadeia; struct _node * no;

#line 142 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
