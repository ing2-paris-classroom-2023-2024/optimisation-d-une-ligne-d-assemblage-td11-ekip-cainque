//
// Created by marti on 24/11/2023.
///
#ifndef LIGNE_ASSEMBLAGE_PRECEDENCES_H
#define LIGNE_ASSEMBLAGE_PRECEDENCES_H
#include "stdio.h"
#include "stdlib.h"
#include "Graphe.h"

void chill(char* filename){
    int op1,op2;
    int nbsommets=0,nbarrete=0;
    FILE* fichier = fopen(filename, "r");
    if (!fichier){
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    while(fscanf(fichier, "%d %d", &op1, &op2) == 2){
        //printf("%d-->%d\n",op1,op2);
        if(op1 > nbsommets){
            nbsommets = op1;
        }
        if(op2 > nbsommets){
            nbsommets = op2;
        }
        nbarrete++;
    }
    printf("%d\n",nbsommets);
    printf("%d\n",nbarrete);

    fseek(fichier,0,0);
    Sommet* Tab_Sommet = malloc(sizeof(Sommet)*nbsommets);
    int tab = malloc((sizeof(int)*1));

    int i;
    for(i=1;i<=nbsommets;i++){
        int* tab_predecesseur = malloc((sizeof(int)*nbarrete));
        Sommet temp = {i+1,tab,0,tab_predecesseur,0,0,0,0};
        Tab_Sommet[i]= temp;
        //printf("%d \n", temp.valeur);
    }

    while(fscanf(fichier, "%d %d", &op1, &op2) == 2){
        Sommet temp = Tab_Sommet[op2];
        int* tab_temp = temp.Liste_ope_pres;
        tab_temp[temp.place_liste] = op1;
        temp.place_liste++;
        temp.Liste_ope_pres = tab_temp;
        Tab_Sommet[op2] = temp;
        printf("%d, ",temp.place_liste);
    }
    /*for(i=1;i<=nbsommets;i++){
        for(int j=1;j<=nbarrete;j++){
            printf("%d, ",Tab_Sommet[i].Liste_ope_pres[j]);
        }
        printf("\n");
    }*/
    for (i = 0; i < nbsommets; i++) {
        free(Tab_Sommet[i].Liste_ope_pres);
    }

    free(Tab_Sommet);
}

#endif //LIGNE_ASSEMBLAGE_PRECEDENCES_H