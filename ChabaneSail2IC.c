#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

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

Liste ajoute(int x, Liste l)
{   Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->valeur = x ;
    tmp->suite = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{ *L = ajoute(x,*L) ; }

void depile(Liste *L)
{   Liste tmp = *L ;
    *L = (*L)->suite ;
    free(tmp) ;
}

void VideListe(Liste *L)
{
    if ( *L != NULL )
    {
        depile(L);
        VideListe(L);
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


//Structure pour les interclassements.
typedef struct ListeStrcut2 {
    Liste valeur;//Elle est sous forme de liste de lists d'entiers.
    struct ListeStrcut2* suite;
}* Liste2;
int* nbrmallocs;
Liste copyAvecChainage(Liste l, Liste suffix){
    //Cette fonction est équivalente à concat(copy(l), suffixe), mais plus optimisée.
    if(l == NULL)
        return suffix;
    Liste Head = NULL;
    Liste* pH = &Head;
    while(l!=NULL){
        *pH = (Liste) malloc(sizeof(Bloc));
        *nbrmallocs=*nbrmallocs+1;
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
        *nbrmallocs=*nbrmallocs+1;
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
        *nbrmallocs = *nbrmallocs+1;
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

int main(int argc, char** argv){
    nbrmallocs=(int) malloc(sizeof(int));
    *nbrmallocs=0;
    Liste l, p ;
    Liste2 inter;

    l = NULL ;
    p = NULL;
    empile(6, &l);
    empile(5, &l);

    empile(9, &p);
    empile(8, &p);
    empile(7, &p);



    affiche_iter(l);
    affiche_iter(p);
    printf("\nLa liste des interclassements: ");
    inter = interclassements(l, p);
    affiche_iter2(inter);
    printf("Nombre d'allocations memoire effectuees: %d.", *nbrmallocs);
    VideListe(&l);
    VideListe(&p);
    clearList2(inter);
    return 0;
}
