#include "node.h"
#include "lista.h"
#include <stdio.h>
#include <string.h>
#include "symbol_table.h"

// Global variables and externs for Bison and Flex integration
int yydebug = 0;
extern int yylex();
extern Node *syntax_tree;
struct node_tac *table_TAC = NULL;
extern FILE* yyin;
symbol_t symbol_table;
int vars_size = 0;   // Tracks the size of the allocated variables
int temps_size = 0;  // Tracks the size of temporary variables
int lex_size = 0;    // Tracks the size of lexical elements
int Temps = 0;       // Counter for temporary variables
int num_temp = 0;    // Number of temporary variables generated

/**
 * Function to create a new symbol in the symbol table.
 * It allocates memory for a new symbol, assigns its name, and allocates space for it.
 *
 * @param lx The name of the symbol.
 * @param type The type of the symbol.
 * @return Pointer to the created entry.
 */
entry_t* create_new_symbol(char *lx, char *type) {
    entry_t* new_entry = (entry_t *) malloc(sizeof(entry_t));
    new_entry->name = lx;
    new_entry->desloc = vars_size;
    new_entry->size = 4;  // Assume all variables are 4 bytes for simplicity
    vars_size += 4;  // Increment the total variable size
    return new_entry;
}

/**
 * Function to check if a symbol has been declared.
 * If the symbol exists in the symbol table, it is returned. Otherwise, NULL is returned.
 *
 * @param lx The name of the symbol.
 * @param type The type of the symbol.
 * @return Pointer to the symbol entry if it exists, NULL otherwise.
 */
entry_t* checking_declaration_symbol(char* lx, char* type) {
    if (lookup(symbol_table, lx)) {
        entry_t* aux = lookup(symbol_table, lx);
        return aux;
    } else {
        return NULL;
    }
}

/**
 * Function to insert a new symbol into the symbol table.
 * It first creates the symbol and then inserts it into the table.
 *
 * @param lx The name of the symbol.
 * @param type The type of the symbol.
 */
void insert_in_symbol_table(char* lx, char* type) {
    if (insert(&symbol_table, create_new_symbol(lx, type)) != 0) {
        return;  // Insertion failed, possibly a duplicate symbol
    }
}

// The following Bison/Yacc rules define the grammar for parsing various expressions
%union { char* cadeia; struct _node *no;}

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

/* Start of Bison/Yacc grammar rules. The `cmd` rule is the entry point for the parser. */
cmd: commands {
    $$ = $1;
    syntax_tree = $$;
    print_tac((table_TAC), symbol_table);  // Print the Three-Address Code (TAC) after parsing
};

/* Recursive parsing of commands. */
commands:
    importExpression commands {
        $$ = create_node(@1.first_line, 1, "import_expression", NULL);
    } |
    generalArithmeticExpression commands {
        $$ = create_node(@1.first_line, 1, "", NULL);
    } |
    commandIf commands {
        $$ = create_node(@1.first_line, 1, "command_if", $1, NULL);
    } |
    whileExpression commands {
        $$ = create_node(@1.first_line, 1, "while", $1, NULL);
    } |
    doWhileExpression commands {
        $$ = create_node(@1.first_line, 1, "do_while", $1, NULL);
    } |
    forExpression commands {
        $$ = create_node(@1.first_line, 1, "for", $1, NULL);
    } |
    {} |  // Empty production to allow ending of recursive commands
    defineExpression commands {
        $$ = create_node(@1.first_line, 1, "define", $1, NULL);
    };

// Rule for handling import expressions
importExpression:
    IMPORT variable SEMICOLON {
        Node* a1 = create_node(@1.first_line, 1, ";", NULL);
        $$ = create_node(@1.first_line, 1, "variable", $2, a1, NULL);
    };

// Rule for handling 'if' statements
commandIf:
    IF OPENPARENTS generalExpression CLOSEPARENTS OPEN_BRACKETS commands CLOSE_BRACKETS {
        Node* a1 = create_node(@1.first_line, 0, "(", NULL);
        Node* a2 = create_node(@1.first_line, 0, ")", NULL);
        Node* a3 = create_node(@1.first_line, 0, "{", NULL);
        Node* a4 = create_node(@1.first_line, 0, "}", NULL);
        $$ = create_node(@1.first_line, 1, "command_if", a1, $3, a2, a3, $6, a4, NULL);
    };

// Rule for handling variable definitions
defineExpression:
    DEFINE assignmentExpression SEMICOLON {
        Node* a1 = create_node(@1.first_line, 0, ";", NULL);
        $$ = create_node(@1.first_line, 1, "define", $2, a1, NULL);
    };

// Additional rules for loops, expressions, and assignments follow the same pattern.
