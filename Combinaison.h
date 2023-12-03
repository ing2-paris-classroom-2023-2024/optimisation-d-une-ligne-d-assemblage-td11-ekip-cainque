#ifndef LIGNE_ASSEMBLAGE_COMBINAISON_H
#define LIGNE_ASSEMBLAGE_COMBINAISON_H

Station* RepartitionStation(Sommet* ops, int nombreOps, int* nbStations, float tempsCycle) {
    Station* stations = malloc(sizeof(Station));
    if (stations == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour les stations");
        exit(1);
    }
    Station initial = {.numStation=1,.tempsTotal=0.0,.operations=NULL,.nbOperations=0};
    stations[0] = initial;

    for (int i = 0; i < nombreOps; i++) {

        if (stations[*nbStations].tempsTotal + ops[i].duree > tempsCycle) {
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

        int indexOperation = stations[*nbStations].nbOperations++;
        stations[*nbStations].operations = realloc(stations[*nbStations].operations,stations[*nbStations].nbOperations * sizeof(Sommet));

        stations[*nbStations].operations[indexOperation] = ops[i];
        stations[*nbStations].tempsTotal += ops[i].duree;

        printf("Step %d: Attribution : Station %d, Opération %d\n", i, *nbStations + 1, ops[i].valeur);
    }

    return stations;
}

Sommet* CombineSommet(Sommet* Exclusions, Sommet* TempsCycle,int taille){
    Sommet* tab_combine = malloc(sizeof(Sommet)*taille);
    for(int i=0;i < taille;i++){
        Sommet temp = Exclusions[TempsCycle[i].valeur];
        temp.duree = TempsCycle[i].duree;
        tab_combine[i] = temp;
    }
    return tab_combine;
}

Station* combinaison(int* nbrstation){
    //Station* stations = RepartitionStation(ops, nombreOps, &nbStations, tempsCycle);

    return NULL;
}


#endif //LIGNE_ASSEMBLAGE_COMBINAISON_H
