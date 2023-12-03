#ifndef LIGNE_ASSEMBLAGE_COMBINAISON_H
#define LIGNE_ASSEMBLAGE_COMBINAISON_H

Station* RepartirOp(Sommet * ops, int nombreOps, int* nbStations, float tempsCycle,int* priorite) {
    Station* stations = malloc(sizeof(Station));
    if (stations == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour les stations");
        exit(1);
    }

    stations[0].numStation = 1;
    stations[0].tempsTotal = 0.0;
    stations[0].operations = NULL;
    stations[0].nbOperations = 0;
    stations[0].color = 0;

    for (int i = 0; i < nombreOps; i++){
        Sommet Opactu;
        for(int k=0;k<nombreOps;k++){
            if(priorite[i] == ops[k].valeur){
                Opactu = ops[k];
                break;
            }
        }
        int indexMinTempsTotal = 0;

        for (int j = 1; j < *nbStations; j++) {
            if (stations[j].tempsTotal < stations[indexMinTempsTotal].tempsTotal) {
                indexMinTempsTotal = j;
            }
        }
        if(stations[indexMinTempsTotal].color == NULL){
            stations[indexMinTempsTotal].color = Opactu.color;
        }

        if ((stations[indexMinTempsTotal].tempsTotal + Opactu.duree > tempsCycle) || (stations[indexMinTempsTotal].color != Opactu.color)){
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
            stations[*nbStations - 1].color = NULL;

            continue;
        }

        int indexOperation = stations[indexMinTempsTotal].nbOperations++;
        stations[indexMinTempsTotal].operations = realloc(stations[indexMinTempsTotal].operations,
                                                          stations[indexMinTempsTotal].nbOperations * sizeof(Sommet));

        stations[indexMinTempsTotal].operations[indexOperation] = Opactu;
        stations[indexMinTempsTotal].tempsTotal += Opactu.duree;

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

#endif //LIGNE_ASSEMBLAGE_COMBINAISON_H
