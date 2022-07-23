#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../IA/base.h"
#include "../Save/save.h"
#include "menu_pause.h"
#include "fonction_affichage.h"
#include "../Save/load.h"
#include "../Parametres&Langues/fonctions/gestion_couleur.h"
#include "../Parametres&Langues/fonctions/parametre_langue.h"
/*=========================================================
Fonction g�rant le menu pause dans le jeu
==========================================================*/

Color * Menu_Pause(char * chemin, char * chemin_profil, int langue, Color * couleur_applicable,
                   Save * donnee_save, int temps_ref)
{

    // on initialise les string permettant d'afficher le texte

    char menu[100] = { "" };
    char chemin_option[100] = { "" };
    char chemin_erreur[100] = { "" };
    char erreur_save[100] = { "" };
    char avertissement_quit[100] = { "" };
    char suppression_save[100] = { "" };
    char chemin_save[100] = { "" };

    strcpy(menu, chemin);
    strcpy(chemin_option, chemin);
    strcpy(chemin_erreur, chemin);
    strcpy(erreur_save, chemin);
    strcpy(avertissement_quit, chemin);
    strcpy(suppression_save, chemin);
    strcpy(chemin_save, chemin_profil);

    strcat(menu, "menu_pause_jeu.txt");
    strcat(chemin_option, "menu_options.txt");
    strcat(chemin_erreur, "erreur.txt");
    strcat(erreur_save, "erreur_save.txt");
    strcat(avertissement_quit, "avertissement_quit.txt");
    strcat(suppression_save, "suppression_save.txt");

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

    strcat(chemin_save, "Save\\");

#else

    strcat(chemin_save, "Save/");


#endif // defined

    int verif = 1;
    int verif2 = 1;
    int x,y;
    int numero_save = 0;
    int numero_save_suppr = 0;
    int boucle = 1;
    int save;
    int quit;
    int quick;

    char c[3];
    char vide_buffer[100];

    Saveslots_Info * info = NULL;

    while(verif)
    {
        boucle = 1;
        affichage_texte(menu);
        fgets(c, 3, stdin);
        x = atoi(c);
        switch (x)
        {
        case 1://continuer
            verif = 0;                                //Continuer
            break;

        case 2://options
            while(verif2)
            {
                cls();
                affichage_texte(chemin_option);
                scanf("%d", &y);
                switch (y)
                {
                case 1:
                    verif = 0;
                    verif2 = 0;
                    cls();

                    couleur_applicable = option_couleur(langue, chemin, chemin_profil);
                    fgets(vide_buffer, 100, stdin);

                    sleep(1);
                    break;
                case 2:
                    fgets(vide_buffer, 100, stdin);
                    verif = 0;
                    verif2 = 0;
                    cls();
                    changement_langue(langue);
                    sleep(1);
                    break;
                case 3:
                    fgets(vide_buffer, 100, stdin);
                    cls();
                    verif2 = 0;
                    break;
                default :
                    fgets(vide_buffer, 100, stdin);
                    cls();
                    affichage_texte(chemin_erreur);
                    sleep(1);
                    cls();
                } //Autres options
            }
            break;
        case 3://sauvegarde
            cls();
            info = get_saveslots_info(chemin_save);
            donnee_save->temps_jeu = temps_ref;
            affichage_save(liste_save(chemin_save), info, chemin);
            while(boucle)
            {
                scanf("%d",&numero_save);
                if (numero_save >= 0 && numero_save < 10 )
                    {
                        save = save_game(numero_save, donnee_save, chemin_save, chemin);
                        if (save == 0)
                            boucle = 0;
                        else
                            affichage_texte(erreur_save);
                    }
                 else if(numero_save == 10)
                {
                    cls();
                    sleep(1);
                    affichage_save_suppr(liste_save(chemin_save), info, chemin);
                    scanf("%d", &numero_save_suppr);
                    if(numero_save_suppr >= 0 && numero_save_suppr < 10)
                    {
                        delete_saveslot(numero_save_suppr,chemin_save);
                        info = get_saveslots_info(chemin_save);
                        cls();
                        sleep(1);
                        affichage_save(liste_save(chemin_save), info, chemin);
                    }
                    else
                    {
                        cls();
                        affichage_save(liste_save(chemin_save), info, chemin);
                    }
                }
                else if (numero_save == 11)
                    boucle = 0;
                else
                {
                    affichage_texte(chemin_erreur);
                    printf("\n");
                }

            }
            fgets(vide_buffer, 100, stdin);
            cls();
            break;
        case 4://quitter
            cls();
            while(boucle)
            {
                 affichage_texte(avertissement_quit);
                 scanf("%d", &quit);
                 if (quit != 1 && quit != 2)
                 {
                     cls();
                     affichage_texte(chemin_erreur);
                     sleep(2);
                     cls();
                 }
                 else if (quit == 1)
                    exit(EXIT_SUCCESS);
                 else
                    boucle = 0;
            }
            fgets(vide_buffer, 100, stdin);
            cls();
            break;
        case 5://quicksave et quitter
            donnee_save->temps_jeu = temps_ref;
            quick = quicksave(donnee_save, chemin_save, chemin);
            switch(quick)
            {
            case -1 :
                affichage_texte(erreur_save);
                break;

            case 0 :
                exit(EXIT_SUCCESS);
                break;
            case 2 :
                break;
            case 1 :
                cls();
                info = get_saveslots_info(chemin_save);
                affichage_quicksave(liste_save(chemin_save), info, chemin);
                while(boucle)
                {
                    scanf("%d",&numero_save);
                    if (numero_save >= 0 && numero_save < 10 )
                        {
                            sleep(1);
                            char file[100];
                            strcpy(file, chemin_save);
                            switch(numero_save)
                            {
                                case 0 :
                                    strcat(file, "savefile_0.txt");
                                    break;
                                case 1 :
                                    strcat(file, "savefile_1.txt");
                                    break;
                                case 2 :
                                    strcat(file, "savefile_2.txt");
                                    break;
                                case 3 :
                                    strcat(file, "savefile_3.txt");
                                    break;
                                case 4 :
                                    strcat(file, "savefile_4.txt");
                                    break;
                                case 5 :
                                    strcat(file, "savefile_5.txt");
                                    break;
                                case 6 :
                                    strcat(file, "savefile_6.txt");
                                    break;
                                case 7 :
                                    strcat(file, "savefile_7.txt");
                                    break;
                                case 8 :
                                    strcat(file, "savefile_8.txt");
                                    break;
                                case 9 :
                                    strcat(file, "savefile_9.txt");
                                    break;
                            }
                            save = replace_savefile(file, numero_save, donnee_save, chemin);
                            if (save == 0)
                                exit(EXIT_SUCCESS);
                            else
                            {
                                affichage_texte(erreur_save);
                                exit(EXIT_SUCCESS);
                            }

                        }
                    else
                    {
                        affichage_texte(chemin_erreur);
                        printf("\n");
                    }

                }
                fgets(vide_buffer, 100, stdin);
                cls();
                break;
            }
            break;
        default:                                  //Faute de frappe
            cls();
            printf("Entree non valide\n\n");
            break;
        }
    }
    return couleur_applicable;
}
