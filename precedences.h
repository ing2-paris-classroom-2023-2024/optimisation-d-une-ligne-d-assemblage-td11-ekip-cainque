//
// Created by marti on 24/11/2023.
//
#ifndef LIGNE_ASSEMBLAGE_PRECEDENCES_H
#define LIGNE_ASSEMBLAGE_PRECEDENCES_H
#include "stdio.h"
#include "stdlib.h"
#include "Graphe.h"

void chill(char* filename, char* filename2){
    int op,op1,op2,i,j,verif;;
    float duree;
    int nbarrete=0,cpt_sommet=0,nb_sommet=0;
    FILE* fichier = fopen(filename, "r");
    if (!fichier){
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    FILE* fichier_d = fopen(filename2, "r");
    if (!fichier_d){
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    while(fscanf(fichier, "%d %d", &op1, &op2) == 2){
        if(op1 > nb_sommet){
            nb_sommet = op1;
        }
        if(op2 > nb_sommet){
            nb_sommet = op2;
        }
        nbarrete++;
    }
    fseek(fichier,0,0);
    /*int* tabs = malloc((sizeof(int)*1));
    while(fscanf(fichier, "%d %d", &op1, &op2) == 2){
        if(op1!=tabs[0]||op1!=tabs[0]){

            tabs[0]=op1;
            cpt_sommet++;
        }
    }
    fseek(fichier,0,0);

    //printf("%d",nbarrete);
    cpt_sommet=31;
    if(cpt_sommet==31){
        printf("\nVrai : %d\n", cpt_sommet);
    }
    else{
        printf("\nFaux : %d\n", cpt_sommet);
    }*/

    Sommet* Tab_Sommet = malloc(sizeof(Sommet)*nb_sommet);
    int tab = malloc((sizeof(int)*1));

    for(i=0;i<nb_sommet;i++){
        int* tab_predecesseur = malloc((sizeof(int)*nb_sommet));
        for(j=0;j<nb_sommet;j++){
            tab_predecesseur[j]=0;
        }
        Sommet temp = {0,tab,0,tab_predecesseur,0,0,0,0};
        verif=1;
        while(fscanf(fichier, "%d %d", &op1, &op2) == 2){
            if(Tab_Sommet[i].valeur==op1 || Tab_Sommet[i].valeur==op2){
                verif=0;
            }
            if((op1==i+1 || op2==i+1)&& verif==1){
                temp.valeur=i+1;
                Tab_Sommet[i]= temp;
            }
        }
        if(temp.valeur!=0){
            printf("%d|", temp.valeur);
        }
        fseek(fichier,0,0);
        //printf("%d -> %f\n", temp.valeur,temp.duree);
    }
    printf("\n");
    for(i=0;i<nb_sommet;i++){
        while(fscanf(fichier, "%d %d", &op1, &op2) == 2){
            if(i==0){
                //printf("%d -> %d\n",op1,op2);
            }

            if(Tab_Sommet[i].valeur==op2){
                if(op2==22){
                    //printf("%d, ",op1);
                }
                Tab_Sommet[i].Liste_ope_pres[Tab_Sommet[i].place_liste]=op1;
                Tab_Sommet[i].place_liste+=1;
                //printf("%d, ",Tab_Sommet[i].place_liste);
            }


        }
        fseek(fichier,0,0);
    }
    /*int x=21;
    printf("les predecesseurs de %d sont :\n",Tab_Sommet[x].valeur);
    for(i=0;i<nb_sommet;i++){
        printf("%d, ",Tab_Sommet[x].Liste_ope_pres[i]);
    }*/
    //printf("\n");
    for(j=0;j<nb_sommet;j++){
        Tab_Sommet[j].place_liste=0;
        //printf("%d, ",Tab_Sommet[j].place_liste);
    }
    int* priorite = malloc((sizeof(int)*nb_sommet));
    int place_prio = 0;
    for(i=0;i<nb_sommet;i++){
        priorite[i]=0;
    }
    for(i=0;i<nb_sommet;i++){
        if(Tab_Sommet[i].valeur!=0){
            if(Tab_Sommet[i].Liste_ope_pres[0]==0){
                priorite[place_prio]=Tab_Sommet[i].valeur;
                place_prio++;
                Tab_Sommet[i].valeur=0;
                //printf("%d, ",Tab_Sommet[i].valeur);
            }
        }
    }

    printf("|");
    for(i=0;i<nb_sommet;i++){
        if(priorite[i]!=0){
            printf("%d|",priorite[i]);
        }
    }
}

#endif //LIGNE_ASSEMBLAGE_PRECEDENCES_H