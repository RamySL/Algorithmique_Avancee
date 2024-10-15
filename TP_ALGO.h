#ifndef TP_ALGO_H_INCLUDED
#define TP_ALGO_H_INCLUDED

typedef struct block {
    int val;
    struct block* next;
}* list;

/*************************************************/
/*                                               */
/*                type booléen                   */
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

#endif // TP_ALGO_H_INCLUDED
