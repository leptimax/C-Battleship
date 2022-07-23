
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pour pouvoir mettre une pause dans le programme
#include "../Systeme/ansi_windows.h"
#include "../IA/base.h"

/*==============================================================================
   Fonction permettant d'adapter la couleur de la croix dans le quadrillage
==============================================================================*/

int Definition_Couleur(char couleur,Color * couleur_applicable)
{
    switch (couleur)
    {
    case 'R':
        switch(couleur_applicable->touche)
        {
        case 1:
            printf("\x1b[37m");
            break;
        case 2:
            printf("\x1b[31m");
            break;
        case 3:
            printf("\x1b[32m");
            break;
        case 4:
            printf("\x1b[33m");
            break;
        case 5:
            printf("\x1b[34m");
            break;
        case 6:
            printf("\x1b[35m");
            break;
        case 7:
            printf("\x1b[36m");
            break;
        }
        break;
    case 'B':
        switch(couleur_applicable->rate)
        {
        case 1:
            printf("\x1b[37m");
            break;
        case 2:
            printf("\x1b[31m");
            break;
        case 3:
            printf("\x1b[32m");
            break;
        case 4:
            printf("\x1b[33m");
            break;
        case 5:
            printf("\x1b[34m");
            break;
        case 6:
            printf("\x1b[35m");
            break;
        case 7:
            printf("\x1b[36m");
            break;
        }
        break;

    case 'V':
        switch(couleur_applicable->bateau)
        {
        case 1:
            printf("\x1b[37m");
            break;
        case 2:
            printf("\x1b[31m");
            break;
        case 3:
            printf("\x1b[32m");
            break;
        case 4:
            printf("\x1b[33m");
            break;
        case 5:
            printf("\x1b[34m");
            break;
        case 6:
            printf("\x1b[35m");
            break;
        case 7:
            printf("\x1b[36m");
            break;
        }
        break;
    default:
        return 0; //code pour le noir
    }
    return 1;
}

/*==============================================================================
   Fonction permettant l'affichage des 2 terrains de jeux
==============================================================================*/

void affichage(char tableau_joueur[10][10], char tableau_ennemi[10][10],
               char pseudo_joueur[], char pseudo_ennemi[],Color * couleur_applicable)
{
    int couleur = 0; //permettra de définir la couleur du texte

    printf("   | A | B | C | D | E | F | G | H | I | J |"
           "		  | A | B | C | D | E | F | G | H | I | J |\n");
    printf("--------------------------------------------"
           "           --------------------------------------------\n");

    /*==========================================================================
      Affichage des quadrillages
    ==========================================================================*/

    for (int i = 0; i < 10; i++)
    {
//on affiche les numéros de chaque ligne des quadrillages

        if (i == 9)
            printf("%d |", i+1);
        else
            printf(" %d |", i+1);


        for (int j = 0; j < 21; j++)
        {
            if (j == 10)
            {
                if (i != 9)
                    printf("\t\t%d |", i+1);
                else
                    printf("	       %d |", i+1);
            }
// on affiche le contenu de chaque case selon la couleur précisé

            setupConsole();
            if (j < 10)  //pour j < 10 on est dans le tableau possédant les infos du joueur
            {
                couleur = Definition_Couleur(tableau_joueur[i][j],couleur_applicable);
                if (couleur != 0)
                {
                    printf(" %c", 'X');
                    printf("\x1b[0m"); //on recolore le texte avec la couleur par défaut
                    printf(" |");
                }
                else
                    printf(" %c |", tableau_joueur[i][j]); //si couleur = 0 alors la case ne contient pas de X donc on ne change pas la couleur
            }
            if (j > 10)  //pour j>10 on est dans le tableau possédant les infos de l'ennemi
            {
                couleur = Definition_Couleur(tableau_ennemi[i][j-11],couleur_applicable);
                if (couleur != 0)
                {
                    printf(" %c", 'X');
                    printf("\x1b[0m");
                    printf(" |");
                }
                else
                    printf(" %c |", tableau_ennemi[i][j-11]);
            }
            restoreConsole();
        }
        printf("\n"); //on revient à la ligne puis on affiche une ligne de séparation
        printf("--------------------------------------------"
               "	       --------------------------------------------\n");
    }
    printf("\t\t%s", pseudo_joueur); //affichage des pseudos sous les tableaux associés
    printf("    \t\t\t\t\t\t %s\n", pseudo_ennemi);
}

/*================================================================
Systeme d'affichage lors du placement des bateaux
================================================================*/

void affichageInitialisation(char tableau_joueur[10][10], Color * couleur_applicable)
{
    int couleur = 0;

    printf("   | A | B | C | D | E | F | G | H | I | J |\n");
    printf("--------------------------------------------\n");

    for (int i = 0; i < 10; i++)
    {
//on affiche les numéros de chaque ligne des quadrillages

        if (i == 9)
            printf("%d |", i+1);
        else
            printf(" %d |", i+1);


        for (int j = 0; j < 10; j++)
        {
// on affiche le contenu de chaque case selon la couleur précisé

            setupConsole();
            if (j < 10)  //pour j < 10 on est dans le tableau possédant les infos du joueur
            {
                couleur = Definition_Couleur(tableau_joueur[i][j], couleur_applicable);
                if (couleur != 0)
                {
                    printf(" %c", 'X');
                    printf("\x1b[0m"); //on recolore le texte avec la couleur par défaut
                    printf(" |");
                }
                else
                    printf(" %c |", tableau_joueur[i][j]); //si couleur = 0 alors la case ne contient pas de X donc on ne change pas la couleur
            }

            restoreConsole();
        }
        printf("\n"); //on revient à la ligne puis on affiche une ligne de séparation
        printf("--------------------------------------------\n");
    }
    printf("\n");
}

/*================================================================
Fonction permettant d'afficher les textes depuis les .txt
=================================================================*/
void affichage_texte(char * chemin)
{
    int x[100];
    int valeur;
    char y[5];
    int i = 0;
    int j = 0;
    int caractere;
    FILE * tete = fopen(chemin, "r");

//on vérifie que l'ouverture du fichier est faite
	if (tete == NULL)
        printf("HS");
    else
    {

//on récupère l'ensemble des valeur ASCII des différents caractères spéciaux situés en tête du fichier

        valeur = fgetc(tete);
        while(valeur != ';')
        {

            if(j == 3)
            {
                j = 0;
                x[i] = atoi(y);
                i++;
            }
            y[j] = (char) valeur;
            j++;
            valeur = fgetc(tete);
        }
        x[i] = atoi(y);

//on lit et on affiche l'ensemble du fichier en remplaçant les %c par la valeur adaptée

        i = 0;
        caractere = fgetc(tete);
        caractere = fgetc(tete);
        while(caractere != EOF)
        {
            if(caractere == '%')
            {
                caractere = fgetc(tete);
                printf("%c", x[i]);
                i++;
            }
            else
            {
                printf("%c", caractere);
            }
            caractere = fgetc(tete);
        }
    }
    fclose(tete);
}

