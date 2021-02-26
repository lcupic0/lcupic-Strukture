#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
10. Napisati program koji iz datoteke čita postfiks izraz i zatim stvara stablo proračuna. Iz
gotovog stabla proračuna upisati u datoteku infiks izraz.
*/

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
	char data[DATA_SIZE] = { 0 };
	while (!feof(fp)) {
		PositionT node = NULL;
		//char data[DATA_SIZE] = { 0 }; moz i ode bit - pa ce se uvik postavit na "" kod ucitavanja novog znaka iz datoteke.

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

	// Ovdje bi sada morao biti null kad popamo jer smo gore dignuli zadnji cvor(rezultat) pa bi sad stog trebao biti prazan odnosno NULL.
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

// tj. u ovim funkcijama moramo jer svugdje imamo uvjet if ( root = NULL), naravno da se vrijednost u mainu nece prominit ako po drugi put
// u funkciji pozivamo malloc, time mičemo adresu i tu se javlja problem!
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

// 2. NAČIN - ovdje koristimo SSCANF i drugaciji ispit funckije, nema nikakvog returna jer sve ide priko pokazivača!

/*
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define DATA_SIZE (11)

struct _tree;
typedef struct _tree* PositionT;
typedef struct _tree {
	char data[DATA_SIZE];
	PositionT L;
	PositionT R;
}Tree;

struct _stack;
typedef struct _stack* PositionS;
typedef struct _stack {
	PositionT treeNode;
	PositionS Next;
}Stack;

int pushStack(PositionS stack, PositionT node);
PositionT popStack(PositionS stack);
PositionT readFromFile(char* filename);
PositionT createNode(char* data);
void inOrder(PositionT tree, char*);

int main() {

	char filename[30];
	char* infix = (char*)malloc(100 * sizeof(char));
	PositionT stablo;
	PositionS stack;

	stack = (PositionS)malloc(sizeof(Stack));
	stack->Next = NULL;

	stablo = readFromFile("brojevi.txt");

	inOrder(stablo, infix);


	return 0;
}

void inOrder(PositionT tree, char* infix) {

	if (tree == NULL)
		return;

	printf("(");
	strcat(infix, "(");

	inOrder(tree->L, infix);

	printf("%s", tree->data);
	strcat(infix, tree->data);

	inOrder(tree->R, infix);

	printf(")");
	strcat(infix, ")");
}

PositionT createNode(char* data) {

	PositionT New;
	New = (PositionT)malloc(sizeof(Tree));
	strcpy(New->data, data);
	New->L = NULL;
	New->R = NULL;

	return New;
}

PositionT readFromFile(char* filename) {

	char* buffer = (char*)malloc(100 * sizeof(char));
	FILE* dat;
	char data[10] = { 0 };
	int broj, brojac = 0;
	int result;
	PositionT New;
	Stack stack;
	stack.Next = NULL;

	dat = fopen(filename, "r");
	if (!dat) {
		printf("Ne mogu otvoriti ulaznu datoteku, returning NULL!\n");
		return NULL;
	}
	fgets(buffer, 100, dat);
	while (*buffer != '\0') {

		result = sscanf(buffer, "%d%n", &data, &brojac);


		if (result == 1) {
			sscanf(buffer, " %s", data);
			New = createNode(data);
			pushStack(&stack, New);
		}

		if (result == 0 || result == -1) {
			sscanf(buffer, " %s", data);
			New = createNode(data);
			New->R = popStack(&stack);
			New->L = popStack(&stack);
			pushStack(&stack, New);
		}

		buffer = buffer + brojac;
	}
	return popStack(&stack);
}

int pushStack(PositionS stack, PositionT node) {

	PositionS temp;
	temp = (PositionS)malloc(sizeof(Stack));
	temp->treeNode = node;

	temp->Next = stack->Next;
	stack->Next = temp;

	return 1;
}

PositionT popStack(PositionS stack) {

	PositionT temp;
	PositionS first = stack->Next;

	if (first == NULL) {
		printf("Stack je prazan, popam NULL! \n");
		return NULL;
	}

	temp = first->treeNode;

	stack->Next = first->Next;
	free(first);

	return temp;
}
*/