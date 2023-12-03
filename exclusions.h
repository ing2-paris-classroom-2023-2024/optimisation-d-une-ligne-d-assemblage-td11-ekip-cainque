#include "stdio.h"
#include "stdlib.h"
#include "Graphe.h"

Sommet *exclusions(char* filename, int* taille){

    FILE* ifs = fopen(filename, "r");
    if (!ifs){
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    int compteur_relation = 0;
    int compteur_sommet = 0;
    int S1,S2;
    //On cherche le sommet le plus eleve, ca sera notre taille de references
    while(fscanf(ifs, "%d %d", &S1, &S2) == 2){
        if(S1 > compteur_sommet){
            compteur_sommet = S1;
        }
        if(S2 > compteur_sommet){
            compteur_sommet = S2;
        }

        compteur_relation++;
    }
    compteur_sommet++;//On ajoute 1 a la taille de references afin de compter egalement le sommet le plus eleve
    *taille = compteur_sommet;//On modifie la valeur du pointeur taille afin de l'utiliser dans le code principal par la suite
    fseek(ifs,0,0);//Retour au debut du fichier

    Sommet* Tab_Sommet = malloc(sizeof(Sommet)*compteur_sommet);

    //Creation d'un tableau de Sommet
    for(int i=0;i<compteur_sommet;i++){
        int* tableau_vide = malloc(sizeof(int)*compteur_relation);
        Sommet temp = {.valeur=i,.Liste_Contrainte=tableau_vide,.contrainte_actu=0,.color=-1};
        Tab_Sommet[i]= temp;
    }

    //Modification des valeurs de chaque sommet en fonction de ce qu'on recupere dans le fichier texte
    while(fscanf(ifs, "%d %d", &S1, &S2) == 2){
        //Chaque relations est compte pour les deux sommets qui ne peuvent pas etre ensemble
        Sommet temp = Tab_Sommet[S1];
        int* tab_temp = temp.Liste_Contrainte;
        tab_temp[temp.contrainte_actu] = S2;
        temp.contrainte_actu++;
        temp.Liste_Contrainte = tab_temp;
        Tab_Sommet[S1] = temp;

        Sommet temp2 = Tab_Sommet[S2];
        int* tab_temp2 = temp2.Liste_Contrainte;
        tab_temp2[temp2.contrainte_actu] = S1;
        temp2.contrainte_actu++;
        temp2.Liste_Contrainte = tab_temp2;
        Tab_Sommet[S2] = temp2;
    }

    //On trie le tableau de Sommet en fonction du nombre de contraintes
    for(int i=0 ; i < compteur_sommet-1; i++){
        for (int j=0 ; j < compteur_sommet-i-1; j++){
            //Compare le nombre de contraintes de chaque sommet
            if (Tab_Sommet[j].contrainte_actu < Tab_Sommet[j+1].contrainte_actu){
                Sommet tmp = Tab_Sommet[j];
                Tab_Sommet[j] = Tab_Sommet[j+1];
                Tab_Sommet[j+1] = tmp;
            }
        }
    }

    int compteur_couleur = 0, color = 1;
    int exclu = 0;
    int* tab_exclu = malloc(sizeof(int) * compteur_sommet);
    int nbr_exclu = 0;

    //Application de l'algorithme de Whelsh et Powell
    while (compteur_sommet > compteur_couleur){
        nbr_exclu = 0;//On compte le nombre de sommets coloree afin de sortir du while au bon moment
        for (int i = 0; i < compteur_sommet; i++) {
            tab_exclu[i] = -1;
        }

        for (int i = 0; i < compteur_sommet; i++){
            Sommet temp = Tab_Sommet[i];
            exclu = 0;
            //On verifie si le sommet n'est pas dans le tableau d'exclusions
            for (int j = 0; j < nbr_exclu; j++){
                if (temp.valeur == tab_exclu[j]){
                    exclu = 1;
                    break;
                }
            }

            if (exclu == 0 && temp.color == -1){
                //Si le sommet n'est pas encore colore et qu'il ne fait pas partie du tableau d'exclusion
                temp.color = color;
                compteur_couleur++;

                // Mettre à jour le tableau d'exclusions avec les contraintes du sommet colore
                for (int j = 0; j < temp.contrainte_actu; j++) {
                    int* tab_temp = temp.Liste_Contrainte;
                    if (nbr_exclu < compteur_sommet) {
                        tab_exclu[nbr_exclu] = tab_temp[j];
                        nbr_exclu++;
                    }
                }
            }

            Tab_Sommet[i] = temp;
        }

        color++;
    }
    fclose(ifs);
    return Tab_Sommet;
}
