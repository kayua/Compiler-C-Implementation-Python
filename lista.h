/** @file lista.h
 *  @brief Header file for managing TAC instructions and linked list structure.
 */

#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "symbol_table.h"

/* Global variables */
extern int vars_size;
extern int temps_size;

/**
 * @brief Structure representing a TAC instruction (used in Step 4).
 */
struct tac {
    char* op;   /**< Operator (e.g., "+", "-", ":=", "if", etc.) */
    char* res;  /**< Result (e.g., "TMP100") */
    char* arg1; /**< First argument (e.g., "TMP0") */
    char* arg2; /**< Second argument (e.g., "TMP1") */
};

/**
 * @brief Constructs a TAC instruction.
 *
 * @param res Result of the instruction (e.g., "TMP100").
 * @param arg1 First argument (e.g., "TMP0").
 * @param op Operator (e.g., "+", "-", ":=", "if").
 * @param arg2 Second argument (e.g., "TMP1").
 * @return Pointer to a newly allocated `struct tac` or NULL if memory allocation fails.
 */
struct tac* create_inst_tac(const char* res, const char* arg1, const char* op, const char* arg2);

/**
 * @brief Prints the content of a TAC instruction.
 *
 * @param out File pointer where the instruction will be printed.
 * @param i The TAC instruction to print.
 */
void print_inst_tac(FILE* out, struct tac i);

/**
 * @brief Basic element of the TAC linked list.
 */
struct node_tac {
    int number;              /**< Entry number (1 for the first element, 2 for the second, etc.). */
    struct tac* inst;        /**< Pointer to the TAC instruction. */
    struct node_tac* next;   /**< Pointer to the next element in the list. */
    struct node_tac* prev;   /**< Pointer to the previous element in the list. */
};

/**
 * @brief Prints the content of the linked list to the file.
 *
 * Each line starts with a three-digit number followed by a colon, representing the instruction number.
 * Example:
 *   001:  some_instruction
 *   002:  another_instruction
 *
 * @param out File pointer where the list will be printed (one line per element).
 * @param code Pointer to the linked list of instructions.
 */
void print_tac(struct node_tac* code, symbol_t table);

/**
 * @brief Appends a TAC instruction to the end of the list.
 *
 * @param code Initial (possibly empty) list. On output, contains the same list with one more element at the end.
 * @param inst The instruction to append to the end of the list.
 */
void append_inst_tac(struct node_tac** code, struct tac* inst);

/**
 * @brief Concatenates two lists of TAC instructions.
 *
 * @param code_a Initial (possibly empty) list. On output, contains the concatenated list with `code_b`.
 * @param code_b The list to concatenate with `code_a`.
 */
void cat_tac(struct node_tac** code_a, struct node_tac** code_b);

#endif
