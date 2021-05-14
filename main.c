#include <stdio.h>
#include "fonction.h"

int main() {
    //test pour fonction de recherche dans l'arbre

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
    dg->fils_droit=NULL;
    dg->fils_gauche=NULL;

    a->listevaccins=NULL;
    g->listevaccins=NULL;
    d->listevaccins=NULL;
    dg->listevaccins=NULL;


    T_ABR * s = search_geq(a, "2021-05-02");
    T_ABR * s1 = search_geq_ajout(a, "2021-08-02");

    printf("%s, %s\n", s->date, s1->date);

    //test fonction ajouterVaccinL()
    T_ListeVaccins* v1 = creerVaccin("louis", 4);
    T_ListeVaccins* v2 = creerVaccin("orhane", 5);
    T_ListeVaccins* v3 = creerVaccin("jade", 6);
    T_ListeVaccins* v4 = NULL;

    v1->suivant=v2;
    v2->suivant=v3;
    v3->suivant=NULL;

    ajouterVaccinL(&v1, "orhane", 7);

    T_ListeVaccins* parcours =v1;

    for(int i=0; i<3; i++){
        printf("%s : %d\n", parcours->marque, parcours->nombre_de_vaccins);
        parcours=parcours->suivant;
    }

    //test fonction ajouterVaccinA()
    dg->listevaccins=v1;
    ajouterVaccinA(&a,"2021-05-02", "raph", 5);
    ajouterVaccinA(&a,"2021-08-02", "emma", 5);
    ajouterVaccinA(&a,"2021-06-02", "raph", 3);
    ajouterVaccinA(&a,"2021-10-02", "raph", 9);


    //T_ListeVaccins* parcours1 =d->fils_droit->listevaccins;
    T_ListeVaccins* parcours1 =dg->listevaccins;


    printf("\ntest ajoutervaccinA(): \n");

    //printf("%s\n", parcours1->marque);

    for(int i=0; i<4; i++){
        printf("%s : %d\n", parcours1->marque, parcours1->nombre_de_vaccins);
        parcours1=parcours1->suivant;
    }

    //test des deux fonctions affiché
    afficherStockL(v1);

    afficherStockA(a);

    //test comptervaccins
    printf("il y a %d vaccins raph\n", compterVaccins(a, "raph"));


    return 0;
}
