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
int addBefore(Position what, Position where, char* prezime);
int sortUnos(Position what, Position where);
int writeDat(Position head);
int scanDat(Position head);
int brojacStudenata();

int main(void)
{
    Student head;
    head.next = NULL;
    Position what;
    char izbor;
    char prezime[MAX];

    printf("Ako zelite izaci iz ovog izbornika unesite: K\n");
    printf("Ako zelite dodati studenta na kraj liste unesite 1\n");
    printf("Ako zelite dodati studenta na pocetak liste unesite 2\n");
    printf("Ako zalite pronaci studenta unesite 3\n");
    printf("Ako zelite pronaci prethodnog studenta unesite 4\n");
    printf("Ako zelite izbrisat studenta unesite 5\n");
    printf("Ako zelite studenta iza odredenog studenta unesite 6\n");
    printf("Ako zelite studenta ispred odredenog studenta unesite 7\n");
    printf("Ako zelite vasu listu studenata dodati u datoteku unesite 8\n");
    printf("Ako zelite studente iz datoteke dodati u listu unesite 9\n");
    printf("Ako zelite sortirani unos studenata unesite s\n");

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

        case '6':
            printf("Unos studenta kojeg zelite dodati:\n");
            what = createStudent();
            addAfter(what, &head);
            break;

        case '7':
            printf("Unos studenta kojeg zelite dodati:\n");
            what = createStudent();
            printf("Unesite prezime studenta ispred kojeg zelite dodati unesenog studenta:\n");
            scanf(" %s", prezime);
            addBefore(what, &head, prezime);

        case '8':
            writeDat(&head);
            break;

        case '9':
            scanDat(&head);
            break;

        case 's':
            printf("Unos studenta koji ce ici u listu sortiranu po prezimenu: \n");
            what = createStudent();
            sortUnos(what, &head);
            break;
        
        case 'i':
            printList(&head);
            break;

        case 'K':
            break;

        default:
            printf("Krivi odabir!\n");
            break;
        }
    }

    printf("\nIzasli ste iz izbornika! \n");

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

//Nakon nekog elementa dodaj novi
int addAfter(Position what, Position where) {  //where = adresa heada
    Position after;
    char prezime[MAX];

    printf("Unesite prezime studenta iza kojeg zelite dodati novog studenta\n");
    scanf(" %s", prezime);

    after = findElement(prezime, where);

    if (after != NULL)
    {
        what->next = after->next;
        after->next = what;
    }
    return 0;
}

int addBefore(Position what, Position head, char* prezime) {
    Position prev;
    prev = findPrev(prezime, head);

    if (prev != NULL)
    {
        what->next = prev->next;
        prev->next = what;
    }

    return 0;
}

int writeDat(Position p) {
    FILE* dat;
    dat = fopen("lista.txt", "w");
    if (dat == NULL)
        printf("Greška, datoteka nije otvorena!\n");

    p = p->next;
    while (p != NULL)
    {
        fprintf(dat, "%s %s %d\n", p->ime, p->prezime, p->godinaRodjenja);
        p = p->next;
    }

    fclose(dat);

    return 0;
}

int sortUnos(Position what, Position where) { //where ce bit adresa od heada
                                              //what - student kojeg unesemo --> pa ćemo njih dvojicu usporedivati po prezimenu i odma sortirati listu!
    while (where->next != NULL && strcmp(what->prezime, where->next->prezime) > 0) // strcmp vraca negativan broj ako je prvi char manji od drugoga
        where = where->next;

    what->next = where->next;
    where->next = what;

    return 0;
}

int brojacStudenata() {
    FILE* dat;
    char niz[MAX];
    int brojac = 0;

    //Otvaranje datoteke
    dat = fopen("lista.txt", "r");
    if (dat == NULL)
        printf("Greska, datoteka nije otvorena!\n");

    while (fgets(niz,MAX, dat) != NULL) {
        if ((niz[0] != '\n'))
            brojac++;
    }
    
    fclose(dat);
    return brojac;
}

//Dodavanje liste iz datoteke
int scanDat(Position head) {

    int i = 0, brojac = 0;
    char niz[MAX];
    Position p;
    FILE* dat;

    brojac = brojacStudenata();
    dat = fopen("lista.txt", "r");

    //Ucitavanje studenata u listu
    printf("Ucitavanje studenata iz datoteke u listu\n");
    for (i = 0; i < brojac; i++) {
        p = (Position)malloc(sizeof(Student));
        fgets(niz, MAX, dat);
        sscanf(niz, "%s %s %d\n", p->ime, p->prezime, &p->godinaRodjenja);
        insertEnd(p, head);
    }
    

    fclose(dat);
    return 0;
}