#include "stdio.h"
#include "stdlib.h"
#include "Graphe.h"
#include "exclusions.h"
#include "precedences.h"
#include "cycle_temp.h"

int main(){
    Station* stations;
    char* Duree_Max = "duree_max.txt";
    char* Duree_Op = "opduree.txt";
    char* exclusion = "exclusions.txt";
    char* precedences = "precedences.txt";

    stations = cycle_temp(Duree_Max,Duree_Op);
}