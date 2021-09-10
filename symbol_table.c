/** @file symbol_table.c
 * \version 1
 * \author Daniel Beck
 * \author Francieli Zanon
 * \author Joseane Barrios
 * \brief Implementacao de uma tabela hash
 */

#include "symbol_table.h"
#define EOS '\0'

int hashpjw(s)
        char *s;
{
    char *p;
    unsigned h = 0, g;
    for ( p = s; *p != EOS; p = p+1 ) {
        h = (h << 4) + (*p);
        if  (g = h&0xf0000000) {
            h = h ^ (g >> 24);
            h = h ^ g;
        }
    }
    return h % PRIME;
}


symbol_t* init_table(symbol_t* table) {

    int x = 0;
    for(x = 0; x < PRIME; x++) {
        table->entries[x] = NULL;
    }
    return table;
}


void free_table(symbol_t* table) {

    int x = 0;

    for(x = 0; x < PRIME; x++) {

        if(table->entries[x] != NULL) {

            struct table_node_entry * atual = table->entries[x];
            struct table_node_entry * proximo = atual->next;
            free(atual);

            while(proximo != NULL) {

                atual = proximo;
                proximo = atual->next;
                free(atual);

            }

            table->entries[x] = NULL;
        }
    }
    return;
}

entry_t* lookup(symbol_t table, char* name) {

    int hash = hashpjw(name);

    if(table.entries[hash] != NULL) {

        struct table_node_entry * atual = table.entries[hash];
        while(( strcmp(name, atual->entry_data->name)) && (atual->next != NULL)) {
            atual = atual->next;
        }

        if( ! strcmp(name, atual->entry_data->name)) {

            return atual->entry_data;

        } else {

            return NULL;
        }

    } else {

        return NULL;
    }
}

int insert(symbol_t* table, entry_t* entry) {

    if(lookup(*table, entry->name) != NULL) {
        return -1;
    }

    struct table_node_entry * nodo = malloc(sizeof(struct table_node_entry));
    nodo->entry_data = entry;
    nodo->next = NULL;

    int hash = hashpjw(entry->name);

    if(table->entries[hash] == NULL) {

        table->entries[hash] = nodo;
    } else {

        nodo->next = table->entries[hash];
        table->entries[hash] = nodo;
    }

    return 0;
}

char * str_entry(char * retbuffer, entry_t* entry);

int print_table(symbol_t table) {
    return print_file_table(stdout, table);
}

int print_file_table(FILE* out, symbol_t table) {
    int entry_count = 0;

    int x = 0;
    for(x = 0; x < PRIME; x++) {

        if(table.entries[x] != NULL) {
            char tmp_string[500];

            struct table_node_entry * atual = table.entries[x];

            do {
                str_entry(tmp_string, atual->entry_data);
                fprintf(out, "%s", tmp_string);
                entry_count++;
                atual = atual->next;
            } while(atual != NULL);

        }
    }


    return entry_count;
}

char * str_entry(char * retbuffer, entry_t* entry) {
    sprintf(retbuffer, "ENTRY: %s;\n\tType: %d;\n\tSize: %d;\n\tDesloc: %d.\n\n",
            entry->name, entry->type, entry->size, entry->desloc);
    return retbuffer;
}