#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_ZNAKOVA (100)

struct _osoba;
typedef struct _osoba* Position;
typedef struct _osoba {
	char ime[MAX_ZNAKOVA];
	char prezime[MAX_ZNAKOVA];
	int godinaRodjenja;
	Position Next;
}Osoba;

Position makeNode();
int insertBeg(Position what, Position where);
int insertEnd(Position what, Position where);
int printList(Position p);
Position findPrev(Position p, char* Ime, char* Prezime);
Position findStudent(Position p, char* Ime, char* Prezime);
int deleteStudent(Position p, char* Ime, char* Prezime);
int addAfter(Position p, Position student);
int addBefore(Position p, Position student);
int sortUnos(Position p, Position student);
int writeDat(Position p);
int scanDat(Position p);
int deleteAll(Position p);

int main()
{
	char tempIme[MAX_ZNAKOVA];
	char tempPrezime[MAX_ZNAKOVA];
	Osoba head;
	head.Next = NULL;
	Position student;
	int x;

	while (1) {
		printf("Unesi opciju: \n");
		scanf("%d", &x);

		if (x == 0)
			break;

		switch (x) {
		case 1:
			printf("Unesi ime trazenog studenta: \n");
			scanf(" %s", tempIme);
			printf("Unesi prezime tog studenta: \n");
			scanf(" %s", tempPrezime);
			printf("Adresa trazenog studenta: %d", findStudent(&head, tempIme, tempPrezime));

			break;
		case 2:
			student = makeNode();
			insertBeg(student, &head);
			break;
		case 3:
			student = makeNode();
			insertEnd(student, &head);
			break;
		case 4:
			printList(&head);
			break;
		case 5:
			printf("Unesi ime studenta za brisanje: \n");
			scanf(" %s", tempIme);
			printf("Unesi prezime studenta za brisanje: \n");
			scanf(" %s", tempPrezime);
			deleteStudent(&head, tempIme, tempPrezime);
			break;
		case 6:
			printf("Unos studenta:\n");
			student = makeNode();
			addAfter(&head, student);
			break;
		case 7:
			printf("Unos studenta:\n");
			student = makeNode();
			addBefore(&head, student);
			break;
		case 8:
			printf("Sortirani unos studenta:\n");
			student = makeNode();
			sortUnos(&head, student);
			break;
		case 9:
			scanDat(&head);
			break;
		case 10:
			deleteAll(&head);
			break;
		case 0:
			break;
		}

	}

	return 0;
}

Position makeNode() {
	Position node;

	node = (Position)malloc(sizeof(Osoba));
	if (node == NULL) {
		printf("Memory allocation failed!\n");
		return NULL;
	}

	node->Next = NULL;

	printf("Insert students name: \n");
	scanf(" %s", node->ime);
	printf("Insert students surname: \n");
	scanf(" %s", node->prezime);
	printf("Insert birth year: \n");
	scanf("%d", &node->godinaRodjenja);

	return node;
}

int insertBeg(Position what, Position head) {

	if (what == NULL) {
		printf("Problem prilikom unosa na pocetak!\n");
		return -1;
	}

	what->Next = head->Next;
	head->Next = what;

	return 1;
}

int insertEnd(Position what, Position p) {

	if (what == NULL) {
		printf("Problem prilikom unosa na pocetak!\n");
		return -1;
	}

	while (p->Next != NULL)
		p = p->Next;

	what->Next = p->Next;
	p->Next = what;

	return 1;
}

int printList(Position p) {

	if (p->Next == NULL) {
		printf("Vaša lista je prazna!\n");
		return 1;
	}

	p = p->Next;
	while (p != NULL) {
		printf("%s %s %d\n", p->ime, p->prezime, p->godinaRodjenja);
		p = p->Next;
	}
	return 1;
}

Position findStudent(Position p, char* Ime, char* Prezime) {

	if (p->Next == NULL) {
		printf("Lista je prazna!\n");
		return NULL;
	}

	p = p->Next;
	while (p != NULL && (strcmp(p->ime, Ime) || strcmp(p->prezime, Prezime))) { // vrti dok oba uvjeta nisu nađena i zato ide ||
		p = p->Next;
	}

	if (p == NULL)
		printf("Trazeni student ne postoji u bazi!\n");

	return p;
}

Position findPrev(Position p, char* Ime, char* Prezime) {

	Position prev = p;

	p = p->Next;
	while (p != NULL && (strcmp(p->ime, Ime) || strcmp(p->prezime, Prezime))) {
		prev = p;
		p = p->Next;
	}

	if (p == NULL) {
		printf("Student cijeg prethodnika trazite ne postoji!\n");
		return NULL;
	}

	return prev;
}

int deleteStudent(Position p, char* Ime, char* Prezime) {

	Position prev, temp;

	prev = findPrev(p, Ime, Prezime);

	if (prev != NULL) {
		temp = prev->Next;
		prev->Next = temp->Next;
		free(temp);
	}

	return 1;
}

int addAfter(Position p, Position student) {
	char Ime[MAX_ZNAKOVA], Prezime[MAX_ZNAKOVA];
	Position temp;

	printf("Unesi ime studenta iza kojeg zelis dodat: \n");
	scanf(" %s", Ime);
	printf("Unesi prezime studenta iza kojeg zelis dodat: \n");
	scanf(" %s", Prezime);

	temp = findStudent(p, Ime, Prezime);

	if (temp == NULL) {
		printf("Taj student ne postoji!\n");
		return 0;
	}

	student->Next = temp->Next;
	temp->Next = student;

	return 1;
}

int addBefore(Position p, Position student) {

	char Ime[MAX_ZNAKOVA], Prezime[MAX_ZNAKOVA];
	Position prev;

	printf("Unesi ime studenta ispred kojeg zelis dodat: \n");
	scanf(" %s", Ime);
	printf("Unesi prezime studenta ispred kojeg zelis dodat: \n");
	scanf(" %s", Prezime);

	prev = findPrev(p, Ime, Prezime);

	if (prev != NULL) {

		student->Next = prev->Next;
		prev->Next = student;
	}

	return 1;
}

int sortUnos(Position p, Position student) {

	if (p->Next == NULL)
	{
		student->Next = p->Next;
		p->Next = student;
		return 1;
	}

	while (p->Next != NULL && strcmp(student->prezime, p->Next->prezime) > 0)
		p = p->Next;

	student->Next = p->Next;
	p->Next = student;

	return 1;
}

int writeDat(Position p) {

	FILE* dat;
	dat = fopen("studenti.txt", "w");
	if (!dat)
		printf("Datoteka se nije uspjesno kreirala!\n");

	if (p->Next == NULL) {
		printf("Lista je prazna i ne unosim je u datoteku!\n");
		return -1;
	}

	p = p->Next;
	while (p != NULL) {
		fprintf(dat, "%s %s %d\n", p->ime, p->prezime, p->godinaRodjenja);
		p = p->Next;
	}

	fclose(dat);
	return 1;
}

int scanDat(Position p) {

	char buffer[MAX_ZNAKOVA];
	FILE* dat;
	int brojac = 0;
	Position temp;
	dat = fopen("studenti.txt", "r");


	if (!dat)
	{
		printf("Datoteka se nije otvorila!\n");
		return -1;
	}

	while (fgets(buffer, MAX_ZNAKOVA, dat)) {
		if (buffer[0] != '\n')
			brojac++;
	}

	rewind(dat);

	for (int i = 0; i < brojac; i++) {
		temp = (Position)malloc(sizeof(Osoba));
		fgets(buffer, MAX_ZNAKOVA, dat);
		sscanf(buffer, "%s %s %d", temp->ime, temp->prezime, &temp->godinaRodjenja);
		sortUnos(p, temp);
	}

	fclose(dat);
	return 1;
}

int deleteAll(Position p) {

	Position temp;

	if (p->Next == NULL) {
		printf("Lista je vec prazna!\n");
		return 1;
	}

	while (p->Next != NULL) {
		temp = p->Next;
		p->Next = temp->Next;
		free(temp);
	}

	printf("Lista je izbrisana!\n");
	return 1;
}