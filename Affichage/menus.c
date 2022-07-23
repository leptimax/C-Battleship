#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../IA/base.h"
#include "../Systeme/clean.h"
#include "menus.h"
#include "fonction_affichage.h"


/*==============================================================================
   Fonction permettant d'afficher les différents menus
==============================================================================*/

Menu_temp * menu(char * chemin)
{
    Menu_temp * temp = malloc(sizeof(Menu_temp));
    char x1[100] = { ' ' };
    char y1[100] = { ' ' };
    int x, y;
    int verif = 1;
    int verif2 = 1;

    char chemin_principal[100] = { "" };
    char chemin_jouer[100] = { "" };
    char chemin_option[100] = { "" };
    char chemin_erreur[100] = { "" };

    strcpy(chemin_principal, chemin);
    strcpy(chemin_jouer, chemin);
    strcpy(chemin_option, chemin);
    strcpy(chemin_erreur, chemin);

    strcat(chemin_principal, "menu_principal.txt");
    strcat(chemin_jouer, "menu_jouer.txt");
    strcat(chemin_option, "menu_options.txt");
    strcat(chemin_erreur, "erreur.txt");
    while (verif)
    {
        affichage_texte(chemin_principal);
        fgets(x1, 100, stdin);
        x = atoi(x1);


        switch (x)
        {
        case 1:                                 //Affichage du menu "Jouer"
            cls();
            affichage_texte(chemin_jouer);
            fgets(y1, 100, stdin);
            y = atoi(y1);

            switch (y)
            {
            case 4:
                cls();
                break;
            default:
                verif = 0;
                break;                         //Retour au menu principal
            }
            break;

        case 2:                                 //Affichage des statistique
            cls();
            verif = 0;
            break;

        case 3:
            while(verif2) //Affichage des options
            {
                cls();
                affichage_texte(chemin_option);
                fgets(y1, 100, stdin);
                y = atoi(y1);
                switch (y)
                {
                case 1:
                    verif = 0;
                    verif2 = 0;
                    break;
                case 2:
                    verif = 0;
                    verif2 = 0;
                    break;
                case 3:
                    cls();
                    verif = 0;
                    verif2 = 0;
                    break;
                default :
                    cls();
                    affichage_texte(chemin_erreur);
                    sleep(1);
                    cls();
                }

            }

            break;

        case 4:
            verif = 0;
            break;

        case 5:
            verif = 0;
            break;

        case 6 :
            verif = 0;
            break;

        case 7 :                                  //Fermeture du programme
            cls();
            exit(EXIT_SUCCESS);
            break;
        /*case 300999 : reserver à l'easter egg en developpement
            verif = 0;
            break;*/
        default:     //Réiteration du menu "Principal" en cas d'erreur du joueur
            cls();
            affichage_texte(chemin_erreur);
            break;
        }
    }

    temp->x[0] = x;
    temp->y[0] = y;
    return temp;
}


