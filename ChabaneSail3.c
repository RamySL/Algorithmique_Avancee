#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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
        printf("Depilement : Pile vide\n");
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
        printf("Peek : Pile vide\n");
        return NULL;
    }
    return Pile->val;
}

void affiche_pile(pile Pile) {
    if (Pile == NULL) {
        printf("Pile vide\n");
        return;
    }

    printf("Pile contents:\n");

    Block* current = Pile;
    while (current != NULL) {
        printf("- %p \n",(current->val)); 
        current = current->next;
    }

    printf("End of pile\n");
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
int nb_malloc = 0;

image Bc() {
    image img =  ((image) malloc (sizeof(struct bloc_image)));
    printf("Allocation de la memoire avec l'adresse : %p \n",img);
    nb_malloc++;
    img -> blanc = true;
    return img;
}

image Nr() {
    return NULL;
}

image Qt(image i0,image i1,image i2,image i3){
    image img =  ((image) malloc (sizeof(struct bloc_image)));
    printf("Allocation de la memoire avec l'adresse : %p \n",img);
    nb_malloc++;
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
- une pile pour stocker les images

- quand on a un + qui est saisie on empile un 0 dans la pile des compteur
- quand un compteur atteint 4 on le dépile et on icrémente le nouveau sommet  et on dépile 
    4 élément de la pile des images et on empile l'image qu'ils forment avec Qt

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

        if(c == '+' || c == 'b' || c == 'N'){
            int top_cpt; 
            // on vient de former une quadtree
            while(pile_compteur != NULL && (top_cpt = *((int*) peek(pile_compteur))) == 4){
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

            if(c == '+'){
                int* cpt = (int*) malloc(sizeof(int));
                *cpt=0;
                empiler(cpt,&pile_compteur);
            }else {
                // ici on est sur le cas ou l'image est soit completement en blanc soit en noir, pas sub division en 4
                if (pile_compteur == NULL){
                    if (c == 'N'){
                        return Nr();
                    }else if(c == 'b'){
                        return Bc();
                    }
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
    }
    int top_cpt;
    top_cpt = *((int*) peek(pile_compteur));
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


/*************************************************/
/*                                               */
/*             Damier                            */
/*                                               */
/*************************************************/

image _Damier(int p){
    if(p==1){
        return Qt(Bc(),Nr(),Nr(),Bc());
    }

    return Qt(_Damier(p-1),_Damier(p-1),_Damier(p-1),_Damier(p-1));
}
image Damier(int p){
    if (p==0){
        return Nr();
    }
    return _Damier(p);
    
}

/*************************************************/
/*                                               */
/*            DemiTour                           */
/*                                               */
/*************************************************/

image DemiTour(image img){

    if (img == NULL){
        return Nr();
    }

    if(img->blanc){
        return Bc();
    }

    return Qt(DemiTour(img->Im[3]), DemiTour(img->Im[2]), DemiTour(img->Im[1]), DemiTour(img->Im[0]));
}

/*************************************************/
/*                                               */
/*            8                                  */
/*                                               */
/*************************************************/

/*
- Il faut supprimer en remontant les appels 
- Donc on fait une version itérative pour éviter les débordement de piles
*/

/*
- procédure qui parcoure tout l'arbre et empile les pointeurs des images dans la pile passée en inout
*/
void collect_ptrs (image img, pile* Pile){
    if(img != NULL){
        empiler(img,Pile);
        if(!img->blanc){
            collect_ptrs(img->Im[0],Pile);
            collect_ptrs(img->Im[1],Pile);
            collect_ptrs(img->Im[2],Pile);
            collect_ptrs(img->Im[3],Pile);
        }
    }
}
/*
- On fait deux passes pour libérer les blocs, une passe pour collecter les pointeurs dans
une pile
- Une autre passe pour le parcours de la pile et la libération des blocs en commençant par les feuilles
*/

void FreeImage(image img){
    pile Pile = NULL;
    collect_ptrs(img,&Pile);

    while (Pile != NULL){
        image i = depiler(&Pile);
        free(i);
        printf("libeartion de la memoire : %p \n",i);
        nb_malloc--;
    }

}

/*************************************************/
/*                                               */
/*           Simplifie                           */
/*                                               */
/*************************************************/

/*
    Précondition : profondeur min 1
    - la fonction regarde qu'a la profondeur sur laquelle l'argument est
    - si l'image contient que des feuilles blanches renvoie 1, si que
    des feuilles noires renvoie 0, si pas monochrome renvoie -1
*/
int estMono(image img){
    int countB = 0;
    int countN = 0;
    int i = 0;
    
    while (i<4){
        if(img->Im[i] == NULL){
            countN ++;
        }else{
            if(img->Im[i]->blanc){
                countB ++;
            }
        }
        i++;
    }
    if(countN == 4){
        return 0;
    }

    if(countB == 4){
        return 1;
    }
    return -1;
}
/*
- elimine les premiers monochromes trouvés qui sont sur la même profondeur, élimine 4 monochrome 
maximum en un seul appel, et 1 au min si il existe
- renvoie vrai dans le cas où il y'avait un monochrome faux sinon
*/
bool ElimineMono1Gen(image* img){

    if(*img != NULL && !(*img)->blanc){
        int mono = estMono(*img);
        if(mono != -1){
            FreeImage(*img);
            //remplacement de +bbbb par b
            if(mono == 1){
                *img = Bc();
            }
            // remplacement de +NNNN par N
            else{
                *img = NULL;
            }

            return true;
        }

        return (ElimineMono1Gen (&((*img)->Im[0])) ||
                ElimineMono1Gen (&((*img)->Im[1])) ||
                ElimineMono1Gen (&((*img)->Im[2])) ||
                ElimineMono1Gen (&((*img)->Im[3]))); 
    }

    return false;
}
void Simplifie (image* img){
    bool monExiste = true;

    while (monExiste){
        monExiste = ElimineMono1Gen(img);
    }
}


/*************************************************/
/*                                               */
/*           IntersectionVide                    */
/*                                               */
/*************************************************/

bool IntersectionVide (image i1, image i2){
    if(i1 == NULL && i2 == NULL){
        return false;
    }

    if((i1 != NULL && i1->blanc) || (i2 != NULL && i2->blanc)){
        return true;
    }

    return (IntersectionVide(i1->Im[0],i2->Im[0]) &&
            IntersectionVide(i1->Im[1],i2->Im[1]) &&
            IntersectionVide(i1->Im[2],i2->Im[2]) &&
            IntersectionVide(i1->Im[3],i2->Im[3]));
}
/*************************************************/
/*                                               */
/*           CompteSousArbres                    */
/*                                               */
/*************************************************/
/*
- teste si les deux arbre sont égaux sémantiquement (et pas qu'en mémoire)
- Une manière plus optimisée serait peut etre que c'est un noeud internes regarder si les quatre feilles sont de même 
nature avant de partir récursivement ?
*/
bool ArbresEgaux (image i1, image i2){

    if((i1 == NULL && i2 == NULL) ||
        ((i1 != NULL && i1->blanc) &&  (i2 != NULL && i2->blanc))){
            
            return true;
    }

    if((i1 != NULL && !i1->blanc) &&  (i2 != NULL && !i2->blanc)){
        return ArbresEgaux(i1->Im[0], i2->Im[0]) &&
                ArbresEgaux(i1->Im[1], i2->Im[1]) &&
                ArbresEgaux(i1->Im[2], i2->Im[2]) &&
                ArbresEgaux(i1->Im[3], i2->Im[3]);
    }

    return false;
}

void _CompteSousArbres (image i1, image i2, int* cpt){
    // si i1 est exactement i2 alors pas besoin de chercher dans les sous arbres
    if(ArbresEgaux(i1,i2)){
        (*cpt)++;
        return;
    }
    if(i2 != NULL && !i2->blanc){
        _CompteSousArbres(i1,i2->Im[0],cpt);
        _CompteSousArbres(i1,i2->Im[1],cpt);
        _CompteSousArbres(i1,i2->Im[2],cpt);
        _CompteSousArbres(i1,i2->Im[3],cpt);
    }
        
    


}

int CompteSousArbres (image i1, image i2){
    int cpt = 0;
    _CompteSousArbres(i1,i2,&cpt);
    return cpt;
}

/*************************************************/
/*                                               */
/*           12- PrintPix                        */
/*                                               */
/*************************************************/

/*
*/
/*
- Calcule a puissance n
*/
int PowExp(int a, int n){
    if (n==0){
        return 1;
    }

    if(n%2 == 0){
        return PowExp(a*a,n/2);
    }

    return a*PowExp(a*a,(n-1)/2);
}

/*
*/

void rempliePixels (image img, char** mat, int col_debut,int lig_debut, int cote_carre){
    char c = '#';
    int lig_fin = lig_debut + cote_carre;
    int col_fin = col_debut + cote_carre;

    if(img == NULL){
        c = '8';
    }else if(img->blanc){
        c = '.';
    }else if(cote_carre == 1){
        c = '-';
    }else{
        cote_carre = cote_carre / 2;
        rempliePixels(img->Im[0], mat, col_debut, lig_debut, cote_carre);
        rempliePixels(img->Im[1], mat, col_debut+cote_carre, lig_debut, cote_carre);
        rempliePixels(img->Im[2], mat, col_debut, lig_debut+cote_carre, cote_carre);
        rempliePixels(img->Im[3], mat, col_debut+cote_carre, lig_debut+cote_carre, cote_carre);
    }

    if(c != '#'){
        //printf("rentrer pour remplire la mtrice de lig : %d - %d et col : %d - %d avec : %c \n",lig_debut,lig_fin,col_debut,col_fin,c );
        for (int i = lig_debut; i < lig_fin; i++){
            for (int j = col_debut; j < col_fin; j++){
                mat[i][j] = c;
            }
        }
    }



}
/*
- On contruit une matrice carrée de dimension 2^k qu'on remplit avec la fonction ci dessus avec le charactere 
approprié.
*/
void PrintPix(image img, int k){
    int dim = PowExp(2,k);
    
    char** mat = (char**)malloc(dim * sizeof(char*));
    for (int i = 0; i < dim; i++) {
        mat[i] = (char*)malloc(dim * sizeof(char));
    }

    rempliePixels(img, mat, 0, 0, dim);

    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            printf("%c",mat[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < dim; i++) {
        free(mat[i]);
    }
    free(mat);



}

void main() {
    image img1 = LireI();
    //image img2 = LireI();
    printf("On est passe au teste \n");
    PrintI(img1);
    printf("\n");
    PrintPix(img1,3);

    

}