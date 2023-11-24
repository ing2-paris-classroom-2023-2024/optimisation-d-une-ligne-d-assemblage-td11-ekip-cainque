#include "stdio.h"
#include "stdlib.h"
#include "Graphe.h"

void initialisation(char* filename){

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
    int* tableau_vide = malloc(sizeof(int)*compteur_relation);
    int tab2 = malloc((sizeof(int)*1));

    for(int i=0;i<compteur_sommet;i++){
        Sommet temp = {i,tableau_vide,0,tab2,0,0,0};
        Tab_Sommet[i]= temp;
    }

    while(fscanf(ifs, "%d %d", &S1, &S2) == 2){
         Sommet temp = Tab_Sommet[S1];
         int** tab_temp = temp.Liste_Contrainte;
         tab_temp[temp.contrainte_actu] = S2;
         temp.contrainte_actu++;
         temp.Liste_Contrainte = tab_temp;
         Tab_Sommet[S1] = temp;
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

    int color = 1;
    for(int i=0; i < compteur_sommet;i++){
        Sommet temp = Tab_Sommet[i];

    }

    for(int i=0;i<compteur_sommet;i++){
        printf("\n%d: %d",Tab_Sommet[i].valeur,Tab_Sommet[i].contrainte_actu);
    }

    fclose(ifs);

    printf("\n\n\nR: %d\nS: %d", compteur_relation, compteur_sommet);
}
