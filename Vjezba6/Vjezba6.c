/*
Napomena: Funkcija "push" sprema cijeli broj, slučajno generirani u opsegu od 10 - 100
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct _list;
typedef struct _list* Position;

typedef struct _list {
	int El;
	Position Next;
}Node;

int pushStack(Position p);
int popStack(Position p);
Position pushRow(Position p, Position last);
int popRow(Position p);
int printList(Position p);
int deleteAll(Position p);

int main()
{
	srand(time(0));

	Position lastInRow;
	Node Red;
	Red.Next = NULL;
	Node Stek;
	Stek.Next = NULL;

	// STACK

	for (int i = 0;i < 7;i++)
		pushStack(&Stek);
	printList(&Stek);

	for (int i = 0;i < 7;i++)
		popStack(&Stek);
	printList(&Stek);

	printf("\n\n");


	// ROW
	lastInRow = &Red;
	for (int i = 0;i < 7;i++)
		lastInRow = pushRow(&Red, lastInRow);
	printList(&Red);
	printf("\n");
	for (int i = 0;i < 7;i++)
		popRow(&Red);
	printList(&Red);

	deleteAll(&Red);
	printList(&Red);
	deleteAll(&Stek);
	printList(&Stek);

	return 0;
}

int pushStack(Position p) { //Dodajemo na pocetak.

	Position new;
	int x;

	x = 10 + rand() % (100 - 10 + 1);

	new = (Position)malloc(sizeof(Node));
	new->El = x;

	new->Next = p->Next;
	p->Next = new;

	return 1;
}

int popStack(Position p) {

	Position temp;

	if (p->Next == NULL) {
		printf("Stog/Red je prazan!\n");
		return -1;
	}

	temp = p->Next;
	p->Next = temp->Next;
	free(temp);

	return 1;
}

int printList(Position p) {

	if (p->Next == NULL)
	{
		printf("Lista je PRAZNA! \n");
		return -1;
	}
	//p = p->Next;
	while (p->Next != NULL) {
		printf("%d ", p->Next->El);
		p = p->Next;
	}


	return 1;
}

Position pushRow(Position p, Position last) { // Dodajemo na kraj, skidamo s pocetka.

	Position new = (Position)malloc(sizeof(Node));
	int x;
	x = 10 + rand() % 91;
	new->El = x; new->Next = NULL;

	if (p->Next == NULL) {
		new->Next = p->Next;
		p->Next = new;
		last = new;
		return last;
	}

	new->Next = last->Next;
	last->Next = new;
	last = new;

	return last;
}

int popRow(Position p) { // Skidam s pocetka.

	Position temp = p->Next;

	if (p->Next == NULL) {
		printf("Row is empty, can't pop!\n");
		return -1;
	}

	p->Next = temp->Next;
	printf("Pop: %d\n", temp->El);
	free(temp);

	return 1;
}

int deleteAll(Position p) {

	Position temp;
	if (p->Next = NULL)
	{
		printf("Lista je vec prazna!\n");
		return 1;
	}

	while (p->Next != NULL) {
		temp = p->Next;
		p->Next = temp->Next;
		free(temp);
	}

	printf("Red/Lista je izbrisan/a\n");

	return 1;
}