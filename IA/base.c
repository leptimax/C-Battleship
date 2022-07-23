#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>

#include "base.h"
#include "../Systeme/clean.h"

/*==============================================================================
   On fait la fonction qui permet de vérifier si les coordonnées sont déjà dans
   la liste
==============================================================================*/

int verif_liste_tir(Coordonnees * coordonnee_tir_IA, int x, int y)
{
    if (coordonnee_tir_IA == NULL)
        return 0;

    Coordonnees * pointeur = coordonnee_tir_IA;
    while (pointeur != NULL)
    {
        if ((pointeur->x == x) && (pointeur->y == y))
            return 1;
        else
            pointeur = pointeur->suivant;
    }
    return 0;
}


Coordonnees * insertionEnTete(Coordonnees * liste, int x, int y)
{
    Coordonnees * coord = malloc(sizeof(Coordonnees));
    coord->x = x;
    coord->y = y;
    if (liste == NULL)
    {
        coord->suivant = NULL;
        liste = coord;
    }
    else
    {
        coord->suivant = liste;
        liste = coord;
    }
    return liste;
}


Coordonnees * ultimateSuppr(Coordonnees * tir_touche_IA)
{
    Coordonnees * pointeur = NULL;

    while (tir_touche_IA != NULL)
    {
        pointeur = tir_touche_IA;
        tir_touche_IA = tir_touche_IA->suivant;
	free(pointeur);
    }
    
    return tir_touche_IA;
}

/*=============================================================================
   On définit la fonction permettant de supprimer un élément dans une liste
   chaînée
==============================================================================*/

Coordonnees * Suppression(Coordonnees * choix_possible, int emplacement)
{
    Coordonnees * pointeur = NULL;
    Coordonnees * p_precedent = NULL;
    int compteur = 0;
    if (emplacement == 0)
    {
        pointeur = choix_possible;
        choix_possible = choix_possible->suivant;
        free(pointeur);
    }

    else
    {
        pointeur = choix_possible;
        p_precedent = NULL;
        while ((pointeur != NULL) && (compteur != emplacement))
        {
            p_precedent = pointeur;
            pointeur = pointeur->suivant;
            compteur++;
        }
        if (pointeur != NULL)
        {
            p_precedent->suivant = pointeur->suivant;
            free(pointeur);
        }
    }
    return choix_possible;
}


int verif_bateau_joueur(Coordonnees * emplacement_bateau_joueur, int x, int y)
{
//On parcourt la liste de coordonnées des bateaux du joueur pour vérifier si le tir touche

    if (emplacement_bateau_joueur == NULL)
        return 0;

    while (emplacement_bateau_joueur != NULL)
    {
        if ((emplacement_bateau_joueur->x == x) &&
            (emplacement_bateau_joueur->y == y))
            return 1;
        else
            emplacement_bateau_joueur = emplacement_bateau_joueur->suivant;
    }
    return 0;
}


/*==============================================================================
   Fonction pour les fonctions de type Taille
==============================================================================*/

Taille *insertion_Taille(Taille *liste_long, int longueur)
{
    Taille *element = malloc(sizeof(Taille));
    element->taille = longueur;
    element->suivant = NULL;
    if (liste_long == NULL)
        liste_long = element;
    else
    {
        element->suivant = liste_long;
        liste_long = element;
    }
    return liste_long;
}

Taille *ultimateSupprTaille(Taille *liste)
{
    Taille *pointeur;

    while (liste != NULL)
    {
        pointeur = liste;
        liste = liste->suivant;
        free(pointeur);
    }
    return liste;
}

Taille * suppression(Taille *liste_long, int longueur)
{
    Taille *p; Taille *q;
    if (liste_long == NULL)
        return liste_long;

    if (longueur == liste_long->taille)
    {
        p = liste_long;
        liste_long = liste_long->suivant;
        free(p);
    }
    else
    {
        p = liste_long;
        q = NULL;
        while ((p != NULL) && (longueur != p->taille))
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
    return liste_long;
}

void cls(void)
{
    system(CLEAN_SCREEN);
}

Taille * insertion_triee_Taille(Taille * liste, int element)
{
    Taille * pointeur = malloc(sizeof(Taille));
    pointeur->taille = element;
    if (liste == NULL)
    {
        liste = pointeur;
    }
    else
    {
        if (element > liste->taille)
            liste = insertion_Taille(liste, element);
        else
        {
            Taille * p = liste;
            Taille * pp = NULL;
            while ((p != NULL) && (element < p->taille))
            {
                pp = p;
                p = p->suivant;
            }

            pp->suivant = pointeur;
            pointeur->suivant = p;
        }
    }
    return liste;
}

void afficher(Coordonnees *liste)
{
    if (liste == NULL)
        printf("liste vide\n");
    else
    {
        Coordonnees *p = liste;
        while (p != NULL)
        {
            printf("--> %d  %d", p->x, p->y);
            p = p->suivant;
        }
    }
}

Coordonnees * insertionEnQueu(Coordonnees * liste, int x, int y)
{
    Coordonnees * coord = malloc(sizeof(Coordonnees));
    coord->x = x;
    coord->y = y;
    Coordonnees * p = NULL;
    Coordonnees * pp = NULL;
    if (liste == NULL)
    {
        coord->suivant = NULL;
        liste = coord;
    }
    else
    {
        p = liste;
        while (p != NULL)
        {
            pp = p;
            p = p->suivant;
        }
        coord->suivant = NULL;
        pp->suivant = coord;
    }
    return liste;
}

void buffer(char input[])
{
    if (!strchr(input, '\n'))    //newline does not exist
        while (fgetc(stdin) != '\n');
}

int compteur_coup(Coordonnees * liste)
{
    Coordonnees * p = NULL;
    int coup = 0;
    if (liste == NULL)
        return 0;
    else
    {
        p = liste;
        while(p != NULL)
        {
            coup ++;
            p = p->suivant;
        }
    }
    return coup;
}

