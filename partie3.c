#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"partie1.h"
#include"partie2.h"
#include"partie3.h"
#include <sys/time.h>
#include<time.h>

struct timeval start1, end;
Etat Etats[100];
int nb_etats=0;
int IR=0;

// pour afficher le but 
void afficher_but (){
  afficher_chaine(finish, nb_finish);
}

// pour afficher l'état initial
void afficher_etat_init(){
  afficher_chaine(start, nb_start);
}

// afficher les regles
void afficher_regles(){
  for(int i=0; i < nb_rules; i++){
      printf("\n\n** règle %d **\n", i+1);
      
      // action
      printf("action: %s", Rules[i].action);
      
      // preconds
      printf("\npreconds: ");
      afficher_chaine(Rules[i].preconds, Rules[i].nb_preconds);
      
      // add
      printf("\nadd: ");
      afficher_chaine(Rules[i].add, Rules[i].nb_add);
      
      // delete
      printf("\ndelete: ");
      afficher_chaine(Rules[i].delete, Rules[i].nb_delete);
  }
}

// melanger l'ordre des regles
void melanger() {
  
  srand(time(NULL));// pour avoir d'autres nobres aleatoire sinon on aura toujours les meme valeurs

    for (int i=0;i<nb_rules -1 ;i++) {
        // Générer un indice aléatoire j entre 0 et i
        int j = rand() % (i + 1);

        // Echanger Rules[i] avec Rules[j]
        Rule temp = Rules[i];
        Rules[i] = Rules[j];
        Rules[j] = temp;
    }
     
    int choix0;
    printf("\nvoulez-vous afficher le nouvel ordre?\n1- pour OUI \n0- pour NON\n");
    do{
      scanf("%d",&choix0);
    }while(choix0!=0 && choix0!=1);
    
    if(choix0){
    afficher_regles();
    
    }
}



// Initialisation de la première case du tableau Etats à l'état initial
void initialiser_Etat3() {
    nb_etats = 1; 
    Etats[0].nb_faits3 = nb_start;  

    for (int i = 0; i < nb_start; i++) {
        strcpy(Etats[0].faits[i], start[i]);  // Copier les faits de start dans la première case
    }
    Etats[0].regle_appliquee = 0;  // Aucune règle n'a encore été appliquée
}

// mémoriser l'état courant dans le tableau Etats
void memoriser_Etat(int regle_appliquee) {
    if (nb_etats < 100) { // vérifier si le tableau Etats n'est pas plein
        Etats[nb_etats].nb_faits3 = nb_faits; // copier le nombre de faits
        
        for (int i = 0; i < nb_faits; i++) {
            strcpy(Etats[nb_etats].faits[i], etat_courant[i]); // copier les éléments du tableau
        }
        Etats[nb_etats].regle_appliquee = regle_appliquee;
        nb_etats++;
    } else {
        printf("Le tableau des états est plein.\n");
    }
}

void moteur_Raisonnement3() {
   gettimeofday(&start1, NULL);
    int possible = 1;
    int IR = 0;
    
    initialiser_Etat(); // initialiser le tableau de l'état courant à l'état initial
    initialiser_Etat3(); // initialiser la première case du tableau des états à l'état courant
    
    // s'il n'y a pas de règles
    if (nb_rules == 0) {
        printf("Aucune règle\n");
        return;
    }
    
    while (!est_But_Atteint() && possible) {
        int trouve = 0;
        
        // Recherche à partir de IR
        for (int i = IR; i < nb_rules; i++) {
            if (est_Regle_Applicable(Rules[i]) && !Rules[i].deja_appl) { // si la règle est applicable et qu'elle n'a pas été déjà appliquée
                printf("Application de la règle %d:\n", i+1);
                appliquer_Regle(Rules[i]); // appliquer la règle
                Rules[i].deja_appl = 1;
                memoriser_Etat(i); // mémoriser le nouvel état dans le tableau des états
               
                IR = 0; // réinitialiser pour une nouvelle recherche
                trouve = 1;
                
                // afficher l'état courant après application de la règle
                printf("Nouvel état : ");
                afficher_Etat();
                printf("\n");
                
                break; // appliquer une seule règle par tour
            }
        }
        if (!trouve) { // si aucune règle n'a été trouvée
            printf("Aucune règle n'est applicable");
            
            if (nb_etats > 1) { // le tableau contient des états
                int j = Etats[nb_etats-1].regle_appliquee;
                printf("\nBacktracking... Annulation de la règle %d", j+1);
                
                // réactiver seulement la règle qui a échoué
                 Rules[j].deja_appl = 0;
                
                // revenir à l'état précédent
                
                nb_etats--;
                nb_faits = Etats[nb_etats-1].nb_faits3; // récupérer le nombre de faits
                for (int k = 0; k < nb_faits; k++) {
                    strcpy(etat_courant[k], Etats[nb_etats-1].faits[k]); // récupérer les faits
                }
                
                // chercher à partir de la règle suivante
                IR = j + 1;
                
                printf("\nRetour à l'état : ");
                afficher_Etat();
                printf("\n");
            } else {
                possible = 0;
            }
        }
    }
    
    if (possible && est_But_Atteint()) {
        printf("\nBut atteint !\n");
        printf("État final : ");
        afficher_Etat();
    } else {
        printf("\nÉchec\n");
    }
    gettimeofday(&end, NULL); 
    double delay = (end.tv_sec - start1.tv_sec)*1e6 + (end.tv_usec -start1.tv_usec);
    printf("%0.0lf microsecondes écoulées\n",delay);
}







int main() {
    int choix;
    int choix2;
    printf("Chargement du fichier...\n");
    charger_Fichier("4.txt");
           

    printf("\n\nVoulez-vous afficher le fichier ?\n0 pour NON\n1 pour FICHIER COMPLET\n2 pour REGLES\n3 pour ETAT INITIAL et BUT\n");
    scanf("%d", &choix);
    while (choix != 0 && choix != 1 && choix != 2 && choix != 3) {
        printf("Erreur, réessayez\n");
        scanf("%d", &choix);
    }
    switch (choix) {
        case 1:
            afficher_Fichier();
            break;
        case 2: 
            afficher_regles();
            break;
        case 3:
            printf("start: ");
            afficher_chaine(start, nb_start); 
            printf("\n");
            printf("finish: ");
            afficher_chaine(finish, nb_finish);
            break;
    }
    
    printf("\nVoulez-vous melanger l'ordre des regles \n1- pour OUI\n0- pour NON\n");
    int choixm;
    do{
      scanf("%d",&choixm);
    }while(choixm!=0 && choixm!=1);
    if(choixm){
      melanger();
    }

    printf("\nVoulez-vous résoudre le problème ?\n1 pour OUI\n0 pour NON\n");
    scanf("%d", &choix2);
    while (choix2 != 0 && choix2 != 1 ) {
        printf("Erreur, réessayez\n");
        scanf("%d", &choix2);
    }
    if(choix2) {
          printf("État initial : ");
          afficher_etat_init();
          printf("\n");
          printf("Le but : ");
          afficher_but();
          printf("\n");
        
          printf("\nRaisonnement en cours...");
          moteur_Raisonnement3();
    
    }
    
    
}

