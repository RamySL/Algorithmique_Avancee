#include <stdio.h>
#include <stdlib.h>
#include "conio.c"
#include "ChabaneSail1.c"
#include "ChabaneSail2.c"


int pointer(int x, int y, int Nb, char tabch[][70], int color1,  int color2, int color3, int color4)
{
    //Fonction d'affichage des listes  de d�cisions
     int z = 0, y1 = y;
     int key;
     do
     {
         gotoxy(x, y);
         textcolor(color4);
         printf(">");
         textcolor(color1);
         printf("   %s", tabch[z]);
         key = getch();
         gotoxy(x, y);
         printf(" ");
         textcolor(color3);
         printf("%c", tabch[z][0]);textcolor(color2);printf("%s   ",tabch[z] + 1);
         if(key == 72){
            y--;
            z--;
            if(y < y1){
                y = y1 + Nb - 1;
                z = Nb - 1;
            }
         }
         else if(key == 80){
            y++;
            z++;
            if(y >= y1 + Nb){
                y = y1;
                z = 0;
            }
         }
     }
     while(key != 27 && key != 13);
     if(key == 13)
        return z;
    else
        return -1;
}

int main(int argc, char** argv){
int stop = 0;
    while (!stop){
        clrscr();
        char lines[3][70] = {"  > Algo1", "  > Algo2", "  > Quitter"};
        int x, y;
        x = wherex();
        y = wherey();
        printf("  > Algo1\n");
        printf("  > Algo2\n");
        printf("  > Quitter\n");
        int choice = pointer(x, y, 3, lines, 10, 15, 14, 9);
        switch (choice)
        {
            case 0:
            {
            char lines2[14][70] = {
                "  > Afficher e (float).",
                "  > Afficher e (double).",
                "  > Afficher yn (float).",
                "  > Afficher yn (double).",
                "  > Afficher l'ecart zn yn.",
                "  > Afficher X1(100).",
                "  > Afficher X2(100).",
                "  > Afficher X3(100).",
                "  > Afficher X4(100).",
                "  > Afficher X(10 ^ k) pour k de 1 à 9.",
                "  > Afficher X1 (long, long double).",
                "  > Afficher BadCpn de 0 a 30.",
                "  > Afficher GoodCpn de 0 a 30.",
                "  > Quitter."
            };

            // Display the list
            printf("\n\t"); int x = wherex(); int y = wherey();
            printf("  > Afficher e (float).\n");
            printf("  \t> Afficher e (double).\n");
            printf("  \t> Afficher yn (float).\n");
            printf("  \t> Afficher yn (double).\n");
            printf("  \t> Afficher l'ecart zn yn.\n");
            printf("  \t> Afficher X1(100).\n");
            printf("  \t> Afficher X2(100).\n");
            printf("  \t> Afficher X3(100).\n");
            printf("  \t> Afficher X4(100).\n");
            printf("  \t> Afficher X(10 ^ k) pour k de 1 à 9.\n");
            printf("  \t> Afficher X1 (long, long double).\n");
            printf("  \t> Afficher BadCpn de 0 a 30.\n");
            printf("  \t> Afficher GoodCpn de 0 a 30.\n");
            printf("  \t> Quitter\n");
            printf("  > Algo2\n");
            printf("  > Quitter\n");

            choice = pointer(x - 1, y, 14, lines2, 10, 15, 14, 9);
            clrscr();
            switch (choice)
            {
                case 0:
                        printf(" e = %.20f\n", Efloat() ) ;

                        break;
                case 1:
                        printf(" e = %.30lf \n", Edouble()) ;

                    break;
                    case 2:
                        afficheYfloat(30);
                        break;
                    case 3:
                        afficheYdouble(30);
                        break;
                    case 4:
                        afficheZdouble(30);
                        break;
                    break;
                    case 5:
                        printf("X1(100)= %f", X1(100));
                        break;
                    case 6:
                        printf("X2(100)= %f", X2(100));
                        break;
                    case 7:
                        printf("X3(100)= %f", X3(100));
                        break;
                    case 8:
                        printf("X4(100)= %f", X4(100));
                        break;
                    case 9:
                            // This case attempts to calculate X(10^k) for k from 1 to 9
                        printf("Calcule de X1 pour k de 1 à 9...\n");
                        calcule_X_10_k(X1, 9); // Calculate X1(10^k) for k=1 to 9

                        printf("Calcule de X2 pour k de 1 à 9...\n");
                        calcule_X_10_k(X2, 9); // Calculate X2(10^k) for k=1 to 9

                        printf("Calcule de X3 pour k de 1 à 9...\n");
                        calcule_X_10_k(X3, 9); // Calculate X3(10^k) for k=1 to 9

                        printf("Calcule de X4 pour k de 1 à 9...\n");
                        calcule_X_10_k(X4, 9); // Calculate X4(10^k) for k=1 to 9
                        break;

                    case 10:
                        printf("Non encore prepraree");
                    break;

                    case 11:
                    printf("\nCette fonctino renvoie un type long long.");
                    for(int i=1; i<31; i++) printf("\nBadCpn(%d, %d) = %lld", i, 2*i, BadCpn(i, 2*i));
                    break;

                    case 12:
                    printf("\nCette fonctino renvoie un type long long.");
                    for(int i=1; i<31; i++) printf("\nGoodCpn(%d, %d) = %lld", i, 2*i, GoodCpn(i, 2*i));
                    break;
                    case 13:
                        stop=1;
                        break;
                }
                getch();
                break;
            }
            case 1:
            {
                char lines2[7][70] = {
                    "  > DeuxEgalX",
                    "  > ContientZero",
                    "  > SousEnsemble",
                    "  > SommeAvantKieme0",
                    "  > SommeApresRetroKieme0",
                    "  > TueDoublons",
                    "  > Quitter"};
                printf("\n\t");x=wherex();y=wherey();printf("  > DeuxEgalX\n");
                printf("  \t> ContientZero\n");
                printf("  \t> SousEnsemble\n");
                printf("  \t> SommeAvantKieme0\n");
                printf("  \t> SommeApresRetroKieme0\n");
                printf("  \t> TueDoublons\n");
                printf("  \t> Quitter\n");
                printf("  > Quitter\n");
                choice = pointer(x - 1, y, 7, lines2, 10, 15, 14, 9);
                clrscr();
                switch (choice) {
                    case 0:
                        {
                            int nbr;
                            printf("\nSignature bool DeuxEgalX(Liste l, int x)");
                            printf("\nSaisissez x: ");
                            scanf("%d", &nbr);
                            printf("\nSaisissez la liste: \n");
                            Liste l = createlist();
                            affiche_iter(l);
                            printf("Resultat %d\n", DeuxEgalX(l, nbr));
                            getch();
                            break;
                        }


                    case 1:
                        printf("Signature: bool ContientZero(Liste l)\n");
                        Liste l1 = createlist();
                        affiche_iter(l1);
                        printf("ContientZero (rec): %d\n", ContientZero_rec(l1));
                        printf("ContientZero (iter): %d\n", ContientZero_iter(l1));
                        getch();
                        break;

                    case 2:
                        printf("Vous avez choisi: SousEnsemble\n");
                        printf("\nListe l1:");
                        Liste l2 = createlist();
                        affiche_iter(l2);
                        printf("\nListe l2:");
                        Liste l3 = createlist();
                        affiche_iter(l3);
                        printf("\nSousEnsemble: %d\n", sousEnsemble(l2, l3));
                        getch();
                        break;

                    case 3:
                        printf("Vous avez choisi: SommeAvantKieme0\n");
                        Liste l4 = createlist();
                        affiche_iter(l4);
                        int k;
                        printf("Saisissez la valeur de k: ");
                        scanf("%d", &k);
                        printf("SommeAvantKieme0 (rec non terminale): %d\n", SommeAvantKieme0_rec_non_terminal(l4, k));
                        printf("SommeAvantKieme0 (iter): %d\n", SommeAvantKieme0_iter(l4, k));
                        printf("SommeAvantKieme0 (sous_fonction): %d\n", SommeAvantKieme0_rec_terminal_sous_fonction(l4, k));
                        printf("SommeAvantKieme0 (sous-procedure): %d\n", SommeAvantKieme0_rec_terminal_sous_procedure(l4, k));
                        getch();
                        break;

                    case 4:
                        printf("Vous avez choisi: SommeApresRetroKieme0\n");
                        Liste l5 = createlist();
                        affiche_iter(l5);
                        printf("Saisissez la valeur de k: ");
                        scanf("%d", &k);
                        printf("SommeApresRetroKieme0: %d\n", sommeApresRetroKieme0(l5, k));
                        getch();
                        break;

                    case 5:
                        printf("Vous avez choisi: TueDoublons\n");
                        Liste l6 = createlist();
                        affiche_iter(l6);
                        printf("TueDoublons1 (rec):\n");
                        TueDoublons1(&l6);
                        affiche_iter(l6);
                        printf("TueDoublons2 (iter):\n");
                        TueDoublons2_iter(&l6);
                        affiche_iter(l6);
                         printf("TueDoublons2 (rec):\n");
                        TueDoublons2_rec(&l6);
                        affiche_iter(l6);
                        getch();
                        break;

                    case 6:
                        printf("Quitter\n");
                        stop = 1;
                        break;

                    default:
                        printf("Choix invalide!\n");
                        break;
                }
                break;
            }

            case 2:
                stop = 1;
                break;
        }
    }
    return 0;
}
