%{
#define YYSTYPE char *

#include <stdio.h>
#include "y.tab.h"
#include "node.h"
%}

%%
"if"                    return IF;
"("                     return OPENPARENTS;
")"                     return CLOSEPARENTS;
"{"                     return OPEN_BRACKETS;
"}"                     return CLOSE_BRACKETS;
";"                     return SEMICOLON;
"import"                return IMPORT;
"for"                   return FOR;
"while"                 return WHILE;
"define"                return DEFINE;
"do"                    return DO;
"try"                   return TRY;
"catch"                 return CATCH;
"except"                return EXCEPT;
"and"                   return AND;
"or"                    return OR;
"not"                   return NOT;
"=="                    return EQUAL;
"!="                    return NOT_EQUAL;
">"                     return GREATER;
"<"                     return LESS;
">="                    return GREATER_OR_EQUAL;
"<="                    return LESS_OR_EQUAL;
"+"                     return SUM;
"-"                     return SUB;
"*"                     return MUL;
"/"                     return DIV;
"%"                     return MOD;
"**"                    return EXP;
"="                     return ASSIGN;
"int"                   return INT;
"float"                 return FLOAT;
"char"                  return CHAR;
"bool"                  return BOOL;
"double"                return DOUBLE;
"true"                  return TRUE;
"false"                 return FALSE;
[0-9]*                  return VALUE_INT;
[a-zA-Z][a-zA-Z]*    yylval=strdup(yytext); return WORD;
\n;
[ \t]+;
%%
