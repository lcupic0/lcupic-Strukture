/*
1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime,apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_BODOVI 53

struct Student
{
    char Ime[50], Prezime[50];
    int bodovi;
};

typedef struct Student Student;

int brojacStudenata(FILE* nekadat) // Je li ovo najbolji nacin za poslati "datoteku" ? PROVJERIT!
{
    int i = 0, brojac = 0;
    char niz[100]; // Kako dinamicki alocirati ako ne unaprijed ne znam broj studenata

    while (fgets(niz, 100, nekadat) != NULL) {
        if ((niz[0] != '\n')) 
            brojac++;
    }

    return brojac;
}

int MaxBodovi(Student* Studenti, int brojac) 
{
    int i = 0, maxbodovi;

    maxbodovi = Studenti[0].bodovi;
    for (i = 0; i < brojac; i++)
    {
        if (maxbodovi <= Studenti[i].bodovi)
            maxbodovi = Studenti[i].bodovi;
    }


    return maxbodovi;
}



int ucitajStudenta(Student* Studenti, int brojac)
{
    int i = 0;
    FILE* dat;
    dat = fopen("studenti.txt", "r");

    for (i = 0;i < brojac;i++)
    {
        fscanf(dat, "%s %s %d", Studenti[i].Ime, Studenti[i].Prezime, &Studenti[i].bodovi); //NE ZABORAVIT & kod int-a !
    }

    fclose(dat);
    return 1;
}

double relativno(int brojbodova, int maxbodovi)
{
    return ((double)brojbodova / maxbodovi) * 100;
}


int main()
{
    FILE* dat;
    int brojac = 0, i, maxbodovi;
    Student* Studenti;

    //Otvaranje i provjera tako da ne moram provjeravat u svakoj funkciji gdje opet otvaram isti file.
    dat = fopen("studenti.txt", "r");
    if (dat == NULL)
    {
        printf("Greska, datoteka nije otvorena!\n");
        return -1;
    }

    brojac = brojacStudenata(dat);
    fclose(dat);
    printf("Broj studenata: %d\n", brojac);

    Studenti = (Student*)malloc(brojac * sizeof(Student));

    ucitajStudenta(Studenti, brojac);
    maxbodovi = MaxBodovi(Studenti, brojac);

    // Ispis Studenata
    printf("Ime\tPrezime\tBroj bodova\tRelativno bodovi\n");
    for (i = 0;i < brojac;i++) {

        printf("%s\t%s\t%d\t\t%lf\n", Studenti[i].Ime, Studenti[i].Prezime, Studenti[i].bodovi, relativno(Studenti[i].bodovi, maxbodovi));
    }

    return 0;
}