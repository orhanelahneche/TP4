//
// Created by Anne LAHNECHE on 07/05/2021.
//

#include "fonction.h"

T_ListeVaccins * creerVaccin(char* marque, int nb_vaccins){
    T_ListeVaccins * V1=malloc(sizeof(T_ListeVaccins));
    V1->marque=malloc(sizeof(char)*50);
    strcpy(V1->marque, marque);
    V1->nombre_de_vaccins=nb_vaccins;
    V1->suivant=NULL;
    return V1;
}

T_ABR * creerABR(char* date){
    T_ABR * a = malloc(sizeof(T_ABR));
    a->date=malloc(sizeof(char)*10);
    strcpy(a->date, date);
    a->listevaccins=NULL;
    a->fils_droit=NULL;
    a->fils_gauche=NULL;
    return a;
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

T_ABR* search_geq_ajout(T_ABR* a, char *date)
{
    if (a!=NULL) {
        if (strcmp(a->date, date) > 0) {
            if (a->fils_gauche == NULL) return a;
            else return search_geq_ajout(a->fils_gauche, date);
        } else {
            if (a->fils_droit == NULL) return a;
            else return search_geq_ajout(a->fils_droit, date);
        }
    }
}

void ajouterVaccinL(T_ListeVaccins** listeVaccins, char* marque, int nb_vaccins) {
    T_ListeVaccins* parcours = *listeVaccins;
    if (*listeVaccins==NULL){ //gestion du cas où on doit insérer en tête de liste parce que la liste est nulle
        T_ListeVaccins* V =creerVaccin(marque, nb_vaccins);
        *listeVaccins = V;
        return;
    }

    while (strcmp(marque, parcours->marque)!=0 && parcours->suivant != NULL){//on parcours la liste
            parcours=parcours->suivant;
    }

    if (strcmp(marque, parcours->marque)==0){//il faut tester ce cas avant ==> cas du dernier élément (parcours->suivant==NULL)
        parcours->nombre_de_vaccins+=nb_vaccins;
    }else{
        parcours->suivant=creerVaccin(marque, nb_vaccins); //le cas où aucun vaccin identique n'est rencontré on crée un nouveau vaccin en fin de liste
        parcours->suivant->suivant=NULL;
    }

};

void ajouterVaccinA(T_ABR** abr, char*date, char*marque, int nb_vaccins){
    if (abr==NULL) {
        printf("il n'y a pas d'ABR initialisé\n");
        return;
    }
    T_ABR * a = search_geq(*abr, date); //on cherche dans l'arbre le noeud correspondant à l'arbre
    if (a!=NULL) ajouterVaccinL(&(a->listevaccins), marque, nb_vaccins); //on y ajoute le vaccin
    else{//si on ne trouve pas de noeud existant on va créer un noeud et créer le stock correspondant dedans
        a = search_geq_ajout(*abr, date);
        T_ABR * new = creerABR(date);
        if (strcmp(a->date,date)>0) a->fils_gauche=new;
        else a->fils_droit=new;
        ajouterVaccinL(&(new->listevaccins), marque, nb_vaccins);
    }
};

void afficherStockL(T_ListeVaccins* listeVaccins){
    T_ListeVaccins * parcours = listeVaccins;
    if (parcours!=NULL) printf("stocks disponibles : \n");
    else printf("il n'y a pas de stock disponible\n");
    while(parcours!=NULL){ //on parcours la liste en affichant la marque et le nombre de vaccin à chaque fois
        printf("    %s : %d\n", parcours->marque, parcours->nombre_de_vaccins);
        parcours=parcours->suivant;
    }
};

void afficherStockA(T_ABR* abr){
    if (abr==NULL){
        printf("il n'y a pas d'ABR initialisé\n");
        return;
    }
    if (abr->fils_gauche!=NULL) afficherStockA(abr->fils_gauche);
    printf("stock pour la date : %s\n", abr->date);
    afficherStockL(abr->listevaccins);
    printf("\n");
    if (abr->fils_droit!=NULL) afficherStockA(abr->fils_droit);
};

int compterVaccins(T_ABR* abr, char*marque){
    if (abr!=NULL) {
        int nb = 0;
        if (abr->listevaccins != NULL) {
            T_ListeVaccins *parcours = abr->listevaccins;
            while (parcours != NULL) {
                if (strcmp(parcours->marque, marque) == 0) {
                    nb += parcours->nombre_de_vaccins;
                    break;
                }
                parcours = parcours->suivant;
            }
        }
        if (abr->fils_gauche == NULL && abr->fils_droit == NULL) return nb;
        if (abr->fils_gauche == NULL) {
            return (nb + compterVaccins(abr->fils_droit, marque));
        } else if (abr->fils_droit == NULL) {
            return (nb + compterVaccins(abr->fils_gauche, marque));
        } else return (nb + compterVaccins(abr->fils_gauche, marque) + compterVaccins(abr->fils_droit, marque));
    }
    return 0;
};

bool marqueEstDedans(T_ABR *abr, char* marque)
{
    T_ListeVaccins* parcours = abr->listevaccins;

    while (parcours!=NULL && strcmp(parcours->marque, marque)!=0)
    {
        parcours = parcours->suivant;
    }
    if (parcours == NULL)
        return false;
    else
        return true;
} // ok

int noeud_minimal_marque(T_ABR * rac, T_ABR ** min, char* marque){
    int i=0;
    if (rac->fils_gauche !=NULL) i=noeud_minimal_marque(rac->fils_gauche, min, marque);
    if (i!=1) {
        if (marqueEstDedans(rac, marque)) {
            printf("on a trouvex gros\n");
            i = 1;
            *min=rac;
            printf("%s\n", (*min)->date);
        }
    }
    if(i!=1){
        if (rac->fils_droit!=NULL) i=noeud_minimal_marque(rac->fils_gauche, min, marque);
    }
    return i;
}



