#ifndef PARTIE2_H
#define PARTIE2_H
#include"partie1.h"
extern string etat_courant[10];
extern int nb_faits; 


void initialiser_Etat();
void afficher_chaine(string T[], int taille);
void afficher_Etat();
int contient_Fait(string fait);
int est_But_Atteint();
int est_Regle_Applicable(Rule r);
void appliquer_Regle(Rule r);
void moteur_Raisonnement();

#endif
