%{
#include "node.h"
#include <stdio.h>
#include <string.h>
int yydebug=0;
extern int yylex();
extern Node * syntax_tree;
extern FILE* yyin;

%}

%union { char* cadeia; struct _node * no;}

%type<no> commands
%type<no> commandIf
%type<no> forExpression
%type<no> importExpression
%type<no> whileExpression
%type<no> exceptExpression
%type<no> doWhileExpression
%type<no> generalArithmeticExpression
%type<no> defineExpression
%type<no> declarationExpression
%type<no> assignmentExpression
%type<no> generalExpression
%type<no> boolExpression
%type<no> comparisonExpression
%type<no> arithmeticOperations
%type<no> comparisonOperators
%type<no> arithmeticOperators
%type<no> boolOperators
%type<no> declarationTypes
%type<no> variable
%type<no> numbers
%type<no> bool

%token WORD SEMICOLON OPENPARENTS CLOSEPARENTS OR AND NOT OPEN_BRACKETS CLOSE_BRACKETS
%token EQUAL NOT_EQUAL GREATER LESS GREATER_OR_EQUAL LESS_OR_EQUAL
%token IF FOR WHILE DO
%token SUM SUB MUL DIV MOD EXP ASSIGN
%token INT FLOAT CHAR BOOL DOUBLE
%token VALUE_INT VALUE_FLOAT VALUE_DOUBLE
%token IMPORT DEFINE
%token TRUE FALSE
%start commands

%left VALUE_INT VALUE_FLOAT VALUE_DOUBLE
%left TRUE FALSE
%left EQUAL NOT_EQUAL GREATER LESS GREATER_OR_EQUAL LESS_OR_EQUAL
%left SUM SUB MUL DIV MOD EXP ASSIGN

%%


commands:

	importExpression {

		$$ = create_node(@1.first_line, 1, "import_expression", NULL); syntax_tree = $$;} |


	generalArithmeticExpression {

	 	$$ = create_node(@1.first_line, 1, "arithmetic_expression", NULL);  syntax_tree = $$;}|


	commandIf {

		$$ = create_node(@1.first_line, 1, "command_if", $1);  syntax_tree = $$;}|


	whileExpression {

		$$ = create_node(@1.first_line, 1, "while", $1);  syntax_tree = $$;}|


	doWhileExpression {

                $$ = create_node(@1.first_line, 1, "do_while", $1);  syntax_tree = $$;}|


	forExpression {

                $$ = create_node(@1.first_line, 1, "for", $1);  syntax_tree = $$;}|


	defineExpression {

        		$$ = create_node(@1.first_line, 1, "define", $1);  syntax_tree = $$;};


importExpression:

 	IMPORT variable SEMICOLON {

        	Node* a1  = create_node(@1.first_line, 1, ";", NULL);
        	$$  = create_node(@1.first_line, 1, "variable", $2, a1);};

commandIf:

	IF OPENPARENTS generalExpression CLOSEPARENTS OPEN_BRACKETS commands CLOSE_BRACKETS{

        	Node* a1  = create_node(@1.first_line, NULL, "(", NULL);
        	Node* a2  = create_node(@1.first_line, NULL, ")", NULL);
        	Node* a3  = create_node(@1.first_line, NULL, "{", NULL);
        	Node* a4  = create_node(@1.first_line, NULL, "}", NULL);
        	$$  = create_node(@1.first_line, 1, "command_if", a1, $3 ,a2, a3, $6 ,a4);};


defineExpression:

 	DEFINE assignmentExpression SEMICOLON {

        	Node* a1  = create_node(@1.first_line, NULL, ";", NULL);
        	$$  = create_node(@1.first_line, 1, "define", $2, a1);};


forExpression:


	FOR OPENPARENTS generalArithmeticExpression comparisonExpression SEMICOLON assignmentExpression CLOSEPARENTS OPEN_BRACKETS commands CLOSE_BRACKETS  {

        	Node* a1  = create_node(@1.first_line, NULL, "(", NULL);
        	Node* a2  = create_node(@1.first_line, NULL, ";", NULL);
        	Node* a4  = create_node(@1.first_line, NULL, ")", NULL);
        	Node* a5  = create_node(@1.first_line, NULL, "{", NULL);
        	Node* a6  = create_node(@1.first_line, NULL, "}", NULL);
        	$$  = create_node(@1.first_line, 1, "FOR", a1, $3 ,$4, a2, $6 , a4, a5, $9, a6);};


whileExpression:

	WHILE OPENPARENTS generalExpression CLOSEPARENTS OPEN_BRACKETS commands CLOSE_BRACKETS {

        	Node* a1  = create_node(@1.first_line, NULL, "(", NULL);
        	Node* a2  = create_node(@1.first_line, NULL, ")", NULL);
        	Node* a3  = create_node(@1.first_line, NULL, "{", NULL);
        	Node* a4  = create_node(@1.first_line, NULL, "}", NULL);
        	$$  = create_node(@1.first_line, 1, "WHILE", a1, $3, a2, a3, $6, a4);};


doWhileExpression:

 	DO OPEN_BRACKETS commands CLOSE_BRACKETS WHILE OPENPARENTS generalExpression CLOSEPARENTS SEMICOLON  {

        	Node* a1  = create_node(@1.first_line, NULL, "{", NULL);
        	Node* a2  = create_node(@1.first_line, NULL, "}", NULL);
        	Node* a3  = create_node(@1.first_line, NULL, "WHILE", NULL);
        	Node* a4  = create_node(@1.first_line, NULL, "(", NULL);
        	Node* a5  = create_node(@1.first_line, NULL, ")", NULL);
        	Node* a6  = create_node(@1.first_line, NULL, ";", NULL);
        	$$  = create_node(@1.first_line, 1, "DOWHILE", a1, $3, a2, a3, a4, $7, a5, a6);};


generalArithmeticExpression:

 	declarationExpression SEMICOLON {

        	Node* a1  = create_node(@1.first_line, NULL, ";", NULL);
        	$$  = create_node(@1.first_line, 1, "general_arithmetic_expression", $1, a1);}|

       	assignmentExpression SEMICOLON{

        	Node* a1  = create_node(@1.first_line, NULL, ";", NULL);
        	$$  = create_node(@1.first_line, 1, "general_arithmetic_expression", $1, a1);};


generalExpression:

 	boolExpression {

        	$$  = create_node(@1.first_line, 1, "general_expression", $1);}|

       	comparisonExpression{

        	$$  = create_node(@1.first_line, 1, "general_expression", $1);};


assignmentExpression:

    	variable {

		$$  = create_node(@1.first_line, 1, "assignment_expression", $1); }|

	variable ASSIGN arithmeticOperations {

        	Node* a1  = create_node(@1.first_line, 1, "variable", NULL);
        	Node* a2  = create_node(@1.first_line, 1, "assing", NULL);
        	$$  = create_node(@1.first_line, 1, "assignment_expression", $1,  a1, a2, $3);};


boolExpression:

 	boolExpression boolOperators boolExpression {

        	$$  = create_node(@1.first_line, 1, "bool_expression", $1, $2, $3);}|

	bool {

        	$$  = create_node(@1.first_line, 1, "bool", $1);}|

        boolOperators {

                $$  = create_node(@1.first_line, 1, "bool_expression", $1);};


comparisonExpression:

 	comparisonExpression comparisonOperators comparisonExpression{

        	$$  = create_node(@1.first_line, 1, "comparison_expression", $1, $2, $3);}|

       	variable{

        	$$  = create_node(@1.first_line, 1, "variable", $1);}|

       	NOT variable{

        	Node* a1  = create_node(@1.first_line, 1, "NOT", NULL);
        	$$  = create_node(@1.first_line, 1, "boolExpression", a1, $2);};


arithmeticOperations:

 	arithmeticOperations arithmeticOperators arithmeticOperations{

        	$$  = create_node(@1.first_line, 1, "arithmetic_operations", $1, $2, $3);}|

       	variable{

       		$$  = create_node(@1.first_line, 1, "arithmetic_operations", $1);}|

       	numbers{

       		$$  = create_node(@1.first_line, 1, "numbers", $1);};


declarationExpression:

 	declarationTypes assignmentExpression {

        	$$  = create_node(@1.first_line, 1, "declaration_expression", $1, $2);};


comparisonOperators:

 	EQUAL {

 		$$  = create_node(@1.first_line, 1, "equal_operator", NULL);}|

 	NOT_EQUAL{

        	$$  = create_node(@1.first_line, 1, "not_equal_operator", NULL);}|

       	GREATER{

        	$$  = create_node(@1.first_line, 1, "greater_operator", NULL);}|

       	LESS{

        	$$  = create_node(@1.first_line, 1, "less_operator", NULL);}|

       	GREATER_OR_EQUAL{

        	$$  = create_node(@1.first_line, 1, "greater_or_equal_operator", NULL);}|

       	LESS_OR_EQUAL{

        	$$  = create_node(@1.first_line, 1, "less_or_equal_operator", NULL);};


arithmeticOperators:

 	SUM{

 		$$  = create_node(@1.first_line, 1, "sum_operation", NULL);}|

 	SUB{

 		$$  = create_node(@1.first_line, 1, "sub_operation", NULL);}|

 	MUL{

 		$$  = create_node(@1.first_line, 1, "mul_operation", NULL);}|

 	DIV{

 		$$  = create_node(@1.first_line, 1, "div_operation", NULL);}|

 	MOD{

 		$$  = create_node(@1.first_line, 1, "mod_operation", NULL);}|

 	EXP{

 		$$  = create_node(@1.first_line, 1, "exp_operation", NULL);};


declarationTypes:

 	INT {

 		$$  = create_node(@1.first_line, 1, "int_type", NULL);}|

 	FLOAT{

 		$$  = create_node(@1.first_line, 1, "float_type", NULL);}|

 	CHAR{

 		$$  = create_node(@1.first_line, 1, "char_type", NULL);}|

 	BOOL{

 		$$  = create_node(@1.first_line, 1, "bool_type", NULL);}|

 	DOUBLE{

 		$$  = create_node(@1.first_line, 1, "double_type", NULL);};


boolOperators:

 	AND {

 		$$  = create_node(@1.first_line, 1, "and_operator", NULL);}|

 	OR{

 		$$  = create_node(@1.first_line, 1, "or_operator", NULL);};


bool:

 	TRUE {

 		$$  = create_node(@1.first_line, 1, "true", NULL);}|

 	FALSE{

 		$$  = create_node(@1.first_line, 1, "false", NULL);};


variable:

	WORD {

        	$$  = create_node(@1.first_line, 1, "variable", NULL);};


numbers:

 	VALUE_INT {

 		$$  = create_node(@1.first_line, 1, "int", NULL);}|

	VALUE_FLOAT {

		$$  = create_node(@1.first_line, 1, "float", NULL);}|

	VALUE_DOUBLE{

                $$  = create_node(@1.first_line, 1, "float", NULL);
	};


%%

void yyerror(const char *str){ fprintf(stderr, "error: %s\n", str);}
int yywrap(){ return 1;}

int main(int argc, char** argv){

       	yyparse();
        uncompile(syntax_tree);
}
