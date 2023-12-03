#ifndef LIGNE_ASSEMBLAGE_GRAPHE_H
#define LIGNE_ASSEMBLAGE_GRAPHE_H

typedef struct Sommet{
    int valeur;
    int* Liste_Contrainte;
    int contrainte_actu;
    int* Liste_ope_pres;
    int* Liste_prec;
    int* Liste_succ;
    int nb_pred;
    int place_liste_pred;
    int color;
    float duree;

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

typedef struct {
    int numStation;
    float tempsTotal;
    Sommet* operations;
    int nbOperations;
    int color;
}Station;


#endif //LIGNE_ASSEMBLAGE_GRAPHE_H
