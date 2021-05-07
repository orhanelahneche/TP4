//
// Created by Anne LAHNECHE on 07/05/2021.
//

#ifndef TP4_FONCTION_H
#define TP4_FONCTION_H

typedef struct ListeVaccins {
    char* marque;
    int nombre_de_vaccins;
    struct ListeVaccins * suivant;
}T_ListeVaccins;

typedef struct ABR {
    char* date;
    T_ListeVaccins * listevaccins;
    ABR* fils_gauche;
    ABR* fils_droite;
}T_ABR;
#endif //TP4_FONCTION_H
