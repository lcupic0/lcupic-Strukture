/*
	md - napravi novi direktorij
	cd - pribaci se na neki drugi direktorij
	cd .. - vrati se u prethodni direktorij
	dir - ispis sadrzaja direktorija
	exit - da nas izbaci iz programa
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME_LENGTH (256)

typedef enum _enum {
	ALLOCATION_FAILED,
	SUCCESS,
	DUPLICATED_DIRECTORY
}Result;

struct _dir;
typedef struct _dir* PositionDir;
typedef struct _dir {
	char name[MAX_NAME_LENGTH];
	PositionDir child;
	PositionDir sibling;
}Dir;

struct _stack;
typedef struct _stack* PositionStack;
typedef struct _stack {
	PositionDir dir;
	PositionDir next;
}Stack;

void pushDirectory(PositionStack stack, PositionDir dir);
PositionDir popDirectory(PositionStack stack);
void deleteTree(PositionDir first);
PositionDir createDirectory(char *name);
PositionDir findDirectory(PositionDir current, char* name);
Result makeDirectory(PositionDir current, char* name);
PositionDir findPrev(PositionDir current, char* name);
Result printDir(PositionDir current);


int main()
{
	int izbor = 0; 
	char name[MAX_NAME_LENGTH];
	PositionDir mainDir = NULL;
	mainDir = createDirectory("C:");

	PositionDir current = mainDir;

	PositionStack stack = NULL; 

	// Izbornik

	printf("\t\tIZBORNIK\n");
	printf("- Kreiranje novog direktorija (md): 0\n");
	printf("- Promjena direktorija (cd): 1\n");
	printf("- Povratak u prethodni direktorij (cd..): 2\n");
	printf("- Ispisivanje sadrzaja direktorija (dir): 3\n");
	printf("- Beginning: 4\n");
	printf("- Exit: 5\n");

	while (1) {

		scanf("%d", &izbor);
		if (izbor == 5)
			break;

		switch (izbor) 
		{

			case 0:
				printf("Unesite ime novog direktorija: \n");
				scanf(" %s", &name);
				makeDirectory(current, name);
				break;

			case 1:
				printf("Unesite ime direktorija na koji zelite ici: \n");
				scanf(" %s", &name);
				pushDirectory(stack, current);
				current = findDirectory(current, name);
				printf("Trenutno: %s", current->name);
				break;

			case 2:
				current = popDirectory(stack);
				printf("Trenutno: %s", current->name);
				break;

			case 3:
				printDir(current);
				break;

			case 4:
				current = mainDir;
				printf("Trenutno: %s", current->name);
				break;

			case 5:
				printf("Izabrali ste izlaz iz menu-a!\n");
				break;

			default:
				printf("Unijeli ste krivu opciju!\n");

		}

	}


	deleteTree(mainDir);

	return EXIT_SUCCESS;
}

void pushDirectory(PositionStack stack, PositionDir dir) {

	PositionStack new = (PositionStack)malloc(sizeof(Stack));

	new->dir = dir;
	new->next = stack->next;
	stack->next = new;
}

PositionDir popDirectory(PositionStack stack) {

	PositionDir directory = NULL;
	PositionStack first = stack->next;

	if (NULL == first)
		return NULL;

	directory = first->dir;

	stack->next = first->next;
	free(first);

	return directory;
}

void deleteTree(PositionDir first) {
	if (NULL == first) return;
	deleteTree(first->sibling);
	deleteTree(first->child);
	free(first);
}

PositionDir createDirectory(char* name) {

	PositionDir newDir = NULL;
	newDir = (PositionDir)malloc(sizeof(Dir));
	if (NULL == newDir)
		printf("Memory allocation FAILED!\n");

	strcpy(newDir->name, name);
	newDir->sibling = NULL;
	newDir->child = NULL;

	return newDir;
}

PositionDir findDirectory(PositionDir current, char* name) {

	PositionDir child = current->child;
	if (NULL == child)
		return NULL;

	while (NULL != child && strcmp(child->name, name) != 0)
		child = child->sibling;

	return child;
}

PositionDir findPrev(PositionDir mainDir, char* name) {

	PositionDir child = mainDir->child;

	while (child->sibling->name != name)
		child = child->sibling;

}

Result makeDirectory(PositionDir current, char* name) {

	PositionDir el = NULL;
	PositionDir child = NULL;

	// 1) Da li vec postoji direktorij s ovim imenom
	if (findDirectory(current, name) != NULL) 
		return DUPLICATED_DIRECTORY;

	el = createDirectory(name);

	if (NULL == el) {
		printf("Memory allocation failed! md command FAILED!\n");
		return ALLOCATION_FAILED;
	}

	child = current->child;

	// 2) Slucaj kad nema drugih poddirektorija
	if (child == NULL) {
		child = el;
		current->child = child; // (( Ovo je 1. sta sam doda ))
		return SUCCESS;
	}

	// 3) Prvo provjeravamo prvi, onda sa whileom idemo na drugi slucaj ako prvi ne vridi

	if (strcmp(child->name, el->name) > 0) {	//strcmp vraca 0 ako su isti, - ako je prvi "manji" od drugoga, + obrnuto.
		current->child = el;
		el->sibling = child;
		return SUCCESS;
	}

	while (child->sibling != NULL && strcmp(child->sibling->name, el->name) < 0) {
		child = child->sibling;
	}

	el->sibling = child->sibling;
	child->sibling = el;

	return SUCCESS;
}

Result printDir(PositionDir current) {

	PositionDir child = current->child;

	if (child == NULL)
		printf("Direktorij je prazan!\n");

	while (child != NULL) {
		printf("\t%s\n", child->name);
		child = child->sibling;
	}


	return SUCCESS;
}