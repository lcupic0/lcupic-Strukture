#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// In case sscanf has successfully read %d and nothing else, it would return 1 (one parameter has been assigned). If there were characters before a number, it would return 0 !
typedef struct Cvor* Position;

typedef struct Cvor {
	int El;
	Position next;
}Data;

int Push(Position S, int i);
int Pop(Position S, Position first);
int printStack(Position S);
int deleteAll(Position S);

int main()
{
	
	char* buffer = NULL; buffer = (char*)malloc(100 * sizeof(char));
	Position stack; stack = (Position)malloc(sizeof(Data));	stack->next = NULL;
	int i = 0, value = 0, counter = 0, digit;

	int a, b, result;
	char operator;
	// -------------------------------------------------------------------------//

	FILE* postfiks = fopen("postfiks.txt", "r");
	if (postfiks == NULL)
		printf("Datoteka sa postfiks izrazom se nije uspjesno otvorila!\n");

	fgets(buffer, 100, postfiks);

	//Postupak računanja postfiksa
	while (*buffer != '\0')
	{
		value = sscanf(buffer, "%d%n", &digit, &counter);

		if (value==1) // jer ne vraca striktno 1 ako je ucita broj, nego vraca neki broj.
		{		   
			Push(stack, digit);
		}

		if (value == 0 || value == -1)
		{
			sscanf(buffer, " %c", &operator); //pripaziti na ovaj razmake!
			a = Pop(stack, stack->next);
			b = Pop(stack, stack->next);

			switch (operator)
			{

			case '+':
				result = a + b;
				Push(stack, result);
				break;
			case '-':
				result = a - b;
				Push(stack, result);
				break;
			case '*':
				result = a * b;
				Push(stack, result);
				break;
			case '/':
				result = a / b;
				Push(stack, result);
				break;
			}
		}

		buffer += counter;

	}



	//ISPIS REZULTATA
	printf("Ispis stoga(rezultata): ");
	printStack(stack->next);

	//BRISANJE STOGA IZ MEMORIJE
	printf("Brisanje stoga!\n");
	deleteAll(stack);
	printStack(stack->next);

	system("pause");
	return 0;
}

int Push(Position head, int x) { //first - samo pokazivac na prvi element, nema podataka. -> bolje radit sa HEADOM.

	Position new = NULL;

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

	return temp->El;

	free(temp);
}

int printStack(Position first) { // S mora biti adresa prvog clana, a ne heada!

	while (first != NULL) {

		printf("%d \n", first->El);
		first = first->next;
	}

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