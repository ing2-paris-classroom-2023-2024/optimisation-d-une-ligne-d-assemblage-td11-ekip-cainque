#include "stdio.h"
#include "stdlib.h"
#include "Graphe.h"

void exclusions(char* filename){

    FILE* ifs = fopen(filename, "r");
    if (!ifs){
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    int compteur_relation = 0;
    int compteur_sommet = 0;
    int S1,S2;
    while(fscanf(ifs, "%d %d", &S1, &S2) == 2){
        if(S1 > compteur_sommet){
            compteur_sommet = S1;
        }
        if(S2 > compteur_sommet){
            compteur_sommet = S2;
        }

        compteur_relation++;
    }
    compteur_sommet++;

    fseek(ifs,0,0);

    Sommet* Tab_Sommet = malloc(sizeof(Sommet)*compteur_sommet);
    int tab2 = malloc((sizeof(int)*1));

    for(int i=0;i<compteur_sommet;i++){
        int* tableau_vide = malloc(sizeof(int)*compteur_relation);
        Sommet temp = {i,tableau_vide,0,tab2,-1,0,0};
        Tab_Sommet[i]= temp;
    }

    while(fscanf(ifs, "%d %d", &S1, &S2) == 2){

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

    for(int i=0 ; i < compteur_sommet-1; i++){
        for (int j=0 ; j < compteur_sommet-i-1; j++){
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

    while (compteur_sommet > compteur_couleur) {

        nbr_exclu = 0;
        for (int i = 0; i < compteur_sommet; i++) {
            tab_exclu[i] = -1;
        }

        for (int i = 0; i < compteur_sommet; i++) {
            Sommet temp = Tab_Sommet[i];
            exclu = 0;

            for (int j = 0; j < nbr_exclu; j++) {
                if (temp.valeur == tab_exclu[j]) {
                    exclu = 1;
                    break;
                }
            }

            if (exclu == 0 && temp.color==-1) {
                temp.color = color;
                compteur_couleur++;

                // Mettre à jour le tableau d'exclusions avec les contraintes du sommet coloré
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


    for (int i = 0; i < compteur_sommet; i++) {
        printf("\n%d: %d", Tab_Sommet[i].valeur, Tab_Sommet[i].color );
    }

    fclose(ifs);

    printf("\n\n\nR: %d\nS: %d", compteur_relation, compteur_sommet);
}