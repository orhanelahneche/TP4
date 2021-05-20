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


typedef struct Pile Pile;
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


/********** A FAIRE */
// Pile de noeud
Pile* creerPile();
bool pilePleine(Pile* pile);
bool pileVide(Pile* pile);
void empiler(Pile* pile, T_ABR* noeud);
T_ABR* depiler(Pile* pile);

// compter le nombre de noeuds d'un arbre
int compterNoeuds(T_ABR* abr);

// supprimer un noeud d'un abr
void supprimer(T_ABR* abr, T_ABR* noeud);
/************ /

/*** Fonctions ***/

// question 1 CARRE
void ajouterVaccinL(T_ListeVaccins** listeVaccins, char*marque, int nb_vaccins) ;

// question 2 CARRE - o
void ajouterVaccinA(T_ABR** abr, char*date, char*marque, int nb_vaccins) ;

// question 3 CARRE - o
void afficherStockL(T_ListeVaccins* listeVaccins);

// question 4 CARRE - o
void afficherStockA(T_ABR* abr);

// question 5 CARRE - o
int compterVaccins(T_ABR* abr, char*marque);

// question 6 CARRE - v
void deduireVaccinL(T_ListeVaccins** listeVaccins, char*marque, int nb_vaccins);

// question 7 - v
T_ListeVaccins* rechercherVaccinDansUneListe(T_ListeVaccins* liste, char* marque);
int compterVaccinsNoeud(T_ABR* noeud, char* marque);
T_ABR* predecesseurDunNoeudAvecFilsGauche(T_ABR* abr);
T_ABR* supprimerVaccin(T_ABR* abr, char* date);
void deduireVaccinA(T_ABR** abr, char*marque, int nb_vaccins);

/* + il faut créer le main !! */


#endif // TP4_H_INCLUDED
