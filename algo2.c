/************* La correction du TD 2 devrait �tre mise sur ecampus ce samedi    ******/

#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                type bool�en                   */
/*                                               */
/*************************************************/

typedef enum {false, true} bool;

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

bool DeuxEgalX (Liste L, int x)
   { return true ; }
   

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
/*           SommeAvantKieme0               */
/*                                          */
/********************************************/
/*
- preconditions : k >= 0
 */
int SommeAvantKieme0_rec_non_terminal (Liste L, int k){

    if(k == 0 || L == NULL){
        return 0;
    }

    if(L != NULL){
        if(L->valeur == 0){
            return (L->valeur) + SommeAvantKieme0_rec_non_terminal (L->suite, k-1);
        }
        return (L->valeur) + SommeAvantKieme0_rec_non_terminal (L->suite, k);
    }
}

int SommeAvantKieme0_iter (Liste L, int k){
    int res = 0;
    int k_copie = k;
    Liste parcours = L;

    while (parcours != NULL && k_copie > 0){

        if(L->valeur == 0){
            k_copie --;
        }
        res += L->valeur;
        parcours = parcours->suite;
    }

    return res;
}
















/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{
    Liste l ;

        l = NULL ;
        empile(0,&l);
        empile(2,&l);
        empile(8,&l);
        empile(0,&l);
        empile(0,&l);
        empile(9,&l);
        empile(4,&l);
        empile(0,&l);
        empile(1,&l);
        empile(0,&l);
        empile(3,&l);
        empile(2,&l);

        affiche_iter(l);

        printf("conitent zero : %d \n", ContientZero_iter(l)); 
        printf("SommeAvantKieme0_rec_non_terminal : %d \n", SommeAvantKieme0_rec_non_terminal(l,4));
        VideListe(&l);
        return 0;
}




