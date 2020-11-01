#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 200

struct _student;
typedef struct _student* Position;

typedef struct _student {

	char ime[MAX], prezime[MAX];
	int godinaRodjenja;

	Position next;

}Student;

int printList(Position head);
Position createStudent();
int insertBeg(Position what, Position where);
int insertEnd(Position what, Position where);
Position findElement(char* prezime, Position where);
int deleteElement(char* prezime, Position where);
Position findPrev(char* prezime, Position where);
int addAfter(Position what, Position where);

int main(void)
{
	Student head;
	head.next = NULL;
	Position what;
	int pom;
	char izbor;
	char ime[MAX], prezime[MAX];

	printf("Ako zelite izaci iz ovog izbornika unesite: 0\n");
	printf("Ako zelite dodati studenta na kraj liste unesite 1\n");
	printf("Ako zelite dodati studenta na pocetak liste unesite 2\n");
	printf("Ako zalite pronaci studenta unesite 3\n");
	printf("Ako zelite pronaci prethodnog studenta unesite 4\n");
	printf("Ako zelite izbrisat studenta unesite 5\n");
	printf("Za ispis studenta unesite i\n");

	while (1)
	{
		scanf(" %c", &izbor);
		if (izbor == '0')
			break;

		switch (izbor) {

		case '1':
			what = createStudent();
			insertEnd(what, &head);
			break;

		case '2':
			what = createStudent();
			insertBeg(what, &head);
			break;

		case '3':
			printf("Unesite prezime studenta kojeg zelite pronaci: \n");
			scanf(" %s", prezime);
			printf("Adresa zeljenog studenta je: %d\n", findElement(prezime, &head));
			break;

		case '4':
			printf("Unesite prezime studenta cijeg prethodnika zelite pronaci: \n");
			scanf(" %s", prezime);
			printf("Adresa prethodnog elementa je: %d\n", findPrev(prezime, &head));
			break;

		case '5':
			printf("Unesite prezime studenta kojeg zelite izbrisati: \n");
			scanf(" %s", prezime);
			deleteElement(prezime, &head);
			break;

		case 'i':
			printList(&head);
			break;

		case '0':
			break;

		default:
			printf("Krivi odabir!\n");
			break;
		}
	}

	printf("\n\tIzasli ste iz programa!\t\n");

	return 0;
}

Position createStudent() {  // POSITION NAM JE SAMO TIP VARIJABLE!!!
							//Ova funkcija samo sluzi za unos u strukturu, a ne u LISTU!!!!
	Position student = NULL;
	student = (Position)malloc(sizeof(Student));

	if (NULL == student) { // ili if(!student);
		printf("Allocation failed\r\n");
		return NULL;
	}

	printf("Insert first name:\r\n");
	scanf(" %s", student->ime);

	printf("Insert last name:\r\n");
	scanf(" %s", student->prezime);

	printf("Insert birth year:\r\n");
	scanf("%d", &student->godinaRodjenja);

	student->next = NULL;

	return student;
}

int insertBeg(Position what, Position where) { //Funkcija koja unosi neki element nakon nekog drugoga!!!
	what->next = where->next; // Skicirat na papir pa će biti lakše za skužiti!
	where->next = what;
	return 0;
}

int insertEnd(Position what, Position where) { // Funkcija koja postavlja neki element na zadnje misto u nizu!!!
	while (where->next != NULL) {
		where = where->next;
	}

	where->next = what;   //what->next=where->next - mislim da ovo dode na isto
	what->next = NULL;	// where->next=what
	return 0;
}

int printList(Position head) {
	Position p = NULL;
	p = head->next; // OVO JE KLJUČNO!

	printf("\nList contains:\r\n");

	while (p != NULL) {
		printf("%s %s %d\n", p->ime, p->prezime, p->godinaRodjenja);
		p = p->next;
	}

	printf("\r\n\r\n");
	return 0;
}

Position findElement(char* prezime, Position where) {
	while (where != NULL && strcmp(where->prezime, prezime))
		where = where->next;

	if (where == NULL)
		return NULL;

	return where;
}

Position findPrev(char* prezime, Position where) {

	Position Prev = NULL;
	Prev = where;
	where = where->next;

	while (where != NULL && strcmp(where->prezime, prezime))
	{
		Prev = where;
		where = where->next; // Trazimo član čiji prethodnik zelimo naci, kad ga nademo stopamo!
	}

	return Prev;
}

int deleteElement(char* prezime, Position where) {

	Position prev = NULL;

	prev = findPrev(prezime, where);
	if (prev->next != NULL)
	{
		where = prev->next;
		prev->next = where->next;
		free(where);
	}
	return 0;
}