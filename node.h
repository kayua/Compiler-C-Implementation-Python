/** @file node.h
 *  @version 1.2
 */

#ifndef _NODE_H_
#define _NODE_H_

#ifdef __GNUC__

#define NULL_TERMINATED __attribute__((sentinel))
#else
#define NULL_TERMINATED
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


typedef int Node_type;

#define code_node             298
#define declaracoes_node      299
#define declaracao_node       300
#define tipo_node             301
#define int_node              501
#define idf_node              502
#define double_node 503
#define real_node 504
#define char_node 505
#define tipolista_node 506
#define listadupla_node 507
#define acoes_node 508
#define atribuicao_node 509
#define swap_node 510
#define if_node 511
#define while_node 512
#define lvalue 513
#define lvalue_node 514
#define listaexp_node 515
#define soma_node 516
#define sub_node 517
#define multi_node 518
#define div_node 519
#define float_node 520
#define true_node 521
#define and_node 522
#define or_node 523
#define maior_node 524
#define menor_node 525
#define menorigual_node 526
#define maiorigual_node 527
#define igual_node 528
#define diferente_node 529
#define listadeclaracao_node 529
#define pontoevirgula_node 530
#define abrepar_node 532
#define fechapar_node 533
#define doispontos_node 534
#define virgula_node 535
#define swaplex_node 536
#define expr_node 537
#define iflex_node 538
#define then_node 539
#define abrechaves_node 540
#define fechachaves_node 541
#define whilelex_node 542
#define end_node 543
#define elselex_node 544
#define fiminstcontrole_node 545
#define abrecol_node 546
#define fechacol_node 547
#define abre_colchete 548
#define fecha_colchete 549
#define mais_node 550
#define menos_node 551
#define vezes_node 552
#define dividido_node 553
#define andlex_node 554
#define orlex_node 555
#define notlex_node 556
#define not_node 557
#define maiorlex_node 558
#define menorlex_node 559
#define menoriguallex_node 560
#define maioriguallex_node 561
#define igualex_node 562
#define diferentelex_node 563


typedef struct _node {
    int line_num;   /**< numero de linha. */
    char* lexeme;   /**< o lexema retornado pelo analizador lexical. */
    Node_type type; /**< Um dos valores definidos acima pelos # defines. */
    void* attribute;/**< Qualquer coisa por enquanto. */

    struct _node** children;
    unsigned int n_child;

} Node;

extern Node * syntax_tree;

Node* create_node(int nl, Node_type t,
                  char* lexeme,  /* Node* children */ ...);

int nb_of_children(Node* n);

int is_leaf(Node* n);

Node* child(Node* n, int i) ;

int deep_free_node(Node* n) ;

int height(Node *n) ;

void uncompile(Node *n) ;


#endif