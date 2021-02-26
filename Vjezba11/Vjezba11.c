#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_CHAR (256)
// Dodat šta ako neki student ima 2 prezimena

/*
Napisati kod koji za zadane podatke studenata (matični broj, ime i prezime) pravi
hash tablicu sa zasebnim redovima. Tablica ima 11 mjesta, a funkcija za preslikavanje
ključ računa da se zbraja ASCII vrijednost prvih pet slova prezimena i zatim računa
ostatak cjelobrojnog dijeljenja te vrijednosti s veličinom tablice. 

Studenti s istim ključem se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
Kada se tablica izgradi treba ispisati cijelu tablicu (naglasiti na kojem ključu se nalaze
koji podaci) te ponuditi mogućnost da se za određenog studenta (prezime i ime) ispiše
njegov matični broj.
*/

struct _hashT;
typedef struct _hashT* hashTab;
struct _list;
typedef struct _list* ListPosition;

typedef struct _list {
	char Ime[MAX_CHAR];
	char Prezime[MAX_CHAR];
	int matBroj;
	ListPosition Next;
}List;

typedef struct _hashT {
								
	ListPosition headList[11]; // hashTab Next - nam ne treba jer mi koristimo niz ovih struktura pa nam ne triba pokazivac na iduci clan.
	int hashSize;

}HashTablica;

int insertInTab(char* Ime, char* Prezime, int matBroj, hashTab table);
int readFromFile(hashTab head);
int findKey(char* surname);
int getIndex(int key, int hashSize);
hashTab tabInit(int hashSize);
int printHashTable(hashTab table);
ListPosition findListMember(hashTab table);

int main()
{
	hashTab myHashTable;
	ListPosition trazeni;

	myHashTable = tabInit(11);

	readFromFile(myHashTable);
	insertInTab("Leo", "Messi", 214, myHashTable);
	insertInTab("Lebron", "James", 213, myHashTable);
	insertInTab("Moja", "Malenkost", 420, myHashTable);
	insertInTab("Mate", "Vodoinstalater", 213, myHashTable);
	insertInTab("Vojko", "Vrucina", 169, myHashTable);


	printHashTable(myHashTable);

	trazeni = findListMember(myHashTable);

	printf("Pronasli smo studenta %s %s. \n", trazeni->Ime, trazeni->Prezime);

	return 0;
}
ListPosition findListMember(hashTab table) {

	char prezime[30] = { 0 };
	char ime[30] = { 0 };
	int kljuc,index;
	ListPosition pom;

	printf("Unesite ime studenta kojeg trazite:\n");
	scanf(" %s", ime);

	printf("Unesite prezime studenta kojeg trazite:\n");
	scanf(" %s", prezime);

	kljuc = findKey(prezime);
	index = getIndex(kljuc, table->hashSize);

	pom = table->headList[index];

	while (pom != NULL && ( strcmp(pom->Ime, ime) != 0 ) && (strcmp(pom->Prezime, prezime) != 0) )
		pom = pom->Next;

	if (pom == NULL) {
		printf("Student %s %s nije upisan u hash tablicu, vraćam NULL!\n");
		return NULL;
	}

	return pom;
}

int findKey(char* surname) {

	int key = 0;

	if (strlen(surname) < 5) {
		printf("Surname is too short for making key!\n");
		return -1;
	}

	for (int i = 0; i < 5; i++) {
		key += surname[i];
	}

	return key;
}

int getIndex(int key, int hashSize) {
	return key % hashSize;
}

hashTab tabInit(int hashSize) {

	hashTab table;
	table = (hashTab)malloc(sizeof(HashTablica));

	if (table == NULL) {
		printf("Greska prilikom inicijalizacije tablice!\n");
		return NULL;
	}

	table->hashSize = hashSize;
	
	for (int i = 0; i < hashSize; i++) {
		table->headList[i] = (ListPosition)malloc(hashSize * sizeof(HashTablica));
		table->headList[i]->Next = NULL;
	}

	return table;
}

int readFromFile(hashTab head) {

	FILE* dat;
	char ime[MAX_CHAR] = { 0 };
	char prezime[MAX_CHAR] = { 0 };
	int matBroj;

	dat = fopen("studenti.txt", "r");
	if (!dat) {
		printf("Ne mogu otvoriti studenti.txt!\n");
		return -1;
	}
	//probat iza pokupit podatke sa fscanfom.
	while (!feof(dat)) {

		fscanf(dat, "%s %s %d", ime, prezime, &matBroj);
		insertInTab(ime, prezime, matBroj, head);
	}

	fclose(dat);

	return 1;
}

int insertInTab(char* Ime, char* Prezime, int matBroj, hashTab table) {

	ListPosition New;
	ListPosition temp;
	int Index, key;
	New = (ListPosition)malloc(sizeof(List));
	
	New->Next = NULL;
	strcpy(New->Ime, Ime);
	strcpy(New->Prezime, Prezime);
	New->matBroj = matBroj;

	key = findKey(Prezime);
	Index = getIndex(key, table->hashSize);
	
	if (table->headList[Index]->Next == NULL) {
		New->Next = table->headList[Index]->Next;
		table->headList[Index]->Next = New;
		return 1;
	}

	temp = table->headList[Index];

	while (temp->Next != NULL && strcmp(temp->Next->Prezime, Prezime) < 0)
		temp = temp->Next;

	New->Next = temp->Next;
	temp->Next = New;

	return 1;
}

int printHashTable(hashTab table) {

	ListPosition head;

	if (table == NULL) {
		printf("Tablica je prazna!\n");
		return -1;
	}

	for (int i = 0; i < table->hashSize; i++) {

		head = table->headList[i];

			while (head->Next != NULL) {
				head = head->Next;
				printf("%s %s %d ; index %d", head->Ime, head->Prezime, head->matBroj, i);
				printf("\n");
			}	
	}
	
	return 1;
}