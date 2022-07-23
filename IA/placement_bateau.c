
#include <stddef.h>
#include <stdlib.h>
#include "base.h"
#include "placement_bateau.h"

/*==============================================
Fonction gérant l'insertion des bateaux de l'IA
===============================================*/

Coordonnees * insertion_bateau_IA(Coordonnees * emplacement_bateau_IA,
                                  int debut, int fin, int sens, int coord_2)
{
    while (fin != debut-1) //on boucle jusqu'à ce que toutes les cases du bateau ait été implémenter
    {
        if (sens == 0) //sens horizontal
            emplacement_bateau_IA = insertionEnTete(emplacement_bateau_IA, fin,
                                                    coord_2);

        else
            emplacement_bateau_IA = insertionEnTete(emplacement_bateau_IA,
                                                    coord_2, fin);

        fin--;
    }
    return emplacement_bateau_IA;
}

/*========================================================
Fonction gérant les cases de placement impossible
=========================================================*/

Coordonnees * ajout_case_impossible(Coordonnees * cases_impossible, int debut,
                                    int fin, int sens, int coord_2)
{
    int compteur = 0;

    while (debut != fin+1)
    {
        if (sens == 1)
        {
            if (compteur == 0)//on est sur la première case du bateau
            {
                cases_impossible = insertionEnTete(cases_impossible, coord_2,
                                                   debut-1);
                cases_impossible = insertionEnTete(cases_impossible, coord_2-1,
                                                   debut);
                cases_impossible = insertionEnTete(cases_impossible, coord_2+1,
                                                   debut);
            }
            if (debut == fin)
            {
                cases_impossible = insertionEnTete(cases_impossible, coord_2,
                                                   debut+1);
                cases_impossible = insertionEnTete(cases_impossible, coord_2-1,
                                                   debut);
                cases_impossible = insertionEnTete(cases_impossible, coord_2+1,
                                                   debut);
            }
            else
            {
                cases_impossible = insertionEnTete(cases_impossible, coord_2-1,
                                                   debut);
                cases_impossible = insertionEnTete(cases_impossible, coord_2+1,
                                                   debut);
            }
        }
        else
        {
            if (compteur == 0)//on est sur la première case du bateau
            {
                cases_impossible = insertionEnTete(cases_impossible, debut-1,
                                                   coord_2);
                cases_impossible = insertionEnTete(cases_impossible, debut,
                                                   coord_2-1);
                cases_impossible = insertionEnTete(cases_impossible, debut,
                                                   coord_2+1);
            }
            if (debut == fin)
            {
                cases_impossible = insertionEnTete(cases_impossible, debut+1,
                                                   coord_2);
                cases_impossible = insertionEnTete(cases_impossible, debut,
                                                   coord_2-1);
                cases_impossible = insertionEnTete(cases_impossible, debut,
                                                   coord_2+1);
            }
            else
            {
                cases_impossible = insertionEnTete(cases_impossible, debut,
                                                   coord_2-1);
                cases_impossible = insertionEnTete(cases_impossible, debut,
                                                   coord_2+1);
            }
        }
        compteur++;
        debut++;
    }

    return cases_impossible;
}

/*==============================================================================
   On définit la fonction qui gère la collision des bateau de l'IA
==============================================================================*/

int test_collision(Coordonnees * emplacement_bateau_IA, int debut, int fin,
                   int sens, int coord_2)
{
    Coordonnees * pointeur = NULL; //sert d'intermédiaire dans les boucles

    if (emplacement_bateau_IA != NULL)
    {
//Pour chaque case du bateau, il vérifie qu'elle n'est pas déjà occupée par un autre bateau

        while (debut != fin+1)
        {
            pointeur = emplacement_bateau_IA;
            if (sens == 0) //si le bateau est placé horizontalement
            {
                while (pointeur != NULL)
                {
                    if ((pointeur->x == debut) && (pointeur->y == coord_2))
                        return 0;
                    else
                        pointeur = pointeur->suivant;
                }
            }
            else //si le bateau est placé verticalement
            {
                while (pointeur != NULL)
                {
                    if ((pointeur->y == debut) && (pointeur->x == coord_2))
                        return 0;
                    else
                        pointeur = pointeur->suivant;
                }
            }
            debut++;
        }
        return 1;
    }
//si la liste de bateau est vide
    else
        return 1;
}

/*==============================================================================
   On définit la fonction qui donne les coordonnées des bateaux de l'IA
==============================================================================*/

Sortie * placement_bateau_IA(Coordonnees * emplacement_bateau_IA,
                             Coordonnees * cases_impossible)
{
    int nb_bateau = 0;
    int x_fin;
    int y_fin;
    int debut;
    int end;
    int x;
    int y;
    int coord_2;    //coordonnee invariante pour le placement du bateau selon le sens de placement
    int sens;     //horizontal ou vertical
    int verif = 0;
    int verif2 = 0;

    Sortie * out = malloc(sizeof(Sortie));
    out->bateau_complet = malloc(sizeof(Joueur));

    Coordonnees * PA = NULL;
    Coordonnees * C = NULL;
    Coordonnees * SM = NULL;
    Coordonnees * CT = NULL;
    Coordonnees * T = NULL;



//tant que l'on a pas les 5 bateaux, on tire des coordonnees de bateau

    while (nb_bateau != 5)
    {
        verif = 0;
        verif2 = 0;
        x = ((rand()%99)/10);
        y = ((rand()%99)/10);
        sens = rand()%2; //on définit aléatoirement le sens du bateau


        switch (nb_bateau) //on fait un cas par bateau en allant du plus long au plus court
        {
        case 0:
        {
            if (sens == 0) //sens horizontal
            {
                x_fin = x+4;

                if (x_fin <= 0 || x_fin >= 10) //on s'assure que la coordonnees de fin est bien dans le tableaux
                    x_fin = x-4;
            }
            else
            {
                y_fin = y+4;

                if (y_fin <= 0 || y_fin >= 10)
                    y_fin = y-4;
            }
            break;
        }

        case 1:
        {
            if (sens == 0)
            {
                x_fin = x+3;

                if (x_fin <= 0 || x_fin >= 10)
                    x_fin = x-3;
            }
            else
            {
                y_fin = y+3;

                if (y_fin <= 0 || y_fin >= 10)
                    y_fin = y-3;
            }
            break;
        }

        case 2:
        {
            if (sens == 0)
            {
                x_fin = x+2;

                if (x_fin <= 0 || x_fin >= 10)
                    x_fin = x-2;
            }
            else
            {
                y_fin = y+2;

                if (y_fin <= 0 || y_fin >= 10)
                    y_fin = y-2;
            }
            break;
        }

        case 3:
        {
            if (sens == 0)     //sens horizontal
            {
                x_fin = x+2;

                if (x_fin <= 0 || x_fin >= 10)
                    x_fin = x-2;
            }
            else
            {
                y_fin = y+2;

                if (y_fin <= 0 || y_fin >= 10)
                    y_fin = y-2;
            }
            break;
        }
        case 4:
        {
            if (sens == 0)     //sens horizontal
            {
                x_fin = x+1;

                if (x_fin <= 0 || x_fin >= 10)
                    x_fin = x-1;
            }
            else
            {
                y_fin = y+1;

                if (y_fin <= 0 || y_fin >= 10)
                    y_fin = y-1;
            }
            break;
        }
        }

//on définit le début et la fin de chaque bateau afin d'ajouter toutes leurs
//coordonnees dans la liste emplacement_bateau_IA

        if (sens == 0)
        {
            coord_2 = y;

            if (x < x_fin)
            {
                debut = x;
                end = x_fin;
            }
            else
            {
                debut = x_fin;
                end = x;
            }
        }
        else
        {
            coord_2 = x;

            if (y < y_fin)
            {
                debut = y;
                end = y_fin;
            }
            else
            {
                debut = y_fin;
                end = y;
            }
        }

// On vérifie que le bateau définie n'entre pas en collision avec un autre

        verif = test_collision(emplacement_bateau_IA, debut, end, sens,
                               coord_2);
        verif2 = test_collision(cases_impossible, debut, end, sens, coord_2);

        if (verif == 1 && verif2 == 1)
        {
            emplacement_bateau_IA = insertion_bateau_IA(emplacement_bateau_IA,
                                                        debut, end, sens,
                                                        coord_2);
            cases_impossible = ajout_case_impossible(cases_impossible, debut,
                                                     end, sens, coord_2);

            switch(nb_bateau)
            {
            case 0:
                PA = insertion_bateau_IA(PA, debut, end, sens, coord_2);
                break;
            case 1:
                C = insertion_bateau_IA(C, debut, end, sens, coord_2);
                break;
            case 2:
                SM = insertion_bateau_IA(SM, debut, end, sens, coord_2);
                break;
            case 3:
                CT = insertion_bateau_IA(CT, debut, end, sens, coord_2);
                break;
            case 4:
                T = insertion_bateau_IA(T, debut, end, sens, coord_2);
                break;

            }
            nb_bateau++;
        }
    }

    out->coord = emplacement_bateau_IA;
    out->cases_restantes = cases_impossible;

    out->bateau_complet->PA = PA;
    out->bateau_complet->C = C;
    out->bateau_complet->SM = SM;
    out->bateau_complet->CT = CT;
    out->bateau_complet->T = T;


    return out;
}
