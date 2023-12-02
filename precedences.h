//
// Created by marti on 24/11/2023.
//
#ifndef LIGNE_ASSEMBLAGE_PRECEDENCES_H
#define LIGNE_ASSEMBLAGE_PRECEDENCES_H
#include "stdio.h"
#include "stdlib.h"
#include "Graphe.h"

int* Precedences(char* filename, char* filename2){
    int op,op1,op2,i,j,verif;
    float duree;
    int nbarrete=0,nb_sommet=0;

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

    Sommet* Tab_Sommet = malloc(sizeof(Sommet)*nb_sommet);
    int tab = malloc((sizeof(int)*1));
    printf("La liste de tous les sommets :\n|");
    for(i=0;i<nb_sommet;i++){
        int* tab_predecesseur = malloc((sizeof(int)*nb_sommet));
        for(j=0;j<nb_sommet;j++){
            tab_predecesseur[j]=0;
        }
        Sommet temp = {0,tab,0,tab_predecesseur,tab_predecesseur,0,0,0,0,0};
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
    }
    printf("\n");

    int cpt_sommet=0;
    for(i=0;i<nb_sommet;i++){
        if(Tab_Sommet[i].valeur!=0){
            cpt_sommet++;
        }
    }
    printf("Il y a %d sommet(s) dans le graphe\n",cpt_sommet);

    for(i=0;i<nb_sommet;i++){
        while(fscanf(fichier, "%d %d", &op1, &op2) == 2){
            if(Tab_Sommet[i].valeur==op2){
                Tab_Sommet[i].Liste_ope_pres[Tab_Sommet[i].place_liste_pred]=op1;
                Tab_Sommet[i].Liste_prec[Tab_Sommet[i].place_liste_pred]=op1;
                Tab_Sommet[i].place_liste_pred+=1;
                //printf("%d, ",Tab_Sommet[i].place_liste_pred);
            }
        }
        fseek(fichier,0,0);
    }
    int x;
    printf("les predecesseurs de quel sommet vous voulez savoir : ");
    scanf("%d",&x);
    for(i=0;i<nb_sommet;i++){
        if(Tab_Sommet[i].valeur==x){
            for(j=0;j<nb_sommet;j++){
                if(Tab_Sommet[i].Liste_prec[j]!=0){
                    printf("%d, ",Tab_Sommet[i].Liste_prec[j]);
                }
            }
        }
    }
    printf("\n");

    for(i=0;i<nb_sommet;i++){
        for(j=0;j<nb_sommet;j++){
            if(Tab_Sommet[i].valeur!=0){
                if(Tab_Sommet[i].Liste_ope_pres[j]!=0){
                    Tab_Sommet[i].nb_pred++;
                }
            }
        }
        if(Tab_Sommet[i].valeur==0){
            Tab_Sommet[i].nb_pred=-1;
            //printf("%d, ",Tab_Sommet[i].nb_pred);
        }
    }

    int* priorite = malloc((sizeof(int)*cpt_sommet));
    int place_prio = 0;
    for(i=0;i<nb_sommet;i++){
        priorite[i]=0;
    }
    int cpt_moins=0;
    for(i=0;i<nb_sommet;i++){
        if(Tab_Sommet[i].valeur!=0){
            if(Tab_Sommet[i].nb_pred==0){
                priorite[place_prio]=Tab_Sommet[i].valeur;
                place_prio++;
                cpt_moins++;
                //printf("%d, ",Tab_Sommet[i].valeur);
                Tab_Sommet[i].valeur=0;
            }
        }
    }

    int cpt=0;
    while(cpt!=cpt_sommet-cpt_moins){
        for(i=0;i<nb_sommet;i++){
            if(Tab_Sommet[i].valeur!=0){
                for(j=0;j<nb_sommet;j++){
                    for(int x=0;x<cpt_sommet;x++){
                        if(Tab_Sommet[i].Liste_ope_pres[j]!=0){
                            if(Tab_Sommet[i].Liste_ope_pres[j]==priorite[x]){
                                Tab_Sommet[i].nb_pred-=1;
                                Tab_Sommet[i].Liste_ope_pres[j]=0;
                            }
                        }
                    }
                }
                if(Tab_Sommet[i].nb_pred==0){
                    priorite[place_prio]=Tab_Sommet[i].valeur;
                    Tab_Sommet[i].valeur=0;
                    place_prio++;
                    cpt++;
                    //printf("%d, ",cpt);
                }
            }
        }
    }
    printf("Le tableau de priorite est :\n|");
    for(i=0;i<nb_sommet;i++){
        if(priorite[i]!=0){
            printf("%d|",priorite[i]);
        }
    }

    return priorite;
}

#endif //LIGNE_ASSEMBLAGE_PRECEDENCES_H