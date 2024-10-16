#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>  // For INT_MAX and INT_MIN
/*************************************************/
/*                                               */
/*                type booléen                   */
/*                                               */
/*************************************************/

typedef enum {false, true} bool;

/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long fact (int n)
{ if (n==0) return 1 ;
  else return n * fact(n-1) ;
}

/*************************************************/

// itou avec un argument out => passage par adresse

void bisfact(int n, long * r) {

  if (n==0)
    *r = 1.0 ;
  else {
    bisfact(n-1,r) ;
    *r = *r *n ;
  }
}

long fact2 (int n){
  long r ;
  bisfact(n,&r) ;
  return r ;
}

/*************************************************/

// itou en stoquant tout dans un tableau... (très bof en complexité espace)

long fact3(int n) {

  long * T = (long *) malloc((n+1)*sizeof(long)) ;
  T[0] = 1 ;

  for (int i=1 ; i <= n ; i++)
          T[i] = i* T[i-1] ;

  long r = T[n] ;
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


float Efloat2 (){

    float res = 0.0;
    int i = 0;
    float fct = 1.0;

    do {
      res += (1.0/fct);
      /*printf ("res : %f \n", res);
      printf("fact : %f \n", fct);*/
      printf ("res : %f \n", 1.0/fct);
      i++;
      fct = fact(i);
    }while(fct <= 1000000000.0);

    return res ;
}

/*************************************************/

double Edouble2 ()
{
    double res = 0.0;
    int i = 0;
    double fct = 1.0;

    do {
      res += (1.0/fct);
      /*printf ("res : %f \n", res);
      printf("fact : %f \n", fct);*/
      i++;
      fct = fact(i);
    }while(fct <= 10000000000.0);

    return res ;
}

float Efloat(){
  float res=2.0;
  int n=2;
  int fct=1;
  float ratio;
  do{
      fct*=n++;
      ratio=1.0/fct;
      res+=ratio;
  }
  while(ratio>0);
  return res;
}

double Edouble(){
  double res=2.0;
  int n=2;
  int fct=1;
  double ratio;
  do{
      fct*=n++;
      ratio=1.0/fct;
      res+=ratio;
  }
  while(ratio>0);
  return res;
}

/*long double Elongdouble(){
  long double res = 2.0;
  int n = 2;
  unsigned long long int fct = 1;
  long double ratio;

  do {
      fct *= n++;
      ratio = 1.0 / fct;
      res += ratio;
  }
  while (ratio > 0);

  return res;
}
*/
/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/

void afficheYfloat (int n)
{
  if(n<0) return;

  float y = Efloat() - 1;
  printf("y(0) = %f\n", y);
  for(int i=1; i<31; i++){
    float ysuiv = i * y - 1;
    y=ysuiv;
    printf("y(%d) = %f\n", i, ysuiv);
  }
}

/*************************************************/

void afficheYdouble (int n)
{
  if(n<0) return;

  double y = Efloat() - 1;
  printf("y(0) = %f\n", y);
  for(int i=1; i<n; i++){
    double ysuiv = i * y - 1;
    y=ysuiv;
    printf("y(%d) = %lf\n", i, ysuiv);
  }
}

void afficheZdouble(int n){
    if(n<0) return;
  double epsilon=1e-15;
  double y = Efloat() - 1, z=y+epsilon;
  printf("y(0) = %f\n", y);
  for(int i=1; i<n; i++){
    double ysuiv = i * y - 1;
    double zsuiv = i * z - 1;
    y=ysuiv;
    z=zsuiv;
    printf("z(%d) - y(%d) = %lf\n", i, i, zsuiv - ysuiv);
  }
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

long long GoodCpn (int p, int n)  // 0 <= p <= n
{ 
  if(p<0 || n<p) {
    printf("\nEntrees invalides.");
    return -1;
  }
  long long denum, num=1;
  if(p>n-p)
    // On s'assure que p est plus petit que n - p pour optimiser les boucles for en bas, qui s'arrêtent d'abord à p, puis à n - p, et enfin à n.
    // On utilise la propriété C(p, n) = C(n - p, n).
    p=n-p;
  for(int i=1; i<=p; i++) num*=i;
  //fact==p!
  denum=num;
  for(int i=p+1; i<=n-p; i++) num *=i;
  
  //fact==(n-p)!
  denum*=num;
  for(int i=n-p+1; i<=n; i++) num *= i;
  return num/denum;
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
        printf(" e1 = %.20f\ne= 2.7182818284590452353602874713527\n", Efloat() ) ;
        printf(" e2 = %.30lf \n", Edouble() ) ;
}

if (false) {
            printf("Valeurs de Y, selon float, double :\n") ;
            afficheYfloat(30) ;
            afficheYdouble(30) ;
            afficheZdouble(30);
}

if(false){
  for(int i=1; i<31; i++) printf("\nBadCpn(%d, %d) = %lld", i, 2*i, BadCpn(i, 2*i));
  
}

if(true){
    for(int i=1; i<31; i++) printf("\nGoodCpn(%d, %d) = %lld", i, 2*i, GoodCpn(i, 2*i));
  
}


    return 0;
}

/*void main(){
  printf ("e : %f %f \n", Edouble2(), Efloat2());
}*/




