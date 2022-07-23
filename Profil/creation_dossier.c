#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "../IA/base.h"
#include <dirent.h>
#include "creation_dossier.h"
#include "../Affichage/fonction_affichage.h"

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

/*=============================================================
Fonction permettant de cr�er un dossier sous windows et linux
==============================================================*/
void make_directory(char * name)
   {
       mkdir(name);
   }

int verif_directory_user()
{
    DIR * rep = opendir(".\\"); //permet d'acc�der � l'ensemble des �l�ments � cette adresse

    if (rep != NULL)
    {
        struct dirent * ent;
        while ((ent = readdir(rep)) != NULL)
        {
            if(strcmp("User", ent->d_name) == 0) //si le profil existe d�j�, on l'indique
            {
                return 1;
            }

        }
        closedir(rep);
    }
    return 0;
}
/*=======================================================================================
 Fonction permettant de v�rifier que le profil n'existe pas d�j� les profils utilisateur
 ========================================================================================*/

int verif_dossier(char * pseudo)
{
    DIR * rep = opendir(".\\User\\"); //permet d'acc�der � l'ensemble des �l�ments � cette adresse

    if (rep != NULL)
    {
        struct dirent * ent;
        while ((ent = readdir(rep)) != NULL)
        {
            if(strcmp(pseudo, ent->d_name) == 0) //si le profil existe d�j�, on l'indique
            {
                return 1;
            }

        }
        closedir(rep);
    }
    return 0;
}

/*===============================================================
Fonction permettant de cr�er le profil complet d'un utilisateur
================================================================*/

char * creation_dossier(char pseudo[100], char * chemin_langue)
{
    int verif = 0;
    char chemin[100] = { "" };

    char * chemin_sortie = malloc(100 * sizeof(char));

    char chemin_profil[100] = { "" };

    strcpy(chemin_profil, chemin_langue);

    strcat(chemin_profil, "profil_existant.txt");

    strcpy(chemin, ".\\User\\"); //chemin de cr�ation des profils
    strcat(chemin,pseudo); //on ajoute le nom du profil au chemin d'acc�s

    verif = verif_dossier(pseudo); // on v�rifie qu'il n'existe pas d�j�
    if(verif == 0)
    {
        make_directory(chemin);
        char * inter = "\\";
        strcat(chemin, inter);

        char dossier_save[100] = { "" };
        char dossier_param[100] = { "" };
        char dossier_stat[100] = { "" };
        char tuto[100] = { "" };
        char vide_buffer[100];

        strcpy(dossier_param, chemin);
        strcpy(dossier_save, chemin);
        strcpy(dossier_stat, chemin);
        strcpy(tuto, chemin_langue);

        strcat(dossier_param, "Parametres\\");
        strcat(dossier_save, "Save\\");
        strcat(dossier_stat, "Statistiques\\");
        strcat(tuto, "tuto.txt");

        make_directory(dossier_param);
        make_directory(dossier_save);
        make_directory(dossier_stat);

        CreationFichier(dossier_param, "parametres_joueurs.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\parametres_joueurs.txt");
        CreationFichier(dossier_param, "parametres_joueurs_de.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\parametres_joueurs_de.txt");
        CreationFichier(dossier_param, "parametres_joueurs_en.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\parametres_joueurs_en.txt");
        CreationFichier(dossier_param, "parametres_joueurs_es.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\parametres_joueurs_es.txt");
        CreationFichier(dossier_param, "parametres_joueurs_is.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\parametres_joueurs_is.txt");
        CreationFichier(dossier_param, "parametres_joueurs_it.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\parametres_joueurs_it.txt");
        CreationFichier(dossier_param, "parametres_joueurs_ne.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\parametres_joueurs_ne.txt");

        CreationFichier(dossier_stat, "stat_fr.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\stat_fr.txt");
        CreationFichier(dossier_stat, "stat_de.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\stat_de.txt");
        CreationFichier(dossier_stat, "stat_en.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\stat_en.txt");
        CreationFichier(dossier_stat, "stat_es.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\stat_es.txt");
        CreationFichier(dossier_stat, "stat_ne.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\stat_ne.txt");
        CreationFichier(dossier_stat, "stat_is.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\stat_is.txt");
        CreationFichier(dossier_stat, "stat_it.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\stat_it.txt");
        CreationFichier(dossier_stat, "valeur_stat.txt", ".\\Parametres&Langues\\REFERENCE_FILE\\valeur_stat.txt");

        strcpy(chemin_sortie, chemin);
        strcat(chemin, "nom.txt");
        FILE * temp = fopen(chemin, "w");
        fprintf(temp, "%s", pseudo);
        fclose(temp);

        cls();
        affichage_texte(tuto);
        scanf("%s", vide_buffer);


        return chemin_sortie;
    }
    else{
        affichage_texte(chemin_profil);
        sleep(2);
        return "a";
    }

}

void vide_dossier(char * adresse)
{
    int compteur = 0;
    char chemin[100] ={""};
    char chemin_suppr[100] = {""};
    strcat(chemin, adresse);
    strcat(chemin, "\\"); //on cr�e l'adress compl�te de l'element

    DIR * rep = opendir(adresse);
    if (rep != NULL)
    {
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL)
        {
            strcpy(chemin_suppr, chemin);
            if(compteur > 1)//on n'affiche pas . et ..
            {
                strcat(chemin_suppr, ent->d_name);
                remove(chemin_suppr);
            }

            compteur++;
        }
        closedir(rep);
    }
    return;
}
/*================================================
Fonction permettant de supprimer un profil
================================================*/
void suppressionDossier(char * adresse)
{
    int compteur = 0;
    char * inter = NULL;
    char chemin[100] ={""};
    char chemin_suppr[100] = {""};

    strcat(chemin, adresse);
    strcat(chemin, "\\"); //on cr�e l'adress compl�te de l'element

//on se place dans le dossier � supprimer, et on supprime tous les fichiers dedans

    DIR * rep = opendir(adresse);
    if (rep != NULL)
    {
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL)
        {
            strcpy(chemin_suppr, chemin);
            if(compteur > 1)//on n'affiche pas . et ..
            {
                inter = strrchr(ent->d_name, '.');
                strcat(chemin_suppr, ent->d_name);
                if(inter != NULL)
                {
                    remove(chemin_suppr);
                }
                else
                {
                    vide_dossier(chemin_suppr);
                    rmdir(chemin_suppr);
                }
            }

            compteur++;
        }
        closedir(rep);
    }
    rmdir(adresse);//on supprime le dossier
    return;
}

#else

void make_directory(char * name)
   {
       mkdir(name,0777);
   }

int verif_directory_user()
{
    DIR * rep = opendir("./"); //permet d'acc�der � l'ensemble des �l�ments � cette adresse

    if (rep != NULL)
    {
        struct dirent * ent;
        while ((ent = readdir(rep)) != NULL)
        {
            if(strcmp("User", ent->d_name) == 0) //si le profil existe d�j�, on l'indique
            {
                return 1;
            }

        }
        closedir(rep);
    }
    return 0;
}

int verif_dossier(char * pseudo)
{
    DIR * rep = opendir("./User/"); //permet d'acc�der � l'ensemble des �l�ments � cette adresse

    if (rep != NULL)
    {
        struct dirent * ent;
        while ((ent = readdir(rep)) != NULL)
        {
            if(strcmp(pseudo, ent->d_name) == 0) //si le profil existe d�j�, on l'indique
            {
                return 1;
            }

        }
        closedir(rep);
    }
    return 0;
}

char * creation_dossier(char pseudo[100], char * chemin_langue)
{
    int verif = 0;
    char chemin[100] = { "" };
    char tuto[100] = { "" };

    char * chemin_sortie = malloc(100 * sizeof(char));

    char chemin_profil[100] = { "" };

    char vide_buffer[100];

    strcpy(chemin_profil, chemin_langue);
    strcpy(tuto, chemin_langue);

    strcat(chemin_profil, "profil_existant.txt");
    strcat(tuto, "tuto.txt");

    strcpy(chemin, "./User/"); //chemin de cr�ation des profils
    strcat(chemin,pseudo); //on ajoute le nom du profil au chemin d'acc�s

    verif = verif_dossier(pseudo); // on v�rifie qu'il n'existe pas d�j�
    if(verif == 0)
    {
        make_directory(chemin);
        char * inter = "/";
        strcat(chemin, inter);

        char dossier_save[100] = { "" };
        char dossier_param[100] = { "" };
        char dossier_stat[100] = { "" };

        strcpy(dossier_param, chemin);
        strcpy(dossier_save, chemin);
        strcpy(dossier_stat, chemin);
	strcpy(chemin_sortie, chemin);

        strcat(dossier_param, "Parametres/");
        strcat(dossier_save, "Save/");
        strcat(dossier_stat, "Statistiques/");

        make_directory(dossier_param);
        make_directory(dossier_save);
        make_directory(dossier_stat);

        CreationFichier(dossier_param, "parametres_joueurs.txt", "./Parametres&Langues/REFERENCE_FILE/parametres_joueurs.txt");
        CreationFichier(dossier_param, "parametres_joueurs_de.txt", "./Parametres&Langues/REFERENCE_FILE/parametres_joueurs_de.txt");
        CreationFichier(dossier_param, "parametres_joueurs_en.txt", "./Parametres&Langues/REFERENCE_FILE/parametres_joueurs_en.txt");
        CreationFichier(dossier_param, "parametres_joueurs_es.txt", "./Parametres&Langues/REFERENCE_FILE/parametres_joueurs_es.txt");
        CreationFichier(dossier_param, "parametres_joueurs_is.txt", "./Parametres&Langues/REFERENCE_FILE/parametres_joueurs_is.txt");
        CreationFichier(dossier_param, "parametres_joueurs_it.txt", "./Parametres&Langues/REFERENCE_FILE/parametres_joueurs_it.txt");
        CreationFichier(dossier_param, "parametres_joueurs_ne.txt", "./Parametres&Langues/REFERENCE_FILE/parametres_joueurs_ne.txt");

        CreationFichier(dossier_stat, "stat_fr.txt", "./Parametres&Langues/REFERENCE_FILE/stat_fr.txt");
        CreationFichier(dossier_stat, "stat_de.txt", "./Parametres&Langues/REFERENCE_FILE/stat_de.txt");
        CreationFichier(dossier_stat, "stat_en.txt", "./Parametres&Langues/REFERENCE_FILE/stat_en.txt");
        CreationFichier(dossier_stat, "stat_es.txt", "./Parametres&Langues/REFERENCE_FILE/stat_es.txt");
        CreationFichier(dossier_stat, "stat_ne.txt", "./Parametres&Langues/REFERENCE_FILE/stat_ne.txt");
        CreationFichier(dossier_stat, "stat_is.txt", "./Parametres&Langues/REFERENCE_FILE/stat_is.txt");
        CreationFichier(dossier_stat, "stat_it.txt", "./Parametres&Langues/REFERENCE_FILE/stat_it.txt");
        CreationFichier(dossier_stat, "valeur_stat.txt", "./Parametres&Langues/REFERENCE_FILE/valeur_stat.txt");


        strcat(chemin, "/nom.txt");
        FILE * temp = fopen(chemin, "w");
        fprintf(temp, "%s", pseudo);
        fclose(temp);

        cls();
        affichage_texte(tuto);
        scanf("%s", vide_buffer);
        return chemin_sortie;
    }
    else{
        affichage_texte(chemin_profil);
        return "a";
    }

}

void vide_dossier(char * adresse)
{
    char chemin[100] ={""};
    char chemin_suppr[100] = {""};
    strcat(chemin, adresse);
    strcat(chemin, "/"); //on cr�e l'adress compl�te de l'element

    DIR * rep = opendir(adresse);
    if (rep != NULL)
    {
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL)
        {
            strcpy(chemin_suppr, chemin);
            if(strcmp(ent->d_name, ".") && strcmp(ent->d_name, ".."))//on n'affiche pas . et ..
            {
                strcat(chemin_suppr, ent->d_name);
                remove(chemin_suppr);
            }

        }
        closedir(rep);
    }
    return;
}

void suppressionDossier(char * adresse)
{
    char * inter = NULL;
    char chemin[100] ={""};
    char chemin_suppr[100] = {""};
    strcat(chemin, adresse);

//on se place dans le dossier � supprimer, et on supprime tous les fichiers dedans

    DIR * rep = opendir(adresse);
    if (rep != NULL)
    {
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL)
        {
            strcpy(chemin_suppr, adresse);
            if(strcmp(ent->d_name, ".") && strcmp(ent->d_name, ".."))//on n'affiche pas . et ..
            {
                inter = strrchr(ent->d_name, '.');
                strcat(chemin_suppr, ent->d_name);
                if(inter != NULL)
                {
                    remove(chemin_suppr);
                }
                else
                {
                    vide_dossier(chemin_suppr);
                    rmdir(chemin_suppr);
                }
            }

        }
        closedir(rep);
    }
    rmdir(adresse);//on supprime le dossier
    return;
}


#endif

/*================================================================
 fonction cr�ant le dossier param�tre pour chaque profil cr�er
 ===============================================================*/

void CreationFichier(char * chemin, char * nom, char * original)
{
    char chemin_final[100] = { "" };
    strcpy(chemin_final, chemin);
    strcat(chemin_final, nom);

    FILE * copie = fopen(chemin_final, "w");
    FILE * fichier = fopen(original, "r");

    int caractere = fgetc(fichier);
    while(caractere != EOF)
    {
        fputc(caractere, copie);
        caractere = fgetc(fichier);
    }
    fclose(copie);
    fclose(fichier);
}

