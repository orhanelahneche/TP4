#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

int main() {

    /* MENU */

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

    deduireVaccinA(&arbre, "moderna", 50);

    afficherStockA(arbre); // fonctionne très bien !

    int choix=0;

    T_ABR * a=NULL;
    char * jour =malloc(sizeof(char)*2);
    char * mois =malloc(sizeof(char)*2);
    char * annee=malloc(sizeof(char)*4);
    char * date=malloc(sizeof(char)*10);
    char * marque=malloc(sizeof(char)*50);

    int nb=0;

    while (choix!=6)
    {
        printf("1 : Initialiser un ABR\n");
        printf("2 : Ajouter un nombre de vaccins d%cune marque dans un ABR par une date indiqu%ce\n",39,130);
        printf("3 : Afficher tous les stocks disponibles dans un ABR\n");
        printf("4 : Compter le nombre de vaccins disponible pour une marque indiqu%ce\n",130);
        printf("5 : D%cduire un nombre de vaccins d%cune marque indiqu%ce dans un ABR\n",130,39,130);
        printf("6 : Quitter\n");
        fflush(stdin);
        scanf("%d", &choix);
        switch (choix) {
            case 1 :
                printf("Avec quelle date voulez vous initialiser le vaccin ?\n");
                printf("Donnez le jour :\n");
                fflush(stdin);
                scanf("%s", jour);
                printf("Donnez le mois :\n");
                fflush(stdin);
                scanf("%s", mois);
                printf("Donnez l'annee :\n");
                fflush(stdin);
                scanf("%s", annee);
                date=annee;
                strcat(date, "-");
                strcat(date, mois);
                strcat(date, "-");
                strcat(date,jour);
                a = creerABR(date);
                break;
            case 2 :
                printf("Combien de vaccins voulez-vous ajouter ?\n");
                fflush(stdin);
                scanf("%d", &nb);
                printf("De quel marque sont ces vaccins ?\n");
                fflush(stdin);
                scanf("%s", marque);
                printf("A quelle date voulez-vous ajouter ces vaccins ?\n");
                printf("donnez le jour :\n");
                fflush(stdin);
                scanf("%s", jour);
                printf("Donnez le mois :\n");
                fflush(stdin);
                scanf("%s", mois);
                printf("Donnez l'annee :\n");
                fflush(stdin);
                scanf("%s", annee);
                date=annee;
                strcat(date, "-");
                strcat(date, mois);
                strcat(date, "-");
                strcat(date,jour);
                ajouterVaccinA(&a, date, marque, nb);
                break;
            case 3:
                afficherStockA(a);
                break;
            case 4:
                printf("De quelle marque voulez vous la quantit%c de stock ?\n",130);
                fflush(stdin);
                scanf("%s", marque);
                nb = compterVaccins(a,marque);
                printf("Il y a %d vaccins dans l'ABR pour cette marque.\n", nb);
                break;
            case 5:
                printf("De quelle marque voulez vous r%cduire le stock ?\n",130);
                fflush(stdin);
                scanf("%s", marque);
                printf("Combien de vaccins voulez-vous supprimer ?\n",130);
                fflush(stdin);
                scanf("%d", &nb);
                deduireVaccinA(&a, marque, nb);
                break;
        }
    }

    return 0;
}
