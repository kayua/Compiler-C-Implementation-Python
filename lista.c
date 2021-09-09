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


void print_tac(struct node_tac * code){

    int digito = 0;

    struct node_tac *aux2 = code;
    struct tac *i;

    while(aux2!=NULL){

        i = aux2->inst;

        if(i->res==""){

            printf("%s := %s %s %s\n",i->res, i->arg1, i->op, i->arg2);

        }else{

            printf("%s := %s %s %s\n",i->res, i->arg1, i->op, i->arg2);
        }

        aux2 = aux2 -> next;
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