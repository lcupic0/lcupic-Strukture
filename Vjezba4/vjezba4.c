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

typedef struct polinom {
	int coef;
	int exp;
	Position next;
}Polinom;

int main()
{
	Polinom head1, head2;
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

	//fscanf(dat1, "%d %d", &coef, &exp); Ovdje ucita, a u datoteci nece

	//ucitavanje listi
	scanDat(dat1, &head1);
	scanDat(dat2, &head2);

	//test print
	printf("Lista 1:\n");
	printList(&head1);
	printf("Lista 2:\n");
	printList(&head2);

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
	fclose(dat);
	return brojac;
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
	for (i = 0;i < brojac;i++)
	{
		fscanf(dat, "%d %d", &coef, &exp);

		p = (Position)malloc(sizeof(struct polinom));
		p->coef = coef;
		p->exp = exp;
		p->next = NULL;

		unosBeg(p, head);
	}

	fclose(dat);
	return 0;
}