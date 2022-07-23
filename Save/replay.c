#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../IA/base.h"
#include "save.h"
#include "load.h"
#include "replay.h"
#include "../Affichage/hit.h"
#include "../Affichage/fonction_affichage.h"
#include "../Parametres&Langues/fonctions/gestion_couleur.h"
#include "../Parametres&Langues/fonctions/parametre_langue.h"

/*===================================================================
Fonction permettant de r�cup�rer les infos du fichier replay
====================================================================*/

Saveslots_Info * get_saveslots_info_replay(char * chemin)
{
    Saveslots_Info * SSinfo_tail = NULL;
    Saveslots_Info * SSinfo = NULL;
    Infos_saveslot_sortie * out = NULL;;


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

    strcat(save0, "replayfile_0.txt");
    strcat(save1, "replayfile_1.txt");
    strcat(save2, "replayfile_2.txt");
    strcat(save3, "replayfile_3.txt");
    strcat(save4, "replayfile_4.txt");
    strcat(save5, "replayfile_5.txt");
    strcat(save6, "replayfile_6.txt");
    strcat(save7, "replayfile_7.txt");
    strcat(save8, "replayfile_8.txt");
    strcat(save9, "replayfile_9.txt");

    int compteur = 0;
    int verif;
    while(compteur < 10)
    {
//on v�rifie les fichiers existants et on remplit un pointeur de l'ensemble des infos d�crivant chaque fichier
        switch(compteur)
        {
        case 0 :
            strcpy(save, "replayfile_0.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save0);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 1 :
            strcpy(save, "replayfile_1.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save1);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 2 :
            strcpy(save, "replayfile_2.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save2);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 3 :
            strcpy(save, "replayfile_3.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save3);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 4 :
            strcpy(save, "replayfile_4.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save4);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 5 :
            strcpy(save, "replayfile_5.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save5);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 6 :
            strcpy(save, "replayfile_6.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save6);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 7 :
            strcpy(save, "replayfile_7.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save7);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 8 :
            strcpy(save, "replayfile_8.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save8);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 9 :
            strcpy(save, "replayfile_9.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save9);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        }

        compteur ++;
    }
    return SSinfo;
}



/*=================================================================
            Fonction de sauvegarde de replay
==================================================================*/

int save_replay(Save_replay * ssave, char * chemin, char * chemin_langue)
{
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

    strcat(save0, "replayfile_0.txt");
    strcat(save1, "replayfile_1.txt");
    strcat(save2, "replayfile_2.txt");
    strcat(save3, "replayfile_3.txt");
    strcat(save4, "replayfile_4.txt");
    strcat(save5, "replayfile_5.txt");
    strcat(save6, "replayfile_6.txt");
    strcat(save7, "replayfile_7.txt");
    strcat(save8, "replayfile_8.txt");
    strcat(save9, "replayfile_9.txt");

    int compteur = 0;
    int verif = 1;
    FILE * file = NULL;
    while(verif == 1 && compteur < 10)//tant qu'on a pas trouver un emplacement vide ou qu'on a pas atteint la limite de save
    {
        switch(compteur)//si on tombe sur un slot vide, on le remplit
        {
        case 0 :
            strcpy(save, "replayfile_0.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save0, "w");
                make_saveslot_replay(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 1 :
            strcpy(save, "replayfile_1.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save1, "w");
                make_saveslot_replay(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 2 :
            strcpy(save, "replayfile_2.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save2, "w");
                make_saveslot_replay(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 3 :
            strcpy(save, "replayfile_3.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save3, "w");
                make_saveslot_replay(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 4 :
            strcpy(save, "replayfile_4.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save4, "w");
                make_saveslot_replay(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 5 :
            strcpy(save, "replayfile_5.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save5, "w");
                make_saveslot_replay(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 6 :
            strcpy(save, "replayfile_6.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save6, "w");
                make_saveslot_replay(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 7 :
            strcpy(save, "replayfile_7.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save7, "w");
                make_saveslot_replay(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 8 :
            strcpy(save, "replayfile_8.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save8, "w");
                make_saveslot_replay(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        case 9 :
            strcpy(save, "replayfile_9.txt");
            verif = verif_saveslot(chemin, save);
            if(verif != 1)
            {
                file = fopen(save9, "w");
                make_saveslot_replay(file, compteur, ssave);
                fclose(file);
                return 0;
            }
            break;
        }

        compteur ++;
    }

//si il n'y a plus de place, on �crase la save la plus vienne et on remet � jour la liste
    replace_replayfile(chemin, ssave);
    return 0;
}

/*=================================================================
    Fonction permettant de mettre � jour les saveslot
=================================================================*/

int modif_nom(char * nom, int nb, char * temp)
{
    FILE * file = fopen(nom, "r");
    FILE * tmp = fopen(temp, "w");
    int caractere;
    if (file == NULL)
        return -1;
    char buf[100];
    fgets(buf, 100, file);
    fprintf(tmp, "Game num.%d\n", nb);
    caractere = fgetc(file);
    while(caractere != EOF)
    {
            fputc(caractere, tmp);
            caractere = fgetc(file);
    }

    fclose(file);
    fclose(tmp);
    remove(nom);
    rename(temp, nom);
    return 0;

}
/*===============================================================
    Fonction permettant de g�rer le remplacement d'un saveslot
================================================================*/

int replace_replayfile(char * chemin, Save_replay * save )
{
    char save_suppr[100];
    char temp[100];
    strcpy(temp, chemin);
    strcat(temp, "temp.txt");
    strcpy(save_suppr, chemin);
    strcat(save_suppr, "replayfile_9.txt");
    remove(save_suppr);//on supprime la save la plus ancienne

    char replay0[100];
    char replay1[100];
    char replay2[100];
    char replay3[100];
    char replay4[100];
    char replay5[100];
    char replay6[100];
    char replay7[100];
    char replay8[100];

    strcpy(replay0, chemin);
    strcpy(replay1, chemin);
    strcpy(replay2, chemin);
    strcpy(replay3, chemin);
    strcpy(replay4, chemin);
    strcpy(replay5, chemin);
    strcpy(replay6, chemin);
    strcpy(replay7, chemin);
    strcpy(replay8, chemin);

    strcat(replay0, "replayfile_0.txt");
    strcat(replay1, "replayfile_1.txt");
    strcat(replay2, "replayfile_2.txt");
    strcat(replay3, "replayfile_3.txt");
    strcat(replay4, "replayfile_4.txt");
    strcat(replay5, "replayfile_5.txt");
    strcat(replay6, "replayfile_6.txt");
    strcat(replay7, "replayfile_7.txt");
    strcat(replay8, "replayfile_8.txt");

//pour chaque save existante restante, on incr�mente de 1 leur num�ro descripteur et leur nom

    printf("%s, %s", replay8,temp);
    modif_nom(replay8, 9, temp);
    rename(replay8, save_suppr);
    sleep(10);
    modif_nom(replay7, 8, temp);
    rename(replay7, replay8);
    modif_nom(replay6, 7, temp);
    rename(replay6, replay7);
    modif_nom(replay5, 6, temp);
    rename(replay5, replay6);
    modif_nom(replay4, 5, temp);
    rename(replay4, replay5);
    modif_nom(replay3, 4, temp);
    rename(replay3, replay4);
    modif_nom(replay2, 3, temp);
    rename(replay2, replay3);
    modif_nom(replay1, 2, temp);
    rename(replay1, replay2);
    modif_nom(replay0, 1, temp);
    rename(replay0, replay1);

//puis on recr�er un saveslot dans l'emplacement lib�rer

    FILE * file = fopen(replay0, "w");
    if(file == NULL)
        return -1;

    make_saveslot_replay(file, 0, save);
    fclose(file);
    return 0;

}
/*=====================================================
Fonction permettant de cr�er les saveslot
======================================================*/

void make_saveslot_replay(FILE * file, int save_number, Save_replay * ssave)
{
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    fprintf(file, "Game num.%d\n", save_number);
    fprintf(file, "%d/%d/%d %d:%d\n", timeinfo->tm_mday, timeinfo->tm_mon+1,
            timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min);
    fprintf(file, "%s\n", ssave->pseudo_ennemi);
    fprintf(file, "%d\n%d\n%d\n", ssave->lvl_IA, ssave->nb_coup,
            ssave->victoire);
    save_coord(file, ssave->emplacement_bateau_joueur);
    save_coord(file, ssave->emplacement_bateau_IA);
    save_coord(file, ssave->liste_tir_joueur);
    save_coord(file, ssave->coordonnee_tir_IA);
}

/*=======================================================
Fonction permettant de charger le replay
=======================================================*/

int load_replay(char * chemin, Save_replay * ssave, int save_number)
{
    char savefile_name[100];
    strcpy(savefile_name, chemin);

    switch(save_number)
    {
        case 0 :
            strcat(savefile_name, "replayfile_0.txt");
            break;
        case 1 :
            strcat(savefile_name, "replayfile_1.txt");
            break;
        case 2 :
            strcat(savefile_name, "replayfile_2.txt");
            break;
        case 3 :
            strcat(savefile_name, "replayfile_3.txt");
            break;
        case 4 :
            strcat(savefile_name, "replayfile_4.txt");
            break;
        case 5 :
            strcat(savefile_name, "replayfile_5.txt");
            break;
        case 6 :
            strcat(savefile_name, "replayfile_6.txt");
            break;
        case 7 :
            strcat(savefile_name, "replayfile_7.txt");
            break;
        case 8 :
            strcat(savefile_name, "replayfile_8.txt");
            break;
        case 9 :
            strcat(savefile_name, "replayfile_9.txt");
            break;
    }
    FILE * savefile = fopen(savefile_name, "rt");
    if (savefile == NULL)
    {
        printf("Erreur, impossible de charger la partie.\n");
        return -1;
    }

    fseek(savefile, 0, SEEK_SET);
    char * buf = malloc(1000 * sizeof(char));
    size_t len;

    fgets(buf, 1000, savefile); //on enl�ve l'indication de replay

    fgets(buf, 1000, savefile);
    ssave->time = strdup(buf);
    len = strlen(ssave->time);
    ssave->time[len-1] = '\0';
    fgets(buf, 1000, savefile);
    ssave->pseudo_ennemi = strdup(buf);
    len = strlen(ssave->pseudo_ennemi);
    ssave->pseudo_ennemi[len-1] = '\0';
    fgets(buf, 1000, savefile);
    ssave->lvl_IA = atoi(buf);
    fgets(buf, 1000, savefile);
    ssave->nb_coup = atoi(buf);
    fgets(buf, 1000, savefile);
    ssave->victoire = atoi(buf);
    fgets(buf, 1000, savefile);
    ssave->emplacement_bateau_joueur = get_coord(ssave->emplacement_bateau_joueur,
                                                 buf);

    fgets(buf, 1000, savefile);
    ssave->emplacement_bateau_IA = get_coord(ssave->emplacement_bateau_IA,
                                             buf);
    fgets(buf, 1000, savefile);
    ssave->liste_tir_joueur = get_coord(ssave->liste_tir_joueur, buf);
    fgets(buf, 1000, savefile);
    ssave->coordonnee_tir_IA = get_coord(ssave->coordonnee_tir_IA, buf);
    fgets(buf, 1000, savefile);

    fclose(savefile);
    return 0;



}

/*================================
Fonction g�rant le replay
=================================*/


Color * replay(char * chemin, Save_replay * donnee_replay, Color * couleur_applicable, char * pseudo_joueur,
            int langue, char * chemin_profil)
{
    char tableau_joueur[10][10];
    char tableau_ennemi[10][10];


    char chemin_pause[100] = { "" };
    char indication_replay[100] = { "" };
    char indication_replay_1[100] = { "" };
    char indication_replay_2[100] = { "" };
    char menu_pause[100] = { "" };
    char erreur[100] = { "" };

    int choix;
    Color * couleur_temp = NULL;

    strcpy(chemin_pause, chemin);
    strcpy(indication_replay, chemin);
    strcpy(menu_pause, chemin);
    strcpy(indication_replay_1, chemin);
    strcpy(erreur, chemin);
    strcpy(indication_replay_2, chemin);


    strcat(chemin_pause, "pause_replay.txt");
    strcat(indication_replay, "indication_replay.txt");
    strcat(menu_pause, "menu_pause_replay.txt");
    strcat(indication_replay_1, "indication_replay_1.txt");
    strcat(erreur, "erreur.txt");
    strcat(indication_replay_2, "indication_replay_2.txt");

    int boucle = 1;

    Coordonnees * tir_joueur_temp = NULL;
    Coordonnees * tir_IA_temp = NULL;
    Coordonnees * p = NULL;

    int tour = 0;
    int coup = compteur_coup(donnee_replay->coordonnee_tir_IA);
    coup = coup + donnee_replay->nb_coup;
    int boucle2 = 1;
    int compteur = 0;
    while(boucle)// � chaque tour on r�initialise int�gralement les tableaux
    {
        boucle2 = 1;
        compteur = 0;
        cls();
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                tableau_joueur[i][j] = ' ';
                tableau_ennemi[i][j] = ' ';
            }
        }
        p = donnee_replay->emplacement_bateau_joueur;
        while(p != NULL)
        {
            tableau_joueur[p->y][p->x] = 'V';
            p = p->suivant;
        }

        p = tir_joueur_temp;
        while (p != NULL)
        {
            if(verification(donnee_replay->emplacement_bateau_IA, p->x-1, p->y-1))//on v�rifie si ca touche
                tableau_ennemi[p->y-1][p->x-1] = 'R';
            else
                tableau_ennemi[p->y-1][p->x-1] = 'B';
            p = p->suivant;
        }
        p = tir_IA_temp;
        while (p != NULL)
        {
            if(verification(donnee_replay->emplacement_bateau_joueur, p->x, p->y))
                tableau_joueur[p->y][p->x] = 'R';
            else
                tableau_joueur[p->y][p->x] = 'B';
            p = p->suivant;
        }

        //on affiche les tableaux

        affichage_texte(chemin_pause);
        affichage(tableau_joueur, tableau_ennemi, pseudo_joueur, donnee_replay->pseudo_ennemi,couleur_applicable);

        if(tour == coup)//si on a atteint le nb de coup max de la partie
        {
            affichage_texte(indication_replay_2);
            while(boucle2)
            {
                choix = selection_replay();
                switch (choix)
                {
                case 81 :
                case 113:
                    if(donnee_replay->victoire == 1) //si le joueur gagne dans la partie
                    {
                         p = tir_joueur_temp;
                        while(p->suivant != NULL)
                        {
                            p = p->suivant;
                            compteur++;
                        }
                        donnee_replay->liste_tir_joueur = insertionEnTete(donnee_replay->liste_tir_joueur, p->x, p->y);
                        tir_joueur_temp = Suppression(tir_joueur_temp, compteur);
                        tour--;
                        boucle2 = 0;
                    }
                    else //si l'ia gagne dans la partie
                    {
                         p = tir_IA_temp;
                        while(p->suivant != NULL)
                        {
                            p = p->suivant;
                            compteur++;
                        }
                        donnee_replay->coordonnee_tir_IA = insertionEnTete(donnee_replay->coordonnee_tir_IA, p->x, p->y);
                        tir_IA_temp = Suppression(tir_IA_temp, compteur);
                        tour--;
                        boucle2 = 0;
                    }

                    break;
                case 80 :
                case 112:
                    cls();
                    couleur_temp = pause_replay(chemin, chemin_profil, langue, couleur_applicable);
                    cls();

                    if(couleur_temp == NULL)
                        return couleur_applicable;
                    else
                    {
                        couleur_applicable = couleur_temp;
                        affichage_texte(chemin_pause);
                        affichage(tableau_joueur, tableau_ennemi, pseudo_joueur, donnee_replay->pseudo_ennemi, couleur_applicable);
                        affichage_texte(indication_replay_1);
                    }

                    break;
                case 27:
                    return couleur_applicable;
                    break;
                default :
                    affichage_texte(erreur);
                    break;

                }
            }

        }
        if(tour % 2 == 0 || tour == 0)//si le tour est pair, c'est qu'on est au tour du joueur
        {
            if (tour == 0)//premier tour de jeu
            {

                affichage_texte(indication_replay_1);
                while(boucle2)
                {
                    choix = selection_replay();//on demande le choix du joueur
                    switch (choix)
                    {
                    case 68 :
                    case 100://si on avance dans la partie on ajoute les coord dans la liste temporaire et on les supprime de l'autre
                        tir_joueur_temp = insertionEnQueu(tir_joueur_temp, donnee_replay->liste_tir_joueur->x, donnee_replay->liste_tir_joueur->y);
                        donnee_replay->liste_tir_joueur = Suppression(donnee_replay->liste_tir_joueur, 0);
                        tour++;
                        boucle2 = 0;
                        break;
                    case 80 :
                    case 112://si il veut la pause
                        cls();
                        couleur_temp = pause_replay(chemin, chemin_profil, langue, couleur_applicable);
                        cls();

                        if(couleur_temp == NULL)
                            return couleur_applicable;
                        else
                        {
                            couleur_applicable = couleur_temp;
                            affichage_texte(chemin_pause);
                            affichage(tableau_joueur, tableau_ennemi, pseudo_joueur, donnee_replay->pseudo_ennemi, couleur_applicable);
                            affichage_texte(indication_replay_1);
                        }

                        break;
                    case 27:
                        return couleur_applicable;
                        break;
                    default :
                        affichage_texte(erreur);
                        break;

                    }
                }
            }
            else//autre tour
            {
                affichage_texte(indication_replay);
                while(boucle2)
                {
                    choix = selection_replay();
                    switch (choix)
                    {
                    case 68 :
                    case 100:
                        tir_joueur_temp = insertionEnQueu(tir_joueur_temp, donnee_replay->liste_tir_joueur->x, donnee_replay->liste_tir_joueur->y);
                        donnee_replay->liste_tir_joueur = Suppression(donnee_replay->liste_tir_joueur, 0);
                        tour++;
                        boucle2 = 0;
                        break;
                    case 80 :
                    case 122:
                        cls();
                        couleur_temp = pause_replay(chemin, chemin_profil, langue, couleur_applicable);
                        cls();

                        if(couleur_temp == NULL)
                            return couleur_applicable;
                        else
                        {
                            couleur_applicable = couleur_temp;
                            affichage_texte(chemin_pause);
                            affichage(tableau_joueur, tableau_ennemi, pseudo_joueur, donnee_replay->pseudo_ennemi, couleur_applicable);
                            affichage_texte(indication_replay);
                        }

                        break;
                    case 27:
                        return couleur_applicable;
                        break;
                    case 81 :
                    case 113://si on recule dans la partie on supprime les coord de la liste temporaire et on les remets dans la liste d'origine
                        p = tir_IA_temp;
                        while(p->suivant != NULL)
                        {
                            p = p->suivant;
                            compteur++;
                        }
                        donnee_replay->coordonnee_tir_IA = insertionEnTete(donnee_replay->coordonnee_tir_IA, p->x, p->y);
                        tir_IA_temp = Suppression(tir_IA_temp, compteur);
                        tour--;
                        boucle2 = 0;
                        break;
                    default :
                        affichage_texte(erreur);
                        break;

                    }
                }
            }

        }
        else //tour de l'ia
        {
            affichage_texte(indication_replay);
            while(boucle2)
            {
                choix = selection_replay();
                switch (choix)
                {
                case 68 :
                case 100:
                    tir_IA_temp = insertionEnQueu(tir_IA_temp, donnee_replay->coordonnee_tir_IA->x, donnee_replay->coordonnee_tir_IA->y);
                    donnee_replay->coordonnee_tir_IA = Suppression(donnee_replay->coordonnee_tir_IA, 0);
                    tour++;
                    boucle2 = 0;
                    break;
                case 80 :
                case 122:
                    cls();
                    couleur_temp = pause_replay(chemin, chemin_profil, langue, couleur_applicable);
                    cls();
                    if(couleur_temp == NULL)
                        return couleur_applicable;
                    else
                    {
                        couleur_applicable = couleur_temp;
                        affichage_texte(chemin_pause);
                        affichage(tableau_joueur, tableau_ennemi, pseudo_joueur, donnee_replay->pseudo_ennemi, couleur_applicable);
                        affichage_texte(indication_replay);
                    }

                    break;
                case 27:
                    return couleur_applicable;
                    break;
                case 81 :
                case 113:
                    p = tir_joueur_temp;
                    while(p->suivant != NULL)
                    {
                        p = p->suivant;
                        compteur++;
                    }
                    donnee_replay->liste_tir_joueur = insertionEnTete(donnee_replay->liste_tir_joueur, p->x, p->y);
                    tir_joueur_temp = Suppression(tir_joueur_temp, compteur);
                    tour--;
                    boucle2 = 0;
                    break;
                default :
                    affichage_texte(erreur);
                    break;

                }
            }
        }

    }
    return couleur_applicable;
}

/*=========================================
Fonction g�rant le menu pause
========================================*/

Color * pause_replay(char * chemin, char * chemin_profil, int langue, Color * couleur_applicable)
{
    char menu[100] = { "" };
    char chemin_option[100] = { "" };
    char chemin_erreur[100] = { "" };

    strcpy(menu, chemin);
    strcpy(chemin_option, chemin);
    strcpy(chemin_erreur, chemin);

    strcat(menu, "menu_pause_replay.txt");
    strcat(chemin_option, "menu_options.txt");
    strcat(chemin_erreur, "erreur.txt");

    int verif = 1;
    int verif2 = 1;
    int x,y;

    char c[3];
    char vide_buffer[100];


    while(verif)
    {
        affichage_texte(menu);
        fgets(c, 3, stdin);
        x = atoi(c);
        switch (x)
        {
        case 1:
            verif = 0;                                //Continuer
            break;

        case 2:
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
        case 3:
            return NULL;
            break;
        case 4:
            exit(EXIT_SUCCESS);
            break;
        default:                                  //Faute de frappe
            cls();
            affichage_texte(chemin_erreur);
            break;
        }
    }
    return couleur_applicable;
}

/* fonction permettant la selection*/
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64


#include <conio.h>
int selection_replay()
{
    int test1 = 0;
    while(!test1)
        test1 = kbhit();
    int x = getch();
    return x;
}
#else
#include "../Systeme/khbit.h"

int selection_replay()
{

int activer=1;

mode_raw(activer);


    int test1 = 0;
    while(!test1)
        test1 = kbhit();
    int x = getch();

mode_raw(!activer);

	return x;
}

#endif // defined
/*===========================================
Fonction permettant de supprimer un saveslot
============================================*/

int delete_saveslot_replay(int save_number, char * chemin)
{
    char chemin_supp[100];
    strcpy(chemin_supp, chemin);

    switch(save_number)
    {
    case 0 :
        strcat(chemin_supp, "replayfile_0.txt");
        break;
    case 1 :
        strcat(chemin_supp, "replayfile_1.txt");
        break;
    case 2 :
        strcat(chemin_supp, "replayfile_2.txt");
        break;
    case 3 :
        strcat(chemin_supp, "replayfile_3.txt");
        break;
    case 4 :
        strcat(chemin_supp, "replayfile_4.txt");
        break;
    case 5 :
        strcat(chemin_supp, "replayfile_5.txt");
        break;
    case 6 :
        strcat(chemin_supp, "replayfile_6.txt");
        break;
    case 7 :
        strcat(chemin_supp, "replayfile_7.txt");
        break;
    case 8 :
        strcat(chemin_supp, "replayfile_8.txt");
        break;
    case 9 :
        strcat(chemin_supp, "replayfile_9.txt");
        break;
    }
    remove(chemin_supp);
    return 0;
}

/*=====================================================
Fonction permettant de d�tecter les emplacements libre
=======================================================*/

int * liste_save_replay(char * chemin)
{
    int * save = malloc(11*sizeof(int));
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

    strcpy(save0, "replayfile_0.txt");
    strcpy(save1, "replayfile_1.txt");
    strcpy(save2, "replayfile_2.txt");
    strcpy(save3, "replayfile_3.txt");
    strcpy(save4, "replayfile_4.txt");
    strcpy(save5, "replayfile_5.txt");
    strcpy(save6, "replayfile_6.txt");
    strcpy(save7, "replayfile_7.txt");
    strcpy(save8, "replayfile_8.txt");
    strcpy(save9, "replayfile_9.txt");


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
