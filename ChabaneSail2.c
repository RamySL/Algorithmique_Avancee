#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
/*
Binome : Chabane Oualid, Sail Ramy
ramy.sail@etu-upsaclay.fr
oualid.chabane@etu-upsaclay.fr

*/

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int valeur ;
    struct Bloc * suite;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


/*** les 5 fonctionnalit�s suivantes sont plus du sucre syntaxique que du code utile  ***/
/*** sauf � vouloir pouvoir basculer � moindre frais sur une impl�menation des listes ***/
/**** diff�rentes des listes chain�es propos�es dans le cadre de ce projet            ***/

// Liste Vide() { return NULL ; }
// void initVide(Liste *L) { *L = NULL ; }
// bool estVide(Liste l) { return l == NULL ; }
// int premier(Liste l) { return l->valeur ; }
// Liste suite(Liste l) { return l->suite ; }

/****************/

void depile(Liste *L)
{   Liste tmp = *L ;
    *L = (*L)->suite ;
    free(tmp) ;
}

Liste ajoute(int x, Liste l)
{   Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->valeur = x ;
    tmp->suite = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{ *L = ajoute(x,*L) ; }

/*****************************/
/*                           */
/*       Affiche             */
/*                           */
/*****************************/

void affiche_rec(Liste l)
{
    if (l == NULL)
        printf("\n");
    else
    {
        printf("%d ", l->valeur);
        affiche_rec(l->suite);
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while( L2 != NULL )
    {
        printf("%d ", L2->valeur);
        L2 = L2->suite;
    }
    printf("\n");
}

/****************************/
/*                          */
/*       Longueur           */
/*                          */
/****************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suite)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P != NULL)
    {   P = P->suite ;
        cpt++ ;
    }
    return cpt ;
}

/*****************************************/
/*                                       */
/*                 VireDernier           */
/*     avec un depile                    */
/* � la main opportuniste (version iter) */
/* ou en utilisant depiie (version rec ) */
/*                                       */
/*****************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( (*L)->suite == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& (*L)->suite) ;
}

void VireDernier_rec (Liste *L)
{
     if ( *L != NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

/*************/

void VireDernier_iter (Liste *L)
{
    if ( *L != NULL)
    {
        while ( (*L)->suite != NULL )
                 L = &  (*L)->suite  ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if ( *L != NULL )
    {
        depile(L);
        VideListe(L);
    }

}

/********************************************/
/*                                          */
/*          DeuxEgalX                       */
/*                                          */
/********************************************/

bool DeuxEgalX (Liste L, int x){
    // Renvoie un entier non nul si x est égal au deuxième élément de la liste, ou 0 si cet élément n'existe pas.
    if(L==NULL || L->suite == NULL) return x==0;
    return x==L->suite->valeur;
    //Conversion de type automatique
}

/********************************************/
/*                                          */
/*          ContientZero                    */
/*                                          */
/********************************************/

bool ContientZero_rec (Liste L){
    if(L == NULL){
        return false;
    }

    if(L->valeur == 0){
        return true;
    }else{
        ContientZero_rec (L->suite);
    }

}

bool ContientZero_iter (Liste L){

    Liste parcours = L;

    while (parcours != NULL){
        if(parcours->valeur == 0){
            return true;
        }

        parcours = parcours -> suite;
    }

    return false;

}
/********************************************/
/*                                          */
/*          SousEnsemble                    */
/*                                          */
/********************************************/
bool sousEnsemble(Liste l1, Liste l2){
    bool stop=false;
    while(l1 != NULL && l2 != NULL && !stop){
        // On avance dans l1 uniquement si l'élément en tête de l1 correspond à l'élément courant de l2.
        if(l1->valeur == l2->valeur) l1 = l1->suite;
        else if(l1->valeur < l2->valeur) stop=true;

        // Dans tous les cas, on avance dans l2.
        l2 = l2->suite;
    }

    // Si nous avons pu parcourir l1 jusqu'à la fin, alors nous sommes certains que toutes ses valeurs existent dans l2.
    // Cela fonctionne même si l1 est vide initialement, car une liste vide est incluse dans toutes les listes, y compris dans la liste vide elle-même.

    //Conversion de type autmatique
    return l1==NULL;
}
/********************************************/
/*                                          */
/*           SommeAvantKieme0               */
/*                                          */
/********************************************/
int SommeAvantKieme0_rec_non_terminal (Liste L, int k){

    if(k <= 0 || L == NULL){
        return 0;
    }

    if(L->valeur == 0){
        return (L->valeur) + SommeAvantKieme0_rec_non_terminal (L->suite, k-1);
    }
    return (L->valeur) + SommeAvantKieme0_rec_non_terminal (L->suite, k);

}

/*
- On sait que les arguments sont passés par valeurs et donc il n'ya pas besoin
de faire des copies, mais on suit juste les conseils du cours
*/
int SommeAvantKieme0_iter (Liste L, int k){
    int res = 0;
    int k_copie = k;
    Liste parcours = L;

    while (parcours != NULL && k_copie > 0){

        if(parcours->valeur == 0){
            k_copie --;
        }
        res += parcours->valeur;
        parcours = parcours->suite;
    }

    return res;
}

int _SommeAvantKieme0_rec_terminal_sous_fonction (Liste L, int k, int res){

    if(k <= 0 || L == NULL){
        return res;
    }

    if(L->valeur == 0){
        return _SommeAvantKieme0_rec_terminal_sous_fonction (L->suite, k-1,res + (L->valeur));
    }
    return _SommeAvantKieme0_rec_terminal_sous_fonction (L->suite, k,res + (L->valeur));

}

int SommeAvantKieme0_rec_terminal_sous_fonction (Liste L, int k){
    return _SommeAvantKieme0_rec_terminal_sous_fonction(L,k,0);
}

void _SommeAvantKieme0_rec_terminal_sous_procedure (Liste L, int k, int* res){

    if(k > 0 && L != NULL){
        (*res) = (*res) + (L->valeur);
        if(L->valeur == 0){
            _SommeAvantKieme0_rec_terminal_sous_procedure (L->suite,k-1,res);
        }else{
            _SommeAvantKieme0_rec_terminal_sous_procedure (L->suite,k,res);
        }

    }
}

int SommeAvantKieme0_rec_terminal_sous_procedure (Liste L, int k){
    int res = 0;
    _SommeAvantKieme0_rec_terminal_sous_procedure(L,k,&res);
    return res;

}

/*************************************************/
/*                                               */
/*           sommeApresRetroKieme0               */
/*                                               */
/*************************************************/
int sommeApresRetroKieme0_aux(Liste l, int k, int* cpt){
    if(k==0 || l==NULL) return 0;
    int res =  sommeApresRetroKieme0_aux(l->suite, k, cpt);
    if(l->valeur==0){
        *cpt = *cpt + 1;
    } else if(*cpt<k) return l->valeur + res;
    return res;
}

int sommeApresRetroKieme0(Liste l, int k){
    int cpt = 0;
    return sommeApresRetroKieme0_aux(l, k, &cpt);
}


Liste createlist(){
  int nbr;
  Liste l=NULL;
  while(true){
    printf("\nVoulez vous terminer la saisie? 0 (non) sinon (oui): ");
    scanf("%d", &nbr);
    if(nbr) break;
    printf("\nSaisissez un nombre pour l'empiler: ");
    scanf("%d", &nbr);
    l = ajoute(nbr, l);

  }
  return l;
}

/*************************************************/
/*                                               */
/*           TueDoublons                         */
/*                                               */
/*************************************************/

/*
- parcours la liste L et à chaque fois qu'une occurence autre que celle pointée par check_point est trouvée
dépile check_pointe pour garder à chaque fois l'occurence la plus récente du parcours et donc la dernière occurence
 */
void _retirePremieresOccTerm(Liste* check_point,Liste* L,bool *depilement){
    if((*L)!=NULL){
        if((*check_point)->valeur == (*L)->valeur){
            *depilement = true;

            if(&((*check_point)->suite) == L){
                // Dans le cas ou le checkpointe et la suite du parcours sont consecutifs
                // quand on va depiler on va perdre le pointeur L, et check_pointe est déjà là ou il est censé être
                // c'est pour ça ce traitement spécifique
                depile(check_point);
                L = check_point;
            }else{
                depile(check_point);
                check_point = L;
            }
        }
        _retirePremieresOccTerm(check_point,&(*L)->suite,depilement);

    }
}

void TueDoublons1 (Liste* L){
    bool depilement = false;

    if((*L) != NULL){
        _retirePremieresOccTerm(L,&(*L)->suite,&depilement);
        if(depilement){
            TueDoublons1(L);
        }else{
            TueDoublons1(&(*L)->suite);
        }
    }
}
/*
- La procédure retire toutes les occurance de x dans L
- complexité linéaire : theta(n)
*/
void _retireOccXdeListe(int x,Liste* L){
    if(*L != NULL){
        if((*L)->valeur == x){
            depile(L);
            _retireOccXdeListe(x,L);
        }else{
            _retireOccXdeListe(x,&((*L)->suite));
        }
    }

}
/*
Complexité quadratique : C(n) = C(n-1) + C_(n-1) + 1
- Avec C : complexité de TueDoublons2_rec et C_ complexité de _retireOccXdeListe, on a mit le cout d'un appel TueDoublons2_rec à 1
plus les appels récursifs

- C(n) = C(n-1) + C_(n-1) + 1 = C(n-1) + n-1 + 1 = C(n-1) + n = 1 + 1 + 2 + .... + n = n**2/2 (équivalent)

*/
void TueDoublons2_rec (Liste* L){

    if(*L != NULL){
        _retireOccXdeListe((*L)->valeur, &(*L)->suite);
        TueDoublons2_rec (&(*L)->suite);
    }
}

void TueDoublons2_iter (Liste* L){

    Liste* parcours_principale = L;
    while ((*parcours_principale) != NULL){

        int val_courante = (*parcours_principale) -> valeur;
        Liste* parcours_aux = &(*parcours_principale) -> suite;

        while((*parcours_aux) != NULL){
            if((*parcours_aux)->valeur == val_courante){
                depile(parcours_aux);
            }else{
                parcours_aux = &(*parcours_aux)->suite;
            }

        }
        parcours_principale = &(*parcours_principale)->suite;
    }
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/


int main() {
    // Initialisation des listes pour les tests
    Liste L = NULL;
    Liste L_vide = NULL;
    Liste L_unique = NULL;
    Liste L_identiques = NULL;
    Liste L_complexe = NULL;
    Liste L_doublons_alt = NULL; // Liste pour le nouveau test

    printf("Test 1 : Liste vide\n");
    printf("Liste avant : ");
    affiche_iter(L_vide);
    TueDoublons2_iter(&L_vide);
    printf("Liste apres : ");
    affiche_iter(L_vide);

    printf("\nTest 2 : Liste avec un seul element\n");
    empile(5, &L_unique);
    printf("Liste avant : ");
    affiche_iter(L_unique);
    TueDoublons2_iter(&L_unique);
    printf("Liste apres : ");
    affiche_iter(L_unique);

    printf("\nTest 3 : Liste avec des elements identiques\n");
    empile(1, &L_identiques);
    empile(1, &L_identiques);
    empile(1, &L_identiques);
    empile(1, &L_identiques);
    printf("Liste avant : ");
    affiche_iter(L_identiques);
    TueDoublons2_iter(&L_identiques);
    printf("Liste apres : ");
    affiche_iter(L_identiques);

    printf("\nTest 4 : Liste avec plusieurs doublons\n");
    empile(5, &L_complexe);
    empile(2, &L_complexe);
    empile(4, &L_complexe);
    empile(5, &L_complexe);
    empile(3, &L_complexe);
    empile(2, &L_complexe);
    empile(4, &L_complexe);
    empile(3, &L_complexe);
    printf("Liste avant : ");
    affiche_iter(L_complexe);
    TueDoublons2_iter(&L_complexe);
    printf("Liste après : ");
    affiche_iter(L_complexe);

    printf("\nTest 5 : Liste avec alternance de doublons {1, 2, 1, 2}\n");
    empile(2, &L_doublons_alt);
    empile(1, &L_doublons_alt);
    empile(2, &L_doublons_alt);
    empile(1, &L_doublons_alt);
    printf("Liste avant : ");
    affiche_iter(L_doublons_alt);
    TueDoublons2_iter(&L_doublons_alt);
    printf("Liste après : ");
    affiche_iter(L_doublons_alt);

    while (L != NULL) {
        depile(&L);
    }
    while (L_unique != NULL) {
        depile(&L_unique);
    }
    while (L_identiques != NULL) {
        depile(&L_identiques);
    }
    while (L_complexe != NULL) {
        depile(&L_complexe);
    }
    while (L_doublons_alt != NULL) {
        depile(&L_doublons_alt);
    }

    return 0;
}
