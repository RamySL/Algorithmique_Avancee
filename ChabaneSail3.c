#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/***
    Binome : Chabane Oualid, Sail Ramy
    ramy.sail@etu-upsaclay.fr
    oualid.chabane@universite-paris-saclay.fr
***/

// 2) Implementation avec les listes chainés
// pile

typedef struct maillon {
    void* val;
    struct maillon* next;
} Block;

typedef struct maillon* pile;

/*
     Dans notre utilisation de la pile, on stock dedans des pointeurs vers des strcutures deja alloués dans le tas
     donc pas besoin d'allouer de la mémoire pour le pointeur val du maillon
*/
void empiler(void* val, pile* Pile) {

    Block* head = (Block*) malloc(sizeof(Block));

    head->val = val;
    head->next = *Pile;
    *Pile = head;
}

void* depiler(pile* Pile) {
    if (*Pile == NULL) {
        printf("Pile vide\n");
        return NULL;
    }

    Block* top = *Pile;
    void * res = top->val;

    *Pile = top->next;
    free(top);

    return res;

}

void* peek(pile Pile) {
    if (Pile == NULL) {
        printf("Pile vide\n");
        return NULL;
    }
    return Pile->val;
}
/*************************************************/
/*                                               */
/*            Définition de types                */
/*                                               */
/*************************************************/

typedef enum {false, true} bool;

typedef struct bloc_image{
     bool blanc ;
    struct bloc_image * Im[4] ;
}bloc_image ;

typedef bloc_image *image ;

/*
Mode simple explication : 
    le + :
        - Entre ascendant, descendant :  
            - est utilisé pour descendre en profondeur dans l'arbre, pas besoin d'un + pour acceder au feuilles (qui sont des blancs)
        - Entre freres : 
            - si le frere est un noeud interne il faut un +, sinon pas besoin
    Par exemple un arbre dont la racine possede que des pointeurs dans le tableau, dans la représentation on aura un ++ 

*/


/*************************************************/
/*                                               */
/*                     1                         */
/*                                               */
/*************************************************/

image Bc() {
    image img =  ((image) malloc (sizeof(struct bloc_image)));
    img -> blanc = true;
    return img;
}

image Nr() {
    return NULL;
}

image Qt(image i0,image i1,image i2,image i3){
    image img =  ((image) malloc (sizeof(struct bloc_image)));
    img -> blanc = false;

    img->Im[0] = i0;
    img->Im[1] = i1;
    img->Im[2] = i2;
    img->Im[3] = i3;

    return img;

}

/*************************************************/
/*                                               */
/*             Affichage                         */
/*                                               */
/*************************************************/

void PrintI(image img) {
    if(img == NULL){
        printf("N");
    }else if(img->blanc){
        printf("b");
    }else{
        printf("+");
        PrintI(img->Im[0]);
        PrintI(img->Im[1]);
        PrintI(img->Im[2]);
        PrintI(img->Im[3]);
    }
}

void _PrintPf (image img, int porfondeur){
    if(img == NULL){
        printf("N");
        printf("%d",porfondeur);
    }else if(img->blanc){
        printf("b");
        printf("%d",porfondeur);
    }else{
        printf("+");
        printf("%d",porfondeur);
        _PrintPf(img->Im[0], porfondeur+1);
        _PrintPf(img->Im[1], porfondeur+1);
        _PrintPf(img->Im[2], porfondeur+1);
        _PrintPf(img->Im[3], porfondeur+1);
    }
}

void PrintPf(image img){
    _PrintPf(img,0);
    printf("\n");   
}

/*************************************************/
/*                                               */
/*             Lecture                           */
/*                                               */
/*************************************************/

/*
- On utilise deux pile : une pile pour compter le nombre de composante construite pour le constructeur + courant
- une pile pour stocker les lettre b et N 

- quand on a un + qui est saisie on empile un 0 dans la pile des compteur
- quand un compteur atteint 4 on le dépile et on icrémente le nouveau sommet  et on dépile 
    4 élément de la pile des lettre et on empile l'image qu'ils forment

*/

/**
 * 
 * !!!!! Oublie pas de liberer les piles !!!!!
 */
image LireI () {
    pile pile_compteur = NULL;
    pile pile_images = NULL;

    int c;
    printf("Entrez l'image en mode simple (soummetez avec la touche entrer):\n");

    while ((c = getchar()) != '\n' && (c!= EOF)) {
        if(c == '+'){
            int* cpt = (int*) malloc(sizeof(int));
            *cpt=0;
            empiler(cpt,&pile_compteur);
        }else if (c == 'N' || c == 'b'){
            // ici on est sur le cas ou l'image est soit completement en blanc soit en noir, pas sub division en 4
            if (pile_compteur == NULL){
                if (c == 'N'){
                    return Nr();
                }else if(c == 'b'){
                    return Bc();
                }
            }
            int top_cpt = *((int*) peek(pile_compteur));
            // on vient de former une quadtree
            while(top_cpt == 4){
                image i0,i1,i2,i3;
                i3 = depiler(&pile_images);
                i2 = depiler(&pile_images);
                i1 = depiler(&pile_images);
                i0 = depiler(&pile_images);
                image qt = Qt(i0,i1,i2,i3);
                empiler(qt,&pile_images);

                // on depile le compteur avec lequel on a terminé
                // on incrémente le compteur suivant après dépilement
                int* cpt; 
                depiler(&pile_compteur); // on a enlevé le 4
                cpt = (int*)depiler(&pile_compteur);
                (*cpt)++;
                empiler(cpt,&pile_compteur);
                top_cpt = *cpt;
            }
            if(c=='N'){
                image img = Nr();
                empiler(img,&pile_images);
            }else{
                image img = Bc();
                empiler(img,&pile_images);
            }
            // un peek et une modif avec le pointeur au lieu de free puis malloc
            int* cpt = (int*)depiler(&pile_compteur);
            (*cpt)++;
            empiler(cpt,&pile_compteur);
        }
    }

    int top_cpt = *((int*) peek(pile_compteur));
            // on vient de former une quadtree
    while(top_cpt == 4 ){
        image i0,i1,i2,i3;
        i3 = depiler(&pile_images);
        i2 = depiler(&pile_images);
        i1 = depiler(&pile_images);
        i0 = depiler(&pile_images);
        image qt = Qt(i0,i1,i2,i3);
        empiler(qt,&pile_images);
        // on depile le compteur avec lequel on a terminé
        // on incrémente le compteur suivant après dépilement
        int* cpt; 
        depiler(&pile_compteur); // on a enlevé le 4
        if (pile_compteur != NULL){
                cpt = (int*) depiler(&pile_compteur);
                (*cpt)++;
                empiler(cpt,&pile_compteur);
                top_cpt = *cpt;
        }else{
            return depiler(&pile_images);
            
        }
    }
  
    printf ("Saisie Invalide \n");
    return NULL;
    

}


/*************************************************/
/*                                               */
/*             5                                 */
/*                                               */
/*************************************************/

bool Noir(image img){
    if(img == NULL){
        return true;
    }

    if(img -> blanc){
        return false;
    }

    return Noir(img->Im[0]) && Noir(img->Im[1]) && Noir(img->Im[2]) && Noir(img->Im[3]);
}

bool Blanc(image img){
    if(img == NULL){
        return false;
    }

    if(img -> blanc){
        return true;
    }

    return Blanc(img->Im[0]) && Blanc(img->Im[1]) && Blanc(img->Im[2]) && Blanc(img->Im[3]);
}




void main() {
   image i0,i1,i2,i3;
   i0=Nr();
   image img_l = LireI();
   printf("Maintenant la comparaison : \n");
   PrintI (img_l);
   


}