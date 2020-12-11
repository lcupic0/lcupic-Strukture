//LIFO
//FIFO
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct Cvor* Position;

typedef struct Cvor {
	int El;
	Position next;
}Data;

int Push(Position S);
int Pop(Position S, Position first);
int printStack(Position S);

Position PushRow(Position S, Position last);
int PopRow(Position S);

int deleteAll(Position S);

int main()
{
	Position stack;
	stack = (Position)malloc(sizeof(Data));
	stack->next = NULL;

	Position row;
	row = (Position)malloc(sizeof(Data));
	row->next = NULL;

	Position last = NULL;
	int i;
	srand(time(0));
	
	//Stack
	for (i = 0;i < 4;i++) {
		Push(stack);
	}
	Pop(stack, stack->next); // Jer zelimo slati prvi element, a ne head!

	printf("Ispis stoga: \n");
	printStack(stack->next); 
	last = row;
	//Row 
	for (i = 0;i < 4;i++) {
		last=PushRow(row, last); //Da ne vrtimo while uvik vracat cemo zadnjeg i uvik ga slat.
	}
	PopRow(row);
	
	printf("\nIspis reda: \n");
	printStack(row->next);

	printf("Brisanje stoga/reda: \n");
	deleteAll(stack); deleteAll(row);
	printStack(stack->next); printStack(row->next);

	return 0;
}

int Push(Position head) { //first - samo pokazivac na prvi element, nema podataka. -> bolje radit sa HEADOM.

	Position new = NULL;
	int x;

	x = 10 + rand() % 91;

	new = (Position)malloc(sizeof(Data));
	new->El = x;
	new->next = head->next;
	head->next = new;

	return 1;
}

int Pop(Position head, Position first) {
	Position temp;

	temp = first;
	head->next = first->next;
	first = first->next; // Nije bitan dio!
	free(temp);

	return 1;
}

int printStack(Position first) { // S mora biti adresa prvog clana, a ne heada!

	while (first!= NULL) {

		printf("%d \n", first->El);
		first = first->next;
	}

	return 0;
}

Position PushRow(Position S, Position last) { //Dodajemo na kraj, a skidamo s pocetka.

	int x;
	Position new = (Position)malloc(sizeof(Data));
	
	x = 10 + rand() % 91;
	/*
	//zadnji element
	while (S->next != NULL) {  ---> glupo je ovo korsitit jer svaki put vrtimo while pa nam nema smisla PRIPAZIT.
		S = S->next;
		last = S;
	} */

	new->El = x;
	new->next = last->next;
	last->next = new;
	last = new;

	return last;
}

int PopRow(Position row) {

	Position first;

	first = row->next;
	row->next = first->next;
	free(first);

	return 0;
}

int deleteAll(Position S) {

	Position Temp = NULL;

	while (S->next != NULL)
	{
		Temp = S->next;
		S->next = Temp->next;
		free(Temp);
	}

	return 0;
}