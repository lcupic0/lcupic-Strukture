/*
Program koji omogucava rad s binarnim stabl.pretrz.
Treba napraviti unos novog elementa, ispis elemenata, brisanje i pronalazenje nekog elementa.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct cvorStabla* Position;
typedef struct cvorStabla* Stablo;
typedef struct cvorStabla {
	int El;
	Position L;
	Position R;
}Cvor;

Stablo unosElementa(int X, Position root);
Stablo deleteElement(int X, Position root);
Position findElement(int X, Position root);
Position findMin(Position root);
int InOrder(Position root);
int PostOrder(Position root);
int PreOrder(Position root);
//int scanDat()


int main()
{
	Stablo root = NULL;
	int element = 0;
	int odabir;
	FILE* dat = NULL;

	dat = fopen("brojevi.txt", "r");
	if (dat == NULL)
		printf("Datoteka sa elementima se nije uspješno otvorila!\n");

	while (!feof(dat))
	{
		fscanf(dat, "%d", &element);    
		root=unosElementa(element, root);
	}

	deleteElement(6, root);

	printf("\tIspis stabla\n");
	printf("1-InOrder, 2-PostOrder, 3-PreOrder, 4-Izlaz\n");
	scanf("%d", &odabir);
	while (1) {
		switch (odabir) {

		case 1:
			InOrder(root);
			puts("\n");
			break;
		case 2:
			PostOrder(root);
			puts("\n");
			break;
		case 3:
			PreOrder(root);
			puts("\n");
			break;
		default:
			printf("Krivi odabir!\n");
			puts("\n");
			break;
		}
		scanf("%d", &odabir);
		if (odabir == 4)
			break;
	}

	return 0;
}

Stablo unosElementa(int X, Position Tree) {

	if (NULL == Tree)
	{
		Tree = (Position)malloc(sizeof(Cvor));
		Tree->El = X;
		Tree->L = NULL;
		Tree->R = NULL;
		return Tree;
	}

	if (X > Tree->El) {
		Tree->R = unosElementa(X, Tree->R);
		return Tree;
	}

	if (X < Tree->El) {
		Tree->L = unosElementa(X, Tree->L);
		return Tree;
	}

}

Position findElement(int X, Position root) {

	if (NULL == root)
		return NULL;
	else if (X > root->El)
		return findElement(X, root->R);
	else if (X < root->El)
		return findElement(X, root->L);
	else
		return root;
}

Position findMin(Position root) {
	if (NULL == root)
		return NULL;
	else if (NULL == root->El)
		return NULL;
	else
		return findMin(root->L); // Jer su najmanji clanovi na pozicija->L!
}

//InOrder - pratit redoslijed.
int InOrder(Position root) {
	if (NULL == root)
		return;
	InOrder(root->L);
	printf("%d ", root->El);
	InOrder(root->R);
}

int PreOrder(Position root)
{
	if (NULL == root)
		return;
	printf("%d ", root->El);
	PreOrder(root->L);
	PreOrder(root->R);
}

int PostOrder(Position root)
{
	if (NULL == root)
		return;
	PostOrder(root->L);
	PostOrder(root->R);
	printf("%d ", root->El);
}

Stablo deleteElement(int X, Position root) {

	Position temp = NULL;
	if (NULL == root)
		printf("Vas element ne postoji!\n");
	else if (X < root->El)
		root->L = deleteElement(X, root->L);
	else if (X > root->El)
		root->R = deleteElement(X, root->R);
	else if (root->L != NULL && root->R != NULL)
	{
		temp = findMin(root->R);
		root->El = temp->El;
		root->R = deleteElement(root->El, root->R);
	}
	else
	{
		temp = root;
		if(NULL == root->R)
		{
			root = root->L;
			free(temp);
		}

	}

	return root;
}