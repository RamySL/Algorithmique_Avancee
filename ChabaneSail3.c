#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/***
    Binome : Chabane Oualid, Sail Ramy
    ramy.sail@etu-upsaclay.fr
    oualid.chabane@universite-paris-saclay.fr
***/

typedef enum {false, true} bool;


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

/***
    Structure de File, utilisé dans la question 13
***/

typedef struct {
    Block* tete;  // Premier élément de la file
    Block* queue; // Dernier élément de la file
} fileB;

typedef fileB* file;

// Fonction pour initialiser la file
void initialiser_file(file* File) {
    *File = (file) malloc(sizeof(fileB));
    (*File)->tete = NULL;
    (*File)->queue = NULL;
}

bool fileVide(file f){
    return f->tete==NULL && f->queue==NULL;
}


// Ajouter un élément à la file (enqueue)
void enfiler(void* val, file File) {
    Block* nouveau = (Block*) malloc(sizeof(Block));

    if (!nouveau) {
        printf("Erreur : Echec de l'allocation memoire\n");
        return;
    }

    nouveau->val = val;
    nouveau->next = NULL;

    if (File->queue == NULL) { // Si la file est vide
        File->tete = nouveau;
        File->queue = nouveau;
    } else { // Ajouter à la fin
        File->queue->next = nouveau;
        File->queue = nouveau;
    }
}

// Retirer un élément de la file (dequeue)
void* defiler(file File) {
    if (File->tete == NULL) { // Si la file est vide
        printf("Defilement : File vide\n");
        return NULL;
    }

    Block* premier = File->tete;
    void* valeur = premier->val;

    File->tete = premier->next;
    if (File->tete == NULL) { // Si la file est maintenant vide
        File->queue = NULL;
    }

    free(premier);
    return valeur;
}

void libererFile(file f) {
    while(f->tete != NULL || f->queue != NULL){
       void* e = defiler(f);
    }
    free(f);
}

// Consulter le premier élément de la file (peek)
void* consulter(file File) {
    if (File->tete == NULL) {
        printf("Consulter : File vide\n");
        return NULL;
    }
    return File->tete->val;
}

// Afficher le contenu de la file
void afficher_file(file File) {
    if (File->tete == NULL) {
        printf("File vide\n");
        return;
    }

    printf("Contenu de la file :\n");

    Block* actuel = File->tete;
    while (actuel != NULL) {
        printf("- %p\n", actuel->val);
        actuel = actuel->next;
    }

    printf("Fin de la file\n");
}

/*************************************************/
/*                                               */
/*         Définition de type d'image            */
/*                                               */
/*************************************************/

typedef struct bloc_image{
     bool blanc ;
    struct bloc_image * Im[4] ;
}bloc_image ;

typedef bloc_image* image ;

/*************************************************/
/*                                               */
/*            1- Bc(), Nr(), Qt()                */
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
/*             2- PrintI                         */
/*                                               */
/*************************************************/

void _PrintI(image img) {
    if(img == NULL){
        printf("N");
    }else if(img->blanc){
        printf("b");
    }else{
        printf("+");
        _PrintI(img->Im[0]);
        _PrintI(img->Im[1]);
        _PrintI(img->Im[2]);
        _PrintI(img->Im[3]);
    }
}

void PrintI(image img){
    _PrintI(img);
    printf("\n");
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

    return (Noir(img->Im[0]) && Noir(img->Im[1]) && Noir(img->Im[2]) && Noir(img->Im[3]));
}

bool Blanc(image img){
    if(img == NULL){
        return false;
    }

    if(img -> blanc){
        return true;
    }

    return (Blanc(img->Im[0]) && Blanc(img->Im[1]) && Blanc(img->Im[2]) && Blanc(img->Im[3]));
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
    int countB = 0;
    int countN = 0;
    int i = 0;

    while (i<4){
        if(img->Im[i] == NULL){
            countN ++;
        }else{
            if(img->Im[i]->blanc){
                countB ++;
            }else{
                return '-';
            }
        }

        if(countB != 0 && countN != 0) {
            return '-';
        }
        i++;
    }
    if(countN == 4){
        return 'N';
    }

    if(countB == 4){
        return 'b';
    }


}

void Simplifie(image* img){
    if(*img != NULL && !(*img)->blanc){
        Simplifie(&((*img)->Im[0]));
        Simplifie(&((*img)->Im[1]));
        Simplifie(&((*img)->Im[2]));
        Simplifie(&((*img)->Im[3]));

        char mono = estMono(*img);

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
- test si les deux arbre sont égaux sémantiquement (et pas qu'en mémoire)
*/
bool ArbresEgaux (image i1, image i2){

    if((i1 == NULL && i2 == NULL) ||
        ((i1 != NULL && i1->blanc) &&  (i2 != NULL && i2->blanc))){

            return true;
    }

    if((i1 != NULL && !i1->blanc) &&  (i2 != NULL && !i2->blanc)){
        return (ArbresEgaux(i1->Im[0], i2->Im[0]) &&
                ArbresEgaux(i1->Im[1], i2->Im[1]) &&
                ArbresEgaux(i1->Im[2], i2->Im[2]) &&
                ArbresEgaux(i1->Im[3], i2->Im[3]));
    }

    return false;
}

void _CompteSousArbres (image i1, image i2, int* cpt, int *h, int hi1){
    if(i2 != NULL && !i2->blanc)
    {
        int* h0=(int*) malloc(sizeof(int));
        int* h1=(int*) malloc(sizeof(int));
        _CompteSousArbres(i1,i2->Im[0],cpt, h0, hi1);
        _CompteSousArbres(i1,i2->Im[1],cpt, h1, hi1);
        if(*h0 < *h1) *h0 = *h1;

        _CompteSousArbres(i1,i2->Im[2],cpt, h1, hi1);
        if(*h0 < *h1) *h0 = *h1;

        _CompteSousArbres(i1,i2->Im[3],cpt, h1, hi1);
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
        int h1 = hauteur(img->Im[0]);
        int h2 = hauteur(img->Im[1]);
        if(h1 < h2) h1 = h2;

        h2 = hauteur(img->Im[2]);
        if(h1 < h2) h1 = h2;

        h2 = hauteur(img->Im[3]);
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

/*************************************************/
/*                                               */
/*           13- Alea                            */
/*                                               */
/*************************************************/


/***
 Le code suivant est une Déclaration de la structure des arbres AVL à utiliser dans la fonction Alea.
 Entièrement développée par nous, nous ne l'avons pas trouvée en ligne.
***/

typedef struct avl_s {
    int diff;
    int e;
    struct avl_s* left;
    struct avl_s* right;
}* avl;

avl create(int e) {
    avl node = (avl) malloc(sizeof(struct avl_s));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    node->diff = 0;
    node->e=e;
    node->left = node->right = NULL;
    return node;
}

void rotate_left(avl* tr){
    avl rs = (*tr)->right;
    (*tr)->right = rs->left;
    rs->left = *tr;
    *tr=rs;
}

void rotate_right(avl* tr){
    avl ls = (*tr)->left;
    (*tr)->left = ls->right;
    ls->right = *tr;
    *tr=ls;
}

void rebalance_right(avl* tr){
    if((*tr)->left->diff > 0){
        int bal = (*tr)->left->right->diff;
        rotate_left(&((*tr)->left));
        rotate_right(tr);
        if(bal == -1){
            (*tr)->left->diff=0;
            (*tr)->right->diff=1;
        } else if (bal == 1){
            (*tr)->left->diff=-1;
            (*tr)->right->diff=0;
        } else if(bal == 0){
            (*tr)->left->diff=0;
            (*tr)->right->diff=0;
        }
        else printf("unexpected");
    } else {
        //simple rotation right
        rotate_right(tr);
        (*tr)->diff=0;
        (*tr)->right->diff=0;
    }
}

void rebalance_left(avl* tr){
    if((*tr)->right->diff < 0){
        //double rotation right, then left
        int bal = (*tr)->right->left->diff;
        rotate_right(&((*tr)->right));
        rotate_left(tr);
        if(bal == -1){
            (*tr)->right->diff=1;
            (*tr)->left->diff=0;
        } else if (bal == 1){
            (*tr)->right->diff=0;
            (*tr)->left->diff=-1;
        } else if(bal == 0){
            (*tr)->right->diff=0;
            (*tr)->left->diff=0;
        }
        else printf("unexpected");
    } else {
        //simple rotation right
        rotate_left(tr);
        (*tr)->diff=0;
        (*tr)->left->diff=0;
    }
}

void add_aux(avl* tr, int e, int* balanced) {
    /*
        Dépendences:
            rebalance_left
            rebalance_right
    */
    if (*tr == NULL) {
        *tr = create(e);
        return;
    }

    if (e < (*tr)->e) {
        add_aux(&((*tr)->left), e, balanced);
        if (!(*balanced)) {
            (*tr)->diff--;
            if ((*tr)->diff == -2) {
                rebalance_right(tr);
                *balanced = 1;
            }
            if((*tr)->diff==0){
                *balanced = 1;
            }
        }
    } else {
        add_aux(&((*tr)->right), e, balanced);
        if (!(*balanced)) {
            (*tr)->diff++;
            if ((*tr)->diff == 2) {
                rebalance_left(tr);
                *balanced = 1;
            }
            if((*tr)->diff==0){
                *balanced = 1;
            }
        }
    }
}

void add(avl* tr, int e){
    /*
        Dépendences:
            add_aux
    */
    int* balanced = (int*) malloc(sizeof(int));
    *balanced=0;
    add_aux(tr, e, balanced);
}


int in_avl(avl tr, int e){
    /*
        ne dépend d'aucune fonction
    */
    if(tr==NULL) return 0;

    if(e<tr->e) return in_avl(tr->left, e);
    if(e>tr->e) return in_avl(tr->right, e);
    return 1;
}

void free_t(avl tr){
    if(tr!=NULL){
        free_t(tr->left);
        free_t(tr->right);
        free(tr);
    }
}

void avl_to_stack(avl tree, pile* p){
    /*
        Dépendences:
            empiler
    */
    if(tree != NULL){
        avl_to_stack(tree->right, p);
        empiler(&(tree->e), p);
        avl_to_stack(tree->left, p);
    }
}

/***
    Fin de déclaration de la structure des AVL
***/


void loi_uniforme(avl* tree, int length, int nblancs){
    /*
        Dépendences:
            in_avl
    */
    *tree = NULL;
    if(nblancs>length) {
        printf("\nLe nombre d'images blanches est absurde");
        return;
    }
    for(int i= 0; i < nblancs; i++){
        int idx = rand()%length, offset=0, stop=0;
        while(!stop){
            //Si l'indice généré est déja présent, on cherche l'indice libre le plus proche à lui
            if(idx + offset < length && !in_avl(*tree, idx + offset)){
                idx+=offset;
                stop=1;
            } else if(idx - offset> -1 && !in_avl(*tree, idx - offset)){
                idx-=offset;
                stop=1;
            } else if(idx - offset < 0 && idx + offset >= length){
                printf("ERROR: n est ttrop grand");
                break;
            }
            offset++;
        }

        add(tree, idx);
    }
}

double normInv(double p, double mu, double sigma) {
    //Cette fonction est trouvé sur github: https://gist.github.com/kmpm/1211922/6b7fcd0155b23c3dc71e6f4969f2c48785371292
    //Elle basée sur les principes de l'analyse numérique, c'est une approximation par tranche de la fonction inverse de la fonction de répartition gaussienne
    if (p <= 0.0 || p >= 1.0) {
        printf("The probability p must be between 0 and 1 (exclusive).\n");
        exit(1);
    }
    if (sigma <= 0.0) {
        printf("The standard deviation sigma must be positive.\n");
        exit(1);
    }

    double q, r, val;

    q = p - 0.5;

    // AS241 Algorithm
    if (fabs(q) <= 0.425) {
        // 0.075 <= p <= 0.925
        r = 0.180625 - q * q;
        val = q * (((((((r * 2509.0809287301226727 +
                         33430.575583588128105) * r + 67265.770927008700853) * r +
                       45921.953931549871457) * r + 13731.693765509461125) * r +
                     1971.5909503065514427) * r + 133.14166789178437745) * r +
                   3.387132872796366608) /
              (((((((r * 5226.495278852854561 +
                     28729.085735721942674) * r + 39307.89580009271061) * r +
                   21213.794301586595867) * r + 5394.1960214247511077) * r +
                 687.1870074920579083) * r + 42.313330701600911252) * r + 1);
    } else {
        // Closer than 0.075 from {0, 1} boundary
        if (q > 0.0) {
            r = 1.0 - p;
        } else {
            r = p;
        }

        r = sqrt(-log(r)); // r = sqrt(-log(r))

        if (r <= 5.0) {
            // <==> min(p,1-p) >= exp(-25) ~= 1.3888e-11
            r -= 1.6;
            val = (((((((r * 7.7454501427834140764e-4 +
                         0.0227238449892691845833) * r + 0.24178072517745061177) *
                       r + 1.27045825245236838258) * r +
                      3.64784832476320460504) * r + 5.7694972214606914055) * r +
                    4.6303378461565452959) * r + 1.42343711074968357734) /
                  (((((((r * 1.05075007164441684324e-9 +
                         5.475938084995344946e-4) * r + 0.0151986665636164571966) *
                       r + 0.14810397642748007459) * r + 0.68976733498510000455) *
                     r + 1.6763848301838038494) * r + 2.05319162663775882187) *
                   r + 1.0);
        } else {
            // Very close to 0 or 1
            r -= 5.0;
            val = (((((((r * 2.01033439929228813265e-7 +
                         2.71155556874348757815e-5) * r +
                        0.0012426609473880784386) * r + 0.026532189526576123093) *
                      r + 0.29656057182850489123) * r +
                     1.7848265399172913358) * r + 5.4637849111641143699) * r +
                   6.6579046435011037772) /
                  (((((((r * 2.04426310338993978564e-15 +
                         1.4215117583164458887e-7) * r +
                        1.8463183175100546818e-5) * r +
                       7.868691311456132591e-4) * r + 0.0148753612908506148525) *
                     r + 0.13692988092273580531) * r + 0.59983220655588793769) *
                   r + 1.0);
        }

        if (q < 0.0) {
            val = -val;
        }
    }

    return mu + sigma * val;
}

void loi_gaussienne(avl* tree, int length, int nblancs, int mu, int sigma){
     /***
     La fonction void loi_gaussienne(avl* tree, int length, int nblancs, int mu, int sigma) génère un échantillon gaussien d'images blanches avec Mu et Sigma.
     Mu représente l'indice de l'image sur laquelle on veut concentrer plus les images blanches dans son voisinage.
     Sigma représente la distance moyenne entre chaque image blanche par rapport à la moyenne.
     Lorsqu'on l'augmente, l'échantillon se répartit de plus en plus largement.
     L'indice d'une image correspond à son ordre parmi les fils.
     ***/
    /*
        Dépendences:
            normInv
            add
    */
    *tree = NULL;
    if(nblancs>length) {
        printf("\nLe nombre d'images blanches est absurde");
        return;
    }
    for(int i= 0; i < nblancs; i++){
        //Pour généraliser encore mieux à une loi quelconque, il suffit de rempalcer normInv par la loi souhaité implementer par exemple rand()%length dans le cas de la loi uniforme
        int idx = (int) normInv((rand() + 1.0) / (RAND_MAX + 2.0), mu, sigma), offset=0, stop=0;
        //Puisque idx est généré par la fonction  de répartition, il y a rien qui l'empeche d'etre négative ou plus grand que length
        //dans ce cas, on le normalize à 0 ou à length-1
        if(idx < 0) idx = 0;
        if(idx >= length) idx = length-1;

        //Si l'indice généré est déja présent, on cherche l'indice libre le plus proche à lui
        while(!stop){
            if(idx + offset < length && !in_avl(*tree, idx + offset)){
                idx+=offset;
                stop=1;
            } else if(idx - offset> -1 && !in_avl(*tree, idx - offset)){
                idx-=offset;
                stop=1;
            } else if(idx - offset < 0 && idx + offset >= length){
                printf("ERROR: n est trop grand");
                break;
            }
            offset++;
        }

        add(tree, idx);
    }
}

image Alea(int k, int n){
    //Fonction de la question 13
    /***
     L'idée : on génère tous les fils à la profondeur k, puis on les enfile, suivant la loi donnée (gaussienne ou uniforme).
     On itère sur la file tant qu'elle est pleine, en regroupant les éléments par quatre pour former des nœuds Qt.
     À la fin, on obtient un arbre dont les fils sont générés selon la loi donnée.
     La génération des fils suit cette démarche :
         1. On appelle la fonction associée à la loi choisie (gaussienne ou uniforme), qui retourne une collection triée d'indices (exemple : 1, 3, 5).
            Ces indices représentent les positions des images blanches dans l'ensemble des images générées.
         2. Ensuite, on parcourt tous les indices de 0 à 2^k - 1.
            - Lorsqu'on rencontre un indice correspondant à la collection d'indices retournée, on le dépile.
            - À cet instant, une image blanche est ajoutée (enfilée) dans la file des images générées.
         Au final, la file contiendra toutes les images, avec les images blanches placées aux indices spécifiés par la loi.
    ***/
    /*
        Dépendences:
            initialiser_file
            PowExp
            loi_uniforme/loi_gaussienne
            avl_to_stack
            depiler
            enfiler
            filevide
            defiler
            liberer_file
            free_t
    */

    int p = PowExp(4, k);
    file f;
    initialiser_file(&f);

    avl tree=NULL;
    pile pl=NULL;

    /***
     La fonction void loi_gaussienne(avl* tree, int length, int nblancs, int mu, int sigma) génère un échantillon gaussien d'images blanches avec Mu et Sigma.
     Mu représente l'indice de l'image sur laquelle on veut concentrer plus les images blanches dans son voisinage.
     Sigma représente la distance moyenne entre chaque image blanche par rapport à la moyenne.
     Lorsqu'on l'augmente, l'échantillon se répartit de plus en plus largement.
     L'indice d'une image correspond à son ordre parmi les fils.
     dans les lignes d ecommentaires suivantes, on vous met un exemple d'un échantillon gaussien généré avec
     L'appel Alea(4, 10) avec Mu = 4*4*4*4-20 et Sigma = 7
     Pour le générer il faut remplacer la ligne du code loi_uniforme(&tree, p, n); par loi_gaussienne(&tree, p, n, 4*4*4*4-20, 7);
    /*
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        888888888888888888888888888888888888....888888888888....8888....
        888888888888888888888888888888888888....888888888888....8888....
        888888888888888888888888888888888888....888888888888....8888....
        888888888888888888888888888888888888....888888888888....8888....
        88888888888888888888888888888888........888888888888888888888888
        88888888888888888888888888888888........888888888888888888888888
        88888888888888888888888888888888........888888888888888888888888
        88888888888888888888888888888888........888888888888888888888888
        8888888888888888888888888888888888888888....8888888888888888....
        8888888888888888888888888888888888888888....8888888888888888....
        8888888888888888888888888888888888888888....8888888888888888....
        8888888888888888888888888888888888888888....8888888888888888....
        88888888888888888888888888888888........8888....8888888888888888
        88888888888888888888888888888888........8888....8888888888888888
        88888888888888888888888888888888........8888....8888888888888888
        88888888888888888888888888888888........8888....8888888888888888
    ***/
    loi_uniforme(&tree, p, n);
    //loi_gaussienne(&tree, p, n, 4*4*4*4-20, 7);
    avl_to_stack(tree, &pl);
    int i=0;
    while(pl != NULL){
        int premiere_borne = *((int*) depiler(&pl));
        while(i < premiere_borne){
            enfiler(Nr(), f);
            i++;
        }
        enfiler(Bc(), f);
        i++;
    }

    while(i < p){
        enfiler(Nr(), f);
        i++;
    }

    image racine;
    while(!fileVide(f)){
        racine = defiler(f);
        if(!fileVide(f)){
            image im1 = defiler(f);
            image im2 = defiler(f);
            image im3 = defiler(f);
            enfiler(Qt(racine, im1, im2, im3), f);
        }
    }
    free_t(tree);
    libererFile(f);
    return racine;
}

void main() {
    image img;
    // test affichage PrintI, PrintPf
    if(false){
        printf("test de l'affichage simple : \n\n");

        img = Bc();
        printf("Doit afficher b : "); PrintI(img);FreeImage(img);
        img = Nr();
        printf("Doit afficher N : "); PrintI(img);FreeImage(img);
        img = Qt(Bc(), Nr(), Bc(), Nr());
        printf("Doit afficher +bNbN : "); PrintI(img);FreeImage(img);
        img = Qt(Qt(Bc(), Nr(), Bc(), Nr()), Nr(), Bc(), Nr());
        printf("Doit afficher ++bNbNNbN : "); PrintI(img);FreeImage(img);

        printf("test de l'affichage en profondeur : \n\n");

        img = Bc();
        printf("Doit afficher b0 : "); PrintPf(img);FreeImage(img);
        img = Nr();
        printf("Doit afficher N0 : "); PrintPf(img);FreeImage(img);
        img = Qt(Bc(), Nr(), Bc(), Nr());
        printf("Doit afficher +0b1N1b1N1 : "); PrintPf(img);FreeImage(img);
        img = Qt(Qt(Bc(), Nr(), Bc(), Nr()), Nr(), Bc(), Nr());
        printf("Doit afficher +0+1b2N2b2N2N1b1N1 : "); PrintPf(img);FreeImage(img);
    }
    // Lecture
    if(false){

        printf("\nTest de la fonction de lecture (Accepte que des entrees valides (vous pouvez utiliser les parentheses)) \n\n");
        char c;
        do{
            img = LireI();
            printf("Mode simple : \n");
            PrintI(img);
            printf("mode profondeur \n");
            PrintPf(img);

            FreeImage(img);

            printf("q : quitter, entrer : continuer \n");
            scanf("%c",&c);

        }while(c!='q');


    }
    // test de noire et blanc
    if (false){
        printf("\n entrez des images quelconque, noir, blanches, pour tester la fonction Noir() et Blanc() \n\n");
        printf("Appuyer sur q pour quitter la boucle de saisie : \n");
        char c;
        do{
            img = LireI();
            bool bN = Noir(img);
            bool bB = Blanc(img);
            FreeImage(img);

            if(bN && bB){
                printf("Probleme avec les fonctions \n");
            }else if(bN){
                printf("image Noire \n");
            }else if(bB){
                printf("image blanche \n");
            }else{
                printf("image en noir et blanc \n");
            }

            printf("q : quitter, entrer : continuer \n");
            scanf("%c",&c);

        }while(c!='q');
    }
    // On test printPix et damier en même temps
    if (false){
        for (int i = 0; i<6; i++){
            printf("Affichge de damier de profondeur %d avec PrintPix avec k = %d \n\n",i,i);
            img = Damier(i);
            PrintPix(img,i);
            FreeImage(img);
        }
    }
    // test demitour
    if(false){
        printf("Test de Demitour : Avec : ++bNNb+bbbN+NNbbN, On doit avoir : +N+bbNN+Nbbb+bNNb, Essaye : \n\n");

        img = LireI();
        PrintI(DemiTour(img));

        printf("\nUne image doit etre egale aux resultat si on lui applique deux fois demi Tour : \n");
        printf("image == DemiTour(Demitour(image)) : %d (1 pour vrai) \n", ArbresEgaux(img, DemiTour(DemiTour(img))));
        FreeImage(img);

        printf("\nUn damier reste le meme apres un demi tour normalement : \n");

        for (int i = 0; i<6; i++){
            img = Damier(i);
            printf("Damier == DemiTour(Damier) (profondeur %d) : %d \n",i, ArbresEgaux(img, DemiTour(img)));
            FreeImage(img);
        }
    }
    // FreeImage a deja été testé avec les print d'allocation et desallocation qui sont en commentaires

    // test de Simplifie
    if (false){
        printf("\n Test de Simplify \n\n");
        img = Qt(Nr(),Nr(),Nr(),Nr());
        Simplifie(&img);

        printf("pour +NNNN on doit avoir N : "); PrintI(img);
        FreeImage(img);

        img = Qt(Bc(),Bc(),Bc(),Bc());
        Simplifie(&img);
        printf("pour +bbbb on doit avoir b : "); PrintI(img);
        FreeImage(img);

        printf("pour +(+NNNN)(+Nb(+NN(+N(+N(+NNNN)NN)NN)N)b)(+NbN(+NbN(+bbbb)))(+bb(+bbbb)b) on doit avoir +N(+NbNb)(+NbN(+NbNb))b : ");
        printf("Rentrez et verifiez : \n");
        img = LireI();
        Simplifie(&img);
        printf("resultat : ");PrintI(img);

    }

    // test intersectionVide
    if(false){
        printf("\nTeste de intersectionVide : \n\n");
        image img2;
        printf("Rentrez ++bNbN+NbbNN+bbNN : ");
        img = LireI();
        printf("Rentrez +b+bNbbb+bNbN : ");
        img2 = LireI();

        printf("InterSectionVide(++bNbN+NbbNN+bbNN, +b+bNbbb+bNbN) : %d \n", IntersectionVide(img,img2));
        FreeImage(img);
        FreeImage(img2);

        printf("Rentrez une premiere image : ");
        img = LireI();
        printf("Rentrez une deuxieme image : ");
        img2 = LireI();

        printf("InterSectionVide(++bNbN+NbbNN+bbNN, +b+bNbbb+bNbN) : %d \n", IntersectionVide(img,img2));
        FreeImage(img);
        FreeImage(img2);

    }

    // test compteSousArbre
    if(true){
        printf("\n test de CompteSousArbre \n\n" );

        image img2;
        printf("Rentrez +b+bNNbNb en I1 : ");
        img = LireI();
        printf("Rentrez +b+bNNbNb en I2 : ");
        img2 = LireI();

        printf("I1 doit etre sous arbre de I2 1 fois et il l'est : %d \n", CompteSousArbres(img,img2));
        FreeImage(img);
        FreeImage(img2);

        printf("Rentrez +b+bNNbNb en I1 : ");
        img = LireI();
        printf("Rentrez +N(+b(+bNNb)Nb)(+b(+b(+bNNb)Nb)Nb)N en I2 : ");
        img2 = LireI();

        printf("I1 doit etre sous arbre de I2 2 fois et il l'est : %d \n", CompteSousArbres(img,img2));
        FreeImage(img);
        FreeImage(img2);

        printf("Rentrez N en I1 : ");
        img = LireI();
        printf("Rentrez ++NNNN+NNNN+NNNN+NNNN en I2 : ");
        img2 = LireI();

        printf("I1 doit etre sous arbre de I2 16 fois et il l'est : %d \n", CompteSousArbres(img,img2));
        FreeImage(img);
        FreeImage(img2);

        printf("Faites des testes libres : \n");
        char c;
        do{
            printf("Rentrez I1 : ");img = LireI();
            printf("Rentrez I2 : ");img2 = LireI();

            printf("I1 est %d fois sous arbre de I2 \n", CompteSousArbres(img,img2));

            FreeImage(img);
            FreeImage(img2);
            printf("q : quitter, entrer : continuer \n");
            scanf("%c",&c);

        } while(c!='q');


    }
    //test de Alea
    if(false){
        srand(time(NULL));
        printf("\n test de la fnction Alea \n\n");

        printf("Alea(0,0) : ");
        img = Alea(0,0);
        PrintI(img);
        FreeImage(img);

        printf("Alea(0,1) : ");
        img = Alea(0,1);
        PrintI(img);
        FreeImage(img);

        printf("Alea(10,1000) : \n\n");
        img = Alea(10,1000);
        PrintPix(img,6);
        FreeImage(img);
        
        printf("Alea(4,20) : \n");
        img = Alea(4, 20);
        PrintPix(img,6);
        FreeImage(img);


        printf("Alea(1,2)  10 fois \n");
        for(int i=0; i<10; i++){
            img = Alea(1,2);
            PrintI(img);
            FreeImage(img);
        }
        


    }

}
