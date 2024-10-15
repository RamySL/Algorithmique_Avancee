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


float Efloat (){

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

double Edouble ()
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
  
/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/

void afficheYfloat (int n) 
{}

/*************************************************/

void afficheYdouble (int n)  
{}


/*************************************************/
/*                                               */
/*             Binomiaux                         */
/*                                               */
/*************************************************/

long BadCpn (int p, int n)  // 0 <= p <= n
{ return 0 ;
}

/*************************************************/

long GoodCpn (int p, int n)  // 0 <= p <= n
{ return 0 ;
}

/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/

/*
int main(int argc, char** argv)
{

       float z1 ;
       double z2 ;
       long double z3 ;
       
       int cpt ;  
}*/
/************************************************************************/
 
      // mettre "if true" vs "if false" selon que vous voulez les tests ou pas
  
/************************  taille des nombres  *************************/
 /*    
if (true) {     

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
*/
/************************  factorielle  *************************/
/*
if (true) {

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

*/
/******************    Autour de e      *******************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274
/*
if (true) {  
        printf("Valeurs de e en float et en double :\n") ;
        printf(" e1 = %.20f  \n", Efloat() ) ;
        printf(" e2 = %.30lf \n", Edouble() ) ;         
}

if (false) {  
            printf("Valeurs de Y, selon float, double :\n") ;
            afficheYfloat(30) ;
            afficheYdouble(30) ;
}
        

    return 0;
}
*/

void main(){
  printf ("e : %f \n", Edouble());
}




