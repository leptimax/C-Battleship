
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "base.h"
#include "../Affichage/fonction_affichage.h"
#include "placement_bateau.h"
#include "IA_2.h"
#include "IA_1.h"

/*==============================================================================
   On définit la fonction permettant de tirer une case parmi les 4 possibles
   lorsque l'on a touché un bateau du joueur
==============================================================================*/

Coordonnees * emplacement_tir_annihilation_2(Coordonnees * coordonnee_tir_IA,
                                             int x, int y)
{
    int x_ref = x;
    int y_ref = y;
    int choix;
    int compteur = 0;
    int i = 4;
    int dedans = 1;
    int stop = 0;

    Coordonnees * choix_possible = NULL;
    Coordonnees * pointeur = NULL;

//on insère les différentes coordonnées de tir possible dans choix_possible

    choix_possible = insertionEnTete(choix_possible, x_ref+1, y_ref);
    choix_possible = insertionEnTete(choix_possible, x_ref-1, y_ref);
    choix_possible = insertionEnTete(choix_possible, x_ref, y_ref+1);
    choix_possible = insertionEnTete(choix_possible, x_ref, y_ref-1);

    while ((stop == 0) && (choix_possible != NULL)) // tant qu'on a pas des coordonnées valide, on en tire
    {
        pointeur = choix_possible;
        choix = rand()%i;
        compteur = 0;

        while (compteur != choix) //on récupère la coordonnée dans la liste
        {
            pointeur = pointeur->suivant;
            compteur++;
        }

        x = pointeur->x;
        y = pointeur->y;
        dedans = verif_liste_tir(coordonnee_tir_IA, x, y); //on vérifie que les coordonnées n'ont pas déjà été pillonnées

        if ((dedans == 1) || (x < 0) || (x > 9) || (y < 0) || (y > 9)) //si la coordonnée est hors tableau ou déjà tiré, on la supprime de la liste
        {
            choix_possible = Suppression(choix_possible, choix);
            i--;
        }
        else
            stop = 1;
    }

    if (choix_possible != NULL) //si il y a bien une coordonnée disponible, on le retourne
    {
        Coordonnees * coord = malloc(sizeof(Coordonnees));
        coord->x = x;
        coord->y = y;
        return coord;
    }
    else
    {
        Coordonnees * coord = NULL; // sinon on retourne NULL
        return coord;
    }
}

/*=============================================================================
   On crée la fonction permettant de gérer les tirs lorsque l'on a entamé
   un navire ennemi
==============================================================================*/

Coordonnees * annihilation_2(Coordonnees * coordonnee_tir_IA,
                             Coordonnees * emplacement_bateau_joueur, int temp,
                             Coordonnees * reference)
{
    int x;
    int y;
    int verif = 0;
    int compteur = 0;
    Coordonnees * p_temp = NULL;
    Coordonnees * coord = NULL;

//si on a pas atteint une extrémité :

    if (temp == 0)
    {
        p_temp = coordonnee_tir_IA;
        // on recherhce dans la liste de coordonnée la dernière coordonnée qui touche
        while ((p_temp != NULL) && (verif != 1) && (compteur < 3))
        {
            x = p_temp->x;
            y = p_temp->y;
            verif = verif_bateau_joueur(emplacement_bateau_joueur, x, y);

            if (verif == 1) //si on est dessus, on tire une des 4 cases possibles autour
                coord = emplacement_tir_annihilation_2(coordonnee_tir_IA, x, y);

            else
            {
                p_temp = p_temp->suivant;
                compteur++;
            }
        }
        return coord;
    }
    else //si le compteur est supérieur à 3, i-e, qu'on a atteint un extrémité
    {
        p_temp = coordonnee_tir_IA;
        //on retourne sur la première coordonnée touchée et on recommence les tirs jusqu'à atteindre l'autre extremité
        while ((p_temp->x != reference->x) || ((p_temp->y != reference->y) &&
                                               (p_temp != NULL)))
            p_temp = p_temp->suivant;


        while ((verif != 1) && (compteur < 3))
        {
            x = p_temp->x;
            y = p_temp->y;
            verif = verif_bateau_joueur(emplacement_bateau_joueur, x, y);

            if (verif == 1)
                coord = emplacement_tir_annihilation_2(coordonnee_tir_IA, x, y);

            else
            {
                p_temp = p_temp->suivant;
                compteur++;
            }
        }
        return coord;
    }
}

/*==============================================================================
   On crée la fonction qui gère l'ensmble des tirs de l'IA LVL 2
==============================================================================*/

Sortie * gestion_coordonnees_tir_IA_2(Coordonnees * coordonnee_tir_IA,
                                      Coordonnees * tir_touche_IA,
                                      Coordonnees * emplacement_bateau_joueur)
{
    Coordonnees * pointeur = NULL;
    Coordonnees * coord = NULL;
    Coordonnees * reference = NULL;

    Sortie * out = malloc(sizeof(Sortie));//on définit la structure de sortie


    int boucle = 0;
    int verif = 0;
    int x;
    int y;
    int temp = 0;

    while (coord == NULL)
    {
//si on a pas de bateau ennemi en cours de destruction ou que l'on commence la partie, on tire aléatoirement une case

        if ((coordonnee_tir_IA == NULL) || (tir_touche_IA == NULL))
        {
            x = rand()%10;
            y = rand()%10;
            while (verif != 1)
            {
                pointeur = coordonnee_tir_IA;    //on repart au début de la liste à chaque fois

                while (pointeur != NULL && boucle != 1)
                {
                    // si les coordonnées ont déjà été pillonées, on en retire et on recommence la vérification depuis le début

                    if (pointeur->x == x && pointeur->y == y)
                    {
                        x = rand()%10;
                        y = rand()%10;
                        boucle = 1;
                    }

                    else
                        pointeur = pointeur->suivant;
                }

                if (pointeur == NULL && boucle == 0)   // si elles n'ont pas été tirées, on les ajoutent à la liste
                {
                    coordonnee_tir_IA = insertionEnTete(coordonnee_tir_IA, x,
                                                        y);
                    verif = 1;
                    out->liste_tir_IA = coordonnee_tir_IA;
                    out->liste_touche_IA = tir_touche_IA;
                    return out;
                }
                else
                    boucle = 0;
            }
            coord = insertionEnTete(coord, x, y);
        }


        else //si on a un bateau ennemi entamé
        {
            coord = annihilation_2(coordonnee_tir_IA, emplacement_bateau_joueur,
                                   temp, coord);  //on cherche des coordonnées de tir optimisé
            if (coord != NULL)
                coordonnee_tir_IA = insertionEnTete(coordonnee_tir_IA, coord->x,
                                                    coord->y);

            else //si il n'y a pas de coordonnées, i-e, qu'on a atteint une extrémité
            {
                temp = 1;//permet d'indiquer qu'il faut chercher des coordonnées en conséquence
                reference = tir_touche_IA;//on prend en référence le premire tir touché
                while (reference != NULL)
                {
                    coord = reference;
                    reference = reference->suivant;
                }

                coord = annihilation_2(coordonnee_tir_IA,
                                       emplacement_bateau_joueur, temp, coord);  //on tire des coords
                if (coord != NULL)
                    coordonnee_tir_IA = insertionEnTete(coordonnee_tir_IA,
                                                        coord->x, coord->y);
                else //si y a toujours pas de coord, on a éliminé l'intégralité du bateau donc on vide la liste de tir touché
                {
                    coord = NULL;
                    tir_touche_IA = ultimateSuppr(tir_touche_IA);
                }
            }
        }
    }
    out->liste_tir_IA = coordonnee_tir_IA;
    out->liste_touche_IA = tir_touche_IA;
    return out;
}


/*=============================================================================
   On définit la fonction qui gère le fonctionnement global de l'IA LVL1
==============================================================================*/

Sortie * IA_LVL_2(int compteur_bateau_touche_IA, char tableau_joueur[][10],
                  Coordonnees * emplacement_bateau_IA,
                  Coordonnees * coordonnee_tir_IA,
                  Coordonnees * emplacement_bateau_joueur,
                  Coordonnees * tir_touche_IA, Joueur * bateau, char * chemin,
                  Joueur * bateau_complet)
{
    emplacement_bateau_IA = emplacement_bateau_IA;
    Sortie * temp = malloc(sizeof(Sortie));//on définit la structure de sortie
    int touche = 0;
    Sortie * out = gestion_coordonnees_tir_IA_2(coordonnee_tir_IA,
                                                tir_touche_IA,
                                                emplacement_bateau_joueur); //l'IA tire
    coordonnee_tir_IA = out->liste_tir_IA;   //on récupère les coordonnées de tir
    tir_touche_IA = out->liste_touche_IA;   //on récupère les coordonnées qui touche

    int x = coordonnee_tir_IA->x;
    int y = coordonnee_tir_IA->y;

    touche = verif_bateau_joueur(emplacement_bateau_joueur, x, y); //on vérifie si le tir touche

    bateau_complet = verif_destruction(bateau_complet, bateau, x, y, chemin);
    if (touche == 1)
    {
        tir_touche_IA = insertionEnTete(tir_touche_IA, x, y); // on ajoute la coordonnée à la liste de celle touchée
        tableau_joueur[y][x] = 'R'; //s'il touche, on place une croix rouge dans le tableau du joueur
        compteur_bateau_touche_IA++;  //on augmente le compteur de touche permettant de définir la victoire de l'IA
    }

    else
        tableau_joueur[y][x] = 'B'; //sinon une croix blanche

    temp->liste_tir_IA = coordonnee_tir_IA;
    temp->liste_touche_IA = tir_touche_IA;
    temp->compteur_touche = compteur_bateau_touche_IA;
    temp->nb_case_restante = 0;
    temp->cases_restantes = NULL;
    temp->compteur_schema = 0;
    temp->bateau_complet = bateau_complet;

    return temp;
}

