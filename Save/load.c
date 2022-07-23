
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../IA/base.h"
#include "../Affichage/fonction_affichage.h"
#include "save.h"
#include "load.h"

/*==================================================================
Fonction permettant de remplir une structure des infos des saveslot
====================================================================*/

Infos_saveslot_sortie * get_info(Saveslots_Info * SSinfo, Saveslots_Info * SSinfo_tail, char * file)
{
    Infos_saveslot_sortie * sortie = malloc(sizeof(Infos_saveslot_sortie));

    FILE * savefile = fopen(file, "r");
    size_t len;
    if (savefile == NULL)
    {
        printf("Erreur, impossible de charger la partie.\n");
        free(savefile);
        return NULL;
    }
    fseek(savefile, 0, SEEK_SET);
    char * buf = malloc(100 * sizeof(char));
    Saveslots_Info * new_SSinfo = malloc(sizeof(Saveslots_Info));
    if (new_SSinfo == NULL)
        return NULL;

    fgets(buf, 100, savefile);
    new_SSinfo->saveslot_number = buf[9] - 48;
    fgets(buf, 100, savefile);
    new_SSinfo->time = strdup(buf);
    len = strlen(new_SSinfo->time);
    new_SSinfo->time[len-1] = '\0';
    fgets(buf, 100, savefile);
    new_SSinfo->pseudo_ennemi = strdup(buf);
    len = strlen(new_SSinfo->pseudo_ennemi);
    new_SSinfo->pseudo_ennemi[len-1] = '\0';
    fgets(buf, 100, savefile);
    new_SSinfo->lvl_IA = atoi(buf);
    new_SSinfo->suivant = NULL;
    if (SSinfo_tail != NULL)
        SSinfo_tail->suivant = new_SSinfo;
    SSinfo_tail = new_SSinfo;
    if (SSinfo == NULL)
        SSinfo = SSinfo_tail;


    int ret = fclose(savefile);
    if(ret != 0)
        printf("ERREUR D ACCES !");

    sortie->SSinfo = SSinfo;
    sortie->SSinfo_tail = SSinfo_tail;
    return sortie;
}
/*=======================================================
Fonction gérant la récup globale des infos des saveslots
=========================================================*/

Saveslots_Info * get_saveslots_info(char * chemin)
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
    int verif;
    while(compteur < 10)
    {
        switch(compteur)//on vérifie si chaque emplacement est remplie ou non et on récupère en conséquence les infos
        {
        case 0 :
            strcpy(save, "savefile_0.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save0);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 1 :
            strcpy(save, "savefile_1.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save1);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 2 :
            strcpy(save, "savefile_2.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save2);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 3 :
            strcpy(save, "savefile_3.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save3);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 4 :
            strcpy(save, "savefile_4.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save4);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 5 :
            strcpy(save, "savefile_5.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save5);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 6 :
            strcpy(save, "savefile_6.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save6);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 7 :
            strcpy(save, "savefile_7.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save7);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 8 :
            strcpy(save, "savefile_8.txt");
            verif = verif_saveslot(chemin, save);
            if(verif == 1)
            {
                out = get_info(SSinfo, SSinfo_tail, save8);
                SSinfo = out->SSinfo;
                SSinfo_tail = out->SSinfo_tail;
            }
            break;
        case 9 :
            strcpy(save, "savefile_9.txt");
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

/*======================================================
Fonction permettant d'extraire les strcuture coordonnee
========================================================*/

Coordonnees * get_coord(Coordonnees * coord, char * buf)
{
    if (strcmp(buf, "NULL\n") == 0)
        return NULL;
    Coordonnees * coord_tail = coord;
    char * x = malloc(3);
    char * y = malloc(3);
    char * xy = strtok(buf, " ");

    while (xy != NULL)
    {
        int i = 0;
        int j = 0;

        while (xy[i] != ';')
        {
            x[i] = xy[i];
            i++;
        }
        x[i] = '\0';
        i++;
        while (xy[i] != '\0')
        {
            y[j] = xy[i];
            i++;
            j++;
        }
        y[j] = '\0';
        Coordonnees *new_coord = malloc(sizeof(Coordonnees));
        if (new_coord == NULL) //si le malloc a �chou�
            return NULL;
        new_coord->x = atoi(x);
        new_coord->y = atoi(y);
        new_coord->suivant = NULL;
        if (coord_tail != NULL) //seulement si on avait d�j� une queue
             coord_tail->suivant = new_coord; //on fait attention que le suivant de la queue actuelle pointe vers la future queue
        coord_tail = new_coord; //la nouvelle liste devient la nouvelle queue
        if (coord == NULL)
            coord = coord_tail;

        xy = strtok(NULL, " ");
    }

    free(x);
    free(y);
    free(xy);
    return coord;
}

/*=========================================================
Fonction permettant de load une partie
==========================================================*/

int load_save(int save_number, char * chemin, Save * ssave, char * chemin_langue)
{
    char * savefile_name = malloc(100 * sizeof(char));
    char erreur[100] = { "" };
    strcpy(savefile_name, chemin);
    strcpy(erreur, chemin_langue);
    strcat(erreur, "erreur_load.txt");
    switch(save_number)
    {
        case 0 :
            strcat(savefile_name, "savefile_0.txt");
            break;
        case 1 :
            strcat(savefile_name, "savefile_1.txt");
            break;
        case 2 :
            strcat(savefile_name, "savefile_2.txt");
            break;
        case 3 :
            strcat(savefile_name, "savefile_3.txt");
            break;
        case 4 :
            strcat(savefile_name, "savefile_4.txt");
            break;
        case 5 :
            strcat(savefile_name, "savefile_5.txt");
            break;
        case 6 :
            strcat(savefile_name, "savefile_6.txt");
            break;
        case 7 :
            strcat(savefile_name, "savefile_7.txt");
            break;
        case 8 :
            strcat(savefile_name, "savefile_8.txt");
            break;
        case 9 :
            strcat(savefile_name, "savefile_9.txt");
            break;
    }

    FILE * savefile = fopen(savefile_name, "rt");
    if (savefile == NULL)
    {
        affichage_texte(erreur);
        free(savefile_name);
        return -1;
    }

    fseek(savefile, 0, SEEK_SET);
    char * buf = malloc(1000 * sizeof(char));
    size_t len;

//on remplit la structure de toute les données lues

    fgets(buf, 1000, savefile);//on retir l'indication de saveslot
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
    ssave->nb_case_restante = atoi(buf);
    fgets(buf, 1000, savefile);
    ssave->compteur_schema = atoi(buf);
    fgets(buf, 1000, savefile);
    ssave->compteur_bateau_touche_IA = atoi(buf);
    fgets(buf, 1000, savefile);
    ssave->compteur_joueur = atoi(buf);
    fgets(buf, 1000, savefile);
    ssave->temps_jeu = atoi(buf);

    fgets(buf, 1000, savefile);
    ssave->verif_bateau_joueur->PA = get_coord(ssave->verif_bateau_joueur->PA, buf);

    fgets(buf, 1000, savefile);
    ssave->verif_bateau_joueur->C = get_coord(ssave->verif_bateau_joueur->C, buf);
    fgets(buf, 1000, savefile);
    ssave->verif_bateau_joueur->SM = get_coord(ssave->verif_bateau_joueur->SM, buf);
    fgets(buf, 1000, savefile);
    ssave->verif_bateau_joueur->CT = get_coord(ssave->verif_bateau_joueur->CT, buf);
    fgets(buf, 1000, savefile);
    ssave->verif_bateau_joueur->T = get_coord(ssave->verif_bateau_joueur->T, buf);

    fgets(buf, 1000, savefile);
    ssave->verif_bateau_IA->PA = get_coord(ssave->verif_bateau_IA->PA, buf);
    fgets(buf, 1000, savefile);
    ssave->verif_bateau_IA->C = get_coord(ssave->verif_bateau_IA->C, buf);
    fgets(buf, 1000, savefile);
    ssave->verif_bateau_IA->SM = get_coord(ssave->verif_bateau_IA->SM, buf);
    fgets(buf, 1000, savefile);
    ssave->verif_bateau_IA->CT = get_coord(ssave->verif_bateau_IA->CT, buf);
    fgets(buf, 1000, savefile);
    ssave->verif_bateau_IA->T = get_coord(ssave->verif_bateau_IA->T, buf);

    fgets(buf, 1000, savefile);
    ssave->bateau_joueur->PA = get_coord(ssave->bateau_joueur->PA, buf);
    fgets(buf, 1000, savefile);
    ssave->bateau_joueur->C = get_coord(ssave->bateau_joueur->C, buf);
    fgets(buf, 1000, savefile);
    ssave->bateau_joueur->SM = get_coord(ssave->bateau_joueur->SM, buf);
    fgets(buf, 1000, savefile);
    ssave->bateau_joueur->CT = get_coord(ssave->bateau_joueur->CT, buf);
    fgets(buf, 1000, savefile);
    ssave->bateau_joueur->T = get_coord(ssave->bateau_joueur->T, buf);

    fgets(buf, 1000, savefile);
    ssave->bateau_IA->PA = get_coord(ssave->bateau_IA->PA, buf);
    fgets(buf, 1000, savefile);
    ssave->bateau_IA->C = get_coord(ssave->bateau_IA->C, buf);
    fgets(buf, 1000, savefile);
    ssave->bateau_IA->SM = get_coord(ssave->bateau_IA->SM, buf);
    fgets(buf, 1000, savefile);
    ssave->bateau_IA->CT = get_coord(ssave->bateau_IA->CT, buf);
    fgets(buf, 1000, savefile);
    ssave->bateau_IA->T = get_coord(ssave->bateau_IA->T, buf);


    fgets(buf, 1000, savefile);
    ssave->emplacement_bateau_joueur = get_coord(ssave->emplacement_bateau_joueur,
                                                 buf);
    fgets(buf, 1000, savefile);
    ssave->emplacement_bateau_IA = get_coord(ssave->emplacement_bateau_IA, buf);
    fgets(buf, 1000, savefile);
    ssave->liste_tir_joueur = get_coord(ssave->liste_tir_joueur, buf);
    fgets(buf, 1000, savefile);
    ssave->coordonnee_tir_IA = get_coord(ssave->coordonnee_tir_IA, buf);
    fgets(buf, 1000, savefile);
    ssave->tir_touche_IA = get_coord(ssave->tir_touche_IA, buf);
    fgets(buf, 1000, savefile);
    ssave->cases_restantes = get_coord(ssave->cases_restantes, buf);
    fgets(buf, 1000, savefile);

    fclose(savefile);
    free(buf);
    free(savefile_name);
    return 0;
}
