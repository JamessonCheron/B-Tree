#define M 5
#define MAX_CHAVES (M - 1)
#define MAZ_FILHOS M
#define MIN_OCUP (M - 1)

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Btree;

int busca_binaria( Btree *no, int info);

//Insere uma chave e o ponteiro para o filho da direita em um n�
void insere_chave( Btree *raiz, int info, Btree *filhodir);

//Realiza a busca do n� para inserir a chave e faz as subdivi��es quando necess�rias
Btree *insere( Btree *raiz, int info, int *h, int *info_retorno);

Btree *insere_avoreB(Btree *raiz, int info);