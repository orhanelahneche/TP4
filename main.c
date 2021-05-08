#include <stdio.h>
#include "fonction.h"

int main() {
    /*test pour fonction de recherche dans l'arbre

    printf("Hello, World!\n");
    T_ABR *a= malloc(sizeof(T_ABR));
    T_ABR *g= malloc(sizeof(T_ABR));
    T_ABR *d= malloc(sizeof(T_ABR));
    T_ABR *dg= malloc(sizeof(T_ABR));

    a->date=malloc(sizeof(char)*10);
    g->date=malloc(sizeof(char)*10);
    d->date=malloc(sizeof(char)*10);
    dg->date=malloc(sizeof(char)*10);

    strcpy(g->date, "2021-04-02");
    strcpy(a->date, "2021-06-02");
    strcpy(d->date, "2021-07-02");
    strcpy(dg->date, "2021-05-02");

    a->fils_gauche=g;
    a->fils_droit=d;
    g->fils_droit=dg;
    g->fils_gauche=NULL;
    d->fils_droit=NULL;
    d->fils_gauche=NULL;


    T_ABR * s = search_geq(a, "2021-06-02");

    printf("%s", s->date);

    */

    /*test fonction ajouterVaccinL()
    T_ListeVaccins* v1 = creerVaccin("louis", 4);
    T_ListeVaccins* v2 = creerVaccin("orhane", 5);
    T_ListeVaccins* v3 = creerVaccin("jade", 6);

    v1->suivant=v2;
    v2->suivant=v3;
    v3->suivant=NULL;

    ajouterVaccinL(&v1, "orhane", 7);

    T_ListeVaccins* parcours =v1;

    for(int i=0; i<3; i++){
        printf("%s : %d\n", parcours->marque, parcours->nombre_de_vaccins);
        parcours=parcours->suivant;
    }*/


    return 0;
}
