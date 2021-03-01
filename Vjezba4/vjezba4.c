#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct _polinom;
typedef struct _polinom* Position;
typedef struct _polinom {
	int coef;
	int exp;
	Position Next;
}Polinom;

int scanDat(Position, Position);
int sortUnos(Position, Position);
int printList(Position);
int unosEnd(Position head, Position p);
Position makeNode(int Coef, int Exp);
Position zbrajanjePol(Position, Position);
Position mnozenjePol(Position, Position);
int deleteAll(Position);

int main() {

	Position polinom1 = NULL;
	Position polinom2 = NULL;
	Position zbroj = NULL;
	Position umnozak = NULL;
	polinom1 = (Position)malloc(sizeof(Polinom));
	polinom1->Next = NULL;
	polinom2 = (Position)malloc(sizeof(Polinom));
	polinom2->Next = NULL;

	scanDat(polinom1, polinom2);

	printList(polinom1);
	printList(polinom2);

	zbroj = zbrajanjePol(polinom1, polinom2);
	printList(zbroj);
	umnozak = mnozenjePol(polinom1, polinom2);
	printList(umnozak);

	deleteAll(polinom1);
	deleteAll(polinom2);
	deleteAll(zbroj);
	deleteAll(umnozak);

	return 0;
}

int unosEnd(Position head, Position p) {

	if (head->Next == NULL) {
		p->Next = head->Next;
		head->Next = p;
		return 1;
	}

	while (head->Next != NULL)
		head = head->Next;

	p->Next = head->Next;
	head->Next = p;

	return 1;
}

Position mnozenjePol(Position pol1, Position pol2) {

	Position r = NULL;
	Position pol2pocetak;
	Position head = (Position)malloc(sizeof(Polinom));
	head->coef = 0; head->exp = 0; head->Next = NULL;

	if (pol1 != NULL)
		pol1 = pol1->Next;

	pol2pocetak = pol2;
	while (pol1 != NULL) {

		while (pol2->Next != NULL) {
			r = makeNode(pol1->coef * pol2->Next->coef, pol1->exp + pol2->Next->exp);
			sortUnos(head, r);
			pol2 = pol2->Next;
		}

		pol2 = pol2pocetak;
		pol1 = pol1->Next;
	}

	return head;
}

Position zbrajanjePol(Position pol1, Position pol2) {

	Position r = NULL;

	Position head;
	head = (Position)malloc(sizeof(Polinom));
	head->coef = 0;
	head->exp = 0;
	head->Next = NULL;

	if (pol1 != NULL && pol2 != NULL) {

		pol1 = pol1->Next;
		pol2 = pol2->Next;
	}

	while (pol1 != NULL && pol2 != NULL) {

		if (pol1->exp == pol2->exp) {
			if (pol1->coef + pol2->coef != 0)
				r = makeNode(pol1->coef + pol2->coef, pol1->exp);

			sortUnos(head, r);
			pol1 = pol1->Next;
			pol2 = pol2->Next;
			continue;
		}

		if (pol1->exp > pol2->exp) {
			r = makeNode(pol1->coef, pol1->exp);
			sortUnos(head, r);
			pol1 = pol1->Next;
			if (pol1 == NULL) {
				r = makeNode(pol2->coef, pol2->exp);
				unosEnd(head, r);
				pol2 = pol2->Next;
			}
			continue;
		}

		if (pol1->exp < pol2->exp) {
			r = makeNode(pol2->coef, pol2->exp);
			sortUnos(head, r);
			pol2 = pol2->Next;
			if (pol2 == NULL) {
				r = makeNode(pol1->coef, pol1->exp);
				unosEnd(head, r);
				pol1 = pol1->Next;
			}

		}
	}

	return head;
}

Position makeNode(int Coef, int Exp) {
	Position p = NULL;

	p = (Position)malloc(sizeof(Polinom));
	p->Next = NULL;
	p->coef = Coef;
	p->exp = Exp;

	return p;
}

int printList(Position polinom) {

	if (polinom->Next == NULL) {
		printf("Lista je prazna!\n");
		return 0;
	}

	while (polinom->Next != NULL)
	{
		printf("%d-%d ", polinom->Next->coef, polinom->Next->exp);
		polinom = polinom->Next;
	}
	printf("\n");
	return 1;
}

int sortUnos(Position polinom, Position p) {

	if (polinom->Next == NULL) {
		p->Next = polinom->Next;
		polinom->Next = p;
		return 1;
	}

	while (polinom->Next != NULL && polinom->Next->exp > p->exp)
	{
		polinom = polinom->Next;
	}

	p->Next = polinom->Next;
	polinom->Next = p;

	return 1;
}

int scanDat(Position head1, Position head2) {

	int Coef, Exp;
	Position p;
	FILE* dat1;
	FILE* dat2;
	dat1 = fopen("datoteka1.txt", "r");
	dat2 = fopen("datoteka2.txt", "r");

	while (!feof(dat1)) {
		fscanf(dat1, "%d %d", &Coef, &Exp);
		p = (Position)malloc(sizeof(Polinom));
		p->coef = Coef;
		p->exp = Exp;
		p->Next = NULL;
		sortUnos(head1, p);
	}
	fclose(dat1);

	while (!feof(dat2)) {
		fscanf(dat2, "%d %d", &Coef, &Exp);
		p = (Position)malloc(sizeof(Polinom));
		p->coef = Coef;
		p->exp = Exp;
		p->Next = NULL;
		sortUnos(head2, p);
	}
	fclose(dat2);

	return 1;
}

int deleteAll(Position p) {

	Position temp;

	if (p->Next == NULL) {
		printf("Nemam sta brisat, lista je vec prazan!\n");
		return 1;
	}

	while (p->Next != NULL) {
		temp = p->Next;
		p->Next = temp->Next;
		free(temp);
	}

	return 1;
}