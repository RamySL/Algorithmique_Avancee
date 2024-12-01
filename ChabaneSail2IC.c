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
    // V�rifie si la liste est vide
    if (l == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    printf("[");

    // Parcours et affichage de la liste
    Liste L2 = l;
    while (L2 != NULL) {
        printf("%d", L2->valeur);

        // Affiche une virgule apr�s chaque �l�ment sauf le dernier
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
    //concatene avec fuites m�moire
    if(l1==NULL) return l2;
    return ajoute2(premier2(l1), concatene(suite2(l1), l2));
}

void concatene_no_leak(Liste2* l1, Liste2 l2){
    /*** La fonction concat na�ve effectue une copie implicite inutile des �l�ments de la liste l1.
     Concat�nation de deux listes de type Liste2. ***/

    if(*l1==NULL){
      *l1=l2;
      return;
    }
    while(*l1 != NULL) l1=&((*l1)->suite);
    *l1 = l2;
}

Liste copy(Liste l){
    //cr�er une copie de la liste l
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
    /*** On peut r��crire cette fonction de mani�re �quivalente, en rempla�ant `ajouter2`
     par une simple affectation qui met � jour la r�f�rence de l'ancienne t�te de liste `l`
     par la nouvelle t�te r�f�renc�e, correspondant � la liste �tendue.***/
    if(l!=NULL){
        AETTL_no_leak(x, l->suite);

        l->valeur = ajoute(x, l->valeur);
    }
}

Liste2 listeinterclassements(Liste l1, Liste l2){
    //la fonction des interclassements avec fuites m�moires
    Liste2 l=NULL;
    if(l1==NULL) return ajoute2(copy(l2), l);//on utilise la fonciton copy pour rendre l'espace m�moire de liste d'interclassement ind�pendent de celui des listes l1 et l2
    if(l2==NULL) return ajoute2(copy(l1), l);

    return concatene(
                    AETTL(premier(l1), listeinterclassements(suite(l1), l2)),
                    AETTL(premier(l2), listeinterclassements(l1, suite(l2)))
                    );
}


Liste2 listeinterclassements_no_leak(Liste l1, Liste l2){
    /*** Les fonctions responsables des fuites de m�moire sont `concatener` et `AETTL`.
     Les fuites de m�moire concernent principalement la structure `Bloc2` et non `Bloc1`.
     Le programme ne pr�sente pas de fuites de m�moire au niveau des objets de type `Bloc1`.

     La fonction `concatener` utilise la fonction `ajoute2` pour chaque �l�ment � ajouter.
     Cela recr�e � chaque fois un nouvel �l�ment, rendant l'ancien premier �l�ment inutilisable.
     Par cons�quent, cet espace m�moire devient perdu (fuite de m�moire).

     De m�me, la fonction `AETTL` g�n�re une fuite m�moire dans la fonction `ajoute2`.
     � chaque fois, l'�l�ment `x` est ajout� au sommet de la liste et la liste r�sultante
     est stock�e dans un nouveau bloc de type `Bloc2`.
     Cela rend l'ancien bloc inutilisable, ce qui entra�ne une fuite m�moire. ***/

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
    // V�rifie si la liste est vide
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
