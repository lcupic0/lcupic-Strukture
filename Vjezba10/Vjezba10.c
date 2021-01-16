#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DATA_SIZE (11)
#define FILE_NAME_SIZE (324)

// 1. Struktura ČVORA
struct _treeNode;
typedef struct _treeNode* PositionT;
typedef struct _treeNode {
	PositionT left;
	PositionT right;
	char data[DATA_SIZE];
}TreeNode;
// 2. Struktura STOGA
struct _listNode;
typedef struct _listNode* PositionL;
typedef struct _listNode {
	PositionT treeNode;
	PositionL next;
}ListNode;

PositionT createNode(char* data); // 1
int pushFront(PositionL head, PositionT treeNode); //2
PositionT popFront(PositionL haed); //3
PositionT readFromFile(char* filename);//4
int isNumber(char* data);// 4 - ovo smo dodali tokom 4. koraka
char* printInOrder(PositionT current, char* data); // Zadnje
//void printInFile(PositionT current, FILE* dat);
void openInFixFile(char *InFix);

int main()
{
	char filename[FILE_NAME_SIZE] = { 0 };
	PositionT root = NULL;
	char InFix[256] = { 0 };
	char* InFixPok = NULL;

	printf("Insert file name: \n");
	scanf(" %s", filename);

	root = readFromFile(filename);
	InFixPok = printInOrder(root, InFix);

	openInFixFile(InFixPok);

	return 0;
}

//
//void printInFile(PositionT current, FILE* dat) { // Previse puta se salje datoteka pa nije dobro.
//
//	fprintf(dat, "(");
//	printInFile(current->left,dat); // Lijevo podstablo
//	fprintf(dat, "%s", current->data);
//	printInFile(current->right,dat);
//	fprintf(dat, ")");
//}

void openInFixFile(char *InFix) {
	FILE* dat = NULL;
	dat = fopen("infix.txt", "w");
	if (!dat) {
		printf("Infix file doesn't exist!\n");
		return;
	}
	
	fprintf(dat, InFix);
}

char* printInOrder(PositionT current, char* InFix) {
	if (NULL == current) return; // Di nas ovo returna?

	printf("(");
	strcat(InFix, "(");

	printInOrder(current->left, InFix);

	strcat(InFix, current->data);
	printf(" %s", current->data);
	
	printInOrder(current->right, InFix);

	strcat(InFix, ")");
	printf(")");

	return InFix;
}


//Ukoliko sscanf očekuje jedan broj i dobije ga u bufferu, vratit će rezultat 1.
//Ukoliko sscanf očekuje jedan broj i dobije + u bufferu, vratit će 0 ili - 1 (EOF).
int isNumber(char* data) {
	int number = 0;

	if (sscanf(data, " %d", &number) == 1) return 1;

	return 0;
}

PositionT readFromFile(char* filename) {

	FILE* fp = NULL;
	PositionT result = NULL;
	ListNode head; // Al ode ne bi triba ic PositionL??
	head.next = NULL;
	// Bolje je radit ove puste provjere jer će nama bit lakše ako negdi pukne program i nađemo ga DEBUGGEROM!
	fp = fopen(filename, "r");
	if (!fp) {
		printf("File doesnt exist or you dont have permissions!\r\n");
		return NULL;
	}

	while (!feof(fp)) {
		PositionT node = NULL;
		char data[DATA_SIZE] = { 0 };

		fscanf(fp, " %s", data);

		if (strlen(data) == 0) { //radi razmaka
			break;
		}

		node = createNode(data);

		if (!node) {
			fclose(fp);
			return NULL;
		}

		if (isNumber(data)) {
			pushFront(&head, node);
		}
		else {
			node->right = popFront(&head);
			if (!node->right) {
				printf("Postfix written in file %s is not good", filename);
				fclose(fp);
				return NULL;
			}

			node->left = popFront(&head);

			if (!node->left) {
				printf("Postfix written in file %s is not good", filename);
				fclose(fp);
				return NULL;
			}
			pushFront(&head, node);
		}

	}

	fclose(fp);
	result = popFront(&head);

	if (!result) {
		printf("Postfix written in file %s is not good", filename);
		return NULL;
	}

	if (popFront(&head) != NULL) { //ispravak, ode ne stavljamo if (result = popFront(&head) != NULL) jer ćemo onda vratit NULL u main!
		printf("Postfix written in file %s is not good", filename);
		return NULL;
	}

	return result;
}

int pushFront(PositionL head, PositionT treeNode) {
	PositionL node = NULL;
	node = (PositionL)malloc(sizeof(ListNode));

	if (!node) {
		printf("Memory allocation failed!\n");
		return -1;
	}

	node->treeNode = treeNode;
	node->next = head->next;
	head->next = node;

	return 0;
}

PositionT popFront(PositionL head) {
	PositionL first = head->next;
	PositionT result = NULL;

	if (!first) {
		return NULL;
	}

	result = first->treeNode;
	head->next = first->next;

	free(first);
	return result;

}

PositionT createNode(char* data) {
	PositionT node = NULL;
	node = (PositionT)malloc(sizeof(TreeNode));

	if (!node) {
		printf("Memory allocation failed!\n");
		return NULL;
	}
	node->left = NULL;
	node->right = NULL;
	strcpy(node->data, data);

	return node;
} 

/*
char* mirko(char* b); // Znaci bez obzira na to da li je pokazivač uvik moramo imati RETURN ako zelimo u mainu prominit vrijednost ovoga sta smo poslali kao argument!

int main()
{
	char* niz;
	niz = "Mirko";

	niz = mirko(niz);

	printf("%s", niz);

	return 0;
}

char* mirko(char* b) {
	b = "Jovo";
	return b;
}
*/