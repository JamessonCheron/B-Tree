#define M 5
#define MAX_CHAVES (M - 1)
#define MAX_FILHOS M
#define MIN_OCUP (M - 1)

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Btree;

int busca_binaria( Btree *no, int info);

void search_value( Btree *raiz, int value);

/*Insere uma chave e o ponteiro para o filho da direita em um nó*/
void insere_chave( Btree *raiz, int info, Btree *filhodir);

/*Realiza a busca do nó para inserir a chave e faz as subdivições quando necessárias*/
Btree *insere( Btree *raiz, int info, int *h, int *info_retorno);

Btree *insere_arvoreB(Btree *raiz, int info);

Btree *novaFolha();

/* delete val from B-tree */
void deletion(int val, Btree *myNode);

/* delete val from the node */
int delValFromNode(int val, Btree *myNode);

/* copy successor for the value to be deleted */
void copySuccessor(Btree *myNode, int pos);

/* removes the value from the given node and rearrange values */
void removeVal(Btree *myNode, int pos);

/* merge nodes */
void mergeNodes(Btree *myNode, int pos);

/* adjusts the given node */
void adjustNode(Btree *myNode, int pos);

/* shifts value from parent to right child */
void doRightShift(Btree *myNode, int pos);

/* shifts value from parent to left child */
void doLeftShift(Btree *myNode, int pos);

/*List B Tree by levels*/
void listBTree(Btree *raiz, int nivel);