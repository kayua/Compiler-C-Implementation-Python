/** @file symbol_table.c
 *  @version 1
 *  @author Kayuã Oleques
 */

#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>

#define EOS '\0'
#define TMP_STRING_SIZE 500  /**< Size of the temporary string buffer. */

/**
 * @brief PJW (Perfect Hash Function) hash function for strings.
 * 
 * @param s Input string.
 * @return The hash value as an integer.
 */
int hashpjw(const char *s) {
    char *p;
    unsigned h = 0, g;
    for (p = (char*)s; *p != EOS; p++) {
        h = (h << 4) + (*p);
        if ((g = h & 0xf0000000)) {
            h ^= (g >> 24);
            h ^= g;
        }
    }
    return h % PRIME;
}

/**
 * @brief Initializes the symbol table, setting all pointers to NULL.
 * 
 * @param table The table to be initialized.
 * @return A pointer to the initialized table.
 */
symbol_t* init_table(symbol_t* table) {
    if (!table) return NULL;
    for (int x = 0; x < PRIME; x++) {
        table->entries[x] = NULL;
    }
    return table;
}

/**
 * @brief Frees the memory allocated for the symbol table.
 * 
 * @param table The table to be freed.
 */
void free_table(symbol_t* table) {
    if (!table) return;

    for (int x = 0; x < PRIME; x++) {
        struct table_node_entry* current = table->entries[x];

        while (current != NULL) {
            struct table_node_entry* next = current->next;
            free(current);
            current = next;
        }

        table->entries[x] = NULL;
    }
}

/**
 * @brief Searches for an entry in the symbol table by name.
 * 
 * @param table The table where the search will be performed.
 * @param name The name of the entry to search for.
 * @return A pointer to the found entry or NULL if not found.
 */
entry_t* lookup(symbol_t table, const char* name) {
    int hash = hashpjw(name);
    struct table_node_entry* current = table.entries[hash];

    while (current != NULL && strcmp(name, current->entry_data->name) != 0) {
        current = current->next;
    }

    return (current != NULL) ? current->entry_data : NULL;
}

/**
 * @brief Inserts a new entry into the symbol table.
 * 
 * @param table The table where the entry will be inserted.
 * @param entry The entry to be inserted.
 * @return 0 if the insertion is successful, -1 if the entry already exists.
 */
int insert(symbol_t* table, entry_t* entry) {
    if (lookup(*table, entry->name) != NULL) {
        return -1;  // Entry already exists.
    }

    struct table_node_entry* node = malloc(sizeof(struct table_node_entry));
    if (!node) return -1;  // Memory allocation failure.

    node->entry_data = entry;
    node->next = NULL;

    int hash = hashpjw(entry->name);

    if (table->entries[hash] == NULL) {
        table->entries[hash] = node;
    } else {
        node->next = table->entries[hash];
        table->entries[hash] = node;
    }

    return 0;
}

/**
 * @brief Prints the symbol table to a file.
 * 
 * @param out The file pointer where the table will be printed.
 * @param table The table to be printed.
 * @return The number of entries in the table.
 */
int print_file_table(FILE* out, symbol_t table) {
    int entry_count = 0;

    for (int x = 0; x < PRIME; x++) {
        if (table.entries[x] != NULL) {
            char tmp_string[TMP_STRING_SIZE];
            struct table_node_entry* current = table.entries[x];

            do {
                str_entry(tmp_string, current->entry_data);
                fprintf(out, "%s", tmp_string);
                entry_count++;
                current = current->next;
            } while (current != NULL);
        }
    }

    return entry_count;
}

/**
 * @brief Converts a symbol table entry to a string.
 * 
 * @param retbuffer The output buffer where the string will be stored.
 * @param entry The table entry.
 * @return The pointer to the output buffer.
 */
char* str_entry(char* retbuffer, entry_t* entry) {
    sprintf(retbuffer, "ENTRY: %s;\n\tType: %d;\n\tSize: %d;\n\tDesloc: %d.\n\n",
            entry->name, entry->type, entry->size, entry->desloc);
    return retbuffer;
}

/**
 * @brief Prints the symbol table to `stdout`.
 * 
 * @param table The table to be printed.
 * @return The number of entries in the table.
 */
int print_table(symbol_t table) {
    return print_file_table(stdout, table);
}
