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

void empiler(void* val, int size, pile* Pile) {

    Block* head = (Block*) malloc(sizeof(Block));

    head->val = malloc(size);
    if(val != NULL){
        memcpy(head->val, val, size);
    }else{
        head->val = NULL;
    }
    
    head->next = *Pile;
    *Pile = head;
}

void depiler(void* dest, int size, pile* Pile) {
    if (*Pile == NULL) {
        printf("Pile vide\n");
        return;
    }
    Block* top = *Pile;
    if(top->val != NULL){
        memcpy(dest, top->val, size);
        *Pile = top->next;
        free(top->val);
    }else{
        dest = NULL;
        *Pile = top->next;
    }
    free(top);

}

void peek(void* dest, int size, pile Pile) {
    if (Pile == NULL) {
        printf("Pile vide\n");
        return;
    }
    memcpy(dest, Pile->val, size); // Copy the top element's value to the destination
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
            printf("Dans le + \n");
            int cpt = 0;
            empiler(&cpt,sizeof(int),&pile_compteur);
        }else if (c == 'N' || c == 'b'){
            printf("Dans le c ou b \n");
            // ici on est sur le cas ou l'image est soit completement en blanc soit en noir, pas sub division en 4
            if (pile_compteur == NULL){
                if (c == 'N'){
                    return Nr();
                }else if(c == 'b'){
                    return Bc();
                }
            }
            int top_cpt; 
            peek(&top_cpt,sizeof(int),pile_compteur);
            // on vient de former une quadtree
            while(top_cpt == 4){
                printf("Dans le while du c ou b \n");
                image i0,i1,i2,i3;
                depiler(i3,sizeof(bloc_image),&pile_images);
                depiler(i2,sizeof(bloc_image),&pile_images);
                depiler(i1,sizeof(bloc_image),&pile_images);
                depiler(i0,sizeof(bloc_image),&pile_images);
                image qt = Qt(i0,i1,i2,i3);
                empiler(qt,sizeof(bloc_image),&pile_images);

                // on depile le compteur avec lequel on a terminé
                // on incrémente le compteur suivant après dépilement
                int cpt; 
                depiler(&cpt,sizeof(int),&pile_compteur); // on a enlevé le 4
                depiler(&cpt,sizeof(int),&pile_compteur);
                cpt++;
                empiler(&cpt,sizeof(int),&pile_compteur);
                top_cpt = cpt;

            }
            if(c=='N'){
                printf("Dans le N \n");
                image img = Nr();
                empiler(img,sizeof(bloc_image),&pile_images);
                int cpt;
                depiler(&cpt,sizeof(int),&pile_compteur);
                cpt++;
                empiler(&cpt,sizeof(int),&pile_compteur);
            }else if (c=='b'){
                printf("Dans le b \n");
                image img = Bc();
                empiler(img,sizeof(bloc_image),&pile_images);
                int cpt;
                depiler(&cpt,sizeof(int),&pile_compteur);
                cpt++;
                empiler(&cpt,sizeof(int),&pile_compteur);
            }
        }
    }

    int top_cpt; 
    peek(&top_cpt,sizeof(int),pile_compteur);
            // on vient de former une quadtree
    while(top_cpt == 4 ){
        printf("Dans le while de fin \n");
        image i0,i1,i2,i3;
        depiler(i3,sizeof(bloc_image),&pile_images);
        printf("apres premier depile \n");
        depiler(i2,sizeof(bloc_image),&pile_images);
        depiler(i1,sizeof(bloc_image),&pile_images);
        depiler(i0,sizeof(bloc_image),&pile_images);
        printf("apres les depilement");
        image qt = Qt(i0,i1,i2,i3);
        empiler(qt,sizeof(bloc_image),&pile_images);

        
        // on depile le compteur avec lequel on a terminé
        // on incrémente le compteur suivant après dépilement
        int cpt; 
        depiler(&cpt,sizeof(int),&pile_compteur); // on a enlevé le 4
        if (pile_compteur != NULL){
            printf("dans le diff de null");
                depiler(&cpt,sizeof(int),&pile_compteur);
                cpt++;
                empiler(&cpt,sizeof(int),&pile_compteur);
                top_cpt = cpt;
        }else{
            printf("dans le egale Null");
            image img; 
            depiler(img,sizeof(bloc_image),&pile_images);
            return img;
        }

        
    }
  
    printf ("Saisie Invalide \n");
    return NULL;
    

}


void main() {
   image i0,i1,i2,i3;
   i0=Nr();
   image img_l = LireI();
   printf("Maintenant la comparaison : \n");
   PrintI (img_l);

}