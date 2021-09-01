#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include "node.h"

typedef int Node_type;

Node * syntax_tree;

Node* create_node(int nl, Node_type t, char* lexeme,  /* Node* children */ ...)
{
    Node* new_node = (Node *)malloc(sizeof(Node));
    new_node->line_num = nl;
    new_node->type = t;
    new_node->lexeme = lexeme;
    new_node->n_child = 0;
    new_node->children = NULL;
    va_list ap;
    va_start(ap, NULL);
    Node* arg = va_arg(ap,  Node*);

    for (;  arg != NULL;  arg = va_arg(ap, Node*)) {

        if (new_node->children == NULL)
            new_node->children = (Node**) malloc(sizeof(Node*));

        else

            new_node->children = (Node**) realloc(new_node->children, (new_node->n_child + 1) * sizeof(Node*));

        new_node->children[new_node->n_child] = arg;
        new_node->n_child++;
    }

    va_end(ap);
    return new_node;

}

int nb_of_children(Node* n){

    assert(n != NULL);
    return n->n_child;
}

int is_leaf(Node* n)
{
    assert(n != NULL);
    return n->n_child == 0;
}

Node* child(Node* n, int i)
{
    assert(n != NULL);
    assert((0 <= i) && ((unsigned int)i < n->n_child));
    return n->children[i];
}

int deep_free_node(Node* n)
{
    int i;
    int size_children;
    if(n->n_child==0){
        free(n);
    }
    else if(n->n_child>0){
        size_children=n->n_child;
        for(i=0; i<size_children; i++){
            deep_free_node(n->children[n->n_child-1]);
            n->children = (Node**) realloc(n->children, (n->n_child - 1) * sizeof(Node*));
            n->n_child--;
        }
        free(n->children);
        free(n);
    }
    return 0;
}

int height(Node* n)
{
    int i=0;
    int _height=0;
    int _height_child=0;
    assert(n != NULL);
    if(n->n_child != 0)
    {
        for(i=0; i<n->n_child; i++){
            _height_child=height(n->children[i]);
            if(_height<_height_child){
                _height=_height_child;
            }
        }
        return 1+_height;
    }
    else
        return 1;
}

void uncompile(Node *n){

    assert(n != NULL);
    int i;


    if(n != NULL) {
        for (i = 0; i < n->n_child; i++) {
            uncompile(n->children[i]);
        }
    }
    printf("%s \n", n->lexeme);
}
