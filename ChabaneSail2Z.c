#include <stdio.h>
#include <stdlib.h>

typedef struct Bloc
{
    int valeur ;
    struct Bloc* next;
    struct Bloc** prec;

} Bloc;

typedef Bloc*** ListeZ ;

void empile(int x,ListeZ* ptr_acces){
    Bloc* ptr_block =  (Bloc*) malloc(sizeof(Bloc));
    ptr_block->valeur = x;
    
    if(*ptr_acces != NULL){
        // pas besoin de verifier tout les pointeurs si ils ne sont pas null 
        //c'est nous on fait correctement la construction

        ptr_block->next = ***ptr_acces;
        ptr_block->prec = **ptr_acces;
        // on lie le bloc de ptr_acces avec le nouveau bloc qu'on veut empiler
        (**ptr_acces) = &(ptr_block->next);
        // le next du dernier bloc doit pointer vers le nouveau bloc à empiler
        //***ptr_acces = ptr_block; faux parceque on a modifié **ptr_acces
        *(ptr_block->prec) = ptr_block;
        // finalement on met à jour acces
        *ptr_acces = &(ptr_block->prec);

    }else{
        ptr_block->next = ptr_block;
        ptr_block->prec = &(ptr_block->next);
        (*ptr_acces) = &(ptr_block->prec);
    }


}

void afficheZ (ListeZ L){
    if(L!=NULL){
        // celui là ne va pas changer
        Bloc* ptr_premier_bloc = **L;
        printf("%d ",ptr_premier_bloc->valeur);
        // celui là on va l'utiliser pour le parcours
        Bloc* parcours = ptr_premier_bloc->next;
        
        while(parcours != ptr_premier_bloc){
            printf("%d ",parcours->valeur);
            parcours = parcours->next;
        }
        printf("\n");
    }else{
        printf("NULL\n");
    }
   

}

/*
- petite fonction auxilere pour ZElimine qui retourne si une liste à un seul element ou pas 
- une liste est un singleton si le poniteur prec (*acces) pointe vers le pointeur 
next ((**acces)->next) du même bloc
*/

int est_singelton(ListeZ acces){
    return (acces != NULL && (&((**acces)->next) == *acces));
}

void ZElimine(ListeZ* acces){

    if(*acces != NULL){
        // le bloc à liberer
        Bloc* elimine = ***acces;

        // on doit traiter à part le cas du singleton parceque il nya aucun moyen de faire apparaitre le pointeur 
        // NULL sans l'écrire en dur dans le code
        if(est_singelton(*acces)){
            *acces = NULL;
        }else{
            // le pointeur next du dernier bloc pointe vers celui qui suit le bloc à liberer
            ***acces = elimine->next;
            // le pointeur prec du bloc suivant elimine doit pointer vers le next du dernier bloc
            (elimine->next)->prec = **acces;
            // on actualise acces
            *acces = &((elimine->next)->prec);
        }

        free(elimine);

    }

}

void main(){
    // teste de ZElimine sur NULL
    ListeZ acces = NULL;
    ZElimine(&acces);
    afficheZ(acces);
    
    // on créer la liste pour tester ZElimine dessus
    empile(42,&acces);
    empile(93,&acces);
    empile(17,&acces);
    empile(23,&acces);

    afficheZ(acces);

    ZElimine(&acces);
    afficheZ(acces);

    ZElimine(&acces);
    afficheZ(acces);

    ZElimine(&acces);
    afficheZ(acces);
    
    ZElimine(&acces);
    afficheZ(acces);
    
}

