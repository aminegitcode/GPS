#include<stdio.h>
#include <string.h>
#include "partie1.h"
#include "partie2.h"

string etat_courant[10];
int nb_faits; // nombre de faits dans l'etat courant

// Copier l'etat initial dans l'etat courant
void initialiser_Etat(){
    nb_faits = nb_start;
    for(int i = 0; i < nb_start; i++){
        strcpy(etat_courant[i], start[i]);
    }
}
  
// Afficher l'etat courant a chaque etape
void afficher_Etat(){
    afficher_chaine(etat_courant, nb_faits);
    printf("\n");
}

// Verifier si un fait existe deja dans les faits de l'etat courant
int contient_Fait(string fait){
    for(int i = 0; i < nb_faits; i++){
        if(strcmp(etat_courant[i], fait) == 0){
            return 1;
        }
    }
    return 0;
}

// Verifier si le but est atteint
int est_But_Atteint(){
    for(int i = 0; i < nb_finish; i++){
        if(!contient_Fait(finish[i])){
            return 0;
        }
    }
    return 1;
}

// Verifier si une regle est applicable
int est_Regle_Applicable(Rule r){
    for(int i = 0; i < r.nb_preconds; i++){
        if(!contient_Fait(r.preconds[i])){
            return 0;
        }
    }
    return 1;
}

// Appliquer une regle
void appliquer_Regle(Rule r){
    if(est_Regle_Applicable(r) && !est_But_Atteint()){
        string temp[10]; // pour stocker les faits a supprimer/ajouter
        int iTemp = 0;

        // Supprimer les faits
        for(int i = 0; i < r.nb_delete; i++){
            for(int j = 0; j < nb_faits; j++){
                if(strcmp(r.delete[i], etat_courant[j]) == 0){
                    strcpy(temp[iTemp], r.delete[i]);
                    iTemp++;

                    // Decaler les elements
                    for(int k = j; k < nb_faits - 1; k++){
                        strcpy(etat_courant[k], etat_courant[k+1]);
                    }
                    nb_faits--;
                    break; // une suppression par fait
                }
            }
        }

        // Afficher les faits supprimes
        if (iTemp > 0) {
            printf("Faits supprimes : ");
            afficher_chaine(temp, iTemp);
            printf("\n");
        }

        // Ajouter les faits
        iTemp = 0;
        for(int i = 0; i < r.nb_add; i++){
            if(!contient_Fait(r.add[i])){
                strcpy(temp[iTemp], r.add[i]);
                iTemp++;

                strcpy(etat_courant[nb_faits], r.add[i]);
                nb_faits++;
            }
        }

        // Afficher les faits ajoutes
        if (iTemp > 0) {
            printf("Faits ajoutes : ");
            afficher_chaine(temp, iTemp);
            printf("\n");
        }
    }
}

// Moteur de raisonnement
void moteur_Raisonnement(){
    initialiser_Etat();
    
    // Afficher l'etat initial
    printf("\nEtat initial : ");
    afficher_Etat();
    
    if (nb_rules == 0){
        printf("Aucune regle\n");
        return;
    }
    
    while(!est_But_Atteint()){
        printf("\nEtat courant (avant application de la regle) : ");
        afficher_Etat();
        
        int regle_appliquee = 0;

        for(int i = 0; i < nb_rules; i++){
            if(est_Regle_Applicable(Rules[i])){
                printf("Application de la regle %d :\n", i);
                appliquer_Regle(Rules[i]); 
                regle_appliquee = 1;
                break;
            }
        }

        if (!regle_appliquee){
            printf("Aucune regle applicable. Echec.\n");
            return;
        }

        printf("Nouvel etat : ");
        afficher_Etat();
    }

    printf("\nBut atteint.\n");
}

/*
int main(){
    printf("Chargement du fichier...\n");
    charger_Fichier("monkeys.txt");
    
    printf("\nRaisonnement en cours...\n");
    moteur_Raisonnement();
}
*/

