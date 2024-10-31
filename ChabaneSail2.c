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

        if(L->valeur == 0){
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
/*           TueDoublons                         */
/*                                               */
/*************************************************/

/*
- retire les premieres occ de x dans la liste en remontant les appels recursifs
- [3] -> [3]
 */
void _retireDernieresOccX(int x,Liste* L,bool *exist){
    if(*L != NULL){
        _retireDernieresOccX(x,&(*L)->suite,exist);

        if((*L)->valeur == x){
            if(*exist){
                // ça veut dire on est déja passé par la toutes derniere occurence de x
                depile(L);
            }else {
                // première occurence à partir de la fin de x
                *exist = true;
            }
        }

    }


}
void TueDoublons1 (Liste* L){
    bool exist = false;

    if(*L != NULL){
        _retireDernieresOccX((*L)->valeur, L,&exist);
        TueDoublons1(&(*L)->suite);
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
                continue;
            }
            parcours_aux = &(*parcours_aux)->suite;
        }

        parcours_principale = &(*parcours_principale)->suite;

    }

}

/*           SommeApresRetroKieme0                                */
/*                                               */
/*************************************************/
#ifdef COMMENT_OUT
int sommeApresRetroKieme0_v2(Liste l, int k){
    /*
    Explicaiton sous forme d'automate:

    */
    Liste pile=NULL;
    int sum=0;
    while(l != NULL){
        if(l->valeur==0){
            if(sum==0)  k--;
            else {
                empile(sum, &pile);
                sum=0;
            }
        } else sum+=l->valeur;
        l=l->suite;
    }
    if(sum!=0) {
        empile(sum, &pile);
        sum=0;
    } else k--;
    while(pile != NULL && k>0){
        sum+=pile->valeur;
        depile(&pile);
        k--;
    }
    return sum;
}
#endif // COMMENT_OUT

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

//Structure pour les interclassements.
typedef struct ListeStrcut2 {
    Liste valeur;//Elle est sous forme de liste de lists d'entiers.
    struct ListeStrcut2* suite;
}* Liste2;

Liste copyAvecChainage(Liste l, Liste suffix){
    //Cette fonction est équivalente à concat(copy(l), suffixe), mais plus optimisée.
    if(l == NULL)
        return suffix;
    Liste Head = NULL;
    Liste* pH = &Head;
    while(l!=NULL){
        *pH = (Liste) malloc(sizeof(Bloc));
        (*pH)->valeur = l->valeur;
        pH = &((*pH)->suite);
        l = l->suite;
    }
    *pH=suffix;
    return Head;
}

void distribute(Liste l, Liste2 L){
    // Cette fonction prend en paramètre une liste de listes L et une liste préfixe l.
    // Elle renvoie une nouvelle liste de listes, où chaque liste de L est concaténée avec une copie de l.
    // Par exemple :
    // distribute([1, 2], [
    //                      [4],
    //                      [5, 6]
    //                    ])
    // retourne :
    // [
    //                      [1, 2, 4],
    //                      [1, 2, 5, 6]
    // ]

    while(L != NULL){
        Liste newHead = copyAvecChainage(l, L->valeur);
        L->valeur = newHead;
        L = L->suite;
    }
}

void concat(Liste2* l1, Liste2 l2){
    //concaténation de deux listes de type Liste2
    if(*l1==NULL){
      *l1=l2;
      return;
    }
    while(*l1 != NULL) l1=&((*l1)->suite);
    *l1 = l2;
}

Liste copy(Liste l){
    Liste R = NULL;
    Liste* ptList = &R;
    while(l != NULL){
        empile(l->valeur, ptList);
        ptList = &((*ptList)->suite);
        l=l->suite;
    }
    *ptList=NULL;
    return R;
}

Liste2 interclassements(Liste l1, Liste l2){
    /*
        Le nombre d'interclassements en résultat correspond aux
        combinaisons possibles de (n + m) éléments, où :
            - n est la taille de l1
            - m est la taille de l2

        Cela représente le nombre de façons de répartir les m éléments de l2
        parmi les n éléments de l1, en ajoutant m positions virtuelles dans l1.

        On rajoute m pour inclure tous les cas, y compris celui où une partie de l2 peut
        être placée à la fin de l1 avec des partitions de taille entre 0 et m.
    */

    if(l1 == NULL){
        //si l1 est vide on renvoie une copie de l2
        Liste2 ret = (Liste2) malloc(sizeof(struct ListeStrcut2));
        ret->suite=NULL;
        ret->valeur = copy(l2);
        return ret;
    }

    /*
        Si l1 n'est pas vide, l'idée de l'interclassement est la suivante :

        1. On prend le premier élément de l1 et on tente de l'insérer à chaque
           position possible dans l2, notée i, où i représente un index dans l2.

        2. Pour chaque position i dans l2, on :
           - Calcule les interclassements du reste de l1 avec les éléments restants
             de l2 (c'est-à-dire ceux situés après la position i dans l2).

        3. On répète cette insertion pour toutes les positions i entre 0 et n, où
           n est la longueur de l2. Cela permet d’obtenir toutes les combinaisons
           possibles d’interclassement des éléments de l1 dans l2.

        4. Finalement, on concatène tous les résultats obtenus pour chaque insertion
           à chaque position i, produisant ainsi la liste complète des interclassements.
    */

    Liste hdl1 = l1;//hdl1 serve à contenire la tete de la liste l1
    l1=l1->suite;
    hdl1->suite=NULL;
    //à cette étape on a découpé l1 vers 2 listes,
    //    la première est hdl1, formée de la tete de la liste l1 uniquement
    //    la deuxième liste est le reste de liste l1 en enlèvent la tete

    //On accumule les interclassements dans la variable interclassesAccumulator,
    //La valeur initial de cette accumulateur est l'interclassement en supposant que la tete de l1 est dans position i=0 de l2
    Liste2 interclassesAccumulator = interclassements(l1, l2);
    //On forme les interclassement avec hdl1 (head L1) dans la position 0 de la liste l2
    distribute(hdl1, interclassesAccumulator);
    Liste beforlastl2=l2, hdl2 = l2;
    while(l2 != NULL){
    /*
        À chaque itération de l'algorithme d'interclassement, nous procédons comme suit :

        1. Création d'une liste temporaire :
           - Nous construisons une liste temporaire qui contient les (i-1) premiers éléments de l2.
           - Nous insérons ensuite la tête de l1 (notée hdl1) à la position i dans cette liste temporaire.

        2. Calcul de l'interclassement partiel :
           - Une fois la tête de l1 placée, nous calculons les interclassements possibles entre :
             - Cette liste temporaire (contenant la tête de l1 et les premiers éléments de l2 jusqu'à la position i),
             - Et le reste de l1, c'est-à-dire les éléments de l1 après la tête.

        3. Concatenation des interclassements :
           - Les interclassements calculés pour chaque position i sont concaténés aux interclassements précédemment calculés.
           - Cela permet de générer tout les interclassements possibles de l1 et l2
             en insérant les éléments de l1 dans l2 à toutes les positions possibles.

        En répétant ces étapes pour chaque position i dans l2, on obtient une liste complète d'interclassements,
        où chaque position de hdl1 dans l2 est explorée pour toutes les combinaisons possibles.
    */

        l2 = l2->suite;
        beforlastl2->suite = hdl1;//on insère la tete de l1 dans la i-ème position
        Liste2 interclasses = interclassements(l1, l2);
        distribute(hdl2, interclasses);//On concatène la liste partielle construite avec les interclassements partiels calculés
        concat(&interclassesAccumulator, interclasses);//on acumule les interclassements
        beforlastl2->suite=l2;
        beforlastl2=l2; //On remet le chainage, et on procède à l aprochaine position
    }

    //On remet le chainage de l1, parcequ'on l'utilise après les appels récursives.
    hdl1->suite=l1;
    return interclassesAccumulator;
}

void affiche_iter2(Liste2 l){
    while(l!=NULL){
        printf("\n\t");
        affiche_iter(l->valeur);
        l=l->suite;
    }
}

void clearList2(Liste2 l){
    //détruire un e liste d'interclassements pour libérer l'espace mémoire qu'elle occupe
    while(l!=NULL){
        while(l->valeur!=NULL) depile(&(l->valeur));
        Liste2 tmp = l->suite;
        free(l);
        l=tmp;
    }
}
/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{
    Liste l, p ;
    Liste2 inter;

        l = NULL ;
        p = NULL;
        empile(6, &l);
        empile(5, &l);
        empile(4, &l);

        empile(9, &p);
        empile(8, &p);
        empile(7, &p);


        affiche_iter(l);
        affiche_iter(p);
        inter = interclassements(l, p);
        affiche_iter2(inter);
        VideListe(&l);
        VideListe(&p);
        clearList2(inter);

        return 0;
}




