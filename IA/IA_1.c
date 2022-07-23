#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "base.h"
#include "placement_bateau.h"
#include "IA_1.h"
#include "../Affichage/fonction_affichage.h"

/*=============================================================================
   On définit la fonction qui gère les coordonnées de tir du niveau 1 de l'IA
==============================================================================*/

Sortie * gestion_coordonnees_tir_LVL1(Coordonnees * coordonnee_tir_IA, char * chemin)
{
/* on tire une case comprise entre 1 et 10 en x et en y pour définir des coordonnees de tir*/

    int x = rand()%10;
    int y = rand()%10;
    Sortie * temp = malloc(sizeof(Sortie));

    char erreur_IA[100] = { "" };
    strcpy(erreur_IA, chemin);
    strcat(erreur_IA, "erreur_IA.txt");

    Coordonnees * pointeur = NULL;
    pointeur = coordonnee_tir_IA;

    int boucle = 0;
    int verif = 0;
    int compteur = 0;

// Sinon, on vérifie que les coordonnees n'ont pas déjà été tirées
//si c'est le cas, on en retire jusqu'à ce qu'elles ne soient pas dans la liste

    if (coordonnee_tir_IA == NULL)
        coordonnee_tir_IA = insertionEnTete(coordonnee_tir_IA, x, y);


    else
    {
        while (verif != 1)
        {
            pointeur = coordonnee_tir_IA;    //on repart au début de la liste à chaque fois

            while (pointeur != NULL && boucle != 1 && compteur != 300)//on limite le nb de nouvelle tentative pour ne pas planter
            {
// si les coordonnées ont déjà été pillonées, on en retire et on recommence la vérification depuis le début

                if (pointeur->x == x && pointeur->y == y)
                {
                    x = rand()%9+1;
                    y = rand()%9+1;
                    boucle = 1;
                    compteur ++;
                }
                else
                    pointeur = pointeur->suivant;
            }

            if (pointeur == NULL && boucle == 0)
            {
                coordonnee_tir_IA = insertionEnTete(coordonnee_tir_IA, x, y);
                verif = 1;
            }
            else
            {
                if(compteur == 300)
                    affichage_texte(erreur_IA);

                boucle = 0;
            }

        }
    }
    temp->liste_tir_IA = coordonnee_tir_IA;
    return temp;
}


/*=============================================================================
   On définit la fonction qui gère le fonctionnement global de l'IA LVL1
==============================================================================*/

Sortie * IA_LVL_1(int compteur_bateau_touche_IA, char tableau_joueur[][10],
                  Coordonnees * emplacement_bateau_IA,
                  Coordonnees * coordonnee_tir_IA,
                  Coordonnees * emplacement_bateau_joueur, Joueur * bateau,
                  char * chemin, Joueur * bateau_complet)
{

    emplacement_bateau_IA = emplacement_bateau_IA;
    int touche = 0;
    Sortie * out = malloc(sizeof(Sortie));
    Sortie * temp = gestion_coordonnees_tir_LVL1(coordonnee_tir_IA,chemin);
    coordonnee_tir_IA = temp->liste_tir_IA;



    int x = coordonnee_tir_IA->x;
    int y = coordonnee_tir_IA->y;
    touche = verif_bateau_joueur(emplacement_bateau_joueur, x, y); //on vérifie si le tir touche

    bateau_complet = verif_destruction(bateau_complet, bateau, x, y, chemin);
    if (touche == 1)
    {
        tableau_joueur[y][x] = 'R'; //s'il touche, on place une croix rouge dans le tableau du joueur
        compteur_bateau_touche_IA++;  //on augmente le compteur de touche permettant de définir la victoire de l'IA
    }
    else
        tableau_joueur[y][x] = 'B'; //sinon une croix blanche

    out->liste_tir_IA = coordonnee_tir_IA;
    out->compteur_touche = compteur_bateau_touche_IA;
    out->liste_touche_IA = NULL;
    out->nb_case_restante = 0;
    out->cases_restantes = NULL;
    out->compteur_schema = 0;
    out->bateau_complet = bateau_complet;
    return out;
}

/*==========================================================================
Fonction permettant de vérifier si l'IA a détruit un bateau du joueur
===========================================================================*/

Joueur * verif_destruction(Joueur * bateau_complet, Joueur * bateau, int x, int y, char * chemin)
{
    int verif = 0;

    char destruction_PA[100] = { "" };
    char destruction_C[100] = { "" };
    char destruction_SM[100] = { "" };
    char destruction_CT[100] = { "" };
    char destruction_T[100] = { "" };

    strcpy(destruction_PA, chemin);
    strcpy(destruction_C, chemin);
    strcpy(destruction_CT, chemin);
    strcpy(destruction_SM, chemin);
    strcpy(destruction_T, chemin);

    strcat(destruction_PA, "destruction_porte_avion.txt");
    strcat(destruction_C, "destruction_croiseur.txt");
    strcat(destruction_SM, "destruction_sous_marin.txt");
    strcat(destruction_CT, "destruction_contre_torpilleur.txt");
    strcat(destruction_T, "destruction_torpilleur.txt");

    Coordonnees * p = bateau->PA;//verif porte avion
    while(p != NULL && verif == 0)
    {
        if(p->x == x && p->y == y)
        {
            bateau_complet->PA = insertionEnTete(bateau_complet->PA, x, y);
            verif = 1;
        }
        else
            p = p->suivant;
    }

    p = bateau->C;//verif croiseur
    while(p != NULL && verif == 0)
    {
        if(p->x == x && p->y == y)
        {
            bateau_complet->C = insertionEnTete(bateau_complet->C, x, y);
            verif = 1;
        }
        else
            p = p->suivant;
    }

    p = bateau->SM;//verif sous marin
    while(p != NULL && verif == 0)
    {
        if(p->x == x && p->y == y)
        {
            bateau_complet->SM = insertionEnTete(bateau_complet->SM, x, y);
            verif = 1;
        }
        else
            p = p->suivant;
    }

    p = bateau->CT;//verif contre torpilleur
    while(p != NULL && verif == 0)
    {
        if(p->x == x && p->y == y)
        {
            bateau_complet->CT = insertionEnTete(bateau_complet->CT, x, y);
            verif = 1;
        }
        else
            p = p->suivant;
    }

    p = bateau->T;//verif torpilleur
    while(p != NULL && verif == 0)
    {
        if(p->x == x && p->y == y)
        {
            bateau_complet->T = insertionEnTete(bateau_complet->T, x, y);
            verif = 1;
        }
        else
            p = p->suivant;
    }


    int taille_PA = compteur_coup(bateau_complet->PA);
    int taille_C = compteur_coup(bateau_complet->C);
    int taille_SM = compteur_coup(bateau_complet->SM);
    int taille_CT = compteur_coup(bateau_complet->CT);
    int taille_T = compteur_coup(bateau_complet->T);

    if(taille_PA == 5)
    {
        cls();
        bateau_complet->PA = ultimateSuppr(bateau_complet->PA);
        affichage_texte(destruction_PA);
        sleep(1);
    }
    if(taille_C == 4)
    {
        cls();
        bateau_complet->C = ultimateSuppr(bateau_complet->C);
        affichage_texte(destruction_C);
        sleep(1);
    }
    if(taille_SM == 3)
    {
        cls();
        bateau_complet->SM = ultimateSuppr(bateau_complet->SM);
        affichage_texte(destruction_SM);
        sleep(1);
    }
    if(taille_CT == 3)
    {
        cls();
        bateau_complet->CT = ultimateSuppr(bateau_complet->SM);
        affichage_texte(destruction_CT);
        sleep(1);
    }
    if(taille_T == 2)
    {
        cls();
        bateau_complet->T = ultimateSuppr(bateau_complet->T);
        affichage_texte(destruction_T);
        sleep(1);
    }
    return bateau_complet;//on retourne les listes de verif


}

