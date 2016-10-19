#define _CRT_SECURE_NO_WARNINGS

#include "b_tree.h"

struct Node
{
	int num_chaves;
	int chaves[MAX_CHAVES];
	Btree *filhos[MAZ_FILHOS];

};

int busca_binaria( Btree *no, int info)
{
	int meio, i, f;

	i = 0;
	f = no->num_chaves - 1;

	while (i <= f)
	{
		meio = (i + f)/2;
		
		if (no->chaves[meio] == info) 
		{
			return meio; // Retorna a posição em que a chave está
		}
		else if (no->chaves[meio] > info)
		{
			f = meio - 1;
		}
		else
		{
			i = meio + 1;
		}

	}
	return i; //Não encotrou. Retrona a Posição do ponteiro para o filho
}

void insere_chave( Btree *raiz, int info, Btree *filhodir)
{

	int k, pos;

	//Busca para obter a posição ideal para inserir a nova chave
	pos = busca_binaria(raiz, info);

	k = raiz->num_chaves;

	//Realiza o remanejamento para manter as chaves ordenadas
	while (k > pos && info < raiz->chaves[k-1])
	{
		
		raiz->chaves[k] = raiz->chaves[k-1];
		raiz->filhos[k+1] = raiz->filhos[k];
		k--;
	}

	//insere a chave na posição ideal
	raiz->chaves[pos] = info;
	raiz->filhos[pos+1] = filhodir;
	raiz->num_chaves++;

}

Btree *insere( Btree *raiz, int info, int *h, int *info_retorno)
{
	int i, pos, info_mediano;
	Btree *temp, *filho_dir;

	if(raiz == NULL)
	{
		*h = 1;
		*info_retorno = info;
		return NULL;
	}
	else
	{
		pos = busca_binaria(raiz, info);

		if (raiz->num_chaves > pos && raiz->chaves[pos] == info)
		{
			printf("Chave ja contida na Arvore");
			*h = 0;
			return raiz;
		}
		else
		{
			filho_dir = insere( raiz->filhos[pos], info, h, info_retorno);

			if (*h)
			{
				if (raiz->num_chaves < MAX_CHAVES)
				{
					insere_chave(raiz, *info_retorno, filho_dir);
					*h = 0;
					return raiz;
				}
				else
				{
					temp = novaFolha();
					temp->num_chaves = 0;
					//incicializa filhos com NULL
					for (i = 0; i < MAZ_FILHOS; i++)
					{
						temp->filhos[i] = NULL;
					}

					//elemento mediano que vai subir para o pai
					info_mediano = raiz->chaves[MIN_OCUP];

					//insere metade do nó raiz no temp (edetua subdivisão)
					temp->filhos[0] = raiz->filhos[MIN_OCUP + 1];

					for (i = MIN_OCUP + 1; i < MAX_CHAVES; i++)
					{
						insere_chave(temp, raiz->chaves[i], raiz->filhos[i+1]);
					}

					//Atualiza nó raiz

					for (i = MIN_OCUP; i < MAX_CHAVES; i++)
					{
						raiz->chaves[i] = 0;
						raiz->filhos[i+1] = NULL;
					}

					raiz->num_chaves = MIN_OCUP;

					//Verifica em qual nó será inserida a nova chave
					if (pos <= MIN_OCUP)
					{
						insere_chave(raiz, *info_retorno, filho_dir);
					}
					else
					{
						insere_chave(temp, *info_retorno, filho_dir);
					}

					//Retorna o mediano para inseri-lo no nó pai e o temp como filho direito do mediano

					*info_retorno = info_mediano;
					return temp;
				}

			}

			return raiz;
		}


	}
}

Btree *insere_avoreB(Btree *raiz, int info)
{
	int h, info_retorno, i;
	Btree *filho_dir, *nova_raiz;

	filho_dir = insere(raiz, info, &h, &info_retorno);

	if (h)
	{
		nova_raiz = novaFolha();
		nova_raiz->num_chaves = 1;
		nova_raiz->chaves[0] = info_retorno;
		nova_raiz->filhos[0] = raiz;
		nova_raiz->filhos[1] = filho_dir;

		for (i = 2; i < MAX_CHAVES; i++)
		{
			nova_raiz->filhos[i] = NULL;
		}
		return nova_raiz;
	}
		return raiz;
}

Btree *novaFolha()
{
	Btree *nova = (Btree*)malloc(sizeof(Btree));
	return nova;
}

  /* delete val from B-tree */
 void deletion(int val, Btree *myNode) 
 {
        
	 Btree *tmp;
     if (!delValFromNode(val, myNode)) {
             printf("Given value is not present in B-Tree\n");
             return;
     } else {
             if (myNode->num_chaves == 0) {
                     tmp = myNode;
                     myNode = myNode->filhos[0];
                     free(tmp);
             }
     }
     //root = myNode;
     //return;
  }

   /* delete val from the node */
  int delValFromNode(int val, Btree *myNode) 
  {

     int pos, flag = 0;

     if (myNode) 
	 {
             if (val < myNode->chaves[1]) 
			 {
                     pos = 0;
                     flag = 0;
             } else 
			 {
                     for (pos = myNode->num_chaves;
                             (val < myNode->chaves[pos] && pos > 1); pos--);
                      if (val == myNode->chaves[pos]) 
					  {
                             flag = 1;
                     } else 
					  {
                             flag = 0;
                     }
             }

             if (flag) 
			 {
                     if (myNode->filhos[pos - 1])
					 {
                             copySuccessor(myNode, pos);
                             flag = delValFromNode(myNode->chaves[pos], myNode->filhos[pos]);
                             if (flag == 0) 
							 {
                                     printf("Given data is not present in B-Tree\n");
                             }
                     } 
					 else 
					 {
                             removeVal(myNode, pos);
                     }
             } 
			 else 
			 {
                     flag = delValFromNode(val, myNode->filhos[pos]);
             }
             if (myNode->filhos[pos]) 
			 {
                     if (myNode->filhos[pos]->num_chaves < MIN_OCUP)
                             adjustNode(myNode, pos);
             }
     }
     return flag;
  }

    /* copy successor for the value to be deleted */
  void copySuccessor(Btree *myNode, int pos) 
  {
        Btree *dummy;

        dummy = myNode->filhos[pos];

        for (;dummy->filhos[0] != NULL;)
                dummy = dummy->filhos[0];

        myNode->chaves[pos] = dummy->chaves[1];

  }

  /* removes the value from the given node and rearrange values */
  void removeVal(Btree *myNode, int pos) 
  {
        int i = pos + 1;

        while (i <= myNode->num_chaves) 
		{
                myNode->chaves[i - 1] = myNode->chaves[i];
                myNode->filhos[i - 1] = myNode->filhos[i];
                i++;
        }
        myNode->num_chaves--;
  }

    /* merge nodes */
  void mergeNodes(Btree *myNode, int pos) 
  {
        int j = 1;
        Btree *x1 = myNode->filhos[pos], *x2 = myNode->filhos[pos - 1];

        x2->num_chaves++;
        x2->chaves[x2->num_chaves] = myNode->chaves[pos];
        x2->filhos[x2->num_chaves] = myNode->filhos[0];

        while (j <= x1->num_chaves) {
                x2->num_chaves++;
                x2->chaves[x2->num_chaves] = x1->chaves[j];
                x2->filhos[x2->num_chaves] = x1->filhos[j];
                j++;
        }

        j = pos;
        while (j < myNode->num_chaves) {
                myNode->chaves[j] = myNode->chaves[j + 1];
                myNode->filhos[j] = myNode->filhos[j + 1];
                j++;
        }
        myNode->num_chaves--;
        free(x1);
  }

  /* adjusts the given node */
  void adjustNode(Btree *myNode, int pos) 
  {
        if (!pos) 
		{
                if (myNode->filhos[1]->num_chaves > MIN_OCUP) 
				{
                        doLeftShift(myNode, 1);
                } else {
                        mergeNodes(myNode, 1);
                }
        } else {
                if (myNode->num_chaves != pos) {
                        if(myNode->filhos[pos - 1]->num_chaves > MIN_OCUP) {
                                doRightShift(myNode, pos);
                        } else {
                                if (myNode->filhos[pos + 1]->num_chaves > MIN_OCUP) {
                                        doLeftShift(myNode, pos + 1);
                                } else {
                                        mergeNodes(myNode, pos);
                                }
                        }
                } else {
                        if (myNode->filhos[pos - 1]->num_chaves > MIN_OCUP)
                                doRightShift(myNode, pos);
                        else
                                mergeNodes(myNode, pos);
                }
        }
  }

    /* shifts value from parent to right child */
  void doRightShift(Btree *myNode, int pos) 
  {
        Btree *x = myNode->filhos[pos];
        int j = x->num_chaves;

        while (j > 0) {
                x->chaves[j + 1] = x->chaves[j];
                x->filhos[j + 1] = x->filhos[j];
        }
        x->chaves[1] = myNode->chaves[pos];
        x->filhos[1] = x->filhos[0];
        x->num_chaves++;

        x = myNode->filhos[pos - 1];
        myNode->chaves[pos] = x->chaves[x->num_chaves];
        myNode->filhos[pos] = x->filhos[x->num_chaves];
        x->num_chaves--;
        return;
  }

  /* shifts value from parent to left child */
  void doLeftShift(Btree *myNode, int pos)
  {
        int j = 1;
        Btree *x = myNode->filhos[pos - 1];

        x->num_chaves++;
        x->chaves[x->num_chaves] = myNode->chaves[pos];
        x->filhos[x->num_chaves] = myNode->filhos[pos]->filhos[0];

        x = myNode->filhos[pos];
        myNode->chaves[pos] = x->chaves[1];
        x->filhos[0] = x->filhos[1];
        x->num_chaves--;

        while (j <= x->num_chaves) {
                x->chaves[j] = x->chaves[j + 1];
                x->filhos[j] = x->filhos[j + 1];
                j++;
        }
        return;
  }

  /* B-Tree Traversal */
  void traversal(Btree *myNode) 
  {
        int i;
        if (myNode)
		{

            for (i = 0; i < myNode->num_chaves; i++)
			{

                traversal(myNode->filhos[i]);
                printf("%d ", myNode->chaves[i + 1]);
            }
            traversal(myNode->filhos[i]);
        }
  }
