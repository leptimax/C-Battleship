#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "base.h"
#include "placement_bateau.h"
#include "IA_4.h"
#include "IA_1.h"
#include "../Affichage/fonction_affichage.h"

/*==============================================================================
   On d�finit la fonction permettant de tirer une case parmi les 4 possibles
   lorsque l'on a touch� un bateau du joueur
==============================================================================*/

Coordonnees * emplacement_tir_annihilation_4(Coordonnees * coordonnee_tir_IA,
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

//on ins�re les diff�rentes coordonn�es de tir possible dans choix_possible

    choix_possible = insertionEnTete(choix_possible, x_ref+1, y_ref);
    choix_possible = insertionEnTete(choix_possible, x_ref-1, y_ref);
    choix_possible = insertionEnTete(choix_possible, x_ref, y_ref+1);
    choix_possible = insertionEnTete(choix_possible, x_ref, y_ref-1);

    while ((stop == 0) && (choix_possible != NULL)) // tant qu'on a pas des coordonn�es valide, on en tire
    {
        pointeur = choix_possible;
        choix = rand()%i;
        compteur = 0;

        while (compteur != choix) //on r�cup�re la coordonn�e dans la liste
        {
            pointeur = pointeur->suivant;
            compteur++;
        }

        x = pointeur->x;
        y = pointeur->y;
        dedans = verif_liste_tir(coordonnee_tir_IA, x, y); //on v�rifie que les coordonn�es n'ont pas d�j� �t� pillonn�es

        if ((dedans == 1) || (x < 0) || (x > 9) || (y < 0) || (y > 9)) //si la coordonn�e est hors tableau ou d�j� tir�, on la supprime de la liste
        {
            choix_possible = Suppression(choix_possible, choix);
            i--;
        }
        else
            stop = 1;
    }

    if (choix_possible != NULL) //si il y a bien une coordonn�e disponible, on le retourne
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

/*==============================================================================
   On cr�e la fonction permettant de tirer les cases du bateau avec pr�cision
==============================================================================*/
Coordonnees * emplacement_tir_annihilation_IA_4(Coordonnees * coordonnee_tir_IA,
                                                Coordonnees * tir_touche_IA,
                                                int temp, int sens)
{
    Coordonnees * pointeur_temp = tir_touche_IA;
    Coordonnees * pointeur = NULL;
    Coordonnees * choix_possible = NULL;

    int x;
    int y;
    int x_ref;
    int y_ref;
    int i = 2;
    int choix;
    int compteur = 0;
    int stop = 0;
    int dedans = 0;

    if (temp == 0) // on a pas encore atteint l'extr�mit�
    {
        x_ref = tir_touche_IA->x;
        y_ref = tir_touche_IA->y;
    }
    else //si on a atteint l'extr�mit�, on repart dans l'autre sens depuis la premi�re case touch� pour v�rifier que tout le bateau est �limin�
    {
        while (pointeur_temp->suivant != NULL)
            pointeur_temp = pointeur_temp->suivant;

        x_ref = pointeur_temp->x;
        y_ref = pointeur_temp->y;
    }

    if (sens == 0)//vertical
    {
        choix_possible = insertionEnTete(choix_possible, x_ref, y_ref+1);
        choix_possible = insertionEnTete(choix_possible, x_ref, y_ref-1);
    }
    else
    {
        choix_possible = insertionEnTete(choix_possible, x_ref+1, y_ref);
        choix_possible = insertionEnTete(choix_possible, x_ref-1, y_ref);
    }
    while ((stop == 0) && (choix_possible != NULL)) // tant qu'on a pas des coordonn�es valide, on en tire
    {
        pointeur = choix_possible;
        choix = rand()%i;
        compteur = 0;

        while (compteur != choix) //on r�cup�re la coordonn�e dans la liste
        {
            pointeur = pointeur->suivant;
            compteur++;
        }

        x = pointeur->x;
        y = pointeur->y;
        dedans = verif_liste_tir(coordonnee_tir_IA, x, y); //on v�rifie que les coordonn�es n'ont pas d�j� �t� pillonn�es

        if ((dedans == 1) || (x < 0) || (x > 9) || (y < 0) || (y > 9)) //si la coordonn�e est hors tableau ou d�j� tir�, on la supprime de la liste
        {
            choix_possible = Suppression(choix_possible, choix);
            i--;
        }
        else
            stop = 1;
    }

    if (choix_possible != NULL) //si il y a bien une coordonn�e disponible, on le retourne
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

/*==============================================================================
   On cr�e la fonction qui va d�termin� le sens du bateau sur lequel l'IA tire
==============================================================================*/

int definition_sens(Coordonnees * tir_touche_IA)
{
    int sens;
    int x_ref = tir_touche_IA->suivant->x;
    int y_ref = tir_touche_IA->suivant->y;
    int x = tir_touche_IA->x;
    int y = tir_touche_IA->y;
    if ((x = x_ref+1) || (x = x_ref-1))
        sens = 0;
    if ((y = y_ref+1) || (y = y_ref-1))
        sens = 1;

    return sens;
}

/*==============================================================================
   On cr�e la fonction permettant de g�rer les tirs lorsque l'on a entam�
   un navire ennemi
==============================================================================*/

Coordonnees * annihilation_4(Coordonnees * coordonnee_tir_IA,
                             Coordonnees * tir_touche_IA,
                             Coordonnees * emplacement_bateau_joueur, int temp,
                             Coordonnees * reference)
{
    reference = reference;
    int x;
    int y;
    int verif = 0;
    int compteur = 0;
    int sens;

    Coordonnees * p_temp = NULL;
    Coordonnees * coord = NULL;

//si on a pas deux cases de touch�s et que l'on ne connait donc pas le sens du bateau
    if (tir_touche_IA->suivant == NULL)
    {
        p_temp = coordonnee_tir_IA;
        // on recherhce dans la liste de coordonn�e la derni�re coordonn�e qui touche
        while ((p_temp != NULL) && (verif != 1) && (compteur < 3))
        {
            x = p_temp->x;
            y = p_temp->y;
            verif = verif_bateau_joueur(emplacement_bateau_joueur, x, y);

            if (verif == 1) //si on est dessus, on tire une des 4 cases possibles autour
                coord = emplacement_tir_annihilation_4(coordonnee_tir_IA, x, y);

            else
            {
                p_temp = p_temp->suivant;
                compteur++;
            }
        }
        return coord;
    }
    else //si on a 2 tirs et donc le sens du bateau
    {

        sens = definition_sens(tir_touche_IA);

        coord = emplacement_tir_annihilation_IA_4(coordonnee_tir_IA,
                                                  tir_touche_IA, temp, sens);
    }


    return coord;
}


/*==============================================================================
   On cr�e la fonction qui s'occupe de convertir les coordonn�es pour coller
   au sch�ma
==============================================================================*/

Coordonnees * assignation_schema_lvl_4(int x, int y, int diagonale)
{
    //si on est en sens vertical, les x ne peuvent prendre que les valeurs 0,2,4,6,8
    //si on est en sens horizontal ce sont les y qui ne peuvent prendre que ces valeurs

    Coordonnees * coord = NULL;

    switch (diagonale)
    {
    case 1:
    {
        y = x;
        x = x+4;
        coord = insertionEnTete(coord, x, y);
        break;
    }
    case 2:
    {
        x = y;
        y = y+4;
        coord = insertionEnTete(coord, x, y);
        break;
    }
    case 3:
    {
        y = 9-x;
        coord = insertionEnTete(coord, x, y);
        break;
    }
    case 4:
    {
        x = x+4;
        y = 13-x;
        coord = insertionEnTete(coord, x, y);
        break;
    }
    case 5:
    {
        x = 5-y;
        coord = insertionEnTete(coord, x, y);
        break;
    }
    }
    return coord;
}

/*==============================================================================
   On cr�e la fonction qui va d�finir les tirs non convertis selon la diagonale
==============================================================================*/

Coordonnees * def_diagonale(int diagonale)
{
    Coordonnees * coord = NULL;

    int x = 0;
    int y = 0;

    switch (diagonale)
    {
    case 0:      //premi�re diagonale partant du coin gauche
    {
        x = (rand()%100)/10;
        y = x;
        coord = insertionEnTete(coord, x, y);
        break;
    }
    case 1:      //une diagonale d�cal�e de 3 cases sur la droite de la premi�re diagonale
    {
        x = ((rand()%60)/10);
        coord = assignation_schema_lvl_4(x, y, diagonale);
        break;
    }
    case 2:      //une diagonale d�cal�e de 3 cases sous la premi�re diagonale
    {
        y = ((rand()%60)/10);
        coord = assignation_schema_lvl_4(x, y, diagonale);
        break;
    }
    case 3:      //premi�re bissectrice
    {
        x = ((rand()%100)/10);
        coord = assignation_schema_lvl_4(x, y, diagonale);
        break;
    }
    case 4:      //une diagonale d�cal�e de 3 cases vers la gauche de la premi�re bissectrice
    {
        x = ((rand()%60)/10);
        coord = assignation_schema_lvl_4(x, y, diagonale);
        break;
    }
    case 5:      //une diagonale d�cal�e de 3 cases vers le bas de la premi�re bissectrice
    {
        y = ((rand()%60)/10);
        coord = assignation_schema_lvl_4(x, y, diagonale);
        break;
    }
    }
    return coord;
}

/*==============================================================================
   On cr�e la fonction qui va g�rer les coordonn�es de tir hors schema
==============================================================================*/

Sortie * tir(Coordonnees * coordonnee_tir_IA, Coordonnees * tir_touche_IA,
             int compteur_schema)
{
    int x = rand()%10;
    int y = rand()%10;
    int verif = 0;
    int boucle = 0;

    Coordonnees * pointeur = NULL;
    Coordonnees * coord = NULL;

    Sortie * out = malloc(sizeof(Sortie));

    while (verif != 1)
    {
        pointeur = coordonnee_tir_IA;    //on repart au d�but de la liste � chaque fois

        while (pointeur != NULL && boucle != 1)
        {
// si les coordonn�es ont d�j� �t� pillon�es, on en retire et on recommence la v�rification depuis le d�but

            if (pointeur->x == x && pointeur->y == y)
            {
                x = rand()%10;
                y = rand()%10;
                boucle = 1;
            }

            else
                pointeur = pointeur->suivant;
        }

        if (pointeur == NULL && boucle == 0)   // si elles n'ont pas �t� tir�es, on les ajoutent � la liste
        {
            coordonnee_tir_IA = insertionEnTete(coordonnee_tir_IA, x, y);
            verif = 1;
            out->liste_tir_IA = coordonnee_tir_IA;
            out->liste_touche_IA = tir_touche_IA;
            out->compteur_schema = compteur_schema;

            coord = insertionEnTete(coord, x, y);
            out->coord = coord;
            return out;
        }
        else
            boucle = 0;
    }
    return NULL;
}

/*==============================================================================
   On cr�e la fonction qui g�re l'ensemble des tirs dans le sch�ma de l'IA LVL 4
==============================================================================*/
Sortie * schema_IA_lvl_4(Coordonnees * coordonnee_tir_IA,
                         Coordonnees * tir_touche_IA,
                         Coordonnees * emplacement_bateau_joueur,
                         int compteur_schema, Coordonnees * possibilite,
                         int nb_possibilite)
{
    emplacement_bateau_joueur = emplacement_bateau_joueur;
    Coordonnees * pointeur = NULL;
    Coordonnees * coord = NULL;
    Coordonnees * coord_temp = NULL;

    Sortie * out = malloc(sizeof(Sortie));


    int x;
    int y;
    int i;

    int compteur = 0;
    int diagonale;
    int verif = 0;
    int boucle = 0;

    if (compteur_schema < 44)
    {
        while (verif != 1)
        {
            // on tire une diagonale al�atoire et on tire suivant cette diagonale
            i = (nb_possibilite+1)*10;
            if (i != 0)
            {
                diagonale = (rand()%i)/10;
                coord_temp = def_diagonale(diagonale);
                x = coord_temp->x;
                y = coord_temp->y;
            }

            pointeur = coordonnee_tir_IA;    //on repart au d�but de la liste � chaque fois


            while (pointeur != NULL && boucle != 1)
            {
                // si les coordonn�es ont d�j� �t� pillon�es, on en retire et on recommence la v�rification depuis le d�but

                //Pour ne pas tomber dans une boucle infinie, si on tire 50 selon une diagonale, si on d�passe cette valeur, on change de diagonale
                if (possibilite != NULL)
                {
                    if (compteur < 50)
                    {
                        if (pointeur->x == x && pointeur->y == y)
                        {
                            coord_temp = def_diagonale(diagonale);
                            x = coord_temp->x;
                            y = coord_temp->y;
                            boucle = 1;
                            compteur++;
                        }

                        else
                            pointeur = pointeur->suivant;
                    }

                    else
                    {
                        possibilite = Suppression(possibilite, diagonale);
                        nb_possibilite--;
                        compteur = 0;
                        pointeur = coordonnee_tir_IA;
                    }
                }
//si on tire 50 cases selon toutes les diagonales et que l'on ne trouve pas de cases libres
//on tire sur case hors sch�ma pour ne pas boucler de mani�re infinie


                else
                {
                    out = tir(coordonnee_tir_IA, tir_touche_IA,
                              compteur_schema);
                    return out;
                }
            }

            if (pointeur == NULL && boucle == 0)   // si elles n'ont pas �t� tir�es, on les ajoutent � la liste
            {
                coordonnee_tir_IA = insertionEnTete(coordonnee_tir_IA, x, y);
                verif = 1;
                out->liste_tir_IA = coordonnee_tir_IA;
                out->liste_touche_IA = tir_touche_IA;

                coord = insertionEnTete(coord, x, y);
                out->coord = coord;

                compteur_schema++;
                out->compteur_schema = compteur_schema;
                return out;
            }

            else
                boucle = 0;
        }
    }
    else
        out = tir(coordonnee_tir_IA, tir_touche_IA, compteur_schema);


    return out;
}

/*==============================================================================
   On cr�e la fonction qui g�rera l'ensemble des tirs de l'IA
==============================================================================*/

Sortie * gestion_coordonnees_tir_IA_4(Coordonnees * coordonnee_tir_IA,
                                      Coordonnees * tir_touche_IA,
                                      Coordonnees * emplacement_bateau_joueur,
                                      Coordonnees * possibilite,
                                      int nb_possibilite, int compteur_schema)
{
    Coordonnees * coord = NULL;
    Coordonnees * reference = NULL;

    Sortie * out_temp = malloc(sizeof(Sortie));//temporaire
    Sortie * out = malloc(sizeof(Sortie));//on d�finit la structure de sortie

    int temp = 0;


    while (coord == NULL)
    {
//si on a pas de bateau ennemi en cours de destruction ou que l'on commence la partie, on tire al�atoirement une case

        if ((coordonnee_tir_IA == NULL) || (tir_touche_IA == NULL))
        {
            //on fait appel � la fonction qui g�re le tir dans le sch�m� puis on r�cup�re les diff�rents �l�ments

            out_temp = schema_IA_lvl_4(coordonnee_tir_IA, tir_touche_IA,
                                       emplacement_bateau_joueur,
                                       compteur_schema, possibilite,
                                       nb_possibilite);
            coordonnee_tir_IA = out_temp->liste_tir_IA;
            tir_touche_IA = out_temp->liste_touche_IA;
            coord = out_temp->coord;
            compteur_schema = out_temp->compteur_schema;
        }


        else //si on a un bateau ennemi entam�
        {
            coord = annihilation_4(coordonnee_tir_IA, tir_touche_IA,
                                   emplacement_bateau_joueur, temp, coord); //on cherche des coordonn�es de tir optimis�
            if (coord != NULL)
                coordonnee_tir_IA = insertionEnTete(coordonnee_tir_IA, coord->x,
                                                    coord->y);

            else //si il n'y a pas de coordonn�es, i-e, qu'on a atteint une extr�mit�
            {
                temp = 1;//permet d'indiquer qu'il faut chercher des coordonn�es en cons�quence
                reference = tir_touche_IA;//on prend en r�f�rence le premire tir touch�
                while (reference != NULL)
                {
                    coord = reference;
                    reference = reference->suivant;
                }

                coord = annihilation_4(coordonnee_tir_IA, tir_touche_IA,
                                       emplacement_bateau_joueur, temp, coord); //on tire des coords
                if (coord != NULL)
                    coordonnee_tir_IA = insertionEnTete(coordonnee_tir_IA,
                                                        coord->x, coord->y);
                else //si y a toujours pas de coord, on a �limin� l'int�gralit� du bateau donc on vide la liste de tir touch�
                {
                    coord = NULL;
                    tir_touche_IA = ultimateSuppr(tir_touche_IA);
                }
            }
        }
    }
    out->liste_tir_IA = coordonnee_tir_IA;
    out->liste_touche_IA = tir_touche_IA;
    out->compteur_schema = compteur_schema;
    return out;
}

/*==============================================================================
   On d�finit la fonction qui g�re le fonctionnement global de l'IA LVL1
==============================================================================*/

Sortie * IA_LVL_4(int compteur_bateau_touche_IA, char tableau_joueur[][10],
                  Coordonnees * emplacement_bateau_IA,
                  Coordonnees * coordonnee_tir_IA,
                  Coordonnees * emplacement_bateau_joueur,
                  Coordonnees * tir_touche_IA,
                  Coordonnees * possibilite, int nb_possibilite,
                  int compteur_schema, Joueur * bateau, char * chemin,
                  Joueur * bateau_complet)
{
    emplacement_bateau_IA = emplacement_bateau_IA;
    Sortie * temp = malloc(sizeof(Sortie));//on d�finit la structure de sortie
    int touche = 0;
    Sortie * out = gestion_coordonnees_tir_IA_4(coordonnee_tir_IA,
                                                tir_touche_IA,
                                                emplacement_bateau_joueur,
                                                possibilite, nb_possibilite,
                                                compteur_schema); //l'IA tire

    coordonnee_tir_IA = out->liste_tir_IA;   //on r�cup�re les coordonn�es de tir
    tir_touche_IA = out->liste_touche_IA;   //on r�cup�re les coordonn�es qui touche
    compteur_schema = out->compteur_schema;

    int x = coordonnee_tir_IA->x;
    int y = coordonnee_tir_IA->y;

    touche = verif_bateau_joueur(emplacement_bateau_joueur, x, y); //on v�rifie si le tir touche
    bateau_complet = verif_destruction(bateau_complet, bateau, x, y, chemin);

    if (touche == 1)
    {
        tir_touche_IA = insertionEnTete(tir_touche_IA, x, y); // on ajoute la coordonn�e � la liste de celle touch�e
        tableau_joueur[y][x] = 'R'; //s'il touche, on place une croix rouge dans le tableau du joueur
        compteur_bateau_touche_IA++;  //on augmente le compteur de touche permettant de d�finir la victoire de l'IA
    }

    else
        tableau_joueur[y][x] = 'B'; //sinon une croix blanche

    temp->liste_tir_IA = coordonnee_tir_IA;
    temp->liste_touche_IA = tir_touche_IA;
    temp->compteur_touche = compteur_bateau_touche_IA;
    temp->compteur_schema = compteur_schema;
    temp->nb_case_restante = 0;
    temp->cases_restantes = NULL;
    temp->bateau_complet = bateau_complet;

    return temp;
}


