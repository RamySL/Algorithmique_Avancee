#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/
int* nbrmallocsl1;
int* nbrmallocsl2;

typedef struct Bloc
{
    int valeur ;
    struct Bloc * suite;
} Bloc;

typedef Bloc *Liste ;

Liste ajoute(int x, Liste l)
{   Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    *nbrmallocsl1 = *nbrmallocsl1+1;
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


void affiche_iter(Liste l) {
    // Vérifie si la liste est vide
    if (l == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    printf("[");

    // Parcours et affichage de la liste
    Liste L2 = l;
    while (L2 != NULL) {
        printf("%d", L2->valeur);

        // Affiche une virgule après chaque élément sauf le dernier
        if (L2->suite != NULL) {
            printf(", ");
        }

        L2 = L2->suite;
    }
    printf("]\n");  // Ferme l'affichage de la liste et ajoute une nouvelle ligne
}


int premier(Liste l){return l->valeur;}
Liste suite(Liste l){return l->suite;}

struct Bloc2
{
    Liste valeur;//Sous forme de liste de lists d'entiers.
    struct Bloc2* suite;
} Bloc2;

typedef struct Bloc2* Liste2;


Liste2 ajoute2(Liste x, Liste2 l)
{
    //fonction d'ajout pour les liste de listes (Bloc2)
    Liste2 tmp = (Liste2) malloc(sizeof(Bloc2)) ;
    *nbrmallocsl2 = *nbrmallocsl2 + 1;
    tmp->valeur = x ;
    tmp->suite = l ;
    return tmp ;
}

void empile2(Liste x, Liste2 *L)
//empile de liste de listes
{ *L = ajoute2(x,*L) ; }

void depile2(Liste2 *L)
{   Liste2 tmp = *L ;
    *L = (*L)->suite ;
    free(tmp) ;
}

void VideListe2(Liste2 *L)
{
    if ( *L != NULL )
    {
        depile2(L);
        VideListe2(L);
    }

}

Liste premier2(Liste2 l){return l->valeur;}
Liste2 suite2(Liste2 l){return l->suite;}

Liste2 concatene(Liste2 l1, Liste2 l2){
    //concatene avec fuites mémoire
    if(l1==NULL) return l2;
    return ajoute2(premier2(l1), concatene(suite2(l1), l2));
}

void concatene_no_leak(Liste2* l1, Liste2 l2){
    /*** La fonction concat naïve effectue une copie implicite inutile des éléments de la liste l1.
     Concaténation de deux listes de type Liste2. ***/

    if(*l1==NULL){
      *l1=l2;
      return;
    }
    while(*l1 != NULL) l1=&((*l1)->suite);
    *l1 = l2;
}

Liste copy(Liste l){
    //créer une copie de la liste l
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

Liste2 AETTL(int x, Liste2 l){
    //Ajoute x en tete de Toutes les Listes de l
    if(l==NULL) return NULL;
    return ajoute2(ajoute(x, premier2(l)), AETTL(x, suite2(l)));
}

void AETTL_no_leak(int x, Liste2 l){
    /*** On peut réécrire cette fonction de manière équivalente, en remplaçant `ajouter2`
     par une simple affectation qui met à jour la référence de l'ancienne tête de liste `l`
     par la nouvelle tête référencée, correspondant à la liste étendue.***/
    if(l!=NULL){
        AETTL_no_leak(x, l->suite);

        l->valeur = ajoute(x, l->valeur);
    }
}

Liste2 listeinterclassements(Liste l1, Liste l2){
    //la fonction des interclassements avec fuites mémoires
    Liste2 l=NULL;
    if(l1==NULL) return ajoute2(copy(l2), l);//on utilise la fonciton copy pour rendre l'espace mémoire de liste d'interclassement indépendent de celui des listes l1 et l2
    if(l2==NULL) return ajoute2(copy(l1), l);

    return concatene(
                    AETTL(premier(l1), listeinterclassements(suite(l1), l2)),
                    AETTL(premier(l2), listeinterclassements(l1, suite(l2)))
                    );
}


Liste2 listeinterclassements_no_leak(Liste l1, Liste l2){
    /*** Les fonctions responsables des fuites de mémoire sont `concatener` et `AETTL`.
     Les fuites de mémoire concernent principalement la structure `Bloc2` et non `Bloc1`.
     Le programme ne présente pas de fuites de mémoire au niveau des objets de type `Bloc1`.

     La fonction `concatener` utilise la fonction `ajoute2` pour chaque élément à ajouter.
     Cela recrée à chaque fois un nouvel élément, rendant l'ancien premier élément inutilisable.
     Par conséquent, cet espace mémoire devient perdu (fuite de mémoire).

     De même, la fonction `AETTL` génère une fuite mémoire dans la fonction `ajoute2`.
     À chaque fois, l'élément `x` est ajouté au sommet de la liste et la liste résultante
     est stockée dans un nouveau bloc de type `Bloc2`.
     Cela rend l'ancien bloc inutilisable, ce qui entraîne une fuite mémoire. ***/

    Liste2 l=NULL;
    if(l1==NULL) return ajoute2(copy(l2), l);
    if(l2==NULL) return ajoute2(copy(l1), l);
    Liste2 constructions_l = listeinterclassements_no_leak(suite(l1), l2), constructions_r = listeinterclassements_no_leak(l1, suite(l2));
    AETTL_no_leak(premier(l1), constructions_l);
    AETTL_no_leak(premier(l2), constructions_r);
    concatene_no_leak(&constructions_l,constructions_r);
    return constructions_l;
}

void affiche_iter2(Liste2 l) {
    // Vérifie si la liste est vide
    if (l == NULL) {
        printf("Liste vide.\n");
        return;
    }

    int index = 0;
    printf("Affichage de la liste de listes :\n");

    while (l != NULL) {
        printf("\n  |---+ Sous-liste %d: ", index++);
        affiche_iter(l->valeur);
        l = l->suite;
    }
    printf("\n\n");
}


int main(int argc, char** argv){
    nbrmallocsl1=(int*) malloc(sizeof(int));
    nbrmallocsl2=(int*) malloc(sizeof(int));

    Liste l, p ;
    Liste2 inter;

    l = NULL ;
    p = NULL;
    empile(6, &l);
    empile(5, &l);
    empile(2, &p);
    *nbrmallocsl2=0;
    *nbrmallocsl1=0;
    printf("+================+ ITERCLASSEMENTS +===============+");
    printf("\nl1: ");
    affiche_iter(l);
    printf("l2: ");
    affiche_iter(p);
    printf("\nLa liste des interclassements avec fuites memoire: ");
    inter = listeinterclassements(p, l);
    affiche_iter2(inter);
    printf("Nombre d'allocations memoire effectuees sur le type Liste: %d."
           "\nNombre d'allocations memoire effectuees sur le type Liste2: %d.", *nbrmallocsl1, *nbrmallocsl2);

    printf("\n\nLa liste des interclassements sans fuites memoire: ");
    VideListe2(&inter);
    *nbrmallocsl1=0;
    *nbrmallocsl2=0;
    inter = listeinterclassements_no_leak(p, l);
    affiche_iter2(inter);
    printf("Nombre d'allocations memoire effectuees sur le type Liste (sans les malloc's de creations de l1 et l2): %d."
           "\nNombre d'allocations memoire effectuees sur le type Liste2: %d.", *nbrmallocsl1, *nbrmallocsl2);

    printf("\nLe nombre de malloc optimal est taille(l1+l2) * Combinaisons(m, m+n) ou m, n sont les tailles de l1, l2.\n\n...Liberation\n\n");
    VideListe(&l);
    VideListe(&p);
    VideListe2(&inter);
    return 0;
}
