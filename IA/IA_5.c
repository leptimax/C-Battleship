
#include <stddef.h>
#include <stdlib.h>
#include "base.h"
#include "placement_bateau.h"
#include "IA_5.h"
#include "IA_1.h"

/*==============================================================================
   On définit le 5ème niveau d'IA
==============================================================================*/

Sortie * IA_LVL_5(int compteur_bateau_touche_IA, char tableau_joueur[][10],
                  Coordonnees * emplacement_bateau_joueur,
                  Coordonnees * liste_tir_ennemi, char * chemin, Joueur * bateau,
                  Joueur * bateau_complet)

{
    Sortie * temp = malloc(sizeof(Sortie));//on définit la structure de sortie
    Coordonnees * pointeur = emplacement_bateau_joueur;

    //L'IA tire directement sur les cases bateaux du joueur.

    int touche = 0;
    while (touche != compteur_bateau_touche_IA)
    {
        pointeur = pointeur->suivant;
        touche++;
    }

    int x = pointeur->x;
    int y = pointeur->y;
    bateau_complet = verif_destruction(bateau_complet, bateau, x, y, chemin);

    liste_tir_ennemi = insertionEnQueu(liste_tir_ennemi, x, y);

    tableau_joueur[y][x] = 'R'; //s'il touche, on place une croix rouge dans le tableau du joueur
    compteur_bateau_touche_IA++;  //on augmente le compteur de touche permettant de définir la victoire de l'IA


    temp->liste_tir_IA = liste_tir_ennemi;
    temp->compteur_touche = compteur_bateau_touche_IA;
    temp->liste_touche_IA = NULL;
    temp->compteur_schema = 0;
    temp->nb_case_restante = 0;
    temp->cases_restantes = NULL;
    temp->bateau_complet = bateau_complet;


    return temp;
}

