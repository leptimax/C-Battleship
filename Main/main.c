#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../IA/base.h"
#include "../Save/save.h"
#include "../Affichage/fonction_affichage.h"
#include "../Affichage/hit.h"
#include "../Affichage/insert_erase_placement.h"
#include "../Affichage/menu_pause.h"
#include "../Affichage/menus.h"
#include "../Affichage/placement.h"
#include "../Affichage/test_placement.h"
#include "../IA/IA_5.h"
#include "../IA/placement_bateau.h"
#include "jeu.h"
#include "../Profil/creation_dossier.h"
#include "../Profil/profil.h"
#include "../Parametres&Langues/fonctions/determination_dossier_langue.h"
#include "../Parametres&Langues/fonctions/parametre_langue.h"
#include "../Parametres&Langues/fonctions/gestion_couleur.h"
#include "../Parametres&Langues/fonctions/gestion_couleur_annexe.h"
#include "../Parametres&Langues/fonctions/statistique.h"
#include "../Save/replay.h"
#include "../Save/load.h"
#include "../Save/save.h"


int main()
{
    /*On déclare et on initialise l'ensemble des variables, pointeurs ...*/
    srand(time(NULL));
    Coordonnees * emplacement_bateau_IA = NULL;
    Coordonnees * emplacement_bateau_joueur = NULL; // cette liste sera défini dans le main par le joueur !!
    Coordonnees * cases_impossible = NULL;

    Sortie * emplacement_temp = malloc(sizeof(Sortie));

    Menu_temp * choix_menu = malloc(sizeof(Menu_temp));

    Color * couleur_applicable = malloc(sizeof(Color));

    Joueur * bateau_joueur = NULL;

    Coordonnees * liste_tir_joueur = NULL;
    Coordonnees * coordonnee_tir_IA = NULL;
    Coordonnees * tir_touche_IA = NULL;

    Save * donnee_save = malloc(sizeof(Save));

    donnee_save->cases_restantes = NULL;
    donnee_save->coordonnee_tir_IA = NULL;
    donnee_save->emplacement_bateau_IA = NULL;
    donnee_save->emplacement_bateau_joueur = NULL;
    donnee_save->liste_tir_joueur = NULL;
    donnee_save->tir_touche_IA = NULL;
    donnee_save->temps_jeu = 0;

    Save * donnee_load = malloc(sizeof(Save));

    donnee_load->bateau_IA = malloc(sizeof(Joueur));
    donnee_load->bateau_IA->PA = NULL;
    donnee_load->bateau_IA->C = NULL;
    donnee_load->bateau_IA->SM = NULL;
    donnee_load->bateau_IA->CT = NULL;
    donnee_load->bateau_IA->T = NULL;

    donnee_load->bateau_joueur = malloc(sizeof(Joueur));
    donnee_load->bateau_joueur->PA = NULL;
    donnee_load->bateau_joueur->C = NULL;
    donnee_load->bateau_joueur->SM = NULL;
    donnee_load->bateau_joueur->CT = NULL;
    donnee_load->bateau_joueur->T = NULL;

    donnee_load->verif_bateau_IA = malloc(sizeof(Joueur));
    donnee_load->verif_bateau_IA->PA = NULL;
    donnee_load->verif_bateau_IA->C = NULL;
    donnee_load->verif_bateau_IA->SM = NULL;
    donnee_load->verif_bateau_IA->CT = NULL;
    donnee_load->verif_bateau_IA->T = NULL;

    donnee_load->verif_bateau_joueur = malloc(sizeof(Joueur));
    donnee_load->verif_bateau_joueur->PA = NULL;
    donnee_load->verif_bateau_joueur->C = NULL;
    donnee_load->verif_bateau_joueur->SM = NULL;
    donnee_load->verif_bateau_joueur->CT = NULL;
    donnee_load->verif_bateau_joueur->T = NULL;

    donnee_load->cases_restantes = NULL;
    donnee_load->coordonnee_tir_IA = NULL;
    donnee_load->emplacement_bateau_IA = NULL;
    donnee_load->emplacement_bateau_joueur = NULL;
    donnee_load->liste_tir_joueur = NULL;
    donnee_load->tir_touche_IA = NULL;

    Save_replay * donnee_replay = malloc(sizeof(Save_replay));

    donnee_replay->coordonnee_tir_IA = NULL;
    donnee_replay->emplacement_bateau_IA = NULL;
    donnee_replay->emplacement_bateau_joueur = NULL;
    donnee_replay->liste_tir_joueur = NULL;

    int longueur_tableau = 10; //la longueur des tableaux est de 10
    int hauteur_tableau = 10; // la hauteur des tbaleaux est de 10
    char tableau_joueur[longueur_tableau][hauteur_tableau]; //tableau stockant l'emplacement des bateaux/tirs reçu par le joueur
    char tableau_ennemi[longueur_tableau][hauteur_tableau]; //tableau stockant l'emplacement des bateaux/tirs reçu par l'ennemi
    int compteur_bateau_touche_IA = 0;
    int compteur_joueur = 0;
    int choix_menu1;
    int choix_menu2;
    char * pseudo_joueur = malloc(100 * sizeof(char));
    int lvl_IA = 0;
    int langue;
    int temps_depart = clock();
    int numero_save;
    int start = 1;
    int numero_save_suppr;

    /*on prépare les chemins d'accès pour lire les fichiers txt permettant l'affichage du texte en jeu*/

    char * chemin_profil = malloc(100 * sizeof(char));

    char * chemin_language = malloc(100 * sizeof(char));
    char vide_buffer[100];
    char pseudo_adversaire[50] = { "" };

    char retour[100] = { "" };
    char tuto[100] = { "" };
    char bio[100] = { "" };
    char credit[100] = { "" };

    char erreur_save[100] = { "" };
    char EE[100] = { "" };
    char chemin_erreur[100] = { "" };
    char erreur_chargement[100] = { "" };




    langue = language();//on récupère le langage sauvegardé
    chemin_language = chemin_langue(langue); //on récupère le chemin d'accès au bon dossier langue

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

#else

    strcat(chemin_language, "linux/");

#endif

    chemin_profil = menuProfil(chemin_language);// on récupère l'accès au bon profil utilisateur
    fgets(vide_buffer, 100, stdin);//permet de vider le buffer après le choix du profil

    pseudo_joueur = recup_pseudo(chemin_profil);

    couleur_applicable = recup_Color(chemin_profil); //on récupère les couleurs sauvegardé

    strcpy(retour, chemin_language);
    strcpy(tuto, chemin_language);
    strcpy(credit, chemin_language);
    strcpy(erreur_save, chemin_language);
    strcpy(chemin_erreur, chemin_language);
    strcpy(erreur_chargement, chemin_language);
    strcpy(EE, chemin_language);
    strcpy(bio, chemin_language);

    strcat(retour, "retour_stat.txt");
    strcat(erreur_chargement, "erreur_chargement.txt");
    strcat(tuto, "tuto.txt");
    strcat(credit, "credit.txt");
    strcat(erreur_save, "erreur_save.txt");
    strcat(chemin_erreur, "erreur.txt");
    strcat(EE, "EE.txt");
    strcat(bio, "bio.txt");



    Saveslots_Info * info = NULL;

    char chemin_save[100] = { "" };

    strcpy(chemin_save, chemin_profil);

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

    strcat(chemin_save, "Save\\");

#else

    strcat(chemin_save, "Save/");


#endif // defined


    while (1)
    {
        start = 1;
        cls();
        choix_menu = menu(chemin_language); //on affiche le menu principal
        choix_menu1 = choix_menu->x[0];
        choix_menu2 = choix_menu->y[0];
        switch (choix_menu1)
        {
        case 1: //menu jouer
            switch (choix_menu2)
                {
                    case 1: //nouvelle partie
                    {
                        cls();


                        lvl_IA = choix_IA(chemin_language);
                        switch(lvl_IA)
                        {
                        case 1:
                            strcpy(pseudo_adversaire, "Christophe Colomb");
                            break;
                        case 2 :
                            strcpy(pseudo_adversaire, "Edouard Montagu");
                            break;
                        case 3:
                            strcpy(pseudo_adversaire, "Louis Thomas Villaret de Joyeuse");
                            break;
                        case 4:
                            strcpy(pseudo_adversaire, "Gunther Lutjens");
                            break;
                        case 5:
                            strcpy(pseudo_adversaire, "Emma ma Richeloix");
                            break;
                        case 6 :
                            start = 0;
                            break;
                        case 5912 :
                            affichage_texte(bio);
                            fgets(vide_buffer, 100, stdin);
                            start = 0;
                            break;


                        }
                        if(start == 1)
                        {//partie placement bateau joueur :
                            bateau_joueur = initialisation_joueur(tableau_joueur,chemin_language, couleur_applicable);

                            emplacement_bateau_joueur = bateau_joueur->emplacement_complet;

                            emplacement_temp = placement_bateau_IA(emplacement_bateau_IA,
                                                                   cases_impossible);

                            emplacement_bateau_IA = emplacement_temp->coord;

                            jeu(compteur_bateau_touche_IA, compteur_joueur, tableau_joueur,
                                tableau_ennemi, pseudo_joueur, pseudo_adversaire,
                                emplacement_bateau_IA, emplacement_bateau_joueur, lvl_IA, chemin_language,
                                couleur_applicable, chemin_profil, langue, bateau_joueur, emplacement_temp->bateau_complet,
                                donnee_save, temps_depart, liste_tir_joueur, coordonnee_tir_IA, tir_touche_IA);

                            sleep(5);
                        }
                        cls();
                        break;
                    }
                    case 2: //chargement de partie
                    {
                        int boucle = 1;
                        int save;
                        int launch = 1;
                        cls();
                        info = get_saveslots_info(chemin_save);
                        affichage_save(liste_save(chemin_save), info, chemin_language);
                        while(boucle)
                        {
                            scanf("%d", &numero_save);
                            if (numero_save >= 0 && numero_save < 10 ) //choix saveslot
                                {
                                    save = load_save(numero_save, chemin_save, donnee_load, chemin_language);
                                    if (save == 0)
                                        boucle = 0;
                                }
                            else if(numero_save == 10) //suppression saveslot
                            {
                                cls();
                                sleep(1);
                                affichage_save_suppr(liste_save(chemin_save), info, chemin_language);
                                scanf("%d", &numero_save_suppr);
                                if(numero_save_suppr >= 0 && numero_save_suppr < 10)
                                {
                                    delete_saveslot(numero_save_suppr, chemin_save);
                                    info = get_saveslots_info(chemin_save);
                                    cls();
                                    sleep(1);
                                    affichage_save(liste_save(chemin_save), info, chemin_language);
                                }
                                else
                                {
                                    cls();
                                    affichage_save(liste_save(chemin_save), info, chemin_language);
                                }
                            }
                            else if (numero_save == 11)
                            {
                                 boucle = 0;
                                 launch = 0;//permet de ne pas lancer le jeu si on fait retour
                            }

                            else
                            {
                                affichage_texte(chemin_erreur);
                                printf("\n");
                            }


                        }
                        fgets(vide_buffer, 100, stdin);
                        cls();

                        sleep(1);
                        if(launch)
                        {
                            jeu(donnee_load->compteur_bateau_touche_IA, donnee_load->compteur_joueur, tableau_joueur, tableau_ennemi,
                                pseudo_joueur, donnee_load->pseudo_ennemi, donnee_load->emplacement_bateau_IA, donnee_load->emplacement_bateau_joueur,
                                donnee_load->lvl_IA, chemin_language, couleur_applicable, chemin_profil, langue,donnee_load->bateau_joueur,
                                donnee_load->bateau_IA, donnee_save, temps_depart, donnee_load->liste_tir_joueur, donnee_load->coordonnee_tir_IA,
                                donnee_load->tir_touche_IA);
                        }
                        sleep(1);
                        break;
                    }
                    case 3: //replay
                    {
                        cls();
                        int boucle = 1;
                        int save;
                        info = get_saveslots_info_replay(chemin_save);
                        affichage_save(liste_save_replay(chemin_save), info, chemin_language);
                        while(boucle)
                        {
                            scanf("%d",&numero_save);
                            if (numero_save >= 0 && numero_save < 10 )// choix d'une partie à regarder
                                {
                                    sleep(1);
                                    save = load_replay(chemin_save, donnee_replay, numero_save);
                                    if (save == 0)
                                        boucle = 0;
                                    else
                                        affichage_texte(erreur_chargement);
                                }
                             else if(numero_save == 10) // suppression d'un saveslot replay
                            {
                                cls();
                                sleep(1);
                                affichage_save_suppr(liste_save_replay(chemin_save), info, chemin_language);
                                scanf("%d", &numero_save_suppr);
                                if(numero_save_suppr >= 0 && numero_save_suppr < 10)
                                {
                                    delete_saveslot_replay(numero_save_suppr, chemin_save);
                                    info = get_saveslots_info_replay(chemin_save);
                                    cls();
                                    sleep(1);
                                    affichage_save(liste_save_replay(chemin_save), info, chemin_language);
                                }
                                else
                                {
                                    cls();
                                    affichage_save(liste_save_replay(chemin_save), info, chemin_language);
                                }
                            }
                            else if (numero_save == 11)
                            {
                                boucle = 0;
                                start = 0;
                            }
                            else
                            {
                                affichage_texte(chemin_erreur);
                                printf("\n");
                            }

                        }
                        fgets(vide_buffer, 100, stdin);
                        cls();
                        sleep(1);
                    }
                    if(start == 1)
                    {
                        couleur_applicable = replay(chemin_language, donnee_replay, couleur_applicable, pseudo_joueur, langue, chemin_profil);
                        cls();
                        sleep(2);
                    }
                    donnee_replay->coordonnee_tir_IA = NULL;
                    donnee_replay->emplacement_bateau_IA = NULL;
                    donnee_replay->emplacement_bateau_joueur = NULL;
                    donnee_replay->liste_tir_joueur = NULL;
                    break;
                }
            break;
            case 2: //statistique
                cls();
                affichage_statistique(chemin_profil,langue);
                affichage_texte(retour);
                fgets(vide_buffer, 100, stdin);
                break;
            case 3://options
                switch (choix_menu2)
                {
                case 1://couleurs
                    cls();

                    couleur_applicable = option_couleur(langue, chemin_language, chemin_profil);
                    fgets(vide_buffer, 100, stdin);

                    sleep(1);
                    break;
                case 2://langue
                    cls();
                    changement_langue(langue);
                    sleep(2);
                    break;
                }
                break;
            case 4: //affichage du tuto
                cls();
                affichage_texte(tuto);
                affichage_texte(retour);
                fgets(vide_buffer, 100, stdin);
                break;
            case 5: //affichage du credit
                cls();
                affichage_texte(credit);
                affichage_texte(retour);
                fgets(vide_buffer, 100, stdin);
                break;
            case 6 : //changement d'utilisateur
                cls();
                chemin_profil = menuProfil(chemin_language);
                pseudo_joueur = recup_pseudo(chemin_profil);
                couleur_applicable = recup_Color(chemin_profil);
                strcpy(chemin_save, chemin_profil);

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

    strcat(chemin_save, "Save\\");

#else

    strcat(chemin_save, "Save/");

#endif // defined
                fgets(vide_buffer, 100, stdin);
                break;
            case 7: //quitter
                return 0;
                break;
            /*case 300999 : zone réserver pour un easter egg en developpement
                cls();
                affichage_texte();
                fgets(vide_buffer, 100, stdin);
                break;*/
        }
    }
}
