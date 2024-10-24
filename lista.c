#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "lista.h"

// Global variable to keep track of the list count
int numList = 1;

// Define the head of the TAC (Three-Address Code) instruction list
struct node_tac *lista = NULL;

// Another global variable for the TAC table
struct node_tac *table_TAC;

/**
 * Function to create a new TAC instruction
 * 
 * @param res The result of the operation
 * @param arg1 The first argument of the operation
 * @param op The operator of the operation
 * @param arg2 The second argument of the operation
 * 
 * @return A pointer to the newly created TAC structure
 */
struct tac* create_inst_tac(const char* res, const char* arg1, const char* op, const char* arg2) {
    // Allocate memory for the new TAC instruction
    struct tac *new = (struct tac*)malloc(sizeof(struct tac));

    // Allocate memory for the result, arguments, and operator
    new->res = malloc(sizeof(res));
    new->arg1 = malloc(sizeof(arg1));
    new->op = malloc(sizeof(op));
    new->arg2 = malloc(sizeof(arg2));

    // If memory allocation fails, exit the program
    if (new == NULL) {
        exit(0);
    }

    // Copy the content of res, arg1, arg2, and op to the new TAC structure if not NULL
    if (res != NULL) strcpy(new->res, res);
    if (arg1 != NULL) strcpy(new->arg1, arg1);
    if (arg2 != NULL) strcpy(new->arg2, arg2);
    if (op != NULL) strcpy(new->op, op);

    return new;
}

/**
 * Function to print a TAC instruction.
 * 
 * @param out File output stream
 * @param i TAC instruction to be printed
 */
void print_inst_tac(FILE* out, struct tac i) {
    printf("\n"); // Currently does nothing, could be implemented for debugging.
}

/**
 * Function to print the entire TAC code in a human-readable format.
 * 
 * @param code The TAC code represented as a linked list
 * @param table A symbol table that helps in looking up symbol details
 */
void print_tac(struct node_tac *code, symbol_t table) {
    int digito = 0; // Unused variable
    struct node_tac *aux2 = code; // Pointer to iterate through the TAC linked list
    struct tac *i; // Temporary pointer to store TAC instructions
    int l = 0; // Counter for instruction numbering
    char str[5]; // String buffer for numbering the instructions
    char str_at[100], str_at2[100]; // Buffers for storing adjusted strings

    while (aux2 != NULL) {
        // Format the instruction number as a 3-digit number
        sprintf(str, "%03d", l);
        i = aux2->inst; // Retrieve the current TAC instruction
        entry_t *aux_p = lookup(table, i->arg1); // Lookup symbol table for arg1
        entry_t *aux_p2 = lookup(table, i->arg2); // Lookup symbol table for arg2

        // Case: Both arguments are not symbols ('S') or temporaries ('T')
        if (i->arg1[0] != 'S' && i->arg2[0] != 'S' && i->arg1[0] != 'T' && i->arg2[0] != 'T') {
            str_at2[0] = '\n';
            strcpy(str_at2, i->res);
            memmove(&str_at2[0], &str_at2[1], strlen(str_at2) - 0); // Adjust string
            printf("%s: %s(Rx) := %03d(SP) %s %03d(SP)\n", str, str_at2, aux_p->desloc, i->op, aux_p2->desloc);
        }

        // Case: First argument is not 'S' or 'T', second is 'S'
        if (i->arg1[0] != 'S' && i->arg2[0] == 'S' && i->arg1[0] != 'T' && i->arg2[0] != 'T') {
            str_at[0] = '\n';
            strcpy(str_at, i->arg2);
            memmove(&str_at[0], &str_at[1], strlen(str_at) - 0);

            if (!strcmp(i->op, ":=")) {
                printf("%s: %03d(SP) %s %s\n", str, aux_p->desloc, i->op, str_at);
            } else {
                str_at2[0] = '\n';
                strcpy(str_at2, i->res);
                memmove(&str_at2[0], &str_at2[1], strlen(str_at2) - 0);
                printf("%s: %s(Rx) := %03d(SP) %s %s\n", str, str_at2, aux_p->desloc, i->op, str_at);
            }
        }

        // Case: First argument is 'S', second is not 'S' or 'T'
        if (i->arg1[0] == 'S' && i->arg2[0] != 'S' && i->arg1[0] != 'T' && i->arg2[0] != 'T') {
            str_at[0] = '\n';
            strcpy(str_at, i->arg1);
            memmove(&str_at[0], &str_at[1], strlen(str_at) - 0);
            str_at2[0] = '\n';
            strcpy(str_at2, i->res);
            memmove(&str_at2[0], &str_at2[1], strlen(str_at2) - 0);

            printf("%s: %s(Rx) := %s %s %03d(SP)\n", str, str_at2, str_at, i->op, aux_p2->desloc);
        }

        // Case: Second argument is 'T', first is not 'S' or 'T'
        if (i->arg1[0] != 'S' && i->arg2[0] != 'S' && i->arg1[0] != 'T' && i->arg2[0] == 'T') {
            str_at[0] = '\n';
            strcpy(str_at, i->arg2);
            memmove(&str_at[0], &str_at[1], strlen(str_at) - 0);

            if (!strcmp(i->op, ":=")) {
                printf("%s: %03d(SP) %s %s(Rx)\n", str, aux_p->desloc, i->op, str_at);
            } else {
                str_at2[0] = '\n';
                strcpy(str_at2, i->res);
                memmove(&str_at2[0], &str_at2[1], strlen(str_at2) - 0);
                printf("%s: %s(Rx) := %03d(SP) %s %s(Rx)\n", str, str_at2, aux_p->desloc, i->op, str_at);
            }
        }

        aux2 = aux2->next; // Move to the next instruction in the list
        l++; // Increment the instruction counter
    }
}

/**
 * Function to append a TAC instruction to a list of TAC instructions.
 * 
 * @param code A double pointer to the TAC list
 * @param inst The TAC instruction to append
 */
void append_inst_tac(struct node_tac **code, struct tac *inst) {
    struct node_tac *node = (struct node_tac*)malloc(sizeof(struct node_tac)); // Create a new node
    node->inst = inst; // Assign the TAC instruction to the node
    node->next = NULL; // Set the next pointer to NULL

    // If the list is empty, initialize the list
    if (*code == NULL) {
        *code = node;
        node->prev = NULL;
    } else {
        // Traverse to the end of the list and append the node
        struct node_tac *aux = *code;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = node;
        node->prev = aux;
    }
}

/**
 * Function to concatenate two lists of TAC instructions.
 * 
 * @param code_a The first list of TAC instructions
 * @param code_b The second list of TAC instructions to be appended to the first list
 */
void cat_tac(struct node_tac **code_a, struct node_tac **code_b) {
    // If the first list is empty, point it to the second list
    if (*code_a == NULL) {
        *code_a = *code_b;
    } 
    // If the second list is not empty, concatenate the lists
    else if (*code_b != NULL) {
        struct node_tac *aux = *code_a;
        // Traverse to the end of the first list
        for (; aux->next != NULL; aux = aux->next);
        aux->next = *code_b;
    }
}
