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

    while(aux2!=NULL){

        sprintf(str, "%03d", l);
        i = aux2->inst;
        entry_t *aux_p = lookup(table, i->arg1);
        entry_t *aux_p2 = lookup(table, i->arg2);
        if(strcmp(i->arg1, i->arg2) ) {

            if(i->arg1[0]=='S' || i->arg2[0]=='S'){

                memmove(&i->arg2[0], &i->arg2[0 + 1], strlen(i->arg2) - 0);
                printf(" -> %s %s %s \n", i->arg1, i->op, i->arg2);
            }else{

                printf(" -> %s %s %s \n", i->arg1, i->op, i->arg2);
            }


        }
        //printf("(%s)\n",aux_p->name);

        /* if(!strcmp(i->op,":=") && strcmp(i->arg1, i->arg2) ){
            memmove(&i->arg2[0], &i->arg2[0 + 1], strlen(i->arg2) - 0);
            printf(" -> %d %s %s \n", aux_p2->desloc, i->op, i->arg2);

        }
        */

        //printf("\n%s (%s) %s \n", i->arg1, i->op, i->arg2);
        /* if(i->arg1[0]=='S'){
            memmove(&i->arg1[0], &i->arg1[0 + 1], strlen(i->arg1) - 0);
            printf("%s: %03d(SP) :=  %s\n", str, aux_p2->desloc, i->arg1);
        }else{


            printf("1: 1(SP) :=  0\n");
        }
    */

    /*
        if(!strcmp(i->op,"SUM") || !strcmp(i->op,"MUL") || !strcmp(i->op,"DIV") || !strcmp(i->op,"SUB")){

            if(aux_p!=NULL){

            if(strcmp(i->arg2,"arithmetic_operations")){

                printf("%s: %s(Rx) := %03d(SP) %s %03d(SP)\n",str, i->res, aux_p->desloc, i->op, aux_p2->desloc);

            }else{

                //printf("%s: %s(Rx) := %03d(SP) %s %03d(RX)\n",str, i->res, aux_p->desloc, i->op, aux_p2->desloc);
            }

        }}
        */

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