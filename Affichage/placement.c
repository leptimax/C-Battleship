#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../IA/base.h"
#include "../Save/save.h"
#include "../Main/jeu.h"
#include "placement.h"
#include "insert_erase_placement.h"
#include "fonction_affichage.h"

/*affichage des structure Taille*/

void afficherT(Taille *liste)
{
    if (liste == NULL)
        printf("liste vide\n");
    else
    {
        Taille *p = liste;
        while (p != NULL)
        {
            printf("--> %d", p->taille);
            p = p->suivant;
        }
    }
}


/*==============================================================================
            Creation des fonctions de placement des bateaux
==============================================================================*/

int CoordonneeX(char * chemin)       //Creation de la coordonnee x choisit par le joueur
{
    char input[100] = { ' ' };
    char x = 0;

    char colonne[100] = { "" };
    char hors_tableau[100] = { "" };

    strcpy(colonne, chemin);
    strcpy(hors_tableau, chemin);

    strcat(colonne, "colonne.txt");
    strcat(hors_tableau, "hors_tableau.txt");
    while (1)
    {
        affichage_texte(colonne);
        fgets(input, 100, stdin);
        x = input[0];

        if (x >= 65 && x <= 74)
            x = x - 64;
        else
        {
            if (x >= 97 && x <= 106)
                x = x - 96;
            else
                x = 0;
        }

        if ((x >= 11) || (x <= 0))      //On verifie que la valeur entree ne soit pas hors tableau
        {
            affichage_texte(hors_tableau);
        }
        else
        {
            return x;
        }
    }
}

int CoordonneeY(char * chemin)       //Creation de la coordonnee y choisit par le joueur
{
    char input[100] = { ' ' };
    char temp[10] = { ' ' };
    int y;

    char ligne[100] = { "" };
    char hors_tableau[100] = { "" };

    strcpy(ligne, chemin);
    strcpy(hors_tableau, chemin);

    strcat(ligne, "ligne.txt");
    strcat(hors_tableau, "hors_tableau.txt");

    while (1)
    {
        affichage_texte(ligne);
        fgets(input, 100, stdin);
        temp[0] = input[0];
        temp[1] = input[1];

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

/*==============================================================================
   On g�re ensuite le sous menu permettant de placer l'emplacement des bateaux
==============================================================================*/

Out_boat * choix_Taille(Taille *liste_long, EnsembleC * ensemblec,
                        char tableau_joueur[10][10], char * chemin, Color * couleur_applicable)
{
    char longueur1[100];
    int longueur;
    Taille *p = liste_long;
    char x1[100];
    int x;
    Out_boat * out = malloc(sizeof(Out_boat));
    Out_boat * temp = malloc(sizeof(Out_boat));

//on r�cup�re les coordonn�es des diff�rents bateaux

    Coordonnees * coord_5 = ensemblec->coord_5;
    Coordonnees * coord_4 = ensemblec->coord_4;
    Coordonnees * coord_3_1 = ensemblec->coord_3_1;
    Coordonnees * coord_3_2 = ensemblec->coord_3_2;
    Coordonnees * coord_2 = ensemblec->coord_2;

// on affiche les choix restant

char taille[100] = { "" };
    char PA[100] = { "" };
    char C[100] = { "" };
    char SM[100] = { "" };
    char CT[100] = { "" };
    char T[100] = { "" };
    char hors_proposition[100] = { "" };
    char alerte_bateau[100] = { "" };
    char alerte_placement[100] = { "" };
    char sous_menu[100] = { "" };
    char annonce_suppression[100] = { "" };
    char annonce_suppression2[100] = { "" };
    char annonce_placement_fini[100] = { "" };

    strcpy(taille, chemin);
    strcpy(PA, chemin);
    strcpy(C, chemin);
    strcpy(SM, chemin);
    strcpy(CT, chemin);
    strcpy(T, chemin);
    strcpy(hors_proposition, chemin);
    strcpy(alerte_bateau, chemin);
    strcpy(alerte_placement, chemin);
    strcpy(sous_menu, chemin);
    strcpy(annonce_suppression, chemin);
    strcpy(annonce_suppression2, chemin);
    strcpy(annonce_placement_fini, chemin);

    strcat(taille, "choix_navire.txt");
    strcat(PA, "porte_avion.txt");
    strcat(C, "croiseur.txt");
    strcat(SM, "sous_marin.txt");
    strcat(CT, "contre_torpilleur.txt");
    strcat(T, "torpilleur.txt");
    strcat(alerte_bateau, "alerte_bateau.txt");
    strcat(hors_proposition, "menu_suppr.txt");
    strcat(alerte_placement, "alerte_placement.txt");
    strcat(sous_menu, "sous_menu_placement.txt");
    strcat(annonce_suppression, "annonce_suppression_unique.txt");
    strcat(annonce_suppression2, "annonce_suppression_totale.txt");
    strcat(annonce_placement_fini, "annonce_placement_fini.txt");


    affichage_texte(taille); //on affiche les choix restants
    while (p != NULL)
    {
        switch (p->taille)
        {
        case 6:
        {
            affichage_texte(PA);
            break;
        }
        case 5:
        {
            affichage_texte(C);
            break;
        }
        case 4:
        {
            affichage_texte(SM);
            break;
        }
        case 3:
        {
            affichage_texte(CT);
            break;
        }
        case 2:
        {
            affichage_texte(T);
            break;
        }
        }
        p = p->suivant;
    }
    affichage_texte(hors_proposition);
    p = liste_long;
    fgets(longueur1, 100, stdin); //on recup�re le choix de l'utilisateur
    longueur = atoi(longueur1);
    if (longueur == 7)//si l'utilisateur veut valider son placement
    {
        cls();
        if (coord_2 != NULL && coord_3_1 != NULL && coord_3_2 != NULL &&
            coord_4 != NULL && coord_5 != NULL)
        {
            out->longueur = longueur;
            out->liste_long = liste_long;
            out->liste = ensemblec;
            return out;
        }
        else
        {
            affichage_texte(alerte_bateau);
            sleep(1);
            cls();
            return choix_Taille(liste_long, ensemblec, tableau_joueur, chemin, couleur_applicable);
        }
    }
    if ((longueur < 1) || (longueur > 6))       //On v�rifie que la taille choisi existe
    {
        cls();
        affichage_texte(alerte_placement);
        sleep(1);
        cls();
        return choix_Taille(liste_long, ensemblec, tableau_joueur, chemin, couleur_applicable);
    }

    if (longueur == 1)//pour supprimer un bateau
    {
        cls();
        affichage_texte(sous_menu);
        fgets(x1, 100, stdin);
        x = atoi(x1);
        switch (x)
        {
        case 1:
            cls();
            temp = suppression_Un_Bateau(liste_long, ensemblec, chemin);
            ensemblec = temp->liste;
            liste_long = temp->liste_long;
            affichage_texte(annonce_suppression);
            sleep(1);
            cls();
            afficheTableau(tableau_joueur, ensemblec, couleur_applicable);
            return choix_Taille(liste_long, ensemblec, tableau_joueur, chemin, couleur_applicable);

        case 2:

            cls();

            temp = suppression_Tous_Bateaux(ensemblec, liste_long);
            ensemblec = temp->liste;
            liste_long = temp->liste_long;
            affichage_texte(annonce_suppression2);
            sleep(1);
            cls();
            afficheTableau(tableau_joueur, ensemblec,couleur_applicable);
            return choix_Taille(liste_long, ensemblec, tableau_joueur, chemin, couleur_applicable);

        default:
            cls();
            return choix_Taille(liste_long, ensemblec, tableau_joueur, chemin, couleur_applicable);
            break;
        }
    }
    else
    {
//Dans cette boucle nous v�rifions qu'il reste des bateaux, de la taille choisie, a placer

        while (p != NULL)
        {
            if (p->taille == longueur)

//Si il y a toujours des bateaux de la taille choisie a placer on enleve 1 "exemplaire" du type de bateau de la liste
            {
                liste_long = suppression(liste_long, longueur);
                cls();
                out->longueur = longueur;
                out->liste_long = liste_long;
                out->liste = ensemblec;
                return out;
            }
            else
            {
                p = p->suivant;
            }
        }
    }

    cls();

//Si la taille choisi n'ai pas trouv� dans la liste on demande au joueur de choisir une taille parmie les restantes

    affichage_texte(annonce_placement_fini);
    sleep(1);
    cls();
    return choix_Taille(liste_long, ensemblec, tableau_joueur, chemin, couleur_applicable);
}
