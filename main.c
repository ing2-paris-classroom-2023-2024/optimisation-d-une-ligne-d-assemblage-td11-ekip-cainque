#include "stdio.h"
#include "stdlib.h"
#include "Graphe.h"
#include "exclusions.h"
#include "precedences.h"
#include "cycle_temp.h"

int main(){
    const char* liste = "opduree.txt";
    int nombreOps = compteNombreOps(liste);
    float tempsCycle = 5;
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

    return 0;
}