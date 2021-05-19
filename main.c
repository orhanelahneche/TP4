#include <stdio.h>
#include "fonction.h"

int main() {
    /*//test pour fonction de recherche dans l'arbre

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
    printf("il y a %d vaccins raph\n", compterVaccins(a, "raph"));*/

    int choix=0;
    T_ABR * a=NULL;
    char * jour =malloc(sizeof(char)*2);
    char * mois =malloc(sizeof(char)*2);
    char * annee=malloc(sizeof(char)*4);
    char * date=malloc(sizeof(char)*10);
    char * marque=malloc(sizeof(char)*50);
    int nb=0;

    while (choix!=6){
        printf("1 : Initialiser un ABR\n");
        printf("2 : Ajouter un nombre de vaccins d’une marque dans un ABR par une date indiquée\n");
        printf("3 : Afficher tous les stocks disponibles dans un ABR\n");
        printf("4 : Compter le nombre de vaccins disponible pour une marque indiquée\n");
        printf("5 : Déduire un nombre de vaccins d’une marque indiquée dans un ABR\n");
        printf("6 : Quitter\n");
        fflush(stdin);
        scanf("%d", &choix);

        switch (choix) {
            case 1 :
                printf("avec quelle date voulez vous initialiser le vaccin ?\n");
                printf("donnez le jour :\n");
                fflush(stdin);
                scanf("%s", jour);
                printf("donnez le mois :\n");
                fflush(stdin);
                scanf("%s", mois);
                printf("donnez l'annee :\n");
                fflush(stdin);
                scanf("%s", annee);
                date=annee;
                strcat(date, "-");
                strcat(date,jour);
                strcat(date, "-");
                strcat(date, mois);
                a = creerABR(date);
                break;

            case 2 :
                printf("combien de vaccins voulez-vous ajouter ?\n");
                fflush(stdin);
                scanf("%d", &nb);
                printf("De quel marque sont ces vaccins ?\n");
                fflush(stdin);
                scanf("%s", marque);
                printf("A quelle date voulez-vous ajouter ces vaccins ?\n");
                printf("donnez le jour :\n");
                fflush(stdin);
                scanf("%s", jour);
                printf("donnez le mois :\n");
                fflush(stdin);
                scanf("%s", mois);
                printf("donnez l'annee :\n");
                fflush(stdin);
                scanf("%s", annee);
                date=annee;
                strcat(date, "-");
                strcat(date,jour);
                strcat(date, "-");
                strcat(date, mois);
                ajouterVaccinA(&a, date, marque, nb);
                break;

            case 3:
                afficherStockA(a);
                break;

            case 4:
                printf("De quelle marque voulez vous la quantité de stock ?\n");
                fflush(stdin);
                scanf("%s", marque);
                nb = compterVaccins(a,marque);
                printf("il y a %d vaccins dans l'ABR pour cette marque.\n", nb);
                break;

            case 5:
                printf("De quelle marque voulez vous réduire le stock ?\n");
                fflush(stdin);
                scanf("%s", marque);
                //insérer la fonction ici
                break;
        }
    }


    return 0;
}
