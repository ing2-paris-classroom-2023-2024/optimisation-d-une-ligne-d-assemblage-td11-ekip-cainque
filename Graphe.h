#ifndef LIGNE_ASSEMBLAGE_GRAPHE_H
#define LIGNE_ASSEMBLAGE_GRAPHE_H

typedef struct Sommet{
    int valeur;
    int Liste_Contrainte;
    int contrainte_actu;
    int Liste_ope_pres;
    int color;
    float debut;
    float fin;
}Sommet;

typedef struct Arc{
    int S1;
    int S2;
    float duree;
}Arc;

typedef struct Graphe{
    int taille;
    int ordre;
    Arc* Liste_Arc;
    float duree_tot;
    float duree_max;
}Graphe;


#endif //LIGNE_ASSEMBLAGE_GRAPHE_H
