#ifndef LIGNE_ASSEMBLAGE_CYCLE_TEMP_H
#define LIGNE_ASSEMBLAGE_CYCLE_TEMP_H

#include <stdio.h>
#include <stdlib.h>
#include "Graphe.h"


void lireOperations(Sommet * ops, int nombreOps, const char* nomFichier) {
    FILE* file = fopen(nomFichier, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    for (int i = 0; i < nombreOps; i++) {
        if (fscanf(file, "%d %f", &ops[i].valeur, &ops[i].duree) != 2) {
            fprintf(stderr, "Erreur de format dans le fichier txt à la ligne %d.\n", i + 1);
            exit(1);
        }
    }

    fclose(file);

    printf("Opérations lues du fichier :\n");
    for (int i = 0; i < nombreOps; i++) {
        printf("Opération %d - Durée : %.2f\n", ops[i].valeur, ops[i].duree);
    }
}

Station* repartirOperations(Sommet * ops, int nombreOps, int* nbStations, float tempsCycle) {
    Station* stations = malloc(sizeof(Station));
    if (stations == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour les stations");
        exit(1);
    }

    stations[0].numStation = 1;
    stations[0].tempsTotal = 0.0;
    stations[0].operations = NULL;
    stations[0].nbOperations = 0;

    for (int i = 0; i < nombreOps; i++) {
        int indexMinTempsTotal = 0;

        for (int j = 1; j < *nbStations; j++) {
            if (stations[j].tempsTotal < stations[indexMinTempsTotal].tempsTotal) {
                indexMinTempsTotal = j;
            }
        }

        if (stations[indexMinTempsTotal].tempsTotal + ops[i].duree > tempsCycle) {
            (*nbStations)++;
            stations = realloc(stations, (*nbStations) * sizeof(Station));
            if (stations == NULL) {
                perror("Erreur lors de l'allocation de mémoire pour les stations");
                exit(1);
            }

            stations[*nbStations - 1].numStation = *nbStations;
            stations[*nbStations - 1].tempsTotal = 0.0;
            stations[*nbStations - 1].operations = NULL;
            stations[*nbStations - 1].nbOperations = 0;

            printf("Step %d: Attribution : Nouvelle Station %d, Opération %d\n", i, *nbStations, ops[i].valeur);

            continue;
        }

        int indexOperation = stations[indexMinTempsTotal].nbOperations++;
        stations[indexMinTempsTotal].operations = realloc(stations[indexMinTempsTotal].operations,
                                                          stations[indexMinTempsTotal].nbOperations * sizeof(Sommet));

        stations[indexMinTempsTotal].operations[indexOperation] = ops[i];
        stations[indexMinTempsTotal].tempsTotal += ops[i].duree;

        printf("Step %d: Attribution : Station %d, Opération %d\n", i, indexMinTempsTotal + 1, ops[i].valeur);
    }

    return stations;
}

void afficherResultats(Station* stations, int nbStations) {
    printf("Résultats :\n");

    for (int i = 0; i < nbStations; i++) {
        printf("Station %d - Temps total : %.2f\n", stations[i].numStation, stations[i].tempsTotal);

        if (stations[i].nbOperations > 0) {
            printf("   Opérations attribuées : \n");

            for (int j = 0; j < stations[i].nbOperations; j++) {
                printf("      Opération %d - Durée : %.2f\n",
                       stations[i].operations[j].valeur, stations[i].operations[j].duree);
            }
        } else {
            printf("   Aucune opération attribuée.\n");
        }

        printf("\n");
    }
}

int compteNombreOps(const char* nomFichier) {
    FILE* file = fopen(nomFichier, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    int nombreOps = 0;
    char buffer[100];

    while (fgets(buffer, 100, file) != NULL) {
        nombreOps++;
    }

    fclose(file);

    return nombreOps;
}

Station *cycle_temp(char* duree_total, char* duree){
    char* liste = duree;
    int nombreOps = compteNombreOps(liste);

    FILE* file = fopen(duree_total, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    float tempsCycle;
    fscanf(file,"%f",&tempsCycle);
    fclose(file);
    int nbStations = 1;

    printf("Nombre d'opérations attendu : %d\n", nombreOps);
    printf("Chemin du fichier : %s\n", liste);

    Sommet * ops = malloc(nombreOps * sizeof(Sommet));
    if (ops == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour ops");
        exit(1);
    }

    lireOperations(ops, nombreOps, liste);
    Station* stations = repartirOperations(ops, nombreOps, &nbStations, tempsCycle);
    afficherResultats(stations, nbStations);

    free(ops);
    for (int i = 0; i < nbStations; i++) {
        free(stations[i].operations);
    }
    free(stations);

    return stations;
}

#endif //LIGNE_ASSEMBLAGE_CYCLE_TEMP_H
