#ifndef PARTIE3_H
#define PARTIE3_H

#include"partie1.h"


  typedef struct {
    string faits[10];
    int nb_faits3;
    int regle_appliquee; 
  }Etat;

extern Etat Etats[100];  
extern int nb_etats;

void moteur_Raisonnement3();

#endif
