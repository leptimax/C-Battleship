
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include "../IA/base.h"
#include "../Affichage/fonction_affichage.h"
#include "save.h"

/*=======================================================
Fonction permettant de vérifier si un saveslot existe
=======================================================*/

int verif_saveslot(char * chemin, char * savefile_name)
{
    DIR * rep = opendir(chemin); //permet d'accéder à l'ensemble des éléments à cette adresse
    if (rep != NULL)
    {
        struct dirent * ent;
        while ((ent = readdir(rep)) != NULL)
        {

            if(strcmp(savefile_name, ent->d_name) == 0) //si le fichier existe déjà, on l'indique
            {
                return 1;
            }

        }
        closedir(rep);
    }
    return 0;
}

/*============================================================
Fonction permettant de sauvegarer les structures coordonnées
==============================================================*/

void save_coord(FILE * savefile, Coordonnees * coord)
{
    if (coord == NULL)
    {
        fprintf(savefile, "%s\n", "NULL");
        return;
    }
    while (coord->suivant != NULL)
    {
        fprintf(savefile, "%d;%d ", coord->x, coord->y);
        coord = coord->suivant;
    }
    fprintf(savefile, "%d;%d\n", coord->x, coord->y);
}

/* Fonction permettant de sauvegarder les structures Joueurs*/

void save_joueur(FILE * savefile, Joueur * player)
{
    save_coord(savefile, player->PA);
    save_coord(savefile, player->C);
    save_coord(savefile, player->SM);
    save_coord(savefile, player->CT);
    save_coord(savefile, player->T);
}

/*===============================================================
Fonction permettant de créer les saveslot
================================================================*/

void make_saveslot(FILE * file, int save_number, Save * ssave)
{
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

//===============================================================
//info descriptrice
    fprintf(file, "Game num.%d\n", save_number);
    fprintf(file, "%d/%d/%d %d:%d\n", timeinfo->tm_mday, timeinfo->tm_mon+1,
            timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min);
//=====================================================================

    fprintf(file, "%s\n", ssave->pseudo_ennemi);
    fprintf(file, "%d\n%d\n%d\n%d\n%d\n%d\n", ssave->lvl_IA, ssave->nb_case_restante,
            ssave->compteur_schema, ssave->compteur_bateau_touche_IA, ssave->compteur_joueur,
            0);

    save_joueur(file, ssave->verif_bateau_joueur);
    save_joueur(file, ssave->verif_bateau_IA);
    save_joueur(file, ssave->bateau_joueur);
    save_joueur(file, ssave->bateau_IA);

    save_coord(file, ssave->emplacement_bateau_joueur);
    save_coord(file, ssave->emplacement_bateau_IA);
    save_coord(file, ssave->liste_tir_joueur);
    save_coord(file, ssave->coordonnee_tir_IA);
    save_coord(file, ssave->tir_touche_IA);
    save_coord(file, ssave->cases_restantes);
}

/*=================================================
Fonction permettant d'écraser un saveslot
==================================================*/

int replace_savefile(char * file, int save_number, Save * ssave, char * chemin)
{
    char temp[100] = { "" };
    strcpy(temp, chemin);

    strcat(temp, "temp.txt");

    FILE * tete = fopen(temp, "w");
    if(tete ==  NULL)
        return -1;

    make_saveslot(tete, save_number, ssave);

    fclose(tete);
    remove(file);
    rename(temp, file);
    return 0;
}

/*===========================================
Fonction gérant la sauvegarde du jeu
===========================================*/

int save_game(int save_number, Save * ssave, char * chemin, char * chemin_langue)
{
    char savefile_name[100] = { "" };
    char chemin_verif[100] = { "" };
    int choix = -1;
    char ch[10] = { "" };
    char save[100] = { "" };

    char saveslot_existant[100] = { "" };
    char erreur[100] = { "" };

    strcpy(saveslot_existant, chemin_langue);
    strcpy(erreur, chemin_langue);

    strcat(saveslot_existant, "saveslot_existant.txt");
    strcat(erreur, "erreur.txt");

    strcpy(savefile_name, chemin);

    int verif;

    strcpy(chemin_verif,savefile_name);

    switch(save_number)//on cree le nom du saveslot
    {
    case 0 :
        strcat(savefile_name, "savefile_0.txt");
        strcpy(save, "savefile_0.txt");
        break;
    case 1 :
        strcat(savefile_name, "savefile_1.txt");
        strcpy(save, "savefile_1.txt");
        break;
    case 2 :
        strcat(savefile_name, "savefile_2.txt");
        strcpy(save, "savefile_2.txt");
        break;
    case 3 :
        strcat(savefile_name, "savefile_3.txt");
        strcpy(save, "savefile_3.txt");
        break;
    case 4 :
        strcat(savefile_name, "savefile_4.txt");
        strcpy(save, "savefile_4.txt");
        break;
    case 5 :
        strcat(savefile_name, "savefile_5.txt");
        strcpy(save, "savefile_5.txt");
        break;
    case 6 :
        strcat(savefile_name, "savefile_6.txt");
        strcpy(save, "savefile_6.txt");
        break;
    case 7 :
        strcat(savefile_name, "savefile_7.txt");
        strcpy(save, "savefile_7.txt");
        break;
    case 8 :
        strcat(savefile_name, "savefile_8.txt");
        strcpy(save, "savefile_8.txt");
        break;
    case 9 :
        strcat(savefile_name, "savefile_9.txt");
        strcpy(save, "savefile_9.txt");
        break;
    }
    
    verif = verif_saveslot(chemin_verif, save);//on vérifie qu'il n'existe pas
    if (verif == 0)
    {
        FILE * savefile = fopen(savefile_name, "r+t");
        if (savefile == NULL)
        {
            savefile = fopen(savefile_name, "w+t");
        }
        if (savefile == NULL)
        {
            printf("Erreur, impossible de sauvegarder la partie.\n");
            return -1;
        }

        make_saveslot(savefile, save_number, ssave);
        fclose(savefile);
    }
    else//si il existe on demande si l'utilisateur veut l'ecraser
    {
        cls();
        affichage_texte(saveslot_existant);
        //scanf("%d", &choix);
        while(choix > 2 || choix < 1)
        {
            fgets(ch, 10, stdin);
            choix = atoi(ch);
            scanf("%d", &choix);
            if(choix > 2 || choix < 1)
            {
                cls();
                affichage_texte(erreur);
                sleep(2);
                cls();
            }
        }
        if (choix == 1)
            replace_savefile(savefile_name, save_number, ssave, chemin_verif);
        else
            return 0;

    }

    return 0;
}

/*===================================================
Fonction permettant de supprimer un saveslot
===================================================*/

int delete_saveslot(int numero_saveslot, char * chemin)
{
    char chemin_supp[100];
    strcpy(chemin_supp, chemin);

    switch(numero_saveslot)
    {
    case 0 :
        strcat(chemin_supp, "savefile_0.txt");
        break;
    case 1 :
        strcat(chemin_supp, "savefile_1.txt");
        break;
    case 2 :
        strcat(chemin_supp, "savefile_2.txt");
        break;
    case 3 :
        strcat(chemin_supp, "savefile_3.txt");
        break;
    case 4 :
        strcat(chemin_supp, "savefile_4.txt");
        break;
    case 5 :
        strcat(chemin_supp, "savefile_5.txt");
        break;
    case 6 :
        strcat(chemin_supp, "savefile_6.txt");
        break;
    case 7 :
        strcat(chemin_supp, "savefile_7.txt");
        break;
    case 8 :
        strcat(chemin_supp, "savefile_8.txt");
        break;
    case 9 :
        strcat(chemin_supp, "savefile_9.txt");
        break;
    }
    remove(chemin_supp);
    return 0;
}

/*=====================================
Fonction gérant la quicksabe
=====================================*/

int quicksave(Save * ssave, char* chemin, char * chemin_langue)
{
    char vide_buffer[100];
    char saveslot_plein[100] = { "" };
    char chemin_erreur[100] = { "" };

    strcpy(saveslot_plein, chemin_langue);
    strcpy(chemin_erreur, chemin_langue);

    strcat(chemin_erreur, "erreur.txt");
    strcat(saveslot_plein, "saveslot_plein.txt");


    char save0[100] = { "" };
    char save1[100] = { "" };
    char save2[100] = { "" };
    char save3[100] = { "" };
    char save4[100] = { "" };
    char save5[100] = { "" };
    char save6[100] = { "" };
    char save7[100] = { "" };
    char save8[100] = { "" };
    char save9[100] = { "" };
    char save[100] = { "" };

    strcpy(save0, chemin);
    strcpy(save1, chemin);
    strcpy(save2, chemin);
    strcpy(save3, chemin);
    strcpy(save4, chemin);
    strcpy(save5, chemin);
    strcpy(save6, chemin);
    strcpy(save7, chemin);
    strcpy(save8, chemin);
    strcpy(save9, chemin);

    strcat(save0, "savefile_0.txt");
    strcat(save1, "savefile_1.txt");
    strcat(save2, "savefile_2.txt");
    strcat(save3, "savefile_3.txt");
    strcat(save4, "savefile_4.txt");
    strcat(save5, "savefile_5.txt");
    strcat(save6, "savefile_6.txt");
    strcat(save7, "savefile_7.txt");
    strcat(save8, "savefile_8.txt");
    strcat(save9, "savefile_9.txt");

    int compteur = 0;
    int verif = 1;
    FILE * file = NULL;
    while(verif == 1 && compteur < 10)//on cherche un slot libre
    {
        switch(compteur)
        {
        case 0 :
            strcpy(save, "savefile_0.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save0, "w");
                make_saveslot(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 1 :
            strcpy(save, "savefile_1.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save1, "w");
                make_saveslot(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 2 :
            strcpy(save, "savefile_2.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save2, "w");
                make_saveslot(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 3 :
            strcpy(save, "savefile_3.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save3, "w");
                make_saveslot(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 4 :
            strcpy(save, "savefile_4.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save4, "w");
                make_saveslot(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 5 :
            strcpy(save, "savefile_5.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save5, "w");
                make_saveslot(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 6 :
            strcpy(save, "savefile_6.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save6, "w");
                make_saveslot(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 7 :
            strcpy(save, "savefile_7.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save7, "w");
                make_saveslot(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 8 :
            strcpy(save, "savefile_8.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save8, "w");
                make_saveslot(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 9 :
            strcpy(save, "savefile_9.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save9, "w");
                make_saveslot(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        }

        compteur ++;
    }

    int choix;
    int boucle = 1;
    while(boucle)//on affiche la demande d'ecrasement
    {
         cls();
         affichage_texte(saveslot_plein);
         scanf("%d", &choix);

         if (choix != 1 && choix != 2)
         {
             cls();
             affichage_texte(chemin_erreur);
             sleep(2);
             cls();
         }
         else
            boucle = 0;
    }
    cls();
    fgets(vide_buffer, 100, stdin);
    return choix;
}

/*===============================================================
Fonction permettant de déterminer la liste des emplacement libre
=================================================================*/

int * liste_save(char * chemin)
{
    int * save = malloc(11 * sizeof(int));
    for(int i = 0; i < 11; i++)
        save[i] = 0;

    char save0[100] = { "" };
    char save1[100] = { "" };
    char save2[100] = { "" };
    char save3[100] = { "" };
    char save4[100] = { "" };
    char save5[100] = { "" };
    char save6[100] = { "" };
    char save7[100] = { "" };
    char save8[100] = { "" };
    char save9[100] = { "" };

    strcpy(save0, "savefile_0.txt");
    strcpy(save1, "savefile_1.txt");
    strcpy(save2, "savefile_2.txt");
    strcpy(save3, "savefile_3.txt");
    strcpy(save4, "savefile_4.txt");
    strcpy(save5, "savefile_5.txt");
    strcpy(save6, "savefile_6.txt");
    strcpy(save7, "savefile_7.txt");
    strcpy(save8, "savefile_8.txt");
    strcpy(save9, "savefile_9.txt");


 int compteur = 0;

 while(compteur < 10)
 {
    switch(compteur)
    {
    case 0 :
        save[compteur] = verif_saveslot(chemin, save0);
        break;
    case 1 :
        save[compteur] = verif_saveslot(chemin, save1);
        break;
    case 2 :
        save[compteur] = verif_saveslot(chemin, save2);
        break;
    case 3 :
        save[compteur] = verif_saveslot(chemin, save3);
        break;
    case 4 :
        save[compteur] = verif_saveslot(chemin, save4);
        break;
    case 5 :
        save[compteur] = verif_saveslot(chemin, save5);
        break;
    case 6 :
        save[compteur] = verif_saveslot(chemin, save6);
        break;
    case 7 :
        save[compteur] = verif_saveslot(chemin, save7);
        break;
    case 8 :
        save[compteur] = verif_saveslot(chemin, save8);
        break;
    case 9 :
        save[compteur] = verif_saveslot(chemin, save9);
        break;
    }
    compteur ++;
 }

    return save;
}

/*================================================
Fonctions gérant les affichages des slots dispo
=================================================*/

void affichage_save(int * save, Saveslots_Info * SSinfo, char * chemin)
{
    int i = 0;
    char chemin_emplacement[100] = { "" };
    char chemin_choix[100] = { "" };
    char retour[100] = { "" };

    strcpy(chemin_choix, chemin);
    strcpy(chemin_emplacement, chemin);
    strcpy(retour, chemin);

    strcat(chemin_emplacement, "emplacement_vide.txt");
    strcat(chemin_choix, "choix_emplacement_save.txt");
    strcat(retour, "choix_suppr_save.txt");

    affichage_texte(chemin_choix);

    while (i != 10)
    {
        if (save[i] == 1)
        {
            printf("%d - %s %s %d ", SSinfo->saveslot_number, SSinfo->time,
               SSinfo->pseudo_ennemi, SSinfo->lvl_IA);

            printf("\n");

            i++;
            SSinfo = SSinfo->suivant;
        }
        else
        {
            printf("%d - ",i);
            affichage_texte(chemin_emplacement);
            printf("\n");
            i++;
        }
    }
    printf("\n");
    affichage_texte(retour);
}

void affichage_save_suppr(int * save, Saveslots_Info * SSinfo, char * chemin)
{
    int i = 0;
    char chemin_emplacement[100] = { "" };
    char chemin_choix[100] = { "" };
    char retour[100] = { "" };

    strcpy(chemin_choix, chemin);
    strcpy(chemin_emplacement, chemin);
    strcpy(retour, chemin);

    strcat(chemin_emplacement, "emplacement_vide.txt");
    strcat(chemin_choix, "choix_emplacement_save_suppr.txt");
    strcat(retour, "retour_suppr_save.txt");

    affichage_texte(chemin_choix);

    while (i != 10)
    {
        if (save[i] == 1)
        {
            printf("%d - %s %s %d ", SSinfo->saveslot_number, SSinfo->time,
               SSinfo->pseudo_ennemi, SSinfo->lvl_IA);

            printf("\n");

            i++;
            SSinfo = SSinfo->suivant;
        }
        else
        {
            printf("%d - ",i);
            affichage_texte(chemin_emplacement);
            printf("\n");
            i++;
        }
    }
    printf("\n");
    affichage_texte(retour);
}

void affichage_quicksave(int * save, Saveslots_Info * SSinfo, char * chemin)
{
    int i = 0;
    char chemin_emplacement[100] = { "" };
    char chemin_choix[100] = { "" };
    char retour[100] = { "" };

    strcpy(chemin_choix, chemin);
    strcpy(chemin_emplacement, chemin);
    strcpy(retour, chemin);

    strcat(chemin_choix, "choix_emplacement_quicksave.txt");

    affichage_texte(chemin_choix);

    while (i != 10)
    {
        if (save[i] == 1)
        {
            printf("%d - %s %s %d ", SSinfo->saveslot_number, SSinfo->time,
               SSinfo->pseudo_ennemi, SSinfo->lvl_IA);

            printf("\n");

            i++;
            SSinfo = SSinfo->suivant;
        }
        else
        {
            printf("%d - ",i);
            affichage_texte(chemin_emplacement);
            printf("\n");
            i++;
        }
    }
    printf("\n");

}

