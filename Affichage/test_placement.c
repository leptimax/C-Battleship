
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../IA/base.h"
#include "placement.h"
#include "test_placement.h"
#include "fonction_affichage.h"


/*==============================================================================
   On définit la fonction permettant de regrouper plusieurs liste en 1
==============================================================================*/

Coordonnees * defEmplacement(Coordonnees * liste, Coordonnees * emplacement)
{
    Coordonnees * p = liste;

    while (p != NULL)
    {
        emplacement = insertionEnTete(emplacement, p->x, p->y);
        p = p->suivant;
    }
    return emplacement;
}

/*==============================================================================
   On définit la fonction qui gère les collisions des bateaux du joueur
==============================================================================*/

int collision(Coordonnees * place_dispo, int x, int y, int fin, int sens)
{
    Coordonnees * pointeur = NULL;
    int debut;
    if (place_dispo != NULL)
    {
//on redéfinit les coordonnées selon le sens du bateau

        switch (sens)
        {
        case -2:
        {
            debut = x;
            break;
        }

        case -1:
        {
            debut = fin;
            fin = x;
            break;
        }
        case 1:
        {
            debut = y;
            break;
        }
        case 2:
        {
            debut = fin;
            fin = y;
            break;
        }
        }

//on vérifie que la coordonnées choisis par le joueur n'est pas déjà prise

        while (debut != fin+1)
        {
            if (sens == -2 || sens == -1)
            {
                pointeur = place_dispo;
                while (pointeur != NULL)
                {
                    if (pointeur->x == debut-1 && pointeur->y == y-1)     //si les coordonnées sont occupés, on l'indique
                        return 0;
                    else
                        pointeur = pointeur->suivant;
                }
            }
            else
            {
                pointeur = place_dispo;
                while (pointeur != NULL)
                {
                    if (pointeur->x == x-1 && pointeur->y == debut-1)
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
    {
        return 1;
    }
}

/*==============================================================================
   On définit la fonction qui affiche les choix possible en coordonnées de fin
==============================================================================*/

Choix * affichageChoix(int xplus, int xmoin, int yplus, int ymoin, int verifxp,
                       int verifxm, int verifyp, int verifym, int x, int y, char * chemin)
{
    Choix * out = malloc(sizeof(Choix));

    char choix_coord[100] = { "" };

    strcpy(choix_coord,chemin);

    strcat(choix_coord, "choix_coord.txt");

    affichage_texte(choix_coord);

    /*Test les coordonnees possibles pour le joueur avant de les proposer*/
    if ((xplus > 0) && (xplus < 11) && (verifxp == 1))
        printf("(%c,%d)  (1)\n", xplus+64, y);
    else
        xplus = 100;
    if ((xmoin > 0) && (xmoin < 11) && (verifxm == 1))
        printf("(%c,%d)  (2)\n", xmoin+64, y);
    else
        xmoin = 100;
    if ((yplus > 0) && (yplus < 11) && (verifyp == 1))
        printf("(%c,%d)  (3)\n", x+64, yplus);
    else
        yplus = 100;
    if ((ymoin > 0) && (ymoin < 11) && (verifym == 1))
        printf("(%c,%d)  (4)\n", x+64, ymoin);
    else
        ymoin = 100;

    out->xplus = xplus;
    out->xmoin = xmoin;
    out->yplus = yplus;
    out->ymoin = ymoin;

    return out;
}

/*==============================================================================
   On définit la fonction qui ajoute les coordonnées bloqué par les bateaux du
   joueur
==============================================================================*/

Ensemble * ajoutCaseBateau(Coordonnees * place_dispo, Coordonnees * liste_coord,
                           int x, int y, int k, int choix)
{
    Ensemble * out = malloc(sizeof(Ensemble));
    switch (choix)
    {
    case 1:
    {
//Ajout des coordonnees du bateau dans les k cases du navire (k étant la taille du navire)
        for (int i = 0; i <= k; i++)
        {
            if (i == 0)
            {
                liste_coord = insertionEnTete(liste_coord, x+i-1, y-1);
                place_dispo = insertionEnTete(place_dispo, x+i-2, y-1);
                place_dispo = insertionEnTete(place_dispo, x+i-1, y-1);
                place_dispo = insertionEnTete(place_dispo, x+i-1, y-2);
                place_dispo = insertionEnTete(place_dispo, x+i-1, y);
            }
            else
            {
                if (i == k)
                    place_dispo = insertionEnTete(place_dispo, x+i-1, y-1);
                else
                {
                    liste_coord = insertionEnTete(liste_coord, x+i-1, y-1);
                    place_dispo = insertionEnTete(place_dispo, x+i-1, y-1);
                    place_dispo = insertionEnTete(place_dispo, x+i-1, y-2);
                    place_dispo = insertionEnTete(place_dispo, x+i-1, y);
                }
            }
        }
        break;
    }
    case 2:
    {
        for (int i = 0; i <= k; i++)
        {
            if (i == 0)
            {
                liste_coord = insertionEnTete(liste_coord, x-i-1, y-1);
                place_dispo = insertionEnTete(place_dispo, x-i-1, y-1);
                place_dispo = insertionEnTete(place_dispo, x-i, y-1);
                place_dispo = insertionEnTete(place_dispo, x-i-1, y-2);
                place_dispo = insertionEnTete(place_dispo, x-i-1, y);
            }
            else
            {
                if (i == k)
                    place_dispo = insertionEnTete(place_dispo, x-i-1, y-1);
                else
                {
                    liste_coord = insertionEnTete(liste_coord, x-i-1, y-1);
                    place_dispo = insertionEnTete(place_dispo, x-i-1, y-1);
                    place_dispo = insertionEnTete(place_dispo, x-i-1, y-2);
                    place_dispo = insertionEnTete(place_dispo, x-i-1, y);
                }
            }
        }
        break;
    }
    case 3:
    {
        for (int i = 0; i <= k; i++)
        {
            if (i == 0)
            {
                liste_coord = insertionEnTete(liste_coord, x-1, y+i-1);
                place_dispo = insertionEnTete(place_dispo, x-1, y+i-1);

                place_dispo = insertionEnTete(place_dispo, x-2, y+i-1);
                place_dispo = insertionEnTete(place_dispo, x, y+i-1);
                place_dispo = insertionEnTete(place_dispo, x-1, y+i-2);
            }
            else
            {
                if (i == k)
                    place_dispo = insertionEnTete(place_dispo, x-1, y+i-1);
                else
                {
                    liste_coord = insertionEnTete(liste_coord, x-1, y+i-1);
                    place_dispo = insertionEnTete(place_dispo, x-1, y+i-1);
                    place_dispo = insertionEnTete(place_dispo, x-2, y+i-1);
                    place_dispo = insertionEnTete(place_dispo, x, y+i-1);
                }
            }
        }
        break;
    }
    case 4:
    {
        for (int i = 0; i <= k; i++)
        {
            if (i == 0)
            {
                liste_coord = insertionEnTete(liste_coord, x-1, y-i-1);
                place_dispo = insertionEnTete(place_dispo, x-1, y-i-1);

                place_dispo = insertionEnTete(place_dispo, x-2, y-i-1);
                place_dispo = insertionEnTete(place_dispo, x, y-i-1);
                place_dispo = insertionEnTete(place_dispo, x-1, y-i);
            }
            else
            {
                if (i == k)
                    place_dispo = insertionEnTete(place_dispo, x-1, y-i-1);
                else
                {
                    liste_coord = insertionEnTete(liste_coord, x-1, y-i-1);
                    place_dispo = insertionEnTete(place_dispo, x-1, y-i-1);
                    place_dispo = insertionEnTete(place_dispo, x-2, y-i-1);
                    place_dispo = insertionEnTete(place_dispo, x, y-i-1);
                }
            }
        }
        break;
    }
    }
    /*printf("bateau : \n");
       afficher(liste_coord);
       printf("\nplace indispo : \n");
       afficher(place_dispo);*/
    out->liste_coord = liste_coord;
    out->place_dispo = place_dispo;
    return out;
}

/*==============================================================================
   On gère la fonction qui permet de choisir les coordonnées
==============================================================================*/

EnsembleC *choix_Coord(int k, EnsembleC * ensemble,char * chemin)
{
    char choix1[100] = { ' ' }; int x, y, taille;
    int choix = -1;
    int xplus = 100;
    int xmoin = 100;
    int yplus = 100;
    int ymoin = 100;

    int verifxp = 0;
    int verifxm = 0;
    int verifyp = 0;
    int verifym = 0;

    int possibilite = 0;

    char annonce[100] = { "" };
    char erreur[100] = { "" };
    char choix_coord_impossible[100] = { "" };

    strcpy(annonce,chemin);
    strcpy(erreur,chemin);
    strcpy(choix_coord_impossible, chemin);

    strcat(annonce, "valeur_choix.txt");
    strcat(erreur, "choix_impossible.txt");
    strcat(choix_coord_impossible, "choix_coord_impossible.txt");

    Coordonnees * liste_coord = NULL;
    Coordonnees * place_dispo = NULL;

    Choix * temp = NULL;

    Ensemble * temp_liste = NULL;

/* on redefini la taille des navires pour ne pas valoir le choix du bateau*/

    if (k > 4)
        taille = k-1;
    if (k == 4 || k == 3)
        taille = 3;
    if (k == 2)
        taille = k;


    while (!verifxp && !verifxm && !verifym && !verifyp)
    {
        x = CoordonneeX(chemin);
        y = CoordonneeY(chemin);

        xplus = x+taille-1;
        xmoin = x-taille+1;
        yplus = y+taille-1;
        ymoin = y-taille+1;

        if (ensemble != NULL)
        {
            place_dispo = defEmplacement(ensemble->coord_5_occupe, place_dispo);
            place_dispo = defEmplacement(ensemble->coord_4_occupe, place_dispo);
            place_dispo = defEmplacement(ensemble->coord_3_1_occupe,
                                         place_dispo);
            place_dispo = defEmplacement(ensemble->coord_3_2_occupe,
                                         place_dispo);
            place_dispo = defEmplacement(ensemble->coord_2_occupe, place_dispo);

            verifxp = collision(place_dispo, x, y, xplus, -2);
            verifxm = collision(place_dispo, x, y, xmoin, -1);
            verifyp = collision(place_dispo, x, y, yplus, 1);
            verifym = collision(place_dispo, x, y, ymoin, 2);

            if (place_dispo != NULL)
                place_dispo = ultimateSuppr(place_dispo);

            if(!verifxm || !verifxp || !verifym || !verifyp)
                affichage_texte(choix_coord_impossible);



        }
    }
    while ((choix <= 0) || (choix >= 5) || possibilite == 0)
    {
        /*Demande une des positions valides au joueur pour le placement de sont bateau*/
        temp = affichageChoix(xplus, xmoin, yplus, ymoin, verifxp, verifxm,
                                  verifyp, verifym, x, y,chemin);

        xplus = temp->xplus;
        xmoin = temp->xmoin;
        yplus = temp->yplus;
        ymoin = temp->ymoin;
        affichage_texte(annonce);
        fgets(choix1, 100, stdin);
        choix = atoi(choix1);
        cls();
        switch (choix)
        {
        case 1:
            if (temp->xplus == 100)         //On vérifie que le choix fait par le joueur soit une des propositions
            {
                cls();

                affichage_texte(erreur);
                sleep(3);
                cls();
            }
            else
            {
                temp_liste = ajoutCaseBateau(place_dispo, liste_coord, x, y,
                                             taille, choix);

                place_dispo = temp_liste->place_dispo;
                liste_coord = temp_liste->liste_coord;

                possibilite = 1;
            }
            break;

        case 2:
            if (temp->xmoin == 100)         //On vérifie que le choix fait par le joueur soit une des propositions
            {
                cls();
                affichage_texte(erreur);
                sleep(3);
                cls();
            }
            else
            {
                temp_liste = ajoutCaseBateau(place_dispo, liste_coord, x, y,
                                             taille, choix);
                place_dispo = temp_liste->place_dispo;
                liste_coord = temp_liste->liste_coord;

                possibilite = 1;
            }
            break;
        case 3:
            if (temp->yplus == 100)         //On vérifie que le choix fait par le joueur soit une des propositions
            {
                cls();
                affichage_texte(erreur);
                sleep(3);
                cls();
            }
            else
            {
                temp_liste = ajoutCaseBateau(place_dispo, liste_coord, x, y,
                                             taille, choix);
                place_dispo = temp_liste->place_dispo;
                liste_coord = temp_liste->liste_coord;

                possibilite = 1;
            }
            break;
        case 4:
            if (temp->ymoin == 100)         //On vérifie que le choix fait par le joueur soit une des propositions
            {
                cls();
                affichage_texte(erreur);
                sleep(3);
                cls();
            }
            else
            {
                temp_liste = ajoutCaseBateau(place_dispo, liste_coord, x, y,
                                             taille, choix);
                place_dispo = temp_liste->place_dispo;
                liste_coord = temp_liste->liste_coord;

                possibilite = 1;
            }
            break;
        }
    }

    switch (k)
    {
    case 6:
    {
        ensemble->coord_5 = liste_coord;
        ensemble->coord_5_occupe = place_dispo;
        break;
    }
    case 5:
    {
        ensemble->coord_4 = liste_coord;
        ensemble->coord_4_occupe = place_dispo;
        break;
    }
    case 4:
    {
        ensemble->coord_3_1 = liste_coord;
        ensemble->coord_3_1_occupe = place_dispo;
        break;

    case 3:
    {
        ensemble->coord_3_2 = liste_coord;
        ensemble->coord_3_2_occupe = place_dispo;
        break;
    }
    case 2:
    {
        ensemble->coord_2 = liste_coord;
        ensemble->coord_2_occupe = place_dispo;
        break;
    }
    }

    }
    return ensemble;
}


