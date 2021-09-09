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

void print_tac(struct node_tac * code){

    struct node_tac * aux_node_tac = code;
    struct tac* aux_tac = NULL;


    while(1){

        aux_tac = aux_node_tac->inst;

        if(aux_tac==NULL){
            break;
        }
        printf("%s %s %s", aux_tac->arg1,aux_tac->op, aux_tac->arg2);

        aux_node_tac = aux_node_tac->next;

    }


}


struct node_tac* append_inst_tac(struct node_tac *code, struct tac * inst){

    struct node_tac *new_node_tac = (struct node_tac*)malloc(sizeof(struct node_tac));
    struct node_tac *table_tac = code;
    struct node_tac *p = NULL;
    int i = 0;

    new_node_tac->inst = inst;
    new_node_tac->number = 0;


    if(table_tac == NULL){

        new_node_tac->prev = NULL;
        new_node_tac->next = NULL;
        printf("Primeira inserção");
        return new_node_tac;

    }else{

        while(1){

            i = i+1;

            if(table_tac->next == NULL){

                break;

            }
            printf("Segunda inserção %d", i);
            table_tac = table_tac->next;

            }

        table_tac->next = new_node_tac;
        new_node_tac->prev = table_tac;
        new_node_tac->next = NULL;
        return code;

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