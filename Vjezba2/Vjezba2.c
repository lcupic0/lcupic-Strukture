/*
2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
a) dinamički dodaje novi element na početak liste,
b) ispisuje listu,
c) dinamički dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.
*/

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
Position findStudent(Position p, char* Ime, char* Prezime);
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
            printf("Unesite ime studenta kojeg zelite pronaci: \n");
            scanf(" %s", ime);
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
    what->next = NULL;      // where->next=what
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

Position findStudent(Position p, char* Ime, char* Prezime) {

    if (p->next == NULL) {
        printf("Lista je prazna!\n");
        return NULL;
    }

    p = p->next;
    while (p != NULL && (strcmp(p->ime, Ime) || strcmp(p->prezime, Prezime))) { //strcmp
        p = p->next;
    }

    if (p == NULL)
        printf("Trazeni student ne postoji u bazi!\n");

    return p;
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

//VERZIJA 2

/*
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
Position findPrev(Position p, char *Ime, char *Prezime);
Position findStudent(Position p, char* Ime, char* Prezime);
int deleteStudent(Position p, char* Ime, char* Prezime);

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

    if (what == NULL){
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
    while (p!= NULL && (strcmp(p->ime,Ime) || strcmp(p->prezime, Prezime))) { //strcmp
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

*/