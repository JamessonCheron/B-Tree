#define _CRT_SECURE_NO_WARNINGS

#include "b_tree.h"

struct Node
{
	int num_chaves;
	int chaves[MAX_CHAVES];
	struct Btree *filhos[MAZ_FILHOS];

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
		return raiz;
	}
	else
	{
		pos = busca_binaria(raiz, info);

		if (raiz->num_chaves > pos && raiz->chaves[pos] == info)
		{
			printf("Chave ja contida na Arvore");
			*h = 0;
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
					temp = (Btree *)malloc(sizeof(Btree));
					temp->num_chaves = 0;
					//incicializa filhos com NULL
					for (i = 0; i < MAZ_FILHOS; i++)
					{
						temp->filhos[i] = NULL;
					}

					//elemento mediano que vai subir para o pai
					info_mediano = raiz->chaves[MIN_OCUP];

					//insere metade do nó raiz no temp (edetua subdivisão)
					temp->filhos[0] = raiz->chaves[MIN_OCUP + 1];

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
		nova_raiz = (Btree *)malloc(sizeof(Btree));
		nova_raiz->num_chaves = 1;
		nova_raiz->chaves[0] = info_retorno;
		nova_raiz->filhos[0] = raiz;
		nova_raiz->filhos[1] = filho_dir;

		for (i = 2; i < MAX_CHAVES; i++)
		{
			nova_raiz->filhos[i] = NULL;
		}

	}
	else
	{
		return raiz;
	}
}