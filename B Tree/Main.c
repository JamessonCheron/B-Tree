#define _CRT_SECURE_NO_WARNINGS

#include "b_tree.h"

int inserirValor();
int menu( );
void opcao( Btree *btree, int op);
void linha();

int main()
{
	int opt;
	Btree *arvereB = NULL;
	
	do{
		opt = menu();
		opcao(arvereB, opt);
	}while(opt);
	
	return 0;
}

int inserirValor(){
	int valor;
	printf("Digite um valor: ");
	scanf("%i", &valor);
	return valor;
}

int menu( )
{
	int opt;
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>[  Binary Tree ]<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	linha();	
	printf("0. Sair\n");
	printf("1. Adicionar registro\n");
	printf("2. Consultar\n");
	printf("3. Exibir\n");
	printf("4. Remover registro\n");
	linha();
	printf("Escolha uma opcao: "); fflush(stdin); scanf("%d", &opt);
	
	return opt;
}

void opcao(Btree *btree, int op)
{

	switch(op)
	{
		case 0:
			return;
			break;
			
		case 1:
			insere_avoreB( btree, inserirValor());
			break;
		
		case 2:
			//printf("Funcinou!! :)\n");
			break;

		case 3:
			//Remove();
			break;
		
		case 4:
			//show_contact(Search());
			break;		
		
		default:
			printf("Comando invalido\n\n");
	}
	system("pause");
	system("cls");

}

void linha()
{

	int i;
    for (i=1;i<=80;i++)
        printf("_");
    printf("\n");
}