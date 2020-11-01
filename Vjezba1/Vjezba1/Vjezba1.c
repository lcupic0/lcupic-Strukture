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
        if((niz[0] != '\n'))
        brojac++;
    }
   

    return brojac;
}

int MaxBodovi(Student* Studenti, int brojac) // Je li ovo najbolji nacin za poslati "datoteku" ? PROVJERIT!
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
    printf("Broj studenata: %d\n", brojac);

    Studenti = (Student*)malloc(brojac * sizeof(Student));

    ucitajStudenta(Studenti, brojac);
    maxbodovi=MaxBodovi(Studenti, brojac);

    // Ispis Studenata - cc
    printf("Ime\tPrezime\tBroj bodova\tRelativno bodovi\n\t");
    for (i = 0;i < brojac;i++) {

        printf("%s\t%s\t%d\t\t%lf\n", Studenti[i].Ime, Studenti[i].Prezime, Studenti[i].bodovi, relativno(Studenti[i].bodovi,maxbodovi));
    }

    fclose(dat);
    return 0;
}