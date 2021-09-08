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

void print_inst_tac(FILE* out, struct tac i){
    printf("\n");
}

void print_tac(FILE* out, struct node_tac * code){
    printf("criar a função para print");

}


void append_inst_tac(struct node_tac ** code, struct tac * inst){

    struct node_tac *novo_no = (struct node_tac*)malloc(sizeof(struct node_tac));
    struct node_tac *atual = *code;
    struct node_tac *p = NULL;
    int i = 0;

    novo_no->inst = (struct tac*)malloc(sizeof(struct tac));
    novo_no->inst = inst;
    novo_no->number = 0;

    if(atual == NULL){
        novo_no->prev = NULL;
        novo_no->next = NULL;
        *code = novo_no;
        return;
    }
    else{

        novo_no->next = *code;
        atual->prev = novo_no;
        novo_no->prev = NULL;
        *code = novo_no;
    }

    p = *code;
    while (p != NULL){
        p->number = i;
        i++;
        p = p->next;
    }

    return;
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