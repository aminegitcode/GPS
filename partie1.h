#ifndef PARTIE1_H
#define PARTIE1_H


typedef char string[50];

typedef struct { 
    string action;
    string preconds[10];
    int nb_preconds;
    string add[10];
    int nb_add;
    string delete[10];
    int nb_delete;
    int deja_appl;// pour la partie 3
} Rule;


extern Rule Rules[100];
extern int nb_rules;
extern string start[10];
extern int nb_start;
extern string finish[10];
extern int nb_finish;

void afficher_chaine(string T[], int taille);
void charger_Fichier(char fileName[]);
int parseLine(char source[], string cible[]);
void afficher_Fichier();

#endif

