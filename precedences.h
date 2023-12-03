#ifndef LIGNE_ASSEMBLAGE_PRECEDENCES_H
#define LIGNE_ASSEMBLAGE_PRECEDENCES_H

int* Precedences(char* filename){
    int op1,op2,i,j,verif;
    int nbarrete=0,nb_sommet=0;

    //Verification si on peut ouvrir le fichier ou pas
    FILE* fichier = fopen(filename, "r");
    if (!fichier){
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    //Tant que des lignes sont presentes on regarde le sommet le plus eleve
    while(fscanf(fichier, "%d %d", &op1, &op2) == 2){
        if(op1 > nb_sommet){
            nb_sommet = op1;
        }
        if(op2 > nb_sommet){
            nb_sommet = op2;
        }
        nbarrete++;
    }
    fseek(fichier,0,0);//retour a la premiere ligne du fichier

    Sommet* Tab_Sommet = malloc(sizeof(Sommet)*nb_sommet);
    int tab = malloc((sizeof(int)*1));
    //Modification des valeurs de chaque sommet
    for(i=0;i<nb_sommet;i++){
        int* tab_predecesseur = malloc((sizeof(int)*nb_sommet));
        for(j=0;j<nb_sommet;j++){
            tab_predecesseur[j]=0;
        }
        Sommet temp = {0,tab,0,tab_predecesseur,tab_predecesseur,0,0,0,0,0};
        verif=1;
        //On recupere les valeures presentes dans le fichier
        while(fscanf(fichier, "%d %d", &op1, &op2) == 2){
            if(Tab_Sommet[i].valeur==op1 || Tab_Sommet[i].valeur==op2){
                verif=0;
            }
            if((op1==i+1 || op2==i+1)&& verif==1){
                temp.valeur=i+1;
                Tab_Sommet[i]= temp;
            }
        }
        fseek(fichier,0,0);
    }

    //On compte le nombre de sommet avec une valeur, le nombre de sommets reelement present dans le fichier
    int cpt_sommet=0;
    for(i=0;i<nb_sommet;i++){
        if(Tab_Sommet[i].valeur!=0){
            cpt_sommet++;
        }
    }

    //Pour chaque sommet, on modifie son tableau de precedences contenants les somemts devants etre effectuer avant
    for(i=0;i<nb_sommet;i++){
        while(fscanf(fichier, "%d %d", &op1, &op2) == 2){
            if(Tab_Sommet[i].valeur==op2){
                Tab_Sommet[i].Liste_ope_pres[Tab_Sommet[i].place_liste_pred]=op1;
                Tab_Sommet[i].Liste_prec[Tab_Sommet[i].place_liste_pred]=op1;
                Tab_Sommet[i].place_liste_pred+=1;
            }
        }
        fseek(fichier,0,0);//retour a la premiere ligne du fichier
    }

    //On compte le nombre de predecesseur pour chaque sommet
    for(i=0;i<nb_sommet;i++){
        for(j=0;j<nb_sommet;j++){
            if(Tab_Sommet[i].valeur!=0){
                if(Tab_Sommet[i].Liste_ope_pres[j]!=0){
                    Tab_Sommet[i].nb_pred++;
                }
            }
        }
        if(Tab_Sommet[i].valeur==0){
            Tab_Sommet[i].nb_pred=-1;
        }
    }

    int* priorite = malloc((sizeof(int)*cpt_sommet));
    int place_prio = 0;
    //Creation du tableau de priorite
    for(i=0;i<nb_sommet;i++){
        priorite[i]=0;
    }
    int cpt_moins=0;
    //On remplie le tableau de priorite
    for(i=0;i<nb_sommet;i++){
        if(Tab_Sommet[i].valeur!=0){
            if(Tab_Sommet[i].nb_pred==0){
                priorite[place_prio]=Tab_Sommet[i].valeur;
                place_prio++;
                cpt_moins++;
                Tab_Sommet[i].valeur=0;
            }
        }
    }

    //Triage du tableau en utilisant un tableau de priorite
    int cpt=0;
    while(cpt!=cpt_sommet-cpt_moins){
        for(i=0;i<nb_sommet;i++){
            if(Tab_Sommet[i].valeur!=0){
                for(j=0;j<nb_sommet;j++){
                    for(int x=0;x<cpt_sommet;x++){
                        if(Tab_Sommet[i].Liste_ope_pres[j]!=0){
                            if(Tab_Sommet[i].Liste_ope_pres[j]==priorite[x]){
                                Tab_Sommet[i].nb_pred-=1;
                                Tab_Sommet[i].Liste_ope_pres[j]=0;
                            }
                        }
                    }
                }
                if(Tab_Sommet[i].nb_pred==0){
                    priorite[place_prio]=Tab_Sommet[i].valeur;
                    Tab_Sommet[i].valeur=0;
                    place_prio++;
                    cpt++;
                }
            }
        }
    }
    return priorite;
}

#endif //LIGNE_ASSEMBLAGE_PRECEDENCES_H