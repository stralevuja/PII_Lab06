#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
    char ime[30];
    char prezime[30];
    char brojIndeksa[10];
} STUDENT;

typedef struct cvor {
    STUDENT s;
    struct cvor *next;
} CVOR;

CVOR* add_begin(CVOR **glava, STUDENT *s);
void printflista(CVOR *glava);
void fprintflista(CVOR *glava, const char *filename);

int main(void) {
    CVOR *glava = NULL;

    STUDENT s1 = {"Marko", "Markovic", "12345"};
    STUDENT s2 = {"Janko", "Jankovic", "54321"};
    STUDENT s3 = {"Ana", "Anic", "67890"};

    glava = add_begin(&glava, &s1);
    glava = add_begin(&glava, &s2);
    glava = add_begin(&glava, &s3);

    printf("Lista studenata:\n");
    printflista(glava);

    fprintflista(glava, "lista.txt");
    printf("\n");
    printf("Lista studenata upisana u fajl.\n");

    CVOR *tmp = glava;
    while(tmp != NULL) {
        CVOR *sledeci = tmp->next;
        free(tmp);
        tmp = sledeci;
    }
    glava = NULL;

    return 0;
}

CVOR* add_begin(CVOR **glava, STUDENT *s) {
    CVOR *novi = (CVOR*)malloc(sizeof(CVOR));
    if (novi == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        exit(1);
    }
    novi->s = *s;
    novi->next = *glava;
    *glava = novi;
    return novi;
}

void printflista(CVOR *glava) {
    CVOR *tmp = glava;
    while(tmp != NULL) {
        printf("%s %s %s\n", tmp->s.ime, tmp->s.prezime, tmp->s.brojIndeksa);
        tmp = tmp->next;
    }
}

void fprintflista(CVOR *glava, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Greska pri otvaranju fajla!\n");
        exit(1);
    }
    CVOR *tmp = glava;
    while(tmp != NULL) {
        fprintf(fp, "%s %s %s\n", tmp->s.ime, tmp->s.prezime, tmp->s.brojIndeksa);
        tmp = tmp->next;
    }
    fclose(fp);
}