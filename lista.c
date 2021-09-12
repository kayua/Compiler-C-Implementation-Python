#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "lista.h"

int numList=1;

struct node_tac *lista = NULL;

struct node_tac * table_TAC;

struct tac* create_inst_tac(const char* res, const char* arg1, const char* op, const char* arg2){

    struct tac *new=(struct tac*)malloc(sizeof(struct tac));
    new->res=malloc(sizeof(res));
    new->arg1=malloc(sizeof(arg1));
    new->op=malloc(sizeof(op));
    new->arg2=malloc(sizeof(arg2));
    if(new==NULL){
        exit(0);
    }
    if(res!=NULL) strcpy(new->res, res);
    if(arg1!=NULL) strcpy(new->arg1, arg1);
    if(arg2!=NULL) strcpy(new->arg2, arg2);
    if(op!=NULL) strcpy(new->op, op);
    return new;

}

void print_inst_tac(FILE* out, struct tac i){ printf("\n"); }


void print_tac(struct node_tac * code, symbol_t table){

    int digito = 0;

    struct node_tac *aux2 = code;
    struct tac *i;
    int l=0;
    char str[5];
    char str_at[100];
    char str_at2[100];

    while(aux2!=NULL){

        sprintf(str, "%03d", l);
        i = aux2->inst;
        entry_t *aux_p = lookup(table, i->arg1);
        entry_t *aux_p2 = lookup(table, i->arg2);

        if (i->arg1[0] != 'S' && i->arg2[0] != 'S' && i->arg1[0] != 'T' && i->arg2[0] != 'T' ) {
                str_at2[0] = '\n';
                strcpy(str_at2, i->res);
                memmove(&str_at2[0], &str_at2[0 + 1], strlen(str_at2) - 0);
                printf("%s: %s(Rx) := %03d(SP) %s %03d(SP)\n", str,str_at2, aux_p->desloc, i->op, aux_p2->desloc);
            }

        if (i->arg1[0] != 'S' && i->arg2[0] == 'S' && i->arg1[0] != 'T' && i->arg2[0] != 'T' ) {

            str_at[0] = '\n';
            strcpy(str_at, i->arg2);
            memmove(&str_at[0], &str_at[0 + 1], strlen(str_at) - 0);

            if(!strcmp(i->op, ":=")){

                printf("%s: %03d(SP) %s %s\n", str, aux_p->desloc, i->op, str_at);

            }else{

                str_at2[0] = '\n';
                strcpy(str_at2, i->res);
                memmove(&str_at2[0], &str_at2[0 + 1], strlen(str_at2) - 0);

                printf("%s: %s(Rx) := %03d(SP) %s %s\n", str, str_at2, aux_p->desloc, i->op, str_at);

            }


        }

        if (i->arg1[0] == 'S' && i->arg2[0] != 'S' && i->arg1[0] != 'T' && i->arg2[0] != 'T' ) {

            str_at[0] = '\n';
            strcpy(str_at, i->arg1);
            memmove(&str_at[0], &str_at[0 + 1], strlen(str_at) - 0);
            str_at2[0] = '\n';
            strcpy(str_at2, i->res);
            memmove(&str_at2[0], &str_at2[0 + 1], strlen(str_at2) - 0);


            printf("%s: %s(Rx) := %s %s %03d(SP)\n", str, str_at2, str_at, i->op, aux_p2->desloc);

        }

        if (i->arg1[0] != 'S' && i->arg2[0] != 'S' && i->arg1[0] != 'T' && i->arg2[0] == 'T' ) {

            if(!strcmp(i->op, ":=")){

                str_at[0] = '\n';
                strcpy(str_at, i->arg2);
                memmove(&str_at[0], &str_at[0 + 1], strlen(str_at) - 0);

                printf("%s: %03d(SP) %s %s(Rx)\n", str, aux_p->desloc, i->op, str_at);

            }else{
                str_at[0] = '\n';
                strcpy(str_at, i->arg2);
                memmove(&str_at[0], &str_at[0 + 1], strlen(str_at) - 0);
                str_at2[0] = '\n';
                strcpy(str_at2, i->res);
                memmove(&str_at2[0], &str_at2[0 + 1], strlen(str_at2) - 0);
                printf("%s: %s(Rx) := %03d(SP) %s %s(Rx)\n", str, str_at2, aux_p->desloc, i->op, str_at);

            }


        }

        aux2 = aux2 -> next;
        l++;
    }

}

void append_inst_tac(struct node_tac ** code, struct tac * inst){

    struct node_tac *node = (struct node_tac*)malloc(sizeof(struct node_tac));
    node->inst = inst;
    node->next = NULL;

    if(*code == NULL){
        *code = node;
        node->prev = NULL;
    }
    else{
        struct node_tac *aux;
        aux = *code;
        while(aux->next!=NULL){
            aux=aux->next;
        }
        aux->next = node;
        node->prev = aux;
    }


}


void cat_tac(struct node_tac ** code_a, struct node_tac ** code_b){

    if(*code_a==NULL){
        *code_a=*code_b;
    }
    else if(*code_b!=NULL){
        struct node_tac*aux=*code_a;
        for(; aux->next!=NULL; aux=aux->next);
        aux->next=*code_b;
    }
}