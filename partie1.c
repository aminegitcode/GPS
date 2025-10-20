#include <stdio.h>
#include <string.h>
#include "partie1.h"

typedef char string[50];

Rule Rules[100];
int nb_rules = 0;

string start[10];
int nb_start = 0;

string finish[10];
int nb_finish = 0;

int parseLine(char source[], string cible[]) {
    int i = 0, n = 0; // i : l'indice de source[], n : l'indice de cible[]
    while (source[i] != ':') i++; // avancer jusqu'à ':'
    i++; // avancer au debut du premier mot
    int j = i; // marquer le debut du premier mot avec j
    while (source[i] != '\n') {
        if (source[i] == ',') {
            // extraire les i-j caractères à partir de j
            memcpy(&cible[n], &source[j], i - j);
            n++;
            j = i + 1; // marquer le debut de la chaîne suivante avec j
        }
        i++;
    }
    return n;
}

// une fonction pour afficher un tableau
void afficher_chaine(string T[], int taille) {
    if (taille == 0) { 
        printf("tableau vide\n");
    } else {
        for (int i = 0; i <= taille - 1; i++) {
            printf("%s,", T[i]);
        }
    }
}

void charger_Fichier(char nomFichier[]) {
    FILE* file = fopen(nomFichier, "r");

    if (file == NULL) {
        printf("impossible d'ouvrir le fichier");
        return;
    }

    char ligne[500];

    while (fgets(ligne, 500, file) != NULL) {
        if (strncmp(ligne, "start:", 6) == 0) {
            nb_start = parseLine(ligne, start);
        }
        else if (strncmp(ligne, "finish:", 7) == 0) {
            nb_finish = parseLine(ligne, finish);
        }
        else if (strncmp(ligne, "action:", 7) == 0) {
            nb_rules++; // on a trouvé une action donc on incrémente nb_rules 
            string temp[] = {""}; // utiliser une variable temporaire pour mettre le contenu
            parseLine(ligne, temp);
            strcpy(Rules[nb_rules - 1].action, temp[0]);
            Rules[nb_rules - 1].deja_appl = 0; // initialiser à 0 pour indiquer que la règle n'a pas été appliquée
        }
        else if (strncmp(ligne, "preconds:", 9) == 0) {
            Rules[nb_rules - 1].nb_preconds = parseLine(ligne, Rules[nb_rules - 1].preconds);
        }
        else if (strncmp(ligne, "add:", 4) == 0) {
            Rules[nb_rules - 1].nb_add = parseLine(ligne, Rules[nb_rules - 1].add);
        }
        else if (strncmp(ligne, "delete:", 7) == 0) {
            Rules[nb_rules - 1].nb_delete = parseLine(ligne, Rules[nb_rules - 1].delete);
        }
    }

    printf("Le Fichier est charge correctement\n");
    fclose(file);
}

// pour afficher le contenu du fichier 
void afficher_Fichier() {
    // afficher l'Etat initial
    printf("\nstart:");
    afficher_chaine(start, nb_start);

    // afficher l'Etat final
    printf("\nfinish:");
    afficher_chaine(finish, nb_finish);

    // afficher les règles
    for (int i = 0; i < nb_rules; i++) {
        printf("\n****\n");

        // action
        printf("action:%s", Rules[i].action);

        // preconditions
        printf("\npreconds:");
        afficher_chaine(Rules[i].preconds, Rules[i].nb_preconds);

        // add
        printf("\nadd:");
        afficher_chaine(Rules[i].add, Rules[i].nb_add);

        // delete
        printf("\ndelete:");
        afficher_chaine(Rules[i].delete, Rules[i].nb_delete);
    }
}
  
