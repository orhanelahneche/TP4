#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"


/*** Utilitaires ***/

// creer vaccin
T_ListeVaccins* creerVaccin(char* marque, int nb_vaccins)
{
    T_ListeVaccins * V1=malloc(sizeof(T_ListeVaccins));
    V1->marque=malloc(sizeof(char)*50);
    strcpy(V1->marque, marque);
    V1->nombre_de_vaccins=nb_vaccins;
    V1->suivant=NULL;
    return V1;
}

// creer ABR
T_ABR * creerABR(char* date)
{
    T_ABR * a = malloc(sizeof(T_ABR));
    a->date=malloc(sizeof(char)*10);
    strcpy(a->date, date);
    a->listevaccins=NULL;
    a->fils_droit=NULL;
    a->fils_gauche=NULL;
    return a;
}

// Parcours d'ABR

T_ABR* search_geq(T_ABR* a, char *date)
// Recherche un noeud de la date pass�e en argument dans un ABR, ou renvoie NULL si le noeud n'existe pas
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
// Renvoie le noeud parent du noeud qui doit �tre ins�r�
{
    if (strcmp(a->date,date)>0) // a->date > date recherch�e -> on va voir � gauche
    {
        if(a->fils_gauche==NULL) return a;
        else return search_geq_ajout(a->fils_gauche, date);
    }
    else { // ajout � droite
        if (a->fils_droit==NULL) return a;
        else return search_geq_ajout(a->fils_droit, date);
    }
}

/*** Fonctions ***/

// question 1

void ajouterVaccinL(T_ListeVaccins** listeVaccins, char* marque, int nb_vaccins)
/* Incr�mente la quantit� d'un vaccin particulier au sein d'une liste, ou l'ajoute en fin de liste
 * si le vaccin n'y figure pas encore */
{
    T_ListeVaccins* parcours = *listeVaccins;

    // Cas de la liste nulle : on l'initialise avec le nouveau vaccin
    if (*listeVaccins == NULL)
    {
        T_ListeVaccins* V = creerVaccin(marque, nb_vaccins);
        *listeVaccins = V;
        return; // hein ?
    }
    // Sinon on parcourt la liste pour rechercher le vaccin
    while (strcmp(marque, parcours->marque) != 0 && parcours->suivant != NULL)
    {
        parcours = parcours->suivant;
    }

    // Sortie de la boucle : cas o� on a trouv� le vaccin
    if (strcmp(marque, parcours->marque) == 0)
    {
        parcours->nombre_de_vaccins += nb_vaccins;
    }else // Dernier cas : le vaccin ne se trouve pas dans la liste, on le cr�e et on l'ajoute en fin de liste
    {
        parcours->suivant = creerVaccin(marque, nb_vaccins);
        parcours->suivant->suivant = NULL;
    }
}

// question 2

void ajouterVaccinA(T_ABR** abr, char* date, char* marque, int nb_vaccins)
{
    // On va chercher dans l'arbre le noeud correspondant � la date pass�e en argument
    T_ABR* a = search_geq(*abr, date);

    // Si on a trouv� le noeud on ajoute le vaccin � sa liste de vaccins
    if (a!=NULL) ajouterVaccinL(&(a->listevaccins), marque, nb_vaccins);

    // Sinon on ajoute un nouveau noeud � l'arbre et on y ajoute le vaccin
    else{
        a = search_geq_ajout(*abr, date); // on recherche le parent du noeud � ins�rer
        T_ABR * new = creerABR(date); // on cr�e un nouvel objet noeud avec la date voulue
        if (strcmp(a->date,date) > 0) a->fils_gauche = new; // on regarde si le nouveau noeud doit devenir le fils gauche de son parent
        else a->fils_droit = new; // sinon il doit devenir son fils droit
        ajouterVaccinL(&(new->listevaccins), marque, nb_vaccins); // on ajoute le vaccin(marque+qt�) dans la liste de vaccins du nouveau noeud cr��
    }
}

// question 3

void afficherStockL(T_ListeVaccins* listeVaccins)
// Affiche tous les stocks de vaccins disponibles de la liste pass�e en argument
{
    T_ListeVaccins * parcours = listeVaccins;
    if (parcours != NULL) printf("Stocks disponibles : \n");
    else printf("Il n'y a pas de stock disponible.\n");
    //On parcourt la liste en affichant la marque et le nombre de vaccin � chaque fois
    while(parcours!=NULL)
    {
        printf("    %s : %d\n", parcours->marque, parcours->nombre_de_vaccins);
        parcours=parcours->suivant;
    }
}

// question 4

void afficherStockA(T_ABR* abr)
{
    if (abr != NULL)
    {
        afficherStockA(abr->fils_gauche);
        printf("Stock pour la date : %s\n", abr->date);
        afficherStockL(abr->listevaccins);
        printf("\n");
        afficherStockA(abr->fils_droit);
    }
}

// question 5

int compterVaccins(T_ABR* abr, char*marque)
{
    if (abr!=NULL)
    {
        int nb = 0;
        // on regarde dans la racine de l'arbre
        if (abr->listevaccins != NULL)
        {
            T_ListeVaccins *parcours = abr->listevaccins; // NB: peut �tre cr�er une sous-fonction responsable de la recherche dans une liste de vacc
            while (parcours != NULL) {
                if (strcmp(parcours->marque, marque) == 0) {
                    nb += parcours->nombre_de_vaccins;
                    break;
                }
                parcours = parcours->suivant;
            }
        }
        // s'il n'y a aucun fils on s'arr�te l�
        if (abr->fils_gauche == NULL && abr->fils_droit == NULL) return nb;
        // s'il y a seulement un fils droit on rappelle la fonction avec le sous-arbre droit
        if (abr->fils_gauche == NULL) {
            return (nb + compterVaccins(abr->fils_droit, marque));
        // s'il y a seulement un fils gauche on rappelle la fonction avec le sous-arbre gauche
        } else if (abr->fils_droit == NULL) {
            return (nb + compterVaccins(abr->fils_gauche, marque));
        // sinon: il y a un fils gauche et un fils droit on va chercher dans les 2 sous-arbres
        } else return (nb + compterVaccins(abr->fils_gauche, marque) + compterVaccins(abr->fils_droit, marque));
    }
    return 0;
}


// question 6

void deduireVaccinL(T_ListeVaccins** listeVaccins, char* marque, int nb_vaccins)
/* Diminue le nombre de vaccins d'une marque parmi une liste de vaccins. Supprime le vaccin de la liste si ce nombre tombe � 0 */
{
    T_ListeVaccins* parcours = *listeVaccins;

    if (listeVaccins == NULL)
    {
        printf("Liste de vaccins vide.\n");
        exit(0);
    }
    // on regarde si le vaccin est en t�te de liste : parcours = t�te
    if (strcmp(parcours->marque, marque) == 0)
    {
        if (parcours->nombre_de_vaccins <= nb_vaccins)
        {
            // printf("Le vaccin %s n'aura plus de stock et sera supprime. Poursuivre l'operation ?\nVotre reponse (o/n): ", marque);
            // while � finir
            *listeVaccins = parcours->suivant;
            free(parcours);
            printf("Vaccin supprime pour cette date.\n\n");
        }
        else parcours->nombre_de_vaccins -= nb_vaccins;
    }
    // sinon on parcourt la liste en regardant le suivant � chaque fois
    else
    {
        while ((parcours->suivant != NULL) && (strcmp(parcours->suivant->marque, marque) != 0))
            parcours = parcours->suivant;

        // sortie de la boucle
        if (parcours->suivant == NULL)
            printf("Le vaccin n'existe pas dans la liste.\n");

        else // le vaccin suivant est celui qui doit �tre modifi� ou supprim�
        {
            T_ListeVaccins* vaccinModif = parcours->suivant;
            if (vaccinModif->nombre_de_vaccins <= nb_vaccins)
            {
                // printf("Le vaccin %s n'aura plus de stock et sera supprime. Poursuivre l'operation ?\nVotre reponse (o/n): ", marque);
                // while � finir
                printf("vaccin supprim%c pour cette date\n", 130);
                parcours->suivant = vaccinModif->suivant;
                free(vaccinModif);
            }
            else vaccinModif->nombre_de_vaccins -= nb_vaccins;
        }
    }
}

// question 7

/*** FONCTIONS PRELIMINAIRES ***/

int compterNoeuds(T_ABR* abr)
{
    if (abr == NULL) return 0;
    else return 1 + compterNoeuds(abr->fils_gauche) + compterNoeuds(abr->fils_droit);
}


// Retourner le pr�decesseur d'un noeud qui a un sous-arbre gauche (c'est-�-dire que le pr�decesseur est forc�ment situ� dans ce sous-arbre gauche)
T_ABR* predecesseurDunNoeudAvecFilsGauche(T_ABR* abr)
// � priori cette fonction est appel�e seulement si un noeud avec un fils gauche et un fils droit doit �tre supprim� (on a donc pas besoin de traiter le cas ou le pr�d�cesseur est le parent gauche du noeud consid�r�)
{
    T_ABR* pred = NULL;
    if (abr->fils_gauche != NULL)
    {
        pred = abr->fils_gauche;
        while (pred->fils_droit != NULL)
            pred = pred->fils_droit;
    }
    else
    {
        printf("pas de fils gauche, erreur\n");
        exit(EXIT_FAILURE);
    }
    return pred;
}


// Supprimer un noeud dans un arbre, recherche par sa date. Retourne le noeud qui prend sa place.
T_ABR* supprimerNoeud(T_ABR* abr, char* date)
{
    if (abr == NULL)
    {
        // printf("noeud nul\n");
        return NULL;
    }
    // on recherche le noeud
    else if (strcmp(abr->date, date) > 0)
    {
        abr->fils_gauche = supprimerNoeud(abr->fils_gauche, date);
    }
    else if (strcmp(abr->date, date) < 0)
    {
        abr->fils_droit = supprimerNoeud(abr->fils_droit, date);
    }

    else // abr est le noeud qui doit �tre supprim�
    {
        if (abr->fils_gauche == NULL)
        {
            T_ABR* retour = abr->fils_droit;
            free(abr);
            return retour;
        }
        else if (abr->fils_droit == NULL)
        {
            T_ABR* retour = abr->fils_gauche;
            free(abr);
            return retour;
        }
        else
        {
            T_ABR* pred = predecesseurDunNoeudAvecFilsGauche(abr);
            // on modifie les cl�s du noeud qui devait �tre supprim�
            abr->date = pred->date;
            abr->listevaccins = pred->listevaccins;
            // on supprime son pr�decesseur
            abr->fils_gauche = supprimerNoeud(abr->fils_gauche, pred->date);
        }
    }
    return abr;
}


// Retourner la quantit� de vaccins d'une certaine marque dans un noeud (� une date) donn�(e)
int compterVaccinsNoeud(T_ABR* noeud, char* marque)
{
    int nombre = 0;
    if (noeud->listevaccins != NULL)
    {
        T_ListeVaccins *parcours = noeud->listevaccins; // NB: peut �tre cr�er une sous-fonction responsable de la recherche dans une liste de vacc
        while (parcours != NULL) {
            if (strcmp(parcours->marque, marque) == 0) {
                nombre += parcours->nombre_de_vaccins;
                break;
            }
            parcours = parcours->suivant;
        }
    }
    return nombre;
}


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
}


int noeud_minimal_marque(T_ABR * rac, T_ABR ** min, char* marque){
    int i=0;
    if (rac->fils_gauche !=NULL) i=noeud_minimal_marque(rac->fils_gauche, min, marque);
    if (i!=1) {
        if (marqueEstDedans(rac, marque)) {
            // printf("on a trouvex gros\n");
            i = 1;
            *min=rac;
            // printf("%s\n", (*min)->date);
        }
    }
    if(i!=1){
        if (rac->fils_droit!=NULL) i=noeud_minimal_marque(rac->fils_droit, min, marque);
    }
    return i;
}

/*** FONCTION FINALE ***/

void deduireVaccinA(T_ABR** abr, char*marque, int nb_vaccins)
{
    int nombreRestant = nb_vaccins;

    int nombreDansCeNoeuds = 0;
    T_ABR* noeudMinimal = malloc(sizeof(T_ABR));

    // rechercher le noeud minimal
    while (*abr != NULL && nombreRestant > 0)
    {
        if (noeud_minimal_marque(*abr, &noeudMinimal, marque) == 1) // la fonction a trouv� un noeud minimal qui contenait le vaccin
            // on r�cup�re le nombre de vaccins du noeud
            nombreDansCeNoeuds = compterVaccinsNoeud(noeudMinimal, marque);
            // on d�cr�mente le nombre de vaccins du noeud
            deduireVaccinL(&(noeudMinimal->listevaccins), marque, nombreRestant);
            // on met � jour le nombre de vaccins
            nombreRestant -= nombreDansCeNoeuds;

            // on regarde si on doit le supprimer
            if (noeudMinimal->listevaccins == NULL)
            {
                *abr = supprimerNoeud(*abr, noeudMinimal->date);
            }
        else
        {
            printf("plus de noeud contenant cette marque\n");
            // return 0;
        }
    }
}




