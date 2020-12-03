#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct element;
typedef struct element* Position;

int scanDat(FILE*, Position);
int brojacKoef(FILE*);
int unosBeg(Position, Position);
int sortUnos(Position, Position);
Position unijaLista(Position, Position);
Position presjekLista(Position, Position, int, int);

typedef struct element {
	int coef;
	Position next;
}Element;

int main()
{
	Element head1, head2;
	head1.next = NULL; head1.coef = 0;
	head2.next = NULL; head2.coef = 0;

	Position unija = NULL, presjek = NULL;

	FILE* dat1;
	FILE *dat2;

	dat1 = fopen("datoteka1.txt", "r");
	if (dat1 == NULL)
		printf("Datoteka nije uspjesno otvorena!\n");
	dat2 = fopen("datoteka2.txt", "r");
	if (dat2 == NULL)
		printf("Datoteka nije uspjesno otvorena!\n");

	int brojac1 = brojacKoef(dat1);
	int brojac2 = brojacKoef(dat2);

	//ucitavanje listi
	scanDat(dat1, &head1);
	scanDat(dat2, &head2);

	//unijaLista
	unija = unijaLista(&head1, &head2);

	//test print
	printf("Lista 1:\n");
	printList(&head1);
	printf("Lista 2:\n");
	printList(&head2);

	printf("Unija lista:\n");
	printList(unija);

	printf("Presjek lista:\n");
	presjek = presjekLista(&head1, &head2, brojac1, brojac2);
	printList(presjek);

	system("pause");
	return 0;
}

int brojacKoef(FILE* dat) { //provjera ne triba jer je u skenu napravljena
	char niz[50];
	int brojac = 0;

	while (fgets(niz, 50, dat) != NULL)
	{
		if (niz[0] != '\n')
			brojac++;
	}
	rewind(dat);
	//fclose(dat); -- ne smimo zatvorit datoteku jer je kasnije opet kroistimo pa zato koristim REWIND!
	return brojac;
}

int sortUnos(Position what, Position where) { //where ce bit adresa od heada
											  //what - koeficijent - JEDNA KUĆICA ajmo reć

	while (where->next != NULL && what->coef < where->next->coef) //where->next != NULL ?
		where = where->next;

	what->next = where->next;
	where->next = what;

	return 0;

}


int scanDat(FILE* dat, Position head) { //p je adresa od heada

	Position p;
	int coef = 0, brojac = 0, i;

	brojac = brojacKoef(dat);

	//stvaranje liste
	for (i = 0; i < brojac; i++)
	{
		fscanf(dat, "%d", &coef);

		p = (Position)malloc(sizeof(Element));
		p->coef = coef;
		p->next = NULL;

		sortUnos(p, head);
	}

	fclose(dat);
	return 0;
}

int unosEnd(Position what, Position where) {

	while (where->next != NULL)
		where = where->next;

	what->next = where->next;
	where->next = what;

	return 0;
}

int unosBeg(Position what, Position where) {

	what->next = where->next;
	where->next = what;

	return 0;
}

int printList(Position head) {

	head = head->next; // NE ZABORAVLJAT NA OVO - ili slat adresu prvog clana!!!
	while (head != NULL) {
		printf("%d \n", head->coef);
		head = head->next;
	}
	return 0;
}

Position unijaLista(Position head1, Position head2) {
	Position head;
	Position r;

	head = (Position)malloc(sizeof(Element));
	head->coef = 0;
	head->next = NULL;

	while (head1->next != NULL && head2->next != NULL) {

		if (head1->next->coef == head2->next->coef) { // U slucaju istih exp, zbroji koef i postavi exp
			r = (Position)malloc(sizeof(Element));
			r->coef = head1->next->coef;
			sortUnos(r, head);
			head1 = head1->next;
			head2 = head2->next;
			if (head1->next == NULL)
			{
				r->coef = head2->next->coef; // OVO NECE RADITI jer smo već koristili r!
				unosEnd(r, head);
			}

			if (head2->next == NULL)
			{
				head1 = head1->next;
				unosEnd(head1, head);
			}

			continue;
		}

		if (head1->next->coef > head2->next->coef) {
			r = (Position)malloc(sizeof(Element));
			r->coef = head1->next->coef;
			sortUnos(r, head);
			head1 = head1->next;
			if (head1->next == NULL)
			{
				r->coef = head2->next->coef;
				unosEnd(r, head);
			}
			continue;
		}

		if (head2->next->coef > head1->next->coef) { // U slucaju da je jedan veci od drugoga u r zapisi veci i makni mu pokaziva na iduci clan
			r = (Position)malloc(sizeof(Element));
			r->coef = head2->next->coef;
			sortUnos(r, head);
			head2 = head2->next;
			if (head2->next == NULL)
			{
				head1 = head1->next;
				unosEnd(head1, head);
			}
		}

	}


	return head;
}

Position presjekLista(Position head1, Position head2, int brojac1, int brojac2) {

	int i, j;
	Position presjek = NULL;
	Position head, pom;
	head = (Position)malloc(sizeof(Element));
	head->next = NULL; head->coef = 0;
	pom = head2;

	for (i = 0;i < brojac1;i++) {

		for (j = 0;j < brojac2;j++) {

			if (head1->next->coef == head2->next->coef) {
				presjek = (Position)malloc(sizeof(Element));
				presjek->coef = head1->next->coef;
				sortUnos(presjek, head);
			}
			head2 = head2->next;
		}
		head1 = head1->next;
		head2 = pom;
	}

	return head;
}