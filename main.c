#include "stdio.h"
#include "stdlib.h"
#include "Graphe.h"
#include "exclusions.h"
#include "precedences.h"
#include "cycle_temp.h"
#include "Combinaison.h"

int main(){
    Station* stations;
    char* Duree_Max = "duree_max.txt";
    char* Duree_Op = "opduree.txt";
    char* exclusion = "exclusions.txt";
    char* precedences = "precedences.txt";

    int taille, nbrStation=0;
    Sommet* Tab_Sommets_Ex  = exclusions(exclusion,&taille);
    for(int i=0 ; i < taille-1; i++){
        for (int j=0 ; j < taille-i-1; j++){
            if (Tab_Sommets_Ex[j].valeur > Tab_Sommets_Ex[j+1].valeur){
                Sommet tmp = Tab_Sommets_Ex[j];
                Tab_Sommets_Ex[j] = Tab_Sommets_Ex[j+1];
                Tab_Sommets_Ex[j+1] = tmp;
            }
        }
    }
    int* Tab_precedences = Precedences(precedences);
    taille = compteNombreOps(Duree_Op);

    Sommet * Tab_Sommets_temp = malloc(taille * sizeof(Sommet));
    if (Tab_Sommets_temp == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour ops");
        exit(1);
    }
    lireOperations(Tab_Sommets_temp, taille, Duree_Op);

    Sommet* Tab_Sommets = malloc(sizeof(Sommet)*taille);
    Tab_Sommets = CombineSommet(Tab_Sommets_Ex,Tab_Sommets_temp,taille);

    for(int i=0;i<taille;i++){
        printf("\n%d => %f et %d",Tab_Sommets[i].valeur,Tab_Sommets[i].duree, Tab_Sommets[i].Liste_Contrainte[0]);
    }

    return 0;
}