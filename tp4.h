#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/*** Structures ***/

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


typedef struct Pile Pile; // pile de noeud
struct Pile
{
    int sommet ; // Indice de l ’ element au sommet de la pile
    int MAX;
    T_ABR** TableauDeNoeuds;
};


/*** Utilitaires ***/

// créer un vaccin
T_ListeVaccins * creerVaccin(char* marque, int nb_vaccins);

// rechercher un noeud dans un arbre
T_ABR* search_geq(T_ABR* a, char *date);

// rechercher le parent d'un noeud dans un arbre
T_ABR* search_geq_ajout(T_ABR* a, char *date);

// compter le nombre de noeuds d'un arbre
int compterNoeuds(T_ABR* abr);

// supprimer un noeud d'un abr
void supprimer(T_ABR* abr, T_ABR* noeud);


/*** Fonctions ***/

// question 1
void ajouterVaccinL(T_ListeVaccins** listeVaccins, char*marque, int nb_vaccins) ;

// question 2
void ajouterVaccinA(T_ABR** abr, char*date, char*marque, int nb_vaccins) ;

// question 3
void afficherStockL(T_ListeVaccins* listeVaccins);

// question 4
void afficherStockA(T_ABR* abr);

// question 5
int compterVaccins(T_ABR* abr, char*marque);

// question 6
void deduireVaccinL(T_ListeVaccins** listeVaccins, char*marque, int nb_vaccins);

// question 7
int compterVaccinsNoeud(T_ABR* noeud, char* marque);
T_ABR* predecesseurDunNoeudAvecFilsGauche(T_ABR* abr);
T_ABR* supprimerVaccin(T_ABR* abr, char* date);
bool marqueEstDedans(T_ABR *abr, char* marque);
int noeud_minimal_marque(T_ABR * rac, T_ABR ** min, char* marque);
void deduireVaccinA(T_ABR** abr, char*marque, int nb_vaccins);

#endif // TP4_H_INCLUDED
