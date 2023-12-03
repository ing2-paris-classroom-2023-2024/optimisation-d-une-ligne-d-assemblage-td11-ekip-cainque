#ifndef LIGNE_ASSEMBLAGE_CYCLE_TEMP_H
#define LIGNE_ASSEMBLAGE_CYCLE_TEMP_H

void lireOperations(Sommet * ops, int nombreOps, const char* nomFichier) {
    //Ouverture du fichier
    FILE *file = fopen(nomFichier, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    //Lecture du fichier pour stocker les valeurs dans le tableau de sommet
    for (int i = 0; i < nombreOps; i++) {
        if (fscanf(file, "%d %f", &ops[i].valeur, &ops[i].duree) != 2) {
            printf("Erreur de format dans le fichier txt à la ligne %d.\n", i + 1);
            exit(1);
        }
    }

    fclose(file);
}

Station* repartirOperations(Sommet * ops, int nombreOps, int* nbStations, float tempsCycle) {

    Station* stations = malloc(sizeof(Station));
    if (stations == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour les stations");
        exit(1);
    }

    //On initialise la premiere station
    stations[0].numStation = 1;
    stations[0].tempsTotal = 0.0;
    stations[0].operations = NULL;
    stations[0].nbOperations = 0;

    //repartition des operations dans les stations
    for (int i = 0; i < nombreOps; i++) {
        int indexMinTempsTotal = 0;

        //trouver la station avec le temps le plus bas
        for (int j = 1; j < *nbStations; j++) {
            if (stations[j].tempsTotal < stations[indexMinTempsTotal].tempsTotal) {
                indexMinTempsTotal = j;
            }
        }

        //Si quand on ajoute le temps du sommet actuel, ca depasse le temps max, on cree une nouvelle station
        if (stations[indexMinTempsTotal].tempsTotal + ops[i].duree > tempsCycle) {
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

        //On ajoute le sommet dans la station et on effectue les modifications necessaire
        int indexOperation = stations[indexMinTempsTotal].nbOperations++;
        stations[indexMinTempsTotal].operations = realloc(stations[indexMinTempsTotal].operations,
                                                          stations[indexMinTempsTotal].nbOperations * sizeof(Sommet));

        stations[indexMinTempsTotal].operations[indexOperation] = ops[i];
        stations[indexMinTempsTotal].tempsTotal += ops[i].duree;

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
int compteNombreOps(const char* nomFichier){
    //Ouverture du fichier
    FILE* file = fopen(nomFichier, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    int nombreOps = 0;
    char buffer[100];

    //On compte le nombre de ligne dans le fichier, ca correspond on nombre de sommets qui seront present
    while (fgets(buffer, 100, file) != NULL) {
        nombreOps++;
    }

    fclose(file);

    return nombreOps;
}
Station *cycle_temp(char* duree_total, char* duree){
    char* liste = duree;
    int nombreOps = compteNombreOps(liste);

    //On recupere le temps maximum pour chaque station
    FILE* file = fopen(duree_total, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    float tempsCycle;
    fscanf(file,"%f",&tempsCycle);
    fclose(file);

    int nbStations = 1;
    Sommet * ops = malloc(nombreOps * sizeof(Sommet));
    if (ops == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour ops");
        exit(1);
    }

    lireOperations(ops, nombreOps, liste);//Lecture du nombre d'operation
    Station* stations = repartirOperations(ops, nombreOps, &nbStations, tempsCycle);//Repartissions des sommets sur les stations
    afficherResultats(stations, nbStations);//Affichage des stations

    //Liberations de la memoire
    free(ops);
    for (int i = 0; i < nbStations; i++) {
        free(stations[i].operations);
    }
    free(stations);

    return stations;
}

#endif //LIGNE_ASSEMBLAGE_CYCLE_TEMP_H
