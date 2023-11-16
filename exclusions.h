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
    int compteur_sommet = -1;
    int S1,S2;
    while(fscanf(ifs, "%d %d", &S1, &S2) == 2){
        if((S1 == compteur_sommet+1) || (S2 == compteur_sommet+1)){
            compteur_sommet++;
            if((S1 == compteur_sommet+1) || (S2 == compteur_sommet+1)){
                compteur_sommet++;
            }
        }
        compteur_relation++;
    }
    fclose(ifs); // N'oubliez pas de fermer le fichier après utilisation.

    printf("R: %d\nS: %d", compteur_relation, compteur_sommet+1);
}
