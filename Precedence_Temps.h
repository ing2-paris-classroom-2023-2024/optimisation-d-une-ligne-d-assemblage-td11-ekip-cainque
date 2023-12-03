#ifndef LIGNE_ASSEMBLAGE_PRECEDENCE_TEMPS_H
#define LIGNE_ASSEMBLAGE_PRECEDENCE_TEMPS_H

Station* Precedence_Temp(Sommet * ops, int nombreOps, int* nbStations, float tempsCycle,int* priorite) {
    Station* stations = malloc(sizeof(Station));
    if (stations == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour les stations");
        exit(1);
    }

    //Initialisation de la premiere station
    stations[0].numStation = 1;
    stations[0].tempsTotal = 0.0;
    stations[0].operations = NULL;
    stations[0].nbOperations = 0;

    for (int i = 0; i < nombreOps; i++){
        //On cherche l'operation actuelle en fonction de la priorite
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

        //Si le temps maximum est depasse on change de station
        if (stations[indexMinTempsTotal].tempsTotal + Opactu.duree > tempsCycle) {
            (*nbStations)++;
            stations = realloc(stations, (*nbStations) * sizeof(Station));
            if (stations == NULL) {
                perror("Erreur lors de l'allocation de mémoire pour les stations");
                exit(1);
            }

            //Initialisation de la nouvelle station
            stations[*nbStations - 1].numStation = *nbStations;
            stations[*nbStations - 1].tempsTotal = 0.0;
            stations[*nbStations - 1].operations = NULL;
            stations[*nbStations - 1].nbOperations = 0;

            continue;
        }

        //On ajoute l'operation dans la station
        int indexOperation = stations[indexMinTempsTotal].nbOperations++;
        stations[indexMinTempsTotal].operations = realloc(stations[indexMinTempsTotal].operations,
                                                          stations[indexMinTempsTotal].nbOperations * sizeof(Sommet));

        stations[indexMinTempsTotal].operations[indexOperation] = Opactu;
        stations[indexMinTempsTotal].tempsTotal += Opactu.duree;

    }
    return stations;
}

#endif //LIGNE_ASSEMBLAGE_PRECEDENCE_TEMPS_H
