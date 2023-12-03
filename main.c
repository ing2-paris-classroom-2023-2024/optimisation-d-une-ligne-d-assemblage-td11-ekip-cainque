#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Graphe.h"
#include "exclusions.h"
#include "precedences.h"
#include "cycle_temp.h"
#include "Combinaison.h"
#include "Precedence_Temps.h"

int main(){
    char* Duree_Max = "duree_max.txt";
    char* Duree_Op = "opduree.txt";
    char* exclusion = "exclusions.txt";
    char* precedences = "precedences.txt";

    //Recuperation temps total
    FILE* file = fopen(Duree_Max, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    float tempsCycle;
    fscanf(file,"%f",&tempsCycle);
    fclose(file);

    //Recuperation de l'exclusion
    int taille, nbStations = 1;
    Sommet* Tab_Sommets_Ex  = exclusions(exclusion,&taille);
    int taille_ex = taille;
    for(int i=0 ; i < taille-1; i++){
        for (int j=0 ; j < taille-i-1; j++){
            if (Tab_Sommets_Ex[j].valeur > Tab_Sommets_Ex[j+1].valeur){
                Sommet tmp = Tab_Sommets_Ex[j];
                Tab_Sommets_Ex[j] = Tab_Sommets_Ex[j+1];
                Tab_Sommets_Ex[j+1] = tmp;
            }
        }
    }

    //Recuperation de l'ordre de priorite
    int* Tab_precedences = Precedences(precedences);

    //Recuperation du temps de chaque Op
    taille = compteNombreOps(Duree_Op);
    Sommet * Tab_Sommets_temp = malloc(taille * sizeof(Sommet));
    if (Tab_Sommets_temp == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour ops");
        exit(1);
    }
    lireOperations(Tab_Sommets_temp, taille, Duree_Op);

    //Combinaison de toutes les informations
    Sommet* Tab_Sommets = malloc(sizeof(Sommet)*taille);
    Tab_Sommets = CombineSommet(Tab_Sommets_Ex,Tab_Sommets_temp,taille);

    int choix;
    printf("\nQue voulez vous faire ?"
           "\n1)Affichage de la couleur de chaque sommet(conditions d'exclusions)"
           "\n2)Affichage des stations en fonction de la precedences et du temps(conditions de precedences et de temps)"
           "\n3) Affichage selon les 3 conditions"
           "\nChoix: ");
    scanf("%d",&choix);
    if(choix == 1){
        for(int i=0;i<taille_ex;i++){
            printf("\nSommet n:%d => Couleur: %d", Tab_Sommets_Ex[i].valeur,Tab_Sommets_Ex[i].color);
        }
    }
    else if(choix == 2){
        Station* stationsprec = Precedence_Temp(Tab_Sommets,taille,&nbStations,tempsCycle,Tab_precedences);
        afficherResultats(stationsprec,nbStations);
    }
    else if(choix == 3){
        Station* stations_trio = RepartirOp(Tab_Sommets,taille,&nbStations,tempsCycle,Tab_precedences);
        afficherResultats(stations_trio,nbStations);
    }
    else{
        printf("\nLe choix n'est pas valide.");
    }

    return 0;
}