#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//koeficijenti i eksponenti se citaju iz datoteke - u njoj ne moraju nuzno biti sortirani!

struct polinom;
typedef struct polinom* Position;

int scanDat(FILE*, Position);
int brojacKoef(FILE*);
int unosBeg(Position, Position);
int sortUnos(Position , Position);

typedef struct polinom {
	int coef;
	int exp;
	Position next;
}Polinom;

int main()
{
	Polinom head1, head2;
	Position zbroj = NULL;
	head1.next = NULL;
	head2.next = NULL;
	FILE* dat1;
	FILE* dat2;
	int coef, exp;
	//Datoteke
	dat1 = fopen("datoteka1.txt", "r");
	if (dat1 == NULL)
		printf("Datoteka nije uspjesno otvorena!\n");
	dat2 = fopen("datoteka2.txt", "r");
	if (dat2 == NULL)
		printf("Datoteka nije uspjesno otvorena!\n");

	//ucitavanje listi
	scanDat(dat1, &head1);
	scanDat(dat2, &head2);

	//test print
	printf("Lista 1:\n");
	printList(&head1);
	printf("Lista 2:\n");
	printList(&head2);

	zbroj = zbrajanjePol(&head1, &head2);

	printf("Zbroj polinoma: \n");
	printList(&zbroj);

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
		printf("%d %d\n", head->coef, head->exp);
		head = head->next;
	}
	return 0;
}

int scanDat(FILE *dat, Position head) { //p je adresa od heada

	Position p;
	int coef = 0, exp = 0, brojac = 0, i;

	brojac = brojacKoef(dat);

	//stvaranje liste
	for (i = 0; i < brojac; i++)
	{
		fscanf(dat, "%d %d", &coef, &exp);

		p = (Position)malloc(sizeof(struct polinom));
		p->coef = coef;
		p->exp = exp;
		p->next = NULL;

		sortUnos(p, head);
	}

	fclose(dat);
	return 0;
}

int sortUnos(Position what, Position where) { //where ce bit adresa od heada
											  //what - koeficijent + eksponent - JEDNA KUĆICA ajmo reć
	
	while (where->next != NULL && what->exp < where->next->exp) //where->next != NULL ?
		where = where->next;

	what->next = where->next;
	where->next = what;

	return 0;

}

Position zbrajanjePol(Position head1, Position head2) {

	Position r;
	Position pom;

	while (head1->next != NULL && head2->next != NULL) {

		if (head1->next->exp = head2->next->exp) { // U slucaju istih exp, zbroji koef i postavi exp
			r = (Position)malloc(sizeof(Polinom));
			r->exp = head1->exp;
			r->coef = head1->coef + head2->coef;

			if (r->coef == 0)
				free(r); // ne triba nam prazni element tj. 0

			head1 = head1->next;
			head2 = head2->next;
		}
		else if (head1->next->exp > head2->next->exp) {
			r = (Position)malloc(sizeof(Polinom));
			r->coef = head1->next->coef;
			r->exp = head1->next->exp;
			head1 = head1->next;
		}
		else if (head1->next->exp < head2->next->exp) { // U slucaju da je jedan veci od drugoga u r zapisi veci i makni mu pokaziva na iduci clan
			r = (Position)malloc(sizeof(Polinom));
			r->coef = head1->next->coef;
			r->exp = head1->next->exp;
			head1 = head1->next;
		}

	}
}