#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

int main() {

    /* MENU */

    /* TESTS */
    /*
    T_ListeVaccins** listeVaccins = malloc(5*sizeof(T_ListeVaccins*));
    *listeVaccins = creerVaccin("violette", 10);
    ajouterVaccinL(listeVaccins, "orhane", 40);
    ajouterVaccinL(listeVaccins, "louis", 200);
    afficherStockL(*listeVaccins);
    printf("\n*** modif ***\n\n");*/

    // question 6 : déduire vaccin L
    // deduireVaccinL(listeVaccins,"chloe",20); YES
    // deduireVaccinL(listeVaccins, "violette", 20); YES
    // deduireVaccinL(listeVaccins, "violette", 5); YES
    // deduireVaccinL(listeVaccins,"orhane",20); YES
    // deduireVaccinL(listeVaccins, "orhane", 40); YES
    // deduireVaccinL(listeVaccins, "louis", 230);
    // afficherStockL(*listeVaccins);

    /* fonction : compterNoeuds OK
    T_ABR* a = malloc(sizeof(T_ABR));
    T_ABR* b = malloc(sizeof(T_ABR));
    T_ABR* c = malloc(sizeof(T_ABR));
    T_ABR* d = malloc(sizeof(T_ABR));
    T_ABR* e = malloc(sizeof(T_ABR));

    e->fils_gauche = NULL;
    e->fils_droit = NULL;

    a->fils_gauche = NULL;
    a->fils_droit = NULL;

    c->fils_gauche = NULL;
    c->fils_droit = NULL;

    d->fils_droit = e;
    d->fils_gauche = b;

    b->fils_droit = c;
    b->fils_gauche = a;

    printf("%d noeuds\n", compterNoeuds(d));*/

    // question 7 : déduireVaccinA

    // racine : 35 vaccins moderna
    T_ABR* arbre = creerABR("2021-05-19");
    ajouterVaccinA(&arbre, "2021-05-19", "moderna", 10);
    ajouterVaccinA(&arbre, "2021-05-19", "moderna", 20);
    ajouterVaccinA(&arbre, "2021-05-19", "moderna", 5);

    // fils gauche : 50 vaccins moderna
    ajouterVaccinA(&arbre,"2021-01-03","moderna",50);
    /*ajouterVaccinA(&arbre,"2021-01-03","pfizer",20);
    ajouterVaccinA(&arbre,"2021-01-03","pfizer",30);
    ajouterVaccinA(&arbre,"2021-01-03","astrazeneca",200);*/

    // fils droit : 10 vaccins moderna
    ajouterVaccinA(&arbre,"2021-11-18", "moderna",10);
    ajouterVaccinA(&arbre,"2021-11-18", "pfizer",50);
    ajouterVaccinA(&arbre,"2021-11-18", "astrazeneca",5);

    // bonus
    ajouterVaccinA(&arbre,"2021-07-30", "pfizer", 20);
    ajouterVaccinA(&arbre,"2021-07-30", "pfizer", 20);

    ajouterVaccinA(&arbre, "2022-05-20", "moderna", 30);

    afficherStockA(arbre);

    printf("\n\t*** modif ***\n\n");

    //T_ABR* nouveauFilsDroit = supprimerNoeud(arbre->fils_droit, "2021-11-18");
//
//    deduireVaccinAPile(&arbre, "moderna", 60);
//    afficherStockA(arbre);

// test marqueEstDedans ok
// test char* minimum(T_ABR* abr, char* marque)


    return 0;
}
