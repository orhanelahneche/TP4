//
// Created by Anne LAHNECHE on 07/05/2021.
//

#ifndef TP4_FONCTION_H
#define TP4_FONCTION_H
#include <stdlib.h>
#include <string.h>

typedef struct ListeVaccins {
    char* marque;
    int nombre_de_vaccins;
    struct ListeVaccins * suivant;
}T_ListeVaccins;

typedef struct ABR {
    char* date;
    T_ListeVaccins * listevaccins;
    struct ABR* fils_gauche;
    struct ABR* fils_droit;
}T_ABR;

void ajouterVaccinL(T_ListeVaccins** listeVaccins, char*marque, int nb_vaccins) ;

T_ListeVaccins * creerVaccin(char* marque, int nb_vaccins);

void ajouterVaccinA(T_ABR** abr, char*date, char*marque, int nb_vaccins) ;

T_ABR* search_geq(T_ABR* a, char *date);
#endif //TP4_FONCTION_H
