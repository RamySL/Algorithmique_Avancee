#include <stdio.h>
#include <stdlib.h>
#include "TP_ALGO.h"

//=========== Fonctions pour g�rer la pile ===========
void push(int e, list* l){
    list newB = (list) malloc(sizeof(struct block));
    newB->val=e;
    newB->next = *l;
    *l=newB;
}

int pop(list* l){
    list tmp = *l;
    *l = (*l)->next;
    int ret = tmp->val;
    free(tmp);
    return ret;
}
//===================================================

int DeuxEgalX(list L, int x){
    // Renvoie un entier non nul si x est �gal au deuxi�me �l�ment de la liste, ou 0 si cet �l�ment n'existe pas.
    if(L==NULL || L->suiv == NULL) return x==0;
    return x==L->next->val;
}

void testDeuxEgalX(){

}

int sousEnsemble(list l1, list l2){
    while(l1 != NULL && l2 != NULL){
        // On avance dans l1 uniquement si l'�l�ment en t�te de l1 correspond � l'�l�ment courant de l2.
        if(l1->val == l2->val) l1 = l1->next;

        // Dans tous les cas, on avance dans l2.
        l2 = l2->next;
    }

    // Si nous avons pu parcourir l1 jusqu'� la fin, alors nous sommes certains que toutes ses valeurs existent dans l2.
    // Cela fonctionne m�me si l1 est vide initialement, car une liste vide est incluse dans toutes les listes, y compris dans la liste vide elle-m�me.
    return l1==NULL;

}

int sommeApresRetroKieme0(list l, int k){
    list pile=NULL;
    int sum=0;
    while(l != NULL){
        if(l->val==0){
            if(sum==0)  k--;
            else {
                push(sum, &pile);
                sum=0;
            }
        } else sum+=l->val;
        l=l->next;
    }
    if(sum!=0) {
        push(sum, &pile);
        sum=0;
    } else k--;
    while(pile != NULL && k>0){
        sum+=pop(&pile);
        k--;
    }
    return sum;
}

int main(int argc, char** argv){

    return 0;
}
