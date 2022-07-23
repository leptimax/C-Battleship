#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "../IA/base.h"
#include "../Save/save.h"
#include "../Affichage/fonction_affichage.h"
#include "../Affichage/hit.h"
#include "../Affichage/menu_pause.h"
#include "../Affichage/menus.h"
#include "../Affichage/placement.h"
#include "../Affichage/test_placement.h"
#include "../IA/IA_1.h"
#include "../IA/IA_2.h"
#include "../IA/IA_3.h"
#include "../IA/IA_4.h"
#include "../IA/IA_5.h"
#include "jeu.h"
#include "../Parametres&Langues/fonctions/statistique.h"
#include "../Save/save.h"
#include "../Save/replay.h"
/*==============================================================================
   On d�finit la fonction permettant d'afficher le tableau du joueur pendant
   l'initialisation
==============================================================================*/

void afficheTableau(char tableau_joueur[10][10], EnsembleC * ensemble, Color * couleur_applicable)
{
    Coordonnees * emplacement_bateau_joueur = NULL;
    Coordonnees * p = NULL;

//on initialise toutes les cases du tableau sur vide repr�sent� par un espace

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            tableau_joueur[i][j] = ' ';
    }

//on rassemble toutes les coordonn�es des bateaux en une seule liste pour faciliter l'affichage dans la grille

    emplacement_bateau_joueur = defEmplacement(ensemble->coord_2,
                                               emplacement_bateau_joueur);
    emplacement_bateau_joueur = defEmplacement(ensemble->coord_3_1,
                                               emplacement_bateau_joueur);
    emplacement_bateau_joueur = defEmplacement(ensemble->coord_3_2,
                                               emplacement_bateau_joueur);
    emplacement_bateau_joueur = defEmplacement(ensemble->coord_4,
                                               emplacement_bateau_joueur);
    emplacement_bateau_joueur = defEmplacement(ensemble->coord_5,
                                               emplacement_bateau_joueur);

//on remplace toutes las cases s�lectionn�es par des cases bateaux

    p = emplacement_bateau_joueur;
    while (p != NULL)
    {
        tableau_joueur[p->y][p->x] = 'V';
        p = p->suivant;
    }

//on vide la liste

    if (emplacement_bateau_joueur != NULL)
        emplacement_bateau_joueur = ultimateSuppr(emplacement_bateau_joueur);


//on affiche enfin la grill

    affichageInitialisation(tableau_joueur, couleur_applicable);

}

/*==============================================================================
   On d�finit la fonction permettant d'initialiser les bateaux du joueur
==============================================================================*/

Joueur * initialisation_joueur(char tableau_joueur[10][10], char * chemin, Color * couleur_applicable)
{
    Joueur * bateau = malloc(sizeof(Joueur));
    bateau->emplacement_complet = NULL;

    char chemin_validation[100] = { "" };
    char chemin_erreur[100] = { "" };

    strcat(chemin_validation, chemin);
    strcat(chemin_erreur, chemin);

    strcat(chemin_validation, "validation_bateau.txt");
    strcat(chemin_erreur, "erreur.txt");

    Taille *liste_long = NULL;              //Liste contenant les tailles restantes a placer

    EnsembleC *ensemble = malloc(sizeof(EnsembleC));

//on initialise toutes les listes qui contiendrons les coordonn�es des bateaux sur NULL pour �viter des probl�mes ult�rieurement

    ensemble->coord_5 = NULL;
    ensemble->coord_4 = NULL;
    ensemble->coord_3_1 = NULL;
    ensemble->coord_3_2 = NULL;
    ensemble->coord_2 = NULL;

    ensemble->coord_5_occupe = NULL;
    ensemble->coord_4_occupe = NULL;
    ensemble->coord_3_1_occupe = NULL;
    ensemble->coord_3_2_occupe = NULL;
    ensemble->coord_2_occupe = NULL;

    Out_boat * out_temp = malloc(sizeof(Out_boat));

//on initialise la liste contenant les bateaux restant � placer

    liste_long = insertion_Taille(liste_long, 0);
    liste_long = insertion_Taille(liste_long, 2);
    liste_long = insertion_Taille(liste_long, 3);
    liste_long = insertion_Taille(liste_long, 4);
    liste_long = insertion_Taille(liste_long, 5);
    liste_long = insertion_Taille(liste_long, 6);

    int taille;
    int stop = 1;
    int stop2 = 1;
    char validation1[100];
    int validation;

//on r�cup�re le choix du bateau a placer

    out_temp = choix_Taille(liste_long, ensemble, tableau_joueur, chemin, couleur_applicable);
    taille = out_temp->longueur;
    liste_long = out_temp->liste_long;
    ensemble = out_temp->liste;

//tant qu'on a pas placer tous les bateaux ET valid� leur emplacement on boucle

    while (stop != 0)
    {
        afficheTableau(tableau_joueur, ensemble, couleur_applicable); //on affiche la grille du joueur avec ces bateaux plac�
        ensemble = choix_Coord(taille, ensemble, chemin); //on r�cup�re les coordonn�es s�lectionn�es par le joueur pour le bateau en cours
        afficheTableau(tableau_joueur, ensemble, couleur_applicable);
        out_temp = choix_Taille(liste_long, ensemble, tableau_joueur, chemin, couleur_applicable);
        taille = out_temp->longueur;
        liste_long = out_temp->liste_long;
        ensemble = out_temp->liste;

//si le joueur choisit de valider l'emplacement de ses bateaux

        if (taille == 7)
        {
            while (stop2 == 1)//tant qu'il ne s�lectionne pas une des 2 options
            {
                affichage_texte(chemin_validation);
                fgets(validation1, 100, stdin);
                validation = atoi(validation1);
                if (validation == 1)
                {
                    stop = 0;
                    stop2 = 0;
                }
                else
                {
                    if (validation != 2)
                        affichage_texte(chemin_erreur);

                    else
                        stop2 = 0;
                }
            }
        }
    }

    bateau->emplacement_complet = defEmplacement(ensemble->coord_2, bateau->emplacement_complet);
    bateau->emplacement_complet = defEmplacement(ensemble->coord_3_1, bateau->emplacement_complet);
    bateau->emplacement_complet = defEmplacement(ensemble->coord_3_2, bateau->emplacement_complet);
    bateau->emplacement_complet = defEmplacement(ensemble->coord_4, bateau->emplacement_complet);
    bateau->emplacement_complet = defEmplacement(ensemble->coord_5, bateau->emplacement_complet);

    bateau->PA = ensemble->coord_5;
    bateau->C = ensemble->coord_4;
    bateau->SM = ensemble->coord_3_1;
    bateau->CT = ensemble->coord_3_2;
    bateau->T = ensemble->coord_2;

    return bateau;
}

/*==============================================================================
   On d�finit la fonction permettant de choisir le niveau de difficult� de l'IA
==============================================================================*/

int choix_IA(char * chemin)
{
    char choix1[100];
    int choix;
    int boucle = 0;

    char chemin_IA[100] = { "" };

    strcat(chemin_IA, chemin);

    strcat(chemin_IA, "IA.txt");

    while (boucle == 0)
    {
        cls();
        affichage_texte(chemin_IA);
        fgets(choix1, 100, stdin);
        choix = atoi(choix1);

        if ((0 < choix && choix < 7) || (choix == 5912))
            boucle = 1;
        else
        {
            printf("choix invalide !");
            sleep(1);
        }
    }
    cls();

    return choix;
}

/*==============================================================================
   Fonction permettant l'initialisation des variables indispensables aux IA
==============================================================================*/

Sortie * initialisation_variable_IA()
{
    Sortie * out = malloc(sizeof(Sortie));

    /*Variable utile pour l'IA 3*/
    Coordonnees * cases_restantes = NULL;

    cases_restantes = insertionEnTete(cases_restantes, 1, 1);
    cases_restantes = insertionEnTete(cases_restantes, 1, 3);
    cases_restantes = insertionEnTete(cases_restantes, 1, 5);
    cases_restantes = insertionEnTete(cases_restantes, 1, 7);
    cases_restantes = insertionEnTete(cases_restantes, 1, 9);

    cases_restantes = insertionEnTete(cases_restantes, 3, 1);
    cases_restantes = insertionEnTete(cases_restantes, 3, 3);
    cases_restantes = insertionEnTete(cases_restantes, 3, 5);
    cases_restantes = insertionEnTete(cases_restantes, 3, 7);
    cases_restantes = insertionEnTete(cases_restantes, 3, 9);

    cases_restantes = insertionEnTete(cases_restantes, 5, 1);
    cases_restantes = insertionEnTete(cases_restantes, 5, 3);
    cases_restantes = insertionEnTete(cases_restantes, 5, 5);
    cases_restantes = insertionEnTete(cases_restantes, 5, 7);
    cases_restantes = insertionEnTete(cases_restantes, 5, 9);

    cases_restantes = insertionEnTete(cases_restantes, 7, 1);
    cases_restantes = insertionEnTete(cases_restantes, 7, 3);
    cases_restantes = insertionEnTete(cases_restantes, 7, 5);
    cases_restantes = insertionEnTete(cases_restantes, 7, 7);
    cases_restantes = insertionEnTete(cases_restantes, 7, 9);

    cases_restantes = insertionEnTete(cases_restantes, 9, 1);
    cases_restantes = insertionEnTete(cases_restantes, 9, 3);
    cases_restantes = insertionEnTete(cases_restantes, 9, 5);
    cases_restantes = insertionEnTete(cases_restantes, 9, 7);
    cases_restantes = insertionEnTete(cases_restantes, 9, 9);

    /*variable utile pour l'IA 4*/

    Coordonnees * possibilite = NULL;

    for (int i = 0; i < 6; i++)
    {
        possibilite = insertionEnTete(possibilite, i, 0);
    }

    out->cases_restantes = cases_restantes;
    out->coord = possibilite;
    return out;
}

/*================================================================
Fonction permettant la gestion de l'ensemble du jeu
=================================================================*/

int jeu(int compteur_bateau_touche_IA, int compteur_joueur,
        char tableau_joueur[10][10],
        char tableau_ennemi[10][10], char pseudo_joueur[], char pseudo_ennemi[],
        Coordonnees * emplacement_bateau_IA,
        Coordonnees * emplacement_bateau_joueur, int lvl_IA, char * chemin, Color * couleur_applicable,
        char * chemin_profil, int langue, Joueur * bateau_joueur, Joueur * emplacement, Save * donnee_save,
        int temps_depart, Coordonnees * liste_tir_joueur, Coordonnees * coordonnee_tir_IA, Coordonnees * tir_touche_IA)
{

//initialisation des tabeaux en fonctions des donn�es (en cas de load) sinon on charge juste le tableau du joueur
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            tableau_joueur[i][j] = ' ';
            tableau_ennemi[i][j] = ' ';
        }
    }
    Coordonnees * p = emplacement_bateau_joueur;
    while (p != NULL)
    {
        tableau_joueur[p->y][p->x] = 'V';
        p = p->suivant;
    }
    p = liste_tir_joueur;
    while (p != NULL)
    {
        if(verification(emplacement_bateau_IA, p->x-1, p->y-1))//on "rejoue" la partie en cas de loading
            tableau_ennemi[p->y-1][p->x-1] = 'R';
        else
            tableau_ennemi[p->y-1][p->x-1] = 'B';
        p = p->suivant;
    }
    p = coordonnee_tir_IA;
    while (p != NULL)
    {
        if(verification(emplacement_bateau_joueur, p->x, p->y))
            tableau_joueur[p->y][p->x] = 'R';
        else
            tableau_joueur[p->y][p->x] = 'B';
        p = p->suivant;
    }

    Sortie * temp = malloc(sizeof(Sortie));
    Sortie * initialisation = malloc(sizeof(Sortie));

    Menu_temp * coord = malloc(sizeof(Menu_temp));

    Coordonnees * possibilite = malloc(sizeof(Coordonnees));
    Coordonnees * cases_restantes = malloc(sizeof(Coordonnees));



//on initialise les variables n�cessaires aux IA

    initialisation = initialisation_variable_IA();

    possibilite = initialisation->coord;
    cases_restantes = initialisation->cases_restantes;

    Joueur * bateau_complet = malloc(sizeof(Joueur));
    bateau_complet->PA = NULL;
    bateau_complet->C = NULL;
    bateau_complet->CT = NULL;
    bateau_complet->SM = NULL;
    bateau_complet->T = NULL;
    bateau_complet->emplacement_complet = NULL;

    Joueur * bateau_complet_joueur = malloc(sizeof(Joueur));
    bateau_complet_joueur->PA = NULL;
    bateau_complet_joueur->C = NULL;
    bateau_complet_joueur->CT = NULL;
    bateau_complet_joueur->SM = NULL;
    bateau_complet_joueur->T = NULL;
    bateau_complet_joueur->emplacement_complet = NULL;


    int x = 0;
    int y = 0;
    int hit = 0;
    int nb_possibilite = 5;
    int resultat;
    int coup;
    int compteur;
    int temps_ref = clock();

    temps_ref = (temps_ref - temps_depart); //d�finition du temps de r�f�rence pour les stats

    char chemin_pause[100] = { "" };
    char chemin_coordonnee_jeu[100] = { "" };
    char victoire[100] = { "" };
    char defaite[100] = { "" };

    strcpy(chemin_pause,chemin);
    strcpy(chemin_coordonnee_jeu,chemin);
    strcpy(victoire,chemin);
    strcpy(defaite,chemin);

    strcat(chemin_pause, "pause.txt");
    strcat(chemin_coordonnee_jeu, "coordonnees_jeu.txt");
    strcat(victoire, "victoire.txt");
    strcat(defaite, "defaite.txt");

    int nb_case_restante = 0;
    int compteur_schema = 0;

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64
    switch(lvl_IA)
    {
    case 1 :
        compteur = 2500000; //environ 40s
        break;
    case 2 :
        compteur = 2000000; //environ 32s
        break;
    case 3 :
        compteur = 1500000; //environ 26s
        break;
    case 4 :
        compteur = 1200000; //environ 20s
        break;
    case 5 :
        compteur = -1; //pas de timer pour ce niveau de difficult�
        break;
    }

#else

    switch(lvl_IA)
    {
    case 1 :
        compteur = 28000000; //environ 40s
        break;
    case 2 :
        compteur = 23000000; //environ 32s
        break;
    case 3 :
        compteur = 18000000; //environ 26s
        break;
    case 4 :
        compteur = 13000000; //environ 20s
        break;
    case 5 :
        compteur = -1; //pas de timer pour ce niveau de difficult�
        break;
    }
#endif
    /*=============================================================
       ============================================================*/

    while (compteur_bateau_touche_IA != 17 && compteur_joueur != 17)
    {
        cls();
        affichage_texte(chemin_pause);
        affichage(tableau_joueur, tableau_ennemi, pseudo_joueur, pseudo_ennemi, couleur_applicable);
        affichage_texte(chemin_coordonnee_jeu);

        //on met � jour � chaque tour les donn�es de sauvegarde

        donnee_save->cases_restantes = cases_restantes;
        donnee_save->coordonnee_tir_IA = coordonnee_tir_IA;
        donnee_save->emplacement_bateau_IA = emplacement_bateau_IA;
        donnee_save->emplacement_bateau_joueur = emplacement_bateau_joueur;
        donnee_save->liste_tir_joueur = liste_tir_joueur;
        donnee_save->tir_touche_IA = tir_touche_IA;
        donnee_save->compteur_schema = compteur_schema;
        donnee_save->lvl_IA = lvl_IA;
        donnee_save->nb_case_restante = nb_case_restante;
        donnee_save->pseudo_ennemi = pseudo_ennemi;
        donnee_save->bateau_IA = emplacement;
        donnee_save->bateau_joueur = bateau_joueur;
        donnee_save->verif_bateau_IA = bateau_complet;
        donnee_save->verif_bateau_joueur = bateau_complet_joueur;
        donnee_save->compteur_bateau_touche_IA = compteur_bateau_touche_IA;
        donnee_save->compteur_joueur = compteur_joueur;
        donnee_save->temps_jeu = difftime(temps_ref,clock());

        //le joueur tir
        coord = Tir(liste_tir_joueur, tableau_joueur, tableau_ennemi,
                    pseudo_joueur, pseudo_ennemi, chemin, couleur_applicable, chemin_profil, langue, donnee_save, temps_ref, compteur);
        x = coord->x[0];
        y = coord->y[0];
        couleur_applicable = coord->couleur;
        sleep(1);
        cls();
        if (x != -1 && y != -1)
        {

            hit = toucherTir(emplacement_bateau_IA, x, y, chemin);//on v�rifie si le tir touche et on affiche les r�sultats
            liste_tir_joueur = insertionEnQueu(liste_tir_joueur, x, y);
            bateau_complet_joueur = verif_destruction_ennemi(bateau_complet_joueur, emplacement, x-1, y-1, chemin);
            if (hit == 1)
            {
                tableau_ennemi[y-1][x-1] = 'R';
                compteur_joueur++;
            }
            else
                tableau_ennemi[y-1][x-1] = 'B';
        }
        else
        {
            liste_tir_joueur = insertionEnQueu(liste_tir_joueur, x, y);//on ins�re les coordonn�es de tir
        }

        cls();


        affichage(tableau_joueur, tableau_ennemi, pseudo_joueur, pseudo_ennemi, couleur_applicable);
        switch (lvl_IA)
        {
        case 1:
            temp = IA_LVL_1(compteur_bateau_touche_IA, tableau_joueur,
                            emplacement_bateau_IA, coordonnee_tir_IA,
                            emplacement_bateau_joueur, bateau_joueur, chemin, bateau_complet);
            break;

        case 2:
            temp = IA_LVL_2(compteur_bateau_touche_IA, tableau_joueur,
                            emplacement_bateau_IA, coordonnee_tir_IA,
                            emplacement_bateau_joueur, tir_touche_IA, bateau_joueur, chemin, bateau_complet);
            break;

        case 3:
            temp = IA_LVL_3(compteur_bateau_touche_IA, tableau_joueur,
                            emplacement_bateau_IA, coordonnee_tir_IA,
                            emplacement_bateau_joueur, tir_touche_IA,
                            cases_restantes, nb_case_restante, bateau_joueur, chemin, bateau_complet);
            break;

        case 4:
            temp = IA_LVL_4(compteur_bateau_touche_IA, tableau_joueur,
                            emplacement_bateau_IA, coordonnee_tir_IA,
                            emplacement_bateau_joueur, tir_touche_IA,
                            possibilite, nb_possibilite,
                            compteur_schema, bateau_joueur, chemin, bateau_complet);

            break;

        case 5:
            temp = IA_LVL_5(compteur_bateau_touche_IA, tableau_joueur,
                            emplacement_bateau_joueur, coordonnee_tir_IA, chemin, bateau_joueur, bateau_complet);
            break;
        }

        compteur_bateau_touche_IA = temp->compteur_touche;
        coordonnee_tir_IA = temp->liste_tir_IA;
        tir_touche_IA = temp->liste_touche_IA;
        cases_restantes = temp->cases_restantes;
        nb_case_restante = temp->nb_case_restante;
        compteur_schema = temp->compteur_schema;
        bateau_complet = temp->bateau_complet;
        sleep(2);
    }
    if(compteur_bateau_touche_IA == 17)
        {
            resultat = 0;
            cls();
            affichage_texte(defaite);
        }
    if (compteur_joueur == 17)
    {
        resultat = 1;
        cls();
        affichage_texte(victoire);
    }

    coup = compteur_coup(liste_tir_joueur); //on r�cup�re le nombre de coup jou�
    int temps_mid = clock();

    float temps_stat = ((temps_mid - temps_ref) + donnee_save->temps_jeu);

    temps_stat = conversion_time(temps_stat);//r�cup�ration du temps de jeu pour les statistiques

    statistique(lvl_IA, resultat, temps_stat, chemin_profil, coup);

    Save_replay * donnee_save_replay = malloc(sizeof(Save_replay));//on enregistre les donn�es pour les replay

    Coordonnees * temporaire = NULL;
    afficher(coordonnee_tir_IA);
    sleep(10);
    while(coordonnee_tir_IA != NULL)
    {
        temporaire = insertionEnTete(temporaire, coordonnee_tir_IA->x, coordonnee_tir_IA->y);
        coordonnee_tir_IA = coordonnee_tir_IA->suivant;
    }

    donnee_save_replay->coordonnee_tir_IA = temporaire;
    donnee_save_replay->emplacement_bateau_IA = emplacement_bateau_IA;
    donnee_save_replay->emplacement_bateau_joueur = emplacement_bateau_joueur;
    donnee_save_replay->liste_tir_joueur = liste_tir_joueur;
    donnee_save_replay->lvl_IA = lvl_IA;
    donnee_save_replay->pseudo_ennemi = pseudo_ennemi;
    donnee_save_replay->nb_coup = coup;
    donnee_save_replay->victoire = resultat;

    char chemin_save[100];
    strcpy(chemin_save, chemin_profil);

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

    strcat(chemin_save, "Save\\");

#else

    strcat(chemin_save, "Save/");


#endif // defined
    save_replay(donnee_save_replay, chemin_save, chemin);//on sauvegarde le replay

    return 0;
}

/*==============================================================
Fonction v�rifiant si le joueur � d�truit un bateau de l'IA
fonctionnement identique � celle v�rifiant la destruction d'un
bateau du joueur
===============================================================*/

Joueur * verif_destruction_ennemi(Joueur * bateau_complet, Joueur * bateau, int x, int y, char * chemin)
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

    strcat(destruction_PA, "destruction_porte_avion_ennemi.txt");
    strcat(destruction_C, "destruction_croiseur_ennemi.txt");
    strcat(destruction_SM, "destruction_sous_marin_ennemi.txt");
    strcat(destruction_CT, "destruction_contre_torpilleur_ennemi.txt");
    strcat(destruction_T, "destruction_torpilleur_ennemi.txt");

    Coordonnees * p = bateau->PA;
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

    p = bateau->C;
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

    p = bateau->SM;
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

    p = bateau->CT;
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

    p = bateau->T;
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
        sleep(2);
        cls();
    }
    if(taille_C == 4)
    {
        cls();
        bateau_complet->C = ultimateSuppr(bateau_complet->C);
        affichage_texte(destruction_C);
        sleep(2);
        cls();
    }
    if(taille_SM == 3)
    {
        cls();
        bateau_complet->SM = ultimateSuppr(bateau_complet->SM);
        affichage_texte(destruction_SM);
        sleep(2);
        cls();
    }
    if(taille_CT == 3)
    {
        cls();
        bateau_complet->CT = ultimateSuppr(bateau_complet->SM);
        affichage_texte(destruction_CT);
        sleep(2);
        cls();
    }
    if(taille_T == 2)
    {
        cls();
        bateau_complet->T = ultimateSuppr(bateau_complet->T);
        affichage_texte(destruction_T);
        sleep(2);
        cls();
    }
    return bateau_complet;


}

/*======================================
Fonction g�rant la conversion du temps
=======================================*/

float conversion_time(float temps)
{
    temps = temps / 100;
    float sortie = temps / 60;
    return sortie;
}
