#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../IA/base.h"
#include "fonction_affichage.h"
#include "insert_erase_placement.h"

#define CHOIX_INC "Ce choix ne fais pas partie des propositions. Veuillez recommencer.\n"/


/*==============================================================================
   On définit la fonction qui supprime tous les bateaux
==============================================================================*/

Out_boat *suppression_Tous_Bateaux(EnsembleC * ensemblec, Taille * liste_long)       //WORK IN PROGRESS
{
    Out_boat * out = malloc(sizeof(Out_boat));
    if (ensemblec->coord_5 != NULL)
        ensemblec->coord_5 = ultimateSuppr(ensemblec->coord_5);
    if (ensemblec->coord_4 != NULL)
        ensemblec->coord_4 = ultimateSuppr(ensemblec->coord_4);
    if (ensemblec->coord_3_1 != NULL)
        ensemblec->coord_3_1 = ultimateSuppr(ensemblec->coord_3_1);
    if (ensemblec->coord_3_2 != NULL)
        ensemblec->coord_3_2 = ultimateSuppr(ensemblec->coord_3_2);
    if (ensemblec->coord_2 != NULL)
        ensemblec->coord_2 = ultimateSuppr(ensemblec->coord_2);

    if (ensemblec->coord_5_occupe != NULL)
        ensemblec->coord_5_occupe = ultimateSuppr(ensemblec->coord_5_occupe);
    if (ensemblec->coord_4_occupe != NULL)
        ensemblec->coord_4_occupe = ultimateSuppr(ensemblec->coord_4_occupe);
    if (ensemblec->coord_3_1_occupe != NULL)
        ensemblec->coord_3_1_occupe = ultimateSuppr(
            ensemblec->coord_3_1_occupe);
    if (ensemblec->coord_3_2_occupe != NULL)
        ensemblec->coord_3_2_occupe = ultimateSuppr(
            ensemblec->coord_3_2_occupe);
    if (ensemblec->coord_2_occupe != NULL)
        ensemblec->coord_2_occupe = ultimateSuppr(ensemblec->coord_2_occupe);

    liste_long = ultimateSupprTaille(liste_long);

    liste_long = insertion_Taille(liste_long, 0);
    liste_long = insertion_Taille(liste_long, 2);
    liste_long = insertion_Taille(liste_long, 3);
    liste_long = insertion_Taille(liste_long, 4);
    liste_long = insertion_Taille(liste_long, 5);
    liste_long = insertion_Taille(liste_long, 6);

    out->liste = ensemblec;
    out->liste_long = liste_long;
    return out;
}

/*==============================================================================
   On définit la fonction qui permet de supprimer un bateau
==============================================================================*/

Out_boat *suppression_Un_Bateau(Taille * liste_long, EnsembleC * ensemblec, char * chemin)
{
    char x1[100] = { ' ' };
    int x;

    Out_boat * out = malloc(sizeof(Out_boat));

    Coordonnees * coord_5 = ensemblec->coord_5;
    Coordonnees * coord_4 = ensemblec->coord_4;
    Coordonnees * coord_3_1 = ensemblec->coord_3_1;
    Coordonnees * coord_3_2 = ensemblec->coord_3_2;
    Coordonnees * coord_2 = ensemblec->coord_2;

    Coordonnees * coord_5_occupe = ensemblec->coord_5_occupe;
    Coordonnees * coord_4_occupe = ensemblec->coord_4_occupe;
    Coordonnees * coord_3_1_occupe = ensemblec->coord_3_1_occupe;
    Coordonnees * coord_3_2_occupe = ensemblec->coord_3_2_occupe;
    Coordonnees * coord_2_occupe = ensemblec->coord_2_occupe;

    char taille[100] = { "" };
    char PA[100] = { "" };
    char C[100] = { "" };
    char SM[100] = { "" };
    char CT[100] = { "" };
    char T[100] = { "" };
    char hors_proposition[100] = { "" };

    strcpy(taille, chemin);
    strcpy(PA, chemin);
    strcpy(C, chemin);
    strcpy(SM, chemin);
    strcpy(CT, chemin);
    strcpy(T, chemin);
    strcpy(hors_proposition, chemin);

    strcat(taille, "taille_navire.txt");
    strcat(PA, "porte_avion.txt");
    strcat(C, "croiseur.txt");
    strcat(SM, "sous_marin.txt");
    strcat(CT, "contre_torpilleur.txt");
    strcat(T, "torpilleur.txt");
    strcat(hors_proposition, "hors_proposition.txt");

//on affiche les choix de bateau restant

    affichage_texte(taille);
    if (coord_5 != NULL)
        affichage_texte(PA);
    if (coord_4 != NULL)
        affichage_texte(C);
    if (coord_3_1 != NULL)
        affichage_texte(SM);
    if (coord_3_2 != NULL)
        affichage_texte(CT);
    if (coord_2 != NULL)
        affichage_texte(T);
    fgets(x1, 100, stdin);

    x = atoi(x1);

    switch (x)
    {
//on supprime le bateau choisit
    case 6:
    {
        if (coord_5 == NULL)
        {
            affichage_texte(hors_proposition);
            return suppression_Un_Bateau(liste_long, ensemblec, chemin);
        }
        else
        {
            coord_5 = ultimateSuppr(coord_5);
            coord_5_occupe = ultimateSuppr(coord_5_occupe);
            liste_long = insertion_triee_Taille(liste_long, 6);
        }
        break;
    }
    case 5:
    {
        if (coord_4 == NULL)
        {
            affichage_texte(hors_proposition);
            return suppression_Un_Bateau(liste_long, ensemblec, chemin);
        }
        else
        {
            coord_4 = ultimateSuppr(coord_4);
            coord_4_occupe = ultimateSuppr(coord_4_occupe);
            liste_long = insertion_triee_Taille(liste_long, 5);
        }
        break;
    }
    case 4:
    {
        if (coord_3_1 == NULL)
        {
            affichage_texte(hors_proposition);
            return suppression_Un_Bateau(liste_long, ensemblec, chemin);
        }
        else
        {
            coord_3_1 = ultimateSuppr(coord_3_1);
            coord_3_1_occupe = ultimateSuppr(coord_3_1_occupe);
            liste_long = insertion_triee_Taille(liste_long, 4);
        }
        break;
    case 3:
        if (coord_3_2 == NULL)
        {
            affichage_texte(hors_proposition);
            return suppression_Un_Bateau(liste_long, ensemblec, chemin);
        }
        else
        {
            coord_3_2 = ultimateSuppr(coord_3_2);
            coord_3_2_occupe = ultimateSuppr(coord_3_2_occupe);
            liste_long = insertion_triee_Taille(liste_long, 3);
        }
        break;
    }
    case 2:
    {
        if (coord_2 == NULL)
        {
            affichage_texte(hors_proposition);
            return suppression_Un_Bateau(liste_long, ensemblec, chemin);
        }
        else
        {
            coord_2 = ultimateSuppr(coord_2);
            coord_2_occupe = ultimateSuppr(coord_2_occupe);
            liste_long = insertion_triee_Taille(liste_long, 2);
        }
        break;
    }
    }
    ensemblec->coord_5 = coord_5;
    ensemblec->coord_4 = coord_4;
    ensemblec->coord_3_1 = coord_3_1;
    ensemblec->coord_3_2 = coord_3_2;
    ensemblec->coord_2 = coord_2;

    ensemblec->coord_5_occupe = coord_5_occupe;
    ensemblec->coord_4_occupe = coord_4_occupe;
    ensemblec->coord_3_1_occupe = coord_3_1_occupe;
    ensemblec->coord_3_2_occupe = coord_3_2_occupe;
    ensemblec->coord_2_occupe = coord_2_occupe;

    out->liste = ensemblec;
    out->liste_long = liste_long;
    return out;
}

//permettant de remplir la structure

Ensemble *insertion_Ensemble_choixcoord(Ensemble *ensemble,
                                        Coordonnees *liste_coord,
                                        Coordonnees *place_dispo)
{
    Ensemble *element = malloc(sizeof(ensemble));
    element->liste_coord = liste_coord;
    element->place_dispo = place_dispo;
    element->liste_long = NULL;

    return ensemble;
}

//insertion des coord dans une structure ensemble

Coordonnees *insertion_Coord_Ensemble(Coordonnees *liste, Ensemble *ensemble)
{
    Coordonnees *element = malloc(sizeof(Coordonnees)); Coordonnees *p;
    element->x = ensemble->liste_coord->x;
    element->y = ensemble->liste_coord->y;
    element->suivant = ensemble->liste_coord->suivant;

    p = element;
    if (liste == NULL)
        liste = element;
    else
    {
        while (element->suivant != NULL)
            element = element->suivant;
        element->suivant = liste;
        liste = p;
    }
    return liste;
}

//fonction permettant de supprimer une coordonnée

Coordonnees *suppression_Coord(Coordonnees *place_dispo, int x, int y)
{
    Coordonnees *p; Coordonnees *q;
    if (place_dispo == NULL)
        return place_dispo;

    if ((x == place_dispo->x) && (y == place_dispo->y))
    {
        p = place_dispo;
        place_dispo = place_dispo->suivant;
        free(p);
    }
    else
    {
        p = place_dispo;
        q = NULL;
        while ((p != NULL) && (x != p->x) && (y != p->y))
        {
            q = p;
            p = p->suivant;
        }
        if (p != NULL)
        {
            q->suivant = p->suivant;
            free(p);
        }
    }
    return place_dispo;
}


