#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//Dodavanje elementa na pocetak stoga je puno brzi od dodavanja na kraj.

typedef struct Cvor* Position;

typedef struct Cvor {
	int El;
	Position next;
}Stog;

void Push(int El, Position S);
int Pop(Position S);

int main()
{
	Position first = NULL;




	return 0;
}

void Push(int x, Position first) {

	Position new = NULL;

	new = (Position)malloc(sizeof(Stog));
	new->El = x;
	new->next = first;
	first = new;

}

int Pop(Position first) {
	Position temp;

	temp = first;
	first = first->next;
	free(temp);

	return 0;
}