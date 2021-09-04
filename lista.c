#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "../_Header/lista.h"

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
        printf("Allocation Error\n");
        exit(0);
    }
    if(res!=NULL) strcpy(new->res, res);
    if(arg1!=NULL) strcpy(new->arg1, arg1);
    if(arg2!=NULL) strcpy(new->arg2, arg2);
    if(op!=NULL) strcpy(new->op, op);
    return new;

}

void print_inst_tac(FILE* out, struct tac i){
    printf("\nnada aqui\n");
}

void print_tac(FILE* out, struct node_tac * code){

    struct node_tac *aux = lista;
    entry_t *aux_deslc = NULL;
    int bytesSP = vars_size, bytesRX = temps_size;
    char op[5], strop[5];

    fprintf(out, "%d\n", bytesSP);
    fprintf(out, "%d\n", bytesRX);
    aux = lista;
    while(aux != NULL){
        strcpy(op, aux->inst->op);
        //printf("OP %s\n", op);
        if(strcmp(op, "+") == 0){
            strcpy(strop, "SUM");
        }
        else if(strcmp(op, "-") == 0){
            strcpy(strop, "SUB");
        }
        else if(strcmp(op, "*") == 0){
            strcpy(strop, "MUL");
        }
        else if(strcmp(op, "/") == 0){
            strcpy(strop, "DIV");
        }
        else{
            strcpy(strop, "");
        }
        if(strcmp(op, "PRINT")==0){
            fprintf(out, "%.3d: PRINT %s\n", aux->number, aux->inst->res);
        }
        else if(strcmp(op, "CONDICIONAL-If")==0){
            fprintf(out, "%.3d: if %s GOTO %s\n", aux->number, aux->inst->res, aux->inst->arg1);
        }
        else if(strcmp(op, "Rotulo")==0){
            fprintf(out, "%.3d: %s\n", aux->number, aux->inst->arg1);
        }
        else if(op!=NULL)
            fprintf(out, "%.3d: %s := %s %s %s\n", aux->number, aux->inst->res, aux->inst->arg1, strop, aux->inst->arg2);
        else
            fprintf(out, "%.3d: %s := %s\n", aux->number, aux->inst->res, aux->inst->arg1);
        aux = aux->next;
    }
    fclose(out);

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