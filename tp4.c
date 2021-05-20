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
    if (strcmp(a->date,date)>0) // a->date > date recherchée -> on va voir à gauche
    {
        if(a->fils_gauche==NULL) return a;
        else return search_geq_ajout(a->fils_gauche, date);
    }
    else { // ajout à droite
        if (a->fils_droit==NULL) return a;
        else return search_geq_ajout(a->fils_droit, date);
    }
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

/* void afficherStockA(T_ABR* abr)
// ORHANE
{
    if (abr->fils_gauche!=NULL) afficherStockA(abr->fils_gauche);
    printf("Stock pour la date : %s\n", abr->date);
    afficherStockL(abr->listevaccins);
    printf("\n");
    if (abr->fils_droit!=NULL) afficherStockA(abr->fils_droit);
    // else printf("noeud nul\n");
} */

// VIOLETTE mieux car évite de rechercher le fils d'un noeud nul
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
            printf("Vaccin supprime pour cette date.\n\n");
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

// version itérative AVEC PILE

/*** Fonctions préliminaires ***/

// Manipulation de la pile de noeuds

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

int empiler(Pile* pile, T_ABR* noeud)
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
    return 1; // retour 1 si l'empilement a bien été effectué
}

T_ABR* depiler(Pile* pile)
{
    if (pile == NULL)
    {
        printf("La pile n'existe pas.\n");
        return NULL;
    }
    if (pileVide(pile))
    {
        printf("Debordement par defaut.\n");
        return NULL;
    }
    pile->sommet --;
    return pile->TableauDeNoeuds[pile->sommet];
}

int compterNoeuds(T_ABR* abr)
{
    if (abr == NULL) return 0;
    else return 1 + compterNoeuds(abr->fils_gauche) + compterNoeuds(abr->fils_droit);
}

// Rechercher dans une liste
T_ListeVaccins* rechercherVaccinDansUneListe(T_ListeVaccins* liste, char* marque)
{
    while (liste != NULL && strcmp(liste->marque, marque)!=0)
        liste = liste->suivant;
    return liste;
}

// Retourner le prédecesseur d'un noeud qui a un sous-arbre gauche (c'est-à-dire que le prédecesseur est forcément situé dans ce sous-arbre gauche)
T_ABR* predecesseurDunNoeudAvecFilsGauche(T_ABR* abr)
// à priori cette fonction est appelée seulement si un noeud avec un fils gauche et un fils droit doit être supprimé (on a donc pas besoin de traiter le cas ou le prédécesseur est le parent gauche du noeud considéré)
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
} // fonctionne bien mais attention usage limité (par flemme pour l'instant)

// Supprimer un noeud dans un arbre, recherche par sa date. Retourne le noeud qui prend sa place.
T_ABR* supprimerNoeud(T_ABR* abr, char* date)
{
    if (abr == NULL)
    {
        printf("noeud nul\n");
        return NULL;
    }
    // on recherche le noeud
    else if (strcmp(abr->date, date) > 0)
    {
        printf("je suis le noeud %s\n", abr->date);
        abr->fils_gauche = supprimerNoeud(abr->fils_gauche, date);
    }
    else if (strcmp(abr->date, date) < 0)
    {
        printf("je suis le noeud %s\n", abr->date);
        abr->fils_droit = supprimerNoeud(abr->fils_droit, date);
    }

    else // abr est le noeud qui doit être supprimé
    {
        printf("je suis le noeud %s\n", abr->date);
        if (abr->fils_gauche == NULL)
        {
            T_ABR* retour = abr->fils_droit;
            free(abr);
            printf("arbre supprime, remplace par son fils droit\n");
            return retour;
        }
        else if (abr->fils_droit == NULL)
        {
            T_ABR* retour = abr->fils_gauche;
            free(abr);
            printf("arbre supprime, remplace par son fils gauche\n");
            return retour;
        }
        else
        {
            T_ABR* pred = predecesseurDunNoeudAvecFilsGauche(abr);
            printf("ma date est : %s\n", abr->date);
            printf("je vais etre remplace par mon predecesseur : %s\n", pred->date);
            // on modifie les clés du noeud qui devait être supprimé
            abr->date = pred->date;
            abr->listevaccins = pred->listevaccins;
            // on supprime son prédecesseur
            abr->fils_gauche = supprimerNoeud(abr->fils_gauche, pred->date);
        }
    }
    return abr;
} // fuites mémoire corrigées // fonctionne

// Retourner la quantité de vaccins d'une certaine marque dans un noeud (à une date) donné(e)
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
} // fonctionne bien

T_ABR* parentDunNoeud(T_ABR* a, char *date)
// Renvoie le noeud parent : parcours infixe avec traitement du noeud
{
    if (a != NULL)
    {
        if ((strcmp(a->fils_gauche->date, date)==0) || (strcmp(a->fils_droit->date, date)==0))
            return a;

        else
        {
            if (strcmp(a->date, date)<0) // on va voir le fils droit
                return parentDunNoeud(a->fils_droit, date);

            else if (strcmp(a->date, date)>0)
                return parentDunNoeud(a->fils_gauche, date);

            else
            {
                printf("pas de parent\n");
                return NULL;
            }
        }
    }
}// ok

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

T_ABR* minimum(T_ABR* abr, char* marque)
// parcours infixe pour trouver le minimum
{
    if (abr->fils_gauche == NULL)
    {
        if (marqueEstDedans(abr, marque))
        {
            return abr;
        }
        else if (abr->fils_droit!=NULL)
        {
            return minimum(abr->fils_droit, marque);
        }
    }
    else return minimum(abr->fils_gauche, marque);
} // ne fonctionne pas

void deduireVaccinA(T_ABR** abr, char*marque, int nb_vaccins)
{
    int nombreRestant = nb_vaccins;
    T_ABR* noeudMinimal = NULL;

    // rechercher le noeud minimal
    while (nombreRestant > 0)
    {
        minimal
        if (noeudMinimal!=NULL)
        {
            deduireVaccinL(&(noeudMinimal->listevaccins));
            if (noeudMinimal->listevaccins == NULL)
            {
                *abr = supprimerNoeud(*abr, noeudMinimal->date);
            }
        }
        else
        {
            printf("pas de noeud contenant cette marque\n");
            exit(0);
        }
    }

    // si plus de liste de vaccins, le supprimer
    // recommencer tant qu'il reste des vaccins à suppr
}





///*** THE fonction avec pile ***/
//
//void deduireVaccinAPile(T_ABR** abr, char* marque, int nb_vaccins)
//{
//    if (abr == NULL)
//    {
//        printf("arbre vide\n");
//        exit(EXIT_FAILURE);
//    }
//    else
//    {
//        int nombreRestant = nb_vaccins; // nb initial de vaccins à déduire (qui sera décrémenté par la suite)
//        int nbDansCeNoeud = 0; // va servir à chaque itération
//
//        // on se lance dans le parcours
//        // on crée une pile et on récupère le noeud courant
//        Pile* pileDeNoeuds = creerPile(compterNoeuds(*abr));
//        T_ABR* courant = *abr;
//
//        while (((courant != NULL) || !(pileVide(pileDeNoeuds))) && nombreRestant!=0) // (a ou b) et c -> fin quand c ou (non a et non b)
//        {
//            printf("il faut deduire %d vaccins\n\n\n", nombreRestant);
//
//            while ((courant != NULL))
//            {
//                int bienEmpile = empiler(pileDeNoeuds, courant);
//                if (bienEmpile != 1) printf("empilement n'a pas marche. pile pleine?\n");
//                courant = courant->fils_gauche;
//            }
//
//            /*** DEBUT traitement du noeud ***/
//
//            courant = depiler(pileDeNoeuds);
//            if (courant == NULL) printf("depilement n'a pas marche\n");
//
//            printf("\t*** je suis dans le noeud %s ***\n", courant->date);
//
//            nbDansCeNoeud = compterVaccinsNoeud(courant, marque);
//            printf("\t    a cette date il y a %d vaccins de la marque %s\n", nbDansCeNoeud, marque);
//
//            // on cherche à déduire le vaccin de sa liste s'il s'y trouve
//            deduireVaccinL(&(courant->listevaccins), marque, nombreRestant);
//
//            // on met à jour le nombre de vaccins qu'il reste à déduire (nombreRestant)
//            if (courant->listevaccins != NULL)
//            {
//                // s'il n'y a plus de vaccin dans ce noeud on doit aller regarder les autres et nombreRestant est décrémenté de nbDansCeNoeud
//                if (compterVaccinsNoeud(courant, marque) == 0)
//                {
//                    nombreRestant -= nbDansCeNoeud;
//                    printf("\t   mtn il reste %d vaccins a deduire\n\n", nombreRestant);
//                }
//                // sinon c'est qu'il y avait plus de vaccins dans le noeud que de vaccins à supprimer donc nombreRestant prend la valeur 0
//                else nombreRestant = 0; // condition d'arrêt remplie
//            }
//
//            // on regarde si le noeud doit être supprimé <=> si sa liste de vaccins est vide
//            if (courant->listevaccins == NULL)
//            {
//                printf("!!! je n'ai plus de vaccins dispo, je dois etre supprime !!!\n\n");
//
//                // le cas pbmatique est celui ou le noeud sera remplace par son fils droit, on récupère donc la date du noeud courant pour pouvoir la comparer ensuite avec celle de son remplaçant :
//                char* dateDuNoeudRemplace = courant->date;
//                printf("mon ancienne date etait %s\n", dateDuNoeudRemplace);
//
//                // on remplace dans l'arbre le noeud supprimé par son remplaçant
//                T_ABR* parent = parentDunNoeud(*abr, courant->date);
//                printf("je suis le parent du noeud qui doit etre remplace, ma date est %s\n\n", parent->date);
//                parent->fils_gauche = supprimerNoeud(courant, courant->date);
//
//                /* 4 possibilités :
//                    1- courant n'avait pas de fils gauche et a été remplacé par son fils droit PB CAR N'A PAS ENCORE ETE TRAITE
//                    2- courant n'avait pas de fils droit et a été remplacé par son fils gauche ok car a deja ete traite
//                    3- courant n'avais ni fils gauche ni fils droit et vaut maintenant NULL ok
//                    4- courant avait un fils gauche et un fils droit et a été remplacé par son prédécesseur (qui faisait partie de son sous-arbre gauche) ok car a deja ete traite
//                */
//                // on va explorer le prochain selon le résultat de cette suppression
//
//                if (parent->fils_gauche != NULL)
//                {
//
//                    printf("mon fils gauche a la date %s\n", parent->fils_gauche->date);
//                    courant = parent->fils_gauche;
//
//                    // on gère le cas pbmatique :
//                    /* si la date du noeud courant est plus grande que la date du noeud qui a ete remplacé,
//                     * ça veut dire que le noeud courant est le fils droit du noeud qui a été remplacé,
//                     * donc on ne touche pas à courant pour qu'il soit traité à la prochaine itération.
//                     * sinon, on va regarder son fils droit. */
//
//                    if (courant != NULL && strcmp(courant->date, dateDuNoeudRemplace) <= 0) // cas 2 ou 4, non problématique
//                    {
//                        courant = courant->fils_droit;
//                    }
//                    // sinon cas 1 ou 3 : courant est traité, c'est le fils droit du noeud qui a été remplacé, ou alors c'est NULL
//
//                }
//
//                else
//                {
//                    printf("mon fils gauche est nul\n\n");
//                    courant = parent; // si le fils est nul on est dans le cas numéro 3, le prochain a traiter est le parents
//                    printf("maintenant je traite le parent : date %s\n\n",courant->date);
//                }
//            }
//
//            else // le noeud n'a pas été supprimé, on va simplement explorer son fils droit
//            {
//                courant = courant->fils_droit;
//            }
//
//            /*** FIN traitement du noeud ***/
//        }
//    }
//}  free pile?
//// ne fonctionne pas : suppression d'un noeud...

