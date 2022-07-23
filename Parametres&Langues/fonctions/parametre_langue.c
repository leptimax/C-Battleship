
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../IA/base.h"
#include "../../Affichage/fonction_affichage.h"
#include "determination_dossier_langue.h"
#include "parametre_langue.h"

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

/*================================================================
Fonction permettant d'afficher l'annonce du changement de langue
=================================================================*/

void affichage_parametre(int langue)
{

    int valeur, i, j;
    int x[100] = {0};

    char y[5];

    char * chemin = malloc(100 * sizeof(char));
    switch(langue)//selon la langue choisie, on affiche le message correspondant
    {
    case 0:
        chemin = ".\\Parametres&Langues\\FR\\annonce_langue.txt";
        break;
    case 1:
        chemin = ".\\Parametres&Langues\\EN\\annonce_langue.txt";
        break;
    case 2:
        chemin = ".\\Parametres&Langues\\ES\\annonce_langue.txt";
        break;
    case 3:
        chemin = ".\\Parametres&Langues\\DE\\annonce_langue.txt";
        break;
    case 4:
        chemin = ".\\Parametres&Langues\\IT\\annonce_langue.txt";
        break;
    case 5:
        chemin = ".\\Parametres&Langues\\IS\\annonce_langue.txt";
        break;
    case 6:
        chemin = ".\\Parametres&Langues\\NE\\annonce_langue.txt";
        break;
    }

    /*on affiche le message*/
    FILE * fichier = fopen(chemin, "r");
    if(fichier != NULL)
    {
        j = 0;
        i = 0;
        valeur = fgetc(fichier);
        while(valeur != ';')
        {

            if(j == 3)
            {
                j = 0;
                x[i] = atoi(y);
                i++;
            }
            y[j] = (char) valeur;
            j++;
            valeur = fgetc(fichier);
        }
        x[i] = atoi(y);

        i = 0;
        valeur = fgetc(fichier);
        while(valeur != EOF)
        {
            if(valeur == '%')
            {
                valeur = fgetc(fichier);
                printf("%c", x[i]);
                i++;
            }
            else
                printf("%c", valeur);
            valeur = fgetc(fichier);
        }
    }
}

/*=========================================================
Fonction permettant de faire la modification de la langue
==========================================================*/

void changement_langue(int langue_actuelle)
{
    char x1[10] = { "" };
    int x = -1;
    char * chemin = NULL;
    char chemin_erreur[100] = { "" };

    chemin = chemin_langue(langue_actuelle);
    strcat(chemin_erreur, chemin);
    strcat(chemin_erreur, "erreur.txt");
    strcat(chemin, "liste_langue.txt");
    while(x < 1 || x > 8)
    {
        cls();
        affichage_texte(chemin);
        fgets(x1, 10, stdin);
        x = atoi(x1);
        cls();
        if(x < 1 || x > 8)
            affichage_texte(chemin_erreur);

    }
    parametre(".\\Parametres&Langues\\" , x-1);
}

#else

void affichage_parametre(int langue)
{

    int valeur,i,j;
    int x[100] = {0};

    char y[5];

    char * chemin = malloc(100 * sizeof(char));
    switch(langue)
    {
    case 0:
        chemin = "./Parametres&Langues/FR/annonce_langue.txt";
        break;
    case 1:
        chemin = "./Parametres&Langues/EN/annonce_langue.txt";
        break;
    case 2:
        chemin = "./Parametres&Langues/ES/annonce_langue.txt";
        break;
    case 3:
        chemin = "./Parametres&Langues/DE/annonce_langue.txt";
        break;
    case 4:
        chemin = "./Parametres&Langues/IT/annonce_langue.txt";
        break;
    case 5:
        chemin = "./Parametres&Langues/IS/annonce_langue.txt";
        break;
    case 6:
        chemin = "./Parametres&Langues/NE/annonce_langue.txt";
        break;
    }

    FILE * fichier = fopen(chemin, "r");
    if(fichier != NULL)
    {
        j = 0;
        i = 0;
        valeur = fgetc(fichier);
        while(valeur != ';')
        {

            if(j == 3)
            {
                j = 0;
                x[i] = atoi(y);
                i++;
            }
            y[j] = (char) valeur;
            j++;
            valeur = fgetc(fichier);
        }
        x[i] = atoi(y);

        i = 0;
        valeur = fgetc(fichier);
        while(valeur != EOF)
        {
            if(valeur == '%')
            {
                valeur = fgetc(fichier);
                printf("%c", x[i]);
                i++;
            }
            else
                printf("%c", valeur);
            valeur = fgetc(fichier);
        }
    }
    sleep(2);
    cls();
}

void changement_langue(int langue_actuelle)
{
    char x1[10] = { "" };
    int x = -1;
    char * chemin = malloc(100 * sizeof(char));
    char * chemin_erreur = malloc(100 * sizeof(char));

    chemin = chemin_langue(langue_actuelle);
    strcpy(chemin_erreur, chemin);
    strcat(chemin_erreur, "erreur.txt");
    strcat(chemin, "liste_langue.txt");

    while(x < 1 || x > 8)
    {
        cls();
        affichage_texte(chemin);
        fgets(x1, 10, stdin);
        x = atoi(x1);
        cls();
        if(x < 1 || x > 8)
            affichage_texte(chemin_erreur);

    }
    if(x != 8)
    {
        parametre("./Parametres&Langues/", x-1);
    }

}
#endif

/*=====================================================
Fonction permettant de changer le paramètre langue
======================================================*/

void parametre(char * adresse, int langue)
{
    
    char chemin[100] = {""};
    char chemin_temp[100] = {""};

    int language;

    strcpy(chemin, adresse);
    strcat(chemin, "langue.txt");

    strcpy(chemin_temp, adresse);
    strcat(chemin_temp, "temp.txt");


    FILE * tete = fopen(chemin, "r");
    FILE * nouveau = fopen(chemin_temp, "w");

    //on récupère la valeur existante

    if(tete != NULL && nouveau != NULL)
    {
        fscanf(tete, "%d;", &language);

        if(language != langue)//si il s'agit d'une nouvelle langue, on affiche un message de redémarrage
        {
            affichage_parametre(langue);
        }
        fprintf(nouveau, "%d;", langue);//on sauvegarde la nouvelle langue

        fclose(nouveau);
        fclose(tete);

        remove(chemin);
        rename(chemin_temp, chemin);
    }

}

