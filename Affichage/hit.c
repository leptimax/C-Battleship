
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../IA/base.h"
#include "../Save/save.h"
#include "fonction_affichage.h"
#include "menu_pause.h"
#include "placement.h"
#include "hit.h"


#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64
#include <conio.h>
#else
#include "../Systeme/khbit.h"
#endif
/*=======================================================================
Fonction permettant de g�rer les coordonn�es en x avec timer
========================================================================*/

Sortie_coordonnee * CoordonneeX_jeu(char * chemin, int compteur)
{
    int compteur_test = 0;
    Sortie_coordonnee * sortie = malloc(sizeof(Sortie_coordonnee));

    char input[100] = { ' ' };
    char x = 0;

    char colonne[100] = { "" };
    char hors_tableau[100] = { "" };

    strcpy(colonne,chemin);
    strcpy(hors_tableau,chemin);

    strcat(colonne, "colonne.txt");
    strcat(hors_tableau, "hors_tableau.txt");

    while (1)
    {
        affichage_texte(colonne);

        int test1 = 0;
        while(!test1)
        {
            test1 = kbhit();//on attend que le joueur rentre une touche
            compteur_test ++;
            if (compteur_test == compteur)
            {
                sortie->x = -1;
                sortie->compteur = compteur_test;
                return sortie;
            }

        }

        fgets(input, 100, stdin);
        x = input[0];

        if (x >= 65 && x <= 74)
            x = x-64;
        else
        {
            if (x >= 97 && x <= 106)
                x = x-96;
            else
            {
                if (x == 80 || x == 81 || x == 112 || x == 113)
                {
                    sortie->x = x;
                    sortie->compteur = compteur_test;
                    return sortie;
                }
                else
                    x = 0;
            }
        }

        if ((x >= 11) || (x <= 0))      //On verifie que la valeur entree ne soit pas hors tableau
        {
            affichage_texte(hors_tableau);
        }
        else
        {
            sortie->x = x;
            sortie->compteur = compteur_test;
            return sortie;
        }
    }
}

/*=======================================================
Fonction g�rant les coordonn�es en y avec timer
========================================================*/

int CoordonneeY_jeu(char * chemin, int compteur, int compteur_test)       //Creation de la coordonnee y choisit par le joueur
{
    char input[100] = { ' ' };
    char temp[10] = { ' ' };

    char y = 0;

    char ligne[100] = { "" };
    char hors_tableau[100] = { "" };

    strcpy(ligne, chemin);
    strcpy(hors_tableau, chemin);

    strcat(ligne, "ligne.txt");
    strcat(hors_tableau, "hors_tableau.txt");


    while (1)
    {
        affichage_texte(ligne);

        int test1 = 0;
        while(!test1)
        {
            test1 = kbhit();
            compteur_test ++;
            if (compteur_test == compteur)
                return -1;

        }

        fgets(input, 100, stdin);
        temp[0] = input[0];
        temp[1] = input[1];

        if (input[0] == 'p' || input[0] == 'P' || input[0] == 'q' || input[0] == 'Q')
            return input[0];

        else
            y = atoi(temp);

        if ((y >= 11) || (y <= 0))      //On v�rifie que la valeur entree ne soit pas hors tableau
        {
            affichage_texte(hors_tableau);
        }
        else
        {
            return y;
        }
    }
}


/*=============================================================
Fonction permettant de g�rer l'int�gralit� du tir du joueur
==============================================================*/

Menu_temp * Tir(Coordonnees * liste, char tableau_joueur[10][10],
                char tableau_ennemi[10][10], char pseudo_joueur[],
                char pseudo_ennemi[], char * chemin, Color * couleur_applicable,
                char * chemin_profil, int langue, Save * donnee_save, int temps_ref, int compteur)
{
    Menu_temp * out = malloc(sizeof(Menu_temp));
    char chemin_pause[100] = { "" };
    char temps_ecoule[100] = { "" };
    char pillone[100] = { "" };


    strcpy(chemin_pause,chemin);
    strcpy(temps_ecoule, chemin);
    strcpy(pillone, chemin);

    strcat(chemin_pause, "pause.txt");
    strcat(temps_ecoule, "temps_ecoule.txt");
    strcat(pillone, "case_pillone.txt");

    Sortie_coordonnee * coord_x = NULL;
//#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64
    int compteur_test = 0;
//#endif

    int temps_save = clock();
    temps_save = (temps_save - temps_ref);

    int verif = 1;
    int pause = 0;
    int x, y;
    while (verif == 1)
    {
        pause = 0;
        coord_x = CoordonneeX_jeu(chemin, compteur);
//#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64
        compteur_test = coord_x->compteur;
//#endif
        x = coord_x->x;

        if(x == -1)//si x = -1 on fait sauter le tour du joueur
        {
            cls();
            affichage_texte(temps_ecoule);
            sleep(2);
            cls();
            out->x[0] = 11;
            out->y[0] = 11;//permet de ne pas poser de pb lors du replay car les coordonn�es sont hors tableau
            out->couleur = couleur_applicable;
            return out;
        }
        while ((x == 80 || x == 112))//si le joueur demande la pause on envoie la pause
        {
            pause = 1;
            cls();
            couleur_applicable = Menu_Pause(chemin, chemin_profil, langue, couleur_applicable, donnee_save, temps_save);
            cls();
            affichage_texte(chemin_pause);
            affichage(tableau_joueur, tableau_ennemi, pseudo_joueur,
                      pseudo_ennemi, couleur_applicable);
	    coord_x = CoordonneeX_jeu(chemin, compteur_test);
   	    compteur_test = coord_x->compteur;
	    x = coord_x->x;

        }
        if ((x == 81 || x == 113))
        {
            cls();
            exit(0);
        }

        y = CoordonneeY_jeu(chemin, compteur, compteur_test);

        if(y == -1)//meme processus que pour x
        {
            cls();
            affichage_texte(temps_ecoule);
            sleep(2);
            cls();
            out->x[0] = -1;
            out->y[0] = -1;
            out->couleur = couleur_applicable;
            return out;
        }

        while ((y == 80 || y == 112))
        {
            pause = 1;
            cls();
            couleur_applicable = Menu_Pause(chemin, chemin_profil, langue, couleur_applicable, donnee_save, temps_save);
            cls();
            affichage_texte(chemin_pause);
            affichage(tableau_joueur, tableau_ennemi, pseudo_joueur,
                      pseudo_ennemi, couleur_applicable);
	    y = CoordonneeY_jeu(chemin, compteur, compteur_test);

        }
        if ((y == 81 || y == 113))
        {
            cls();
            exit(0);
        }
        if (pause == 0)
        {
            verif = verification(liste, x, y);
            if (verif == 1)
            {
                cls();
                affichage_texte(pillone);
                sleep(1);
                cls();
                affichage(tableau_joueur, tableau_ennemi, pseudo_joueur,
                          pseudo_ennemi, couleur_applicable);
            }
        }
    }
    out->x[0] = x;
    out->y[0] = y;
    out->couleur = couleur_applicable;
    return out;
}

/*================================================================================
Fonction permettant de v�rifier si les coordonn�es sont pr�sentes dans une liste
=================================================================================*/

int verification(Coordonnees * liste, int x, int y)
{
    if (liste == NULL)
        return 0;
    else
    {
        Coordonnees * p = liste;
        while (p != NULL)
        {
            if (p->x == x && p->y == y)
                return 1;
            else
                p = p->suivant;
        }
        return 0;
    }
}

/*================================================================
Fonction permettant de v�rifier si les coord de tir touche
=================================================================*/

int toucherTir(Coordonnees *liste, int x, int y, char * chemin)
{
    Coordonnees *p = NULL;
    p = liste;
    char rate[100] = { "" };
    char touche[100] = { "" };

    strcpy(rate, chemin);
    strcpy(touche, chemin);

    strcat(rate, "rate.txt");
    strcat(touche, "touche.txt");

    while (p != NULL)
    {
        if ((x-1 == p->x) && (y-1 == p->y))
        {
            affichage_texte(touche);
            sleep(1);
            cls();
            return 1;
        }
        else
            p = p->suivant;
    }
    affichage_texte(rate);
    sleep(1);
    cls();
    return 0;
}
