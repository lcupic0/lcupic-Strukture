/*
5. Za dvije sortirane liste L1 i L2 (mogu se pročitati iz datoteke ili unijeti ručno, bitno je
samo da su sortirane), napisati program koji stvara novu vezanu listu tako da računa:
a) L1 U L2 --> UNIJA
b) L1  L2 --> PRESJEK
Liste osim pokazivača na slijedeću strukturu imaju i jedan cjelobrojni element, po
kojem su sortirane
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct _list;
typedef struct _list* Position;

typedef struct _list {
	int El;
	Position Next;
}List;

int scanDat(Position head, FILE* dat);
int sortUnos(Position, Position);
Position unija(Position, Position);
Position presjek(Position, Position);

int main()
{
	List head1, head2;
	Position Unija, Presjek;
	head1.Next = NULL;
	head2.Next = NULL;

	FILE* dat1;
	FILE* dat2;

	dat1 = fopen("datoteka1.txt", "r");
	if (!dat1)
		printf("Datoteka 1 nije otvorena!\n");
	dat2 = fopen("datoteka2.txt", "r");
	if (!dat2)
		printf("Datoteka 1 nije otvorena!\n");

	scanDat(&head1, dat1);
	scanDat(&head2, dat2);

	printList(&head1); printList(&head2);

	printf("Unija: \n");
	Unija = unija(&head1, &head2);
	printList(Unija);

	printf("Presjek: \n");
	Presjek = presjek(&head1, &head2);
	printList(Presjek);

	return 0;
}

int scanDat(Position head, FILE* dat) {

	char buffer[10];
	int brojac = 0;
	Position p;

	while (fgets(buffer, 10, dat)) {
		if (buffer[0] != '\n')
			brojac++;
	}
	rewind(dat);

	for (int i = 0; i < brojac; i++) {
		p = (Position)malloc(sizeof(List));
		fscanf(dat, "%d", &p->El);
		p->Next = NULL;
		sortUnos(head, p);
	}

	fclose(dat);

	return 1;
}

int sortUnos(Position head, Position p) {

	if (head->Next == NULL) {
		p->Next = head->Next;
		head->Next = p;
		return 1;
	}

	while (head->Next != NULL && head->Next->El < p->El)
		head = head->Next;

	p->Next = head->Next;
	head->Next = p;

	return 1;
}

int printList(Position p) {

	if (p->Next == NULL) {
		printf("Vasa lista je prazna!\n");
		return 1;
	}

	while (p->Next != NULL) {
		p = p->Next;
		printf("%d ", p->El);
	}
	printf("\n");

	return 1;
}

Position unija(Position p1, Position p2) {

	Position head, temp;
	head = (Position)malloc(sizeof(List));
	head->Next = NULL;
	p1 = p1->Next;
	p2 = p2->Next;

	while (p1 != NULL || p2 != NULL) {

		if (p1->El == p2->El) {
			temp = (Position)malloc(sizeof(List));
			temp->El = p1->El;
			sortUnos(head, temp);

			p1 = p1->Next;
			p2 = p2->Next;
		}
		else if (p1->El > p2->El) {

			temp = (Position)malloc(sizeof(List));
			temp->El = p2->El;
			sortUnos(head, temp);

			p2 = p2->Next;
		}
		else {

			temp = (Position)malloc(sizeof(List));
			temp->El = p1->El;
			sortUnos(head, temp);

			p1 = p1->Next;
		}

		if (p1 == NULL) {

			while (p2 != NULL)
			{
				temp = (Position)malloc(sizeof(List));
				temp->El = p2->El;
				sortUnos(head, temp);
				p2 = p2->Next;
			}

		}

		if (p2 == NULL) {

			while (p1 != NULL)
			{
				temp = (Position)malloc(sizeof(List));
				temp->El = p1->El;
				sortUnos(head, temp);
				p1 = p1->Next;
			}

		}

	}

	return head;
}

Position presjek(Position p1, Position p2) {

	Position Presjek;
	Position temp;
	Position new;
	Presjek = (Position)malloc(sizeof(List));
	Presjek->Next = NULL;


	p2 = p2->Next;
	temp = p2;
	p1 = p1->Next;
	while (p1 != NULL) {

		while (p2 != NULL)
		{
			if (p1->El == p2->El) {
				new = (Position)malloc(sizeof(List));
				new->El = p1->El;
				sortUnos(Presjek, new);
			}

			p2 = p2->Next;
		}
		p2 = temp;
		p1 = p1->Next;
	}

	return Presjek;
}