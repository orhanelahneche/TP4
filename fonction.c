//
// Created by Anne LAHNECHE on 07/05/2021.
//

#include "fonction.h"

T_ListeVaccins * creerVaccin(char* marque, int nb_vaccins){
    T_ListeVaccins * V1=malloc(sizeof(T_ListeVaccins));
    V1->marque=malloc(sizeof(char)*50);
    strcpy(V1->marque, marque);
    V1->nombre_de_vaccins=nb_vaccins;
    return V1;
}

T_ABR* search_geq(T_ABR* a, char *date)
{
    if(a==NULL || strcmp(a->date, date)==0) return a;
    else if (strcmp(a->date,date)>0)
    {
        T_ABR* result =  search_geq(a->fils_gauche, date);
        return result;
    }
    else return search_geq(a->fils_droit, date);
}

void ajouterVaccinL(T_ListeVaccins** listeVaccins, char* marque, int nb_vaccins) {
    T_ListeVaccins* parcours = *listeVaccins;
    if (*listeVaccins==NULL){ //gestion du cas où on doit insérer en tête de liste parce que la liste est nulle
        *listeVaccins = creerVaccin(marque, nb_vaccins);
        return;
    }

    while (strcmp(marque, parcours->marque)!=0 && parcours->suivant != NULL){//on parcours la liste
            parcours=parcours->suivant;
    }

    if (strcmp(marque, parcours->marque)!=0){//il faut tester ce cas avant ==> cas du dernier élément (parcours->suivant==NULL)
        parcours->nombre_de_vaccins+=nb_vaccins;
    }else{
        parcours->suivant=creerVaccin(marque, nb_vaccins);
    }

};

