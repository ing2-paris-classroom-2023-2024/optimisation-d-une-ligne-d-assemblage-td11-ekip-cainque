//
// Created by marti on 24/11/2023.
//
#ifndef LIGNE_ASSEMBLAGE_PRECEDENCES_H
#define LIGNE_ASSEMBLAGE_PRECEDENCES_H
#include "stdio.h"
#include "stdlib.h"
#include "Graphe.h"

int chill(char* filename){
    FILE* ifs = fopen(filename, "r");
    if (!ifs){
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    return 0;
};

#endif //LIGNE_ASSEMBLAGE_PRECEDENCES_H