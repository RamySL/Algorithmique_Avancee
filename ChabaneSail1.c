#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

/***
Binome : Chabane Oualid, Sail Ramy
ramy.sail@etu-upsaclay.fr
oualid.chabane@universite-paris-saclay.fr
***/

typedef enum {false, true} bool;

/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long long fact (int n)
{ if (n==0) return 1 ;
  else return n * fact(n-1) ;
}

/*************************************************/

// itou avec un argument out => passage par adresse

void bisfact(int n, long long * r) {

  if (n==0)
    *r = 1.0 ;
  else {
    bisfact(n-1,r) ;
    *r = *r *n ;
  }
}

long long fact2 (int n){
  long long r ;
  bisfact(n,&r) ;
  return r ;
}

/*************************************************/

// itou en stoquant tout dans un tableau... (très bof en complexité espace)

long long fact3(int n) {

  long long * T = (long long *) malloc((n+1)*sizeof(long long)) ;
  T[0] = 1 ;

  for (int i=1 ; i <= n ; i++)
          T[i] = i* T[i-1] ;

  long long r = T[n] ;
  free(T) ;
  return r ;
}


/*************************************************/
/*                                               */
/*            Calcul de e                        */
/*                                               */
/*************************************************/


  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995
  //       9574966967 6277240766 3035354759 4571382178 5251664274
  // il est bien sûr interdit d'injecter directement cette approximation

/*************************************************/
/*
  - Notre condition d'arrêt est quand le ratio 1.0/fct s'annulle càd quand on a pas assez de précision
  en float pour capturer un aussi petit nombre
  - On évite aussi le recalcule du factoriel
*/
float Efloat(){
  float e=2.0;
  int n=2;
  long long fct= 1;
  float ratio;

  do{
      fct = fct * n;
      n++;
      ratio=1.0/fct;
      e+=ratio;

  }while(ratio > 0);

  return e;
}

double Edouble(){
  double e=2.0;
  int n=2;
  long long fct=1;
  double ratio;

  do{
      fct = fct * n;
      n++;
      ratio=1.0/fct;
      e += ratio;
  } while(ratio > 0);

  return e;
}

/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/

void afficheYfloat (int n)
{
    /***
    On constate que la suite diverge à partire de n=10
    ***/
  if(n < 0) return;

  float y = Efloat() - 1;
  printf("y(0) = %f\n", y);
  for(int i=1; i<=n; i++){
    y = i * y - 1;
    printf("y(%d) = %f\n", i, y);
  }
}

/*************************************************/

void afficheYdouble (int n)
{
    /***
    On constate que la suite diverge à partir de n=15
    Dû au fait que la valeur réelle de y15 est inférieure à la valeur calculée, la norme IEEE754 ne permet pas d'atteindre cette valeur
    réelle, les mathématiques font diverger la suite parce qu'elle est sortie de son scope
    ***/
  if(n<0) return;

  double y = Edouble() - 1;
  printf("y(0) = %f\n", y);
  for(int i=1; i<=n; i++){
    y = i * y - 1;
    printf("y(%d) = %lf\n", i, y);
  }
}

void afficheZdouble(int n){
  if(n < 0) return;

  double epsilon = 1e-15;
  double y = Edouble() - 1;
  double z = y + epsilon;

  printf("z(0) - y(0) = %f\n", z - y);

  for(int i = 1; i <= n; i++)
  {
    y = i * y - 1;
    z = i * z - 1;
    printf("z(%d) - y(%d) = %lf\n", i, i, z - y);
  }
}

/*************************************************/
/*                                               */
/*            Suite de reeles Xn                 */
/*                                               */
/*************************************************/
/*
précondition (n>=0)
il vaut mieux rendre -1 quand n<0 ?
*/
float X1 (int n){

  float res = 1.0f;

  while(n > 0){
    res = res + (1/res);
    n --;
  }

  return res;
}

float X2 (int n){
  if(n<=0){
    return 1;
  }
  float xn_1 = X2(n-1);
  return xn_1 + 1/xn_1;


}

float _X3(int n, float acc){
  if(n<=0){
    return acc;
  }

  return _X3(n-1,acc + 1/acc);
}
float X3(int n){
  return _X3(n,1);
}

void _X4(int n, float* acc){

  if(n > 0){
    *acc = *acc + 1/(*acc);
     _X4(n-1,acc);
  }

}
float X4(int n){
  float res = 1.0f;
  _X4(n,&res);
  return res;
}

/**
 * Après le test du calcul des X pour des puissances de 10, on constate que toutes les version recursive font crasher
 * le programme après 10^4, on déduit que le compilateur n'optimise pas les appels récursifs
 */

long double X1_bis(long n){

  long double res = 1.0;

  while(n > 0){
    res = res + (1/res);
    n --;
  }

  return res;
}

/*
après l'utilisation de X1 avec long double (X1_bis) on se rend compte les valeurs calculées par X1 devenaient clairement fausses à partir de 10^7
avec 4472.137049 pour X1_bis et 4096 pour X1 comme le montre les tests dans le main
*/


/*
  - fonction utilisée pour calculer la suite X avec les différentes fonction X1,X2...
  - calcule X(10^k) de 1 à k avec la fonction passée en argument
*/
void calcule_X_10_k (float (*X)(int n),int k){
  int pow = 1;
  for (int i = 1; i<=k;i++){
    pow *= 10;
    printf("X(10^%d) : %f | ",i,X(pow));
  }
  printf("\n");
}

/*************************************************/
/*                                               */
/*             Binomiaux                         */
/*                                               */
/*************************************************/

long long BadCpn (int p, int n)  // 0 <= p <= n
{
  if(p<0 ||n<p){
    printf("\nEntrées invalides.");
    return -1;
  }
  if(p==n || p==0) return 1;
  return BadCpn(p-1, n-1) + BadCpn(p, n-1);
}

/*************************************************/
int imageN(int n, int p){
    return n - (p+1);
}

int imageP(int p){
    return p-1;
}

long long _GoodCpn (long long** pascal_mat, int p, int n)
{
    /***
     Pour calculer C(p, n), seules certaines cases du triangle de Pascal sont utilisées (#) :

     | | | | | | | | | | | | | | | | | | |
     | | |#|#|#|#|#|#|#|#|#|#|#| | | | | |
     | | | |#|#|#|#|#|#|#|#|#|#|#| | | | |
     | | | | |#|#|#|#|#|#|#|#|#|#|#| | | |
     | | | | | |#|#|#|#|#|#|#|#|#|#|#| | |
     | | | | | | |#|#|#|#|#|#|#|#|#|#|#| |
     | | | | | | | |#|#|#|#|#|#|#|#|#|#| | <- On veut calculer ça
     | | | | | | | | | | | | | | | | | | |
     | | | | | | | | | | | | | | | | | | |
     | | | | | | | | | | | | | | | | | | |
     | | | | | | | | | | | | | | | | | | |
     | | | | | | | | | | | | | | | | | | |
     | | | | | | | | | | | | | | | | | | |

     1. La diagonale (C(p, p) = 1)
     2. La première ligne (C(0, n) = 1)
     Leurs valeures sont toujours à 1, donc on n'a pas besoin de les stocker dans la matrice finale

     L'espace utilisé peut être transformé en une matrice compacte de taille p × (n - p) :
     |#|#|#|#|#|#|#|#|#|#|#|
     |#|#|#|#|#|#|#|#|#|#|#|
     |#|#|#|#|#|#|#|#|#|#|#|
     |#|#|#|#|#|#|#|#|#|#|#|
     |#|#|#|#|#|#|#|#|#|#|#|
     |#|#|#|#|#|#|#|#|#|#|#|

     La position de C(p, n) est obtenue par une translation (1, p + 1) :
     Position de C(p, n) dans la matrice en appliquant la translation est [p - 1][n - (p + 1)]
    ***/
    if(p==n || p==0) return 1;
    if(pascal_mat[imageP(p)][imageN(n, p)] != -1) return pascal_mat[imageP(p)][imageN(n, p)];
    long long c1 = _GoodCpn(pascal_mat, p, n-1);
    long long c2 = _GoodCpn(pascal_mat, p-1, n-1);

    pascal_mat[imageP(p)][imageN(n, p)] = c1+c2;

    return pascal_mat[imageP(p)][imageN(n, p)];
}
long long GoodCpn (int p, int n)
{
/***
    La taille de la matrice qui va contenir le triangle de pascale va dépendre de n et p
    La matrice qui va contenire le triangle de Pascale est de taille p * (n-p)
        Explication:
    Si on utilise une matrice de taille (n+1) * (p+1) seulement sa moitié va etre utilisé

    On a deux optimisations:
        1) - on a supprimé les cases qui contient que des 1, on traite le cas
        de 1 dans la fonction récursive, on n'a pas besoin de stoquer une valeur qu'on connais déja.
        2) - On a supprimé le triangle vide non utilisé avec une simple fonction d'image qui fait une
        conversion du plan (p, n) vers le plan matriciel [0..p][0..(n-p)]
        2-bis) Une optimisation qu'on a voulu rajouter mais on n'a pas pu à cause de sa complexité est d'éliminer
        la case qui contient C(n-p, n) si on a déja une case qui contient C(p, n)
***/
  //Erreur si p>n
  if(p > n) return -1;

//L: length, nombre de lignes
//W: Width, nombre de colonnes
  int L = p;
  int W = n-p;
//Allocation de la matrice
  long long** pascal_mat = (long long**) malloc(L * sizeof(long long*));

  for(int i = 0; i<L; i++)
   {
       pascal_mat[i] = (long long*) malloc(W * sizeof(long long));
       for(int j=0; j<W; j++){
            pascal_mat[i][j] = -1;
       }
   }
   //Calcule du résultat
  long long ret = _GoodCpn(pascal_mat, p, n);

  for(int i = 0; i<L; i++)
   {
       free(pascal_mat[i]);
   }
   free(pascal_mat);

  return ret;
}
/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/

int main(int argc, char** argv)
{

       float z1 ;
       double z2 ;
       long double z3 ;

       int cpt ;

/************************************************************************/

      // mettre "if true" vs "if false" selon que vous voulez les tests ou pas

/************************  taille des nombres  *************************/

        if (false) {

               printf("tailles des entiers (peuvent varier selon le compilo) :\n") ;

               printf("short : %d octets\n", (int) sizeof(short));
               printf("int : %d octets\n", (int) sizeof(int));
               printf("long : %d octets\n", (int) sizeof(long));
               printf("long long : %d octets\n", (int) sizeof(long long));
               printf("float : %d octets\n", (int) sizeof(float));
               printf("double : %d octets\n", (int) sizeof(double));
               printf("long double : %d octets\n", (int) sizeof(long double));
               printf("\n") ;

               printf("limite des flottants (peuvent varier selon le compilo) :\n") ;

               z1 = 2.0 ; cpt = 0 ;
               while ( z1 > 1 ) { z1 = (z1-1)/10+1 ; cpt ++ ; }
               printf("1+1/10^c devient 1 a partir de c=%d pour les float\n", cpt) ;

               z2 = 2.0 ; cpt = 0 ;
               while ( z2 > 1 ) { z2 = (z2-1)/10+1 ; cpt ++ ; }
               printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cpt) ;

               z3 = 2.0 ; cpt = 0 ;
               while ( z3 > 1 ) { z3 = (z3-1)/10+1 ; cpt ++ ; }
               printf("1+1/10^c devient 1 a partir de c=%d pour les long double\n", cpt) ;

               z1 = 1.0 ; cpt = 0 ;
               while ( z1 > 0 ) { z1 = z1/10 ; cpt ++ ; }
               printf("1/10^c devient 0 a partir de c=%d pour les float\n", cpt) ;

               z2 = 1.0 ; cpt = 0 ;
               while ( z2 > 0 ) { z2 = z2/10 ; cpt ++ ; }
               printf("1/10^c devient 0 a partir de c=%d pour les double\n", cpt) ;

               z3 = 1.0 ; cpt = 0 ;
               while ( z3 > 0 ) { z3 = z3/10 ; cpt ++ ; }
               printf("1/10^c devient 0 a partir de c=%d pour les long double\n", cpt) ;

               printf("\nce programme suppose que les \"long\" font au moins 8 octets\n") ;
               printf("Si ce n'est pas le cas, utiliser des \"long long\" ? \n\n") ;

        }

        /************************  factorielle  *************************/

        if (false) {

             printf("factorielles de 0, de 5, de 20, trois codes : \n") ;
             printf("%ld \n",fact(0)) ;
             printf("%ld \n",fact2(0)) ;
             printf("%ld \n",fact3(0)) ;
             printf("%ld \n",fact(5)) ;
             printf("%ld \n",fact2(5)) ;
             printf("%ld \n",fact3(5)) ;
             printf("%ld \n",fact(20)) ;
             printf("%ld \n",fact2(20)) ;
             printf("%ld \n",fact3(20)) ;
             printf("Note : fact(20) est le dernier qui passe correctement avec 8 octets \n") ;
             printf("\n") ;

        }


        /******************    Autour de e      *******************************/

          // d'après google,
          // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995
          //       9574966967 6277240766 3035354759 4571382178 5251664274

        if (false) {
                printf("Valeurs de e en float et en double :\n") ;
                printf(" float : e1 = %.20f\n"
                       " reele :  e = 2.7182818284590452353602874713527\n", Efloat() ) ;
                printf(" double: e2 = %.20lf \n", Edouble() ) ;
        }

        if (true) {
                    printf("Valeurs de Y, selon float, double :\n\nYFloat:\n") ;
                    afficheYfloat(30) ;
                    printf("\nYDouble:\n");
                    afficheYdouble(30) ;
                    printf("\nZDouble:\n");
                    afficheZdouble(30);
        }

        if(false){
          for(int i=1; i<31; i++) printf("\nBadCpn(%d, %d) = %lld", i, 2*i, BadCpn(i, 2*i));

        }

        if(false){
            for(int i=1; i<31; i++) printf("\nGoodCpn(%d, %d) = %lld", i, 2*i, GoodCpn(i, 2*i));

        }
        /* LA suite Xn*/
        if(false){
          /*Calcule de X100 avec les 4 fonction*/
          printf ("X(100) avec X1 donne : %f \n",X1(100));
          printf ("X(100) avec X2 donne : %f \n",X2(100));
          printf ("X(100) avec X3 donne : %f \n",X3(100));
          printf ("X(100) avec X4 donne : %f \n",X4(100));

          printf ("\n");
          /*
          printf("Calcule de X(10^k) avec k de 1 a 9 avec X1 \n\n");
          calcule_X_10_k(X1,9);*/

          printf ("\n");
          /*
          printf("Calcule de X(10^k) avec k de 1 a 9 avec X2 \n\n");
          calcule_X_10_k(X2,9);

          printf ("\n");

          printf("Calcule de X(10^k) avec k de 1 a 9 avec X3 \n\n");
          calcule_X_10_k(X3,9);

          printf ("\n");

          printf("Calcule de X(10^k) avec k de 1 a 9 avec X4 \n\n");
          calcule_X_10_k(X4,9);
          */

          /*

          !!! à cause d'un problème de compatibilité sur windows l'affichage des long double ne marche pas
          parceque le compilateur gcc est bien destiné à représenter long double sur 128 bits mais l'environement
          de microsoft sous windows utilise 64 bits, ce qui cause les bug d'affichage.
          - pour ça il faut compiler avec l'option : -D__USE_MINGW_ANSI_STDIO, pour forcer mingw à utiliser sa propre
          implementation des long double
          */

          printf("Calcule de X(10^k) avec k de 1 a 12 avec X1_bis de type long double \n\n");
          long pow = 1;
          for (int i = 1; i<=12;i++){
            pow *= 10;
            printf("X(10^%d) : %Lf | ",i,X1_bis(pow));
          }
          printf("\n");

        }
}

