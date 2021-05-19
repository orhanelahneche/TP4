#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"


/*** Utilitaires ***/

// Créations

// vaccin
T_ListeVaccins* creerVaccin(char* marque, int nb_vaccins)
{
    T_ListeVaccins * V1=malloc(sizeof(T_ListeVaccins));
    V1->marque=malloc(sizeof(char)*50);
    strcpy(V1->marque, marque);
    V1->nombre_de_vaccins=nb_vaccins;
    V1->suivant=NULL;
    return V1;
}

// ABR
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
// Recherche un noeud de la date passée en argument dans un ABR, ou renvoie NULL si le noeud n'existe pas
{
    if(a==NULL || strcmp(a->date, date)==0) return a;
    else if (strcmp(a->date,date)>0)
    {
        T_ABR* result =  search_geq(a->fils_gauche, date);
        return result;
    }
    else return search_geq(a->fils_droit, date);
}

/* pourquoi on ne ferait pas simplement:
if(a==NULL || strcmp(a->date, date)==0) return a;
    else if (strcmp(a->date,date)>0)
    {
        return search_geq(a->fils_gauche, date);
    }
    else return search_geq(a->fils_droit, date);
*/

T_ABR* search_geq_ajout(T_ABR* a, char *date)
// Renvoie le noeud parent du noeud qui doit être inséré
{
    if (strcmp(a->date,date)>0)
    {
        if(a->fils_gauche==NULL) return a;
        else return search_geq_ajout(a->fils_gauche, date);
    }
    else {
        if (a->fils_droit==NULL) return a;
        else return search_geq_ajout(a->fils_droit, date);
    }
}

// Fonctions utiles à la manipulation de la pile question 7

Pile* creerPile(int max)
{
    Pile* nvPile = malloc(sizeof(Pile));
    if (nvPile!=NULL)
    {
        nvPile->sommet = 0;
        nvPile->MAX = max;
        nvPile->TableauDeNoeuds = malloc(max*sizeof(T_ABR*)); // max sera égal nombre de noeuds dans l'abr / la place est déjà réservée pour les structures de noeuds
    }
    return nvPile;
}

bool pilePleine(Pile* pile)
{
    if (pile == NULL)
        exit(EXIT_FAILURE);
    return pile->sommet == pile->MAX;
}

bool pileVide(Pile* pile)
{
    if (pile == NULL)
        exit(EXIT_FAILURE);
    return pile->sommet == 0;
}

void empiler(Pile* pile, T_ABR* noeud)
{
    if (pile == NULL)
    {
        printf("La pile n'existe pas.\n");
        return 0;
    }
    if (pilePleine(pile))
    {
        printf("Debordement par exces.");
        return 0;
    }
    pile->TableauDeNoeuds[pile->sommet] = noeud;
    pile->sommet ++;
    return 1;
}

T_ABR* depiler(Pile* pile)
{
    if (pile == NULL)
    {
        printf("La pile n'existe pas.\n");
        exit(EXIT_FAILURE);
    }
    if (pileVide(pile))
    {
        printf("Debordement par defaut.\n");
        exit(EXIT_FAILURE);
    }
    pile->sommet --;
    return pile->TableauDeNoeuds[pile->sommet];
}

int compterNoeuds(T_ABR* abr)
{
    if (abr == NULL) return 0;
    else return 1 + compterNoeuds(abr->fils_gauche) + compterNoeuds(abr->fils_droit);
}

/*** Fonctions ***/

// question 1

void ajouterVaccinL(T_ListeVaccins** listeVaccins, char* marque, int nb_vaccins)
/* Incrémente la quantité d'un vaccin particulier au sein d'une liste, ou l'ajoute en fin de liste
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

    // Sortie de la boucle : cas où on a trouvé le vaccin
    if (strcmp(marque, parcours->marque) == 0)
    {
        parcours->nombre_de_vaccins += nb_vaccins;
    }else // Dernier cas : le vaccin ne se trouve pas dans la liste, on le crée et on l'ajoute en fin de liste
    {
        parcours->suivant = creerVaccin(marque, nb_vaccins);
        parcours->suivant->suivant = NULL;
    }
}

// question 2

void ajouterVaccinA(T_ABR** abr, char* date, char* marque, int nb_vaccins)
{
    // On va chercher dans l'arbre le noeud correspondant à la date passée en argument
    T_ABR* a = search_geq(*abr, date);

    // Si on a trouvé le noeud on ajoute le vaccin à sa liste de vaccins
    if (a!=NULL) ajouterVaccinL(&(a->listevaccins), marque, nb_vaccins);

    // Sinon on ajoute un nouveau noeud à l'arbre et on y ajoute le vaccin
    else{
        a = search_geq_ajout(*abr, date); // on recherche le parent du noeud à insérer
        T_ABR * new = creerABR(date); // on crée un nouvel objet noeud avec la date voulue
        if (strcmp(a->date,date) > 0) a->fils_gauche = new; // on regarde si le nouveau noeud doit devenir le fils gauche de son parent
        else a->fils_droit = new; // sinon il doit devenir son fils droit
        ajouterVaccinL(&(new->listevaccins), marque, nb_vaccins); // on ajoute le vaccin(marque+qté) dans la liste de vaccins du nouveau noeud créé
    }
}

// question 3

void afficherStockL(T_ListeVaccins* listeVaccins)
// Affiche tous les stocks de vaccins disponibles de la liste passée en argument
{
    T_ListeVaccins * parcours = listeVaccins;
    if (parcours != NULL) printf("Stocks disponibles : \n");
    else printf("Il n'y a pas de stock disponible.\n");
    //On parcourt la liste en affichant la marque et le nombre de vaccin à chaque fois
    while(parcours!=NULL)
    {
        printf("    %s : %d\n", parcours->marque, parcours->nombre_de_vaccins);
        parcours=parcours->suivant;
    }
}

// question 4

void afficherStockA(T_ABR* abr)
/* Parcours infixe de l'ABR avec affichage*/
{
    if (abr->fils_gauche!=NULL) afficherStockA(abr->fils_gauche);
    printf("Stock pour la date : %s\n", abr->date);
    afficherStockL(abr->listevaccins);
    printf("\n");
    if (abr->fils_droit!=NULL) afficherStockA(abr->fils_droit);
}

/* Pourquoi pas simplement:
    if (abr != NULL)
        afficherStockA(abr->fils_gauche);
        printf("Stock pour la date : %s\n", abr->date);
        afficherStockL(abr->listevaccins);
        printf("\n");
        afficherStockA(abr->fils_droit);
*/

// question 5

int compterVaccins(T_ABR* abr, char*marque)
{
    if (abr!=NULL)
    {
        int nb = 0;
        // on regarde dans la racine de l'arbre
        if (abr->listevaccins != NULL)
        {
            T_ListeVaccins *parcours = abr->listevaccins; // NB: peut être créer une sous-fonction responsable de la recherche dans une liste de vacc
            while (parcours != NULL) {
                if (strcmp(parcours->marque, marque) == 0) {
                    nb += parcours->nombre_de_vaccins;
                    break;
                }
                parcours = parcours->suivant;
            }
        }
        // s'il n'y a aucun fils on s'arrête là
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
/* Diminue le nombre de vaccins d'une marque parmi une liste de vaccins. Supprime le vaccin de la liste si ce nombre tombe à 0 */
{
    T_ListeVaccins* parcours = *listeVaccins;

    if (listeVaccins == NULL)
    {
        printf("Liste de vaccins vide.\n");
        exit(0);
    }
    // on regarde si le vaccin est en tête de liste : parcours = tête
    if (strcmp(parcours->marque, marque) == 0)
    {
        if (parcours->nombre_de_vaccins <= nb_vaccins)
        {
            printf("Le vaccin %s n'aura plus de stock et sera supprime. Poursuivre l'operation ?\nVotre reponse (o/n): ", marque);
            // while à finir
            *listeVaccins = parcours->suivant;
            free(parcours);
            printf("Vaccin supprime pour cette date.\n");
        }
        else parcours->nombre_de_vaccins -= nb_vaccins;
    }
    // sinon on parcourt la liste en regardant le suivant à chaque fois
    else
    {
        while ((parcours->suivant != NULL) && (strcmp(parcours->suivant->marque, marque) != 0))
            parcours = parcours->suivant;

        // sortie de la boucle
        if (parcours->suivant == NULL)
            printf("Le vaccin n'existe pas dans la liste.\n");

        else // le vaccin suivant est celui qui doit être modifié ou supprimé
        {
            T_ListeVaccins* vaccinModif = parcours->suivant;
            if (vaccinModif->nombre_de_vaccins <= nb_vaccins)
            {
                printf("Le vaccin %s n'aura plus de stock et sera supprime. Poursuivre l'operation ?\nVotre reponse (o/n): ", marque);
                // while à finir
                parcours->suivant = vaccinModif->suivant;
                free(vaccinModif);
            }
            else vaccinModif->nombre_de_vaccins -= nb_vaccins;
        }
    }
}

// question 7
// version récursive

/* Rechercher dans une liste
T_ListeVaccins* rechercherVaccinDansUneListe(T_ListeVaccins* liste, char* marque)
{
    while (liste != NULL && strcmp(liste->marque, marque)!=0)
        liste = liste->suivant;
    return liste;
}*/

int compterVaccinsNoeud(T_ABR* noeud, char* marque)
{
    int nombre = 0;
    if (noeud->listevaccins != NULL)
    {
        T_ListeVaccins *parcours = noeud->listevaccins; // NB: peut être créer une sous-fonction responsable de la recherche dans une liste de vacc
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

void deduireVaccinA(T_ABR** abr, char* marque, int nb_vaccins)
/* condition d'arrêt : nb_vaccins tombe à 0 (il est décrémenté à chaque appel)
 * ou on arrive sur un noeud nul*/
{
    if (*abr != NULL && nb_vaccins > 0)
    {
        deduireVaccinA((*abr)->fils_gauche, marque, nb_vaccins);

        /*** début traitement noeud ***/
        int nbDansCeNoeud = compterVaccinsNoeud(*abr, marque);
        deduireVaccinL(*abr, marque, nb_vaccins);
        nb_vaccins -= nbDansCeNoeud;

        if ((*abr)->listevaccins==NULL) // le noeud doit être supprimé
        {

        }
        /*** fin traitement noeud ***/

        deduireVaccinA((*abr)->fils_droit, marque, nb_vaccins);
    }

    /* ensuite on va supprimer tous les noeuds qui ne comptent plus de vaccins
    while
    if ((*abr)->listevaccins == NULL)
    {
        printf("Plus de vaccin prevu pour cette date, noeud doit etre supprime.\n");
        // récupérer le prédecesseur
        //
        supprimer(abr);
    }*/
}

/*int compterNombreVaccinsAdeduire(T_ABR* abr, char* marque, int nb_vaccins)
{
    unsigned int nombreVaccinsInitial = 0;
    // recherche du vaccin
    T_ListeVaccins* vaccinConcerne = rechercherVaccinDansUneListe(abr->listevaccins, marque);
    if (vaccinConcerne != NULL)
    {
       nombreVaccinsInitial = vaccinConcerne->nombre_de_vaccins;
    }
    deduireVaccinL(&(abr->listevaccins), marque, nb_vaccins);
    return nombreVaccinsInitial - vaccinConcerne->nombre_de_vaccins;
}*/















/* version pile : itératif
void deduireVaccinA(T_ABR** abr, char* marque, int nb_vaccins)
/* Déduit le stock d'un vaccin dans un arbre par ordre croissant de date de réception. Si un noeud ne contient plus de vaccins alors, il est supprimé
 * Ordre croissant -> parcours infixe
{
    if (abr == NULL)
    {
        printf("Arbre vide\n");
        exit(0);
    }
    // on récupère le nombre de vaccins initial, et le nombre de vaccins auquel on veut arriver une fois la déduction faite
    unsigned int nombreEnCours = compterVaccins(*abr, marque);
    unsigned int nouveauNombreEnCours = 0;
    printf("\n***** pour l'instant il y a %d vaccins de la marque %s *****\n", nombreEnCours, marque);
    unsigned int nombreADeduire = nb_vaccins;
    unsigned int nombreDeduit = 0;
    printf("***** on veut arriver a un total de %d vaccins pour que leCompteSoitBon *****\n\n\t*****\n\n", nombreEnCours - nombreADeduire);

    // parcours infixe itératif jusqu'à ce que leCompteEstBon soit atteint
    // on crée une pile de noeuds : au plus, elle contient le nombre de noeuds de l'arbre
    Pile* pile = creerPile(compterNoeuds(*abr));
    T_ABR* Ncourant = *abr;

    while ((Ncourant != NULL) && (nombreADeduire > 0))
    {
        while (Ncourant != NULL)
        {
            empiler(pile, Ncourant);
            Ncourant = Ncourant->fils_gauche;
        }
        Ncourant = depiler(pile);

        // on traite le noeud : déduction vaccin et suppression si nécessaire
        deduireVaccinL(&(Ncourant->listevaccins), marque, nombreADeduire);
        if (Ncourant->listevaccins == NULL) // il faut supprimer le noeud
        {
            T_ABR* old = Ncourant;
            Ncourant = Ncourant->fils_droit;
            supprimer(abr, old->date);
        }
        else Ncourant = Ncourant->fils_droit;

        nouveauNombreEnCours = compterVaccins(*abr, marque);
        nombreDeduit = nombreEnCours - nouveauNombreEnCours;
        nombreEnCours = nouveauNombreEnCours;
        nombreADeduire = nombreADeduire - nombreDeduit;

        printf("\n***** maintenant il y a %d vaccins de la marque %s *****\n\n", nombreEnCours, marque);
        printf("\tnombre deduit : %d\n", nombreDeduit);
        printf("\tnombreADeduire = %d\n\n", nombreADeduire);
    }
    // free pile
}
*/






