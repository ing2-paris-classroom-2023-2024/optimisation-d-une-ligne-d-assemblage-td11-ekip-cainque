#ifndef LIGNE_ASSEMBLAGE_GRAPHE_H
#define LIGNE_ASSEMBLAGE_GRAPHE_H

typedef struct Sommet{
    int Liste_Contrainte;
    int Liste_ope_pres;
    int Etape_debut; //1 oui, 0 non
    int Etape_fin; //1 oui, 0 non
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
}Graphe;


#endif //LIGNE_ASSEMBLAGE_GRAPHE_H
