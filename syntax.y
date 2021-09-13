%{

	#include "node.h"
	#include "lista.h"
	#include <stdio.h>
	#include <string.h>
	#include "symbol_table.h"

	int yydebug=0;
	extern int yylex();
	extern Node * syntax_tree;
	struct node_tac * table_TAC = NULL;
	extern FILE* yyin;
	symbol_t symbol_table;
	int vars_size=0;
	int temps_size=0;
	int lex_size=0;
	int Temps = 0;
        int num_temp = 0;

	entry_t* create_new_symbol(char *lx, char *type){

        	entry_t* new_entry = (entry_t *) malloc(sizeof(entry_t));
        	new_entry->name = lx;
       		new_entry->desloc = vars_size;
        	new_entry->size = 4;
        	vars_size += 4;
       		return new_entry;

        }


	entry_t* checking_declaration_symbol(char* lx, char* type){

		if(lookup(symbol_table, lx)){

                	entry_t* aux = lookup(symbol_table,lx);
                        return aux;

		}else{

			return NULL;

		}

	}


	void insert_in_symbol_table(char* lx, char* type){

		if(insert(&symbol_table, create_new_symbol(lx, type)) != 0){

                	return;

                }


        }



%}

%union { char* cadeia; struct _node * no;}

%type<no> commands
%type<no> commandIf
%type<no> forExpression
%type<no> importExpression
%type<no> whileExpression
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
%type<no> cmd

%token WORD SEMICOLON OPENPARENTS CLOSEPARENTS OR AND NOT OPEN_BRACKETS CLOSE_BRACKETS
%token EQUAL NOT_EQUAL GREATER LESS GREATER_OR_EQUAL LESS_OR_EQUAL
%token IF FOR WHILE DO
%token SUM SUB MUL DIV MOD EXP ASSIGN
%token INT FLOAT CHAR BOOL DOUBLE
%token VALUE_INT VALUE_FLOAT VALUE_DOUBLE
%token IMPORT DEFINE
%token TRUE FALSE
%start cmd

%left VALUE_INT VALUE_FLOAT VALUE_DOUBLE
%left TRUE FALSE
%left EQUAL NOT_EQUAL GREATER LESS GREATER_OR_EQUAL LESS_OR_EQUAL
%left SUM SUB MUL DIV MOD EXP ASSIGN

%%

cmd: commands{

	//$$ = create_node(@1.first_line, 1, "command", $1, NULL);
	$$ = $1;
	syntax_tree = $$;
	print_tac((table_TAC), symbol_table );

	};


commands:

	importExpression commands {

		$$ = create_node(@1.first_line, 1, "import_expression", NULL);} |


	generalArithmeticExpression commands {

	 	$$ = create_node(@1.first_line, 1, "", NULL);



	}|


	commandIf commands {

		$$ = create_node(@1.first_line, 1, "command_if", $1, NULL);}|


	whileExpression commands {

		$$ = create_node(@1.first_line, 1, "while", $1, NULL);}|


	doWhileExpression commands {

                $$ = create_node(@1.first_line, 1, "do_while", $1, NULL);}|


	forExpression commands{

                $$ = create_node(@1.first_line, 1, "for", $1, NULL);}|

       	{}|

	defineExpression commands {

        		$$ = create_node(@1.first_line, 1, "define", $1, NULL);};


importExpression:

 	IMPORT variable SEMICOLON {

        	Node* a1  = create_node(@1.first_line, 1, ";", NULL);
        	$$  = create_node(@1.first_line, 1, "variable", $2, a1, NULL);};


commandIf:

	IF OPENPARENTS generalExpression CLOSEPARENTS OPEN_BRACKETS commands CLOSE_BRACKETS{

        	Node* a1  = create_node(@1.first_line, 0, "(", NULL);
        	Node* a2  = create_node(@1.first_line, 0, ")", NULL);
        	Node* a3  = create_node(@1.first_line, 0, "{", NULL);
        	Node* a4  = create_node(@1.first_line, 0, "}", NULL);
        	$$  = create_node(@1.first_line, 1, "command_if", a1, $3 ,a2, a3, $6 ,a4, NULL);};


defineExpression:

 	DEFINE assignmentExpression SEMICOLON {

        	Node* a1  = create_node(@1.first_line, 0, ";", NULL);
        	$$  = create_node(@1.first_line, 1, "define", $2, a1, NULL);};


forExpression:


	FOR OPENPARENTS generalArithmeticExpression comparisonExpression SEMICOLON assignmentExpression CLOSEPARENTS OPEN_BRACKETS commands CLOSE_BRACKETS  {

        	Node* a1  = create_node(@1.first_line, 0, "(", NULL);
        	Node* a2  = create_node(@1.first_line, 0, ";", NULL);
        	Node* a4  = create_node(@1.first_line, 0, ")", NULL);
        	Node* a5  = create_node(@1.first_line, 0, "{", NULL);
        	Node* a6  = create_node(@1.first_line, 0, "}", NULL);
        	$$  = create_node(@1.first_line, 1, "FOR", a1, $3 ,$4, a2, $6 , a4, a5, $9, a6, NULL);};


whileExpression:

	WHILE OPENPARENTS generalExpression CLOSEPARENTS OPEN_BRACKETS commands CLOSE_BRACKETS {

        	Node* a1  = create_node(@1.first_line, 0, "(", NULL);
        	Node* a2  = create_node(@1.first_line, 0, ")", NULL);
        	Node* a3  = create_node(@1.first_line, 0, "{", NULL);
        	Node* a4  = create_node(@1.first_line, 0, "}", NULL);
        	$$  = create_node(@1.first_line, 1, "WHILE", a1, $3, a2, a3, $6, a4, NULL);};


doWhileExpression:

 	DO OPEN_BRACKETS commands CLOSE_BRACKETS WHILE OPENPARENTS generalExpression CLOSEPARENTS SEMICOLON  {

        	Node* a1  = create_node(@1.first_line, 0, "{", NULL);
        	Node* a2  = create_node(@1.first_line, 0, "}", NULL);
        	Node* a3  = create_node(@1.first_line, 0, "WHILE", NULL);
        	Node* a4  = create_node(@1.first_line, 0, "(", NULL);
        	Node* a5  = create_node(@1.first_line, 0, ")", NULL);
        	Node* a6  = create_node(@1.first_line, 0, ";", NULL);
        	$$  = create_node(@1.first_line, 1, "DOWHILE", a1, $3, a2, a3, a4, $7, a5, a6, NULL);};


generalArithmeticExpression:

 	declarationExpression SEMICOLON {

        	Node* a1  = create_node(@1.first_line, 0, ";", NULL);
        	$$  = create_node(@1.first_line, 1, "general_arithmetic_expression", $1, a1, NULL);}|

       	assignmentExpression SEMICOLON{

        	Node* a1  = create_node(@1.first_line, 0, ";", NULL);
        	$$  = create_node(@1.first_line, 1, "general_arithmetic_expression", $1, a1, NULL);};


generalExpression:

 	boolExpression {

        	$$  = create_node(@1.first_line, 1, "general_expression", $1, NULL);}|

       	comparisonExpression{

        	$$  = create_node(@1.first_line, 1, "general_expression", $1, NULL);};


assignmentExpression:

    	variable {

		$$  = create_node(@1.first_line, 1, $1->lexeme, $1, NULL);}|

	variable ASSIGN arithmeticOperations {

        	Node* a1  = create_node(@1.first_line, 1, "variable", NULL);
        	Node* a2  = create_node(@1.first_line, 1, "assing", NULL);
        	$$  = create_node(@1.first_line, 1, $3->lexeme , $1,  a1, a2, $3, NULL);
        	char *temp=(char*)malloc(8*sizeof(char));
		sprintf(temp,"T%03d",Temps);
                struct tac* new_tac = create_inst_tac(temp, $1->lexeme, ":=", $3->lexeme);
                free(temp);
                num_temp ++;

                append_inst_tac(&(table_TAC), new_tac);
                Temps++;};


boolExpression:

 	boolExpression boolOperators boolExpression {

        	$$  = create_node(@1.first_line, 1, "bool_expression", $1, $2, $3, NULL);

        	        char *temp=(char*)malloc(8*sizeof(char));
                     	struct tac* new_tac = create_inst_tac(temp, $1->lexeme, $2->lexeme, $3->lexeme);
                       	printf("%s - %s - %s\n", $1->lexeme, $2->lexeme, $3->lexeme);
                       	free(temp);

                       	append_inst_tac(&(table_TAC),new_tac);

        	}|

	bool {

        	$$  = create_node(@1.first_line, 1, "bool", $1, NULL);}|

        boolOperators {

                $$  = create_node(@1.first_line, 1, "bool_expression", $1, NULL);};


comparisonExpression:

 	comparisonExpression comparisonOperators comparisonExpression{

        	$$  = create_node(@1.first_line, 1, "comparison_expression", $1, $2, $3, NULL);
        	char *temp=(char*)malloc(8*sizeof(char));
                struct tac* new_tac = create_inst_tac(temp, $1->lexeme, $2->lexeme, $3->lexeme);
                free(temp);
                num_temp ++;
               	append_inst_tac(&(table_TAC),new_tac);

        	}|

       	variable{

        	$$  = create_node(@1.first_line, 1, "variable", $1, NULL);}|

       	NOT variable{

        	Node* a1  = create_node(@1.first_line, 1, "NOT", NULL);
        	$$  = create_node(@1.first_line, 1, "boolExpression", a1, $2, NULL);};


arithmeticOperations:

 	arithmeticOperations arithmeticOperators arithmeticOperations{


		char *temp=(char*)malloc(8*sizeof(char));
		sprintf(temp,"T%03d",Temps);
        	$$  = create_node(@1.first_line, 1, temp, $1, $2, $3, NULL);
		char *lex=(char*)malloc(8*sizeof(char));
        	if(strstr($3->lexeme, ".") || strstr($1->lexeme, ".")){ sprintf(lex,"F%s",$2->lexeme);}else{sprintf(lex,"%s",$2->lexeme);}
               	struct tac* new_tac = create_inst_tac(temp, $1->lexeme, lex, $3->lexeme);
               	free(temp);
               	num_temp ++;
               	append_inst_tac(&(table_TAC), new_tac);}|

       	variable{

       		$$  = create_node(@1.first_line, 1, $1->lexeme, $1, NULL);

                        	if(checking_declaration_symbol($1->lexeme, $1->lexeme)==NULL){

                        		insert_in_symbol_table($1->lexeme, "var");

                        	}

       		}|

       	numbers{

       		$$  = $1;};


declarationExpression:

 	declarationTypes assignmentExpression {


        	$$  = create_node(@1.first_line, 1, $2->lexeme, $2, NULL);

		};


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

 		$$  = create_node(@1.first_line, 1, "SUM", NULL);}|

 	SUB{

 		$$  = create_node(@1.first_line, 1, "SUB", NULL);}|

 	MUL{

 		$$  = create_node(@1.first_line, 1, "MUL", NULL);}|

 	DIV{

 		$$  = create_node(@1.first_line, 1, "DIV", NULL);}|

 	MOD{

 		$$  = create_node(@1.first_line, 1, "MOD", NULL);}|

 	EXP{

 		$$  = create_node(@1.first_line, 1, "EXP", NULL);};


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

        	$$  = create_node(@1.first_line, 1, yylval.cadeia, NULL);};


numbers:


 	VALUE_INT {

		char sMensagem[100] = "S";
              	strcat(sMensagem, yylval.cadeia);
 		$$  = create_node(@1.first_line, 1, sMensagem, NULL);}|

	VALUE_FLOAT {

		char sMensagem[100] = "S";
                strcat(sMensagem, yylval.cadeia);

		$$  = create_node(@1.first_line, 1, sMensagem, NULL);}|

	VALUE_DOUBLE{

		char sMensagem[100] = "S";
               	strcat(sMensagem, yylval.cadeia);
                $$  = create_node(@1.first_line, 1, sMensagem, NULL);
	};


%%

void yyerror(const char *str){ fprintf(stderr, "error: %s\n", str);}
int yywrap(){ return 1;}

int main(int argc, char** argv){

       	//yyparse();
        //uncompile(syntax_tree);

        if (argc < 2) {
        		printf("uso: %s <input_file>. Try again!\n", argv[0]);
        		exit(-1);
        	}
        	yyin = fopen("test.t", "r");

        	if (!yyin) {
        		printf("Uso: %s <input_file>. Could not find %s. Try again!\n",
        				argv[0], argv[1]);
        		exit(-1);
        	}


        	int result = yyparse();
		uncompile(syntax_tree);


}
