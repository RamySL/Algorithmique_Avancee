#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***
    Binome : Chabane Oualid, Sail Ramy
    ramy.sail@etu-upsaclay.fr
    oualid.chabane@universite-paris-saclay.fr
***/

/*
- Une implémentation de la structure de pile dont on aura besoin avec les liste chainées
- Dans notre utilisation de la pile, on stock dedans des pointeurs vers des strcutures deja alloués dans le tas
  donc pas besoin d'allouer de la mémoire pour le pointeur val du maillon quand on empile
*/

typedef struct maillon {
    void* val;
    struct maillon* next;
} Block;

typedef struct maillon* pile;

/*

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
/*         Définition de type d'image            */
/*                                               */
/*************************************************/

typedef enum {false, true} bool;

typedef struct bloc_image{
     bool blanc ;
    struct bloc_image * Im[4] ;
}bloc_image ;

typedef bloc_image *image ;

/*************************************************/
/*                                               */
/*            1- Bc(), Nr(), Qt()                */
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
/*             2- PrintI                         */
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

/*************************************************/
/*                                               */
/*             3- PrintPf                        */
/*                                               */
/*************************************************/
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
/*             4- LireI                          */
/*                                               */
/*************************************************/

/*
Principe Utilisé :

- On utilise deux pile : une pile pour compter le nombre de composante (images) saisie pour le constructeur + courant
    - une pile accumuler les images saisies (à chaque image saisie le compteur de tête de pile est incrémenté)

- quand on a un + qui est saisie on empile un 0 dans la pile des compteur
- quand un compteur atteint 4 on le dépile et on dépile 4 images de la pile des images et on empile l'image qu'ils forment avec Qt
(On incrémente aussi le compteur suivant de la pile si il existe)
*/

/*
- Préconditions : 4 images min dans la pile d'images et pile_compteur non vide
- Rassemble 4 sous images saisie après un + dans une seule avec la fonction Qt()
- Modifie la pile de compteur de manière approrié (dépilement, incrémentation de nombre de composante
d'ancien constrcuteurs +
*/
void mergeSousArbres (pile* pile_compteur, pile* pile_images){
    // on vient de former une quadtree
    image i0,i1,i2,i3;
    i3 = depiler(pile_images);
    i2 = depiler(pile_images);
    i1 = depiler(pile_images);
    i0 = depiler(pile_images);
    image qt = Qt(i0,i1,i2,i3);
    empiler(qt,pile_images);

    // on depile le compteur avec lequel on a terminé
    int* cpt;
    depiler(pile_compteur); // on a enlevé le 4
    if(*pile_compteur != NULL){
        // on incrémente le compteur (du constructeur ascendant) après dépilement
        cpt = (int*)peek(*pile_compteur);
        (*cpt)++;
        if((*cpt) == 4){
            mergeSousArbres(pile_compteur,pile_images);
        }
    }
}

/*
- Précondition : Entrée valide, avec ou sans parenthèse
- Rq : en supposant la précondition les malloc fait pour les entiers vont tous être libérer
à la fin de l'execution de la fonction avec les dépilement de la fonction auxiliaire
*/
image LireI () {
    pile pile_compteur = NULL;
    pile pile_images = NULL;

    char c;
    printf("Entrez l'image en mode simple (soummetez avec la touche entrer):\n");

    while ((c = getchar()) != '\n' && (c!= EOF)) {

        if(c == '+'){
            int* cpt = (int*) malloc(sizeof(int));
            *cpt=0;
            empiler(cpt,&pile_compteur);
        }else if (c=='N' || c == 'b') {

            if(c=='N'){
                image img = Nr();
                empiler(img,&pile_images);
            }else{
                image img = Bc();
                empiler(img,&pile_images);
            }

            if(pile_compteur != NULL){
                int* cpt = (int*)peek(pile_compteur);
                (*cpt)++;
                if((*cpt) == 4){
                    mergeSousArbres(&pile_compteur, &pile_images);
                }
            }
        }
    }

    return depiler(&pile_images);
}


/*************************************************/
/*                                               */
/*             5- Noire, Bla                     */
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
/*             6- Damier                         */
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
/*            7- DemiTour                        */
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
/*            8- FreeImag                        */
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
/*           9-Simplifie                         */
/*                                               */
/*************************************************/

/*
    Précondition : profondeur min 1
    - la fonction regarde qu'a la profondeur sur laquelle l'argument est (pas plus loin)
    - si l'image contient que des feuilles blanches renvoie b, si que
    des feuilles noires renvoie N, si pas monochrome renvoie -
*/
char estMono(image img){

    bool blanc = true;
    bool noir = true;

    int i = 0;
    while (blanc || noir){
        if(blanc && img->Im[i] == NULL){
            // cas d'une sous-image noire, on met blanc à false
            blanc = false;
        }
        else if(noir && img->Im[i]->blanc){
             // cas d'une sous-image blanc, on met noir à false
                noir = false;
        }
        else {
            //cas d'une sous image composée, on s'arrete, car l'image n'est pas monochrome
            noir = false;
            blanc = false;
        }
        i++;
    }
    if(noir){
        return 'N';
    }

    if(blanc){
        return 'b';
    }

    return '-';
}

void Simplifie(image* img){
    if(*img != NULL && !(*img)->blanc){
        Simplifie(&((*img)->Im[0]));
        Simplifie(&((*img)->Im[1]));
        Simplifie(&((*img)->Im[2]));
        Simplifie(&((*img)->Im[3]));

        int mono = estMono(*img);

        if(mono == 'b'){
            FreeImage(*img);
            *img = Bc();
        }
        else if(mono == 'N'){
            FreeImage(*img);
            *img = NULL;
        }
    }
}

/*************************************************/
/*                                               */
/*           10- IntersectionVide                */
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
/*           11- CompteSousArbres                */
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

void _CompteSousArbres (image i1, image i2, int* cpt, int *h, int hi1){
    if(i2 != NULL && !i2->blanc)
    {
        int* h0=(int*) malloc(sizeof(int)), h1=(int*) malloc(sizeof(int));
        _CompteSousArbres(i1,i2->Im[0],cpt, h0);
        _CompteSousArbres(i1,i2->Im[1],cpt, h1);
        if(*h0 < *h1) *h0 = *h1;

        _CompteSousArbres(i1,i2->Im[2],cpt, h1);
        if(*h0 < *h1) *h0 = *h1;

        _CompteSousArbres(i1,i2->Im[3],cpt, h1);
        if(*h0 < *h1) *h0 = *h1;
        *h = *h0 + 1;

        free(h0);
        free(h1);
    }
    else *h=0;


    if(*h == hi1 && ArbresEgaux(i1,i2)){
        (*cpt)++;
    }
}

int hauteur(image img){
    if(img == NULL || img->blanc) return 0;
    else {
        int h1 = hauteur(img.Im[0]);
        int h2 = hauteur(img.Im[1]);
        if(h1 < h2) h1 = h2;

        h2 = hauteur(img.Im[2]);
        if(h1 < h2) h1 = h2;

        h2 = hauteur(img.Im[3]);
        if(h1 < h2) h1 = h2;
        return h1 + 1;
    }
}

int CompteSousArbres (image i1, image i2){
    int cpt = 0;
    int *h = (int*) malloc(sizeof(int));
    _CompteSousArbres(i1,i2,&cpt, h, hauteur(i1));
    return cpt;
}

/*************************************************/
/*                                               */
/*           12- PrintPix                        */
/*                                               */
/*************************************************/


int PowExpTerm(int a, int n, int acc) {
    if (n == 0) {
        return acc;
    }
    if (n % 2 == 0) {
        return PowExpTerm(a * a, n / 2, acc);
    }
    return PowExpTerm(a, n - 1, acc * a);
}
/*
- Calcule a puissance n
*/
int PowExp(int a, int n) {
    return PowExpTerm(a, n, 1);
}

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
    PrintI(img1);
}
