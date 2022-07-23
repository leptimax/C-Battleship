

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

/*================================================================
Fonction permettant de mettre à jour les statistiques du joueur
=================================================================*/

void modif_statistique(int lvl_IA , int coup , int resultat , float temps , char * fichier_ref , char * adresse)
{
    char adresse_temp[100] = {""};

    float duree[7] = {0};
    float Coup[7] = {0};
    float ratio[7] = {0};
    int victoire[7] = {0};
    int defaite[7] = {0};


    //on crée l'adresse du nouveau fichier

    strcat(adresse_temp , adresse);
    strcat(adresse_temp , "\\temp.txt");

    FILE * fichier = fopen(fichier_ref , "r");
    FILE * temp = fopen(adresse_temp , "w");

    if(temp == NULL || fichier == NULL)
    {
        printf("HELP !");
    }
    else//on récupère les statistiques existantes
    {
        fscanf(fichier , "%f?%f?%f?%f?%f;" , &duree[0] , &duree[1] , &duree[2] , &duree[3] , &duree[4]);
        fscanf(fichier , "%f?%f?%f?%f?%f;" , &Coup[0] , &Coup[1] , &Coup[2] , &Coup[3] , &Coup[4]);
        fscanf(fichier , "%d?%d?%d?%d?%d;" , &victoire[0] , &victoire[1] , &victoire[2] , &victoire[3] , &victoire[4]);
        fscanf(fichier , "%d?%d?%d?%d?%d;" , &defaite[0] , &defaite[1] , &defaite[2] , &defaite[3] , &defaite[4]);
        fscanf(fichier , "%f?%f?%f?%f?%f;" , &ratio[0] , &ratio[1] , &ratio[2] , &ratio[3] , &ratio[4]);
        fscanf(fichier , "%f;" , &duree[5]);

        switch(lvl_IA)//on les modifient
        {
        case 1:
            if(duree[0] == 0)
                duree[0] = temps;
            else
                duree[0] = (duree[0] + temps)/2;
            if(Coup[0] == 0)
                Coup[0] = coup;
            else
                Coup[0] = (Coup[0] + coup)/2;
            if(resultat == 1)
                  victoire[0] = victoire[0] + 1;

            else
                defaite[0] = defaite[0] + 1;
            if(defaite[0] == 0)
                ratio[0] = victoire[0];
            else
                ratio[0] = victoire[0] / defaite[0];

            break;
        case 2:
            if(duree[1] == 0)
                duree[1] = temps;
            else
                duree[1] = (duree[1] + temps)/2;
            if(Coup[1] == 0)
                Coup[1] = coup;
            else
                Coup[1] = (Coup[1] + coup)/2;
            if(resultat == 1)
                  victoire[1] = victoire[1] + 1;

            else
                defaite[1] = defaite[1] + 1;
            if(defaite[1] == 0)
                ratio[1] = victoire[1];
            else
                ratio[1] = victoire[1] / defaite[1];

            break;
        case 3:
            if(duree[2] == 0)
                duree[2] = temps;
            else
                duree[2] = (duree[2] + temps)/2;
            if(Coup[2] == 0)
                Coup[2] = coup;
            else
                Coup[2] = (Coup[2] + coup)/2;
            if(resultat == 1)
                  victoire[2] = victoire[2] + 1;

            else
                defaite[2] = defaite[2] + 1;
            if(defaite[2] == 0)
                ratio[2] = victoire[2];
            else
                ratio[2] = victoire[2] / defaite[2];

            break;
        case 4:
            if(duree[3] == 0)
                duree[3] = temps;
            else
                duree[3] = (duree[3] + temps)/2;
            if(Coup[3] == 0)
                Coup[3] = coup;
            else
                Coup[3] = (Coup[3] + coup)/2;
            if(resultat == 1)
                  victoire[3] = victoire[3] + 1;

            else
                defaite[3] = defaite[3] + 1;
            if(defaite[3] == 0)
                ratio[3] = victoire[3];
            else
                ratio[3] = victoire[3] / defaite[3];

            break;
        case 5:
            if(duree[4] == 0)
                duree[4] = temps;
            else
                duree[4] = (duree[4] + temps)/2;
            if(Coup[4] == 0)
                Coup[4] = coup;
            else
                Coup[4] = (Coup[4] + coup)/2;
            if(resultat == 1)
                  victoire[4] = victoire[4] + 1;

            else
                defaite[4] = defaite[4] + 1;
            if(defaite[4] == 0)
                ratio[4] = victoire[4];
            else
                ratio[4] = victoire[4] / defaite[4];

            break;
        }
        duree[5] = duree[5] + temps;
//on les remets dans le nouveau fichier
        fprintf(temp , "%.1f?%.1f?%.1f?%.1f?%.1f;\n" , duree[0] , duree[1] , duree[2] , duree[3] , duree[4]);
        fprintf(temp , "%.1f?%.1f?%.1f?%.1f?%.1f;\n" , Coup[0] , Coup[1] , Coup[2] , Coup[3] , Coup[4]);
        fprintf(temp , "%d?%d?%d?%d?%d;\n" , victoire[0] , victoire[1] , victoire[2] , victoire[3] , victoire[4]);
        fprintf(temp , "%d?%d?%d?%d?%d;\n" , defaite[0] , defaite[1] , defaite[2] , defaite[3] , defaite[4]);
        fprintf(temp , "%.1f?%.1f?%.1f?%.1f?%.1f;\n" , ratio[0] , ratio[1] , ratio[2] , ratio[3] , ratio[4]);
        fprintf(temp , "%.1f;\n" , duree[5]);

        fclose(fichier);
        fclose(temp);
    }
    remove(fichier_ref);
    rename(adresse_temp , fichier_ref);

}

/*=========================================================================================
Fonction permettant de lancer la mise à jour de tous les fichiers statistiques du joueur
==========================================================================================*/

void statistique(int lvl_IA , int resultat , float temps , char * adresse , int coup)
{
    char chemin[100] = {""};


    char chemin_FR[100] = {""}; //adresse du fichier d'origine

    //on crée le chemin complet du fichier d'origine

    strcat(chemin , adresse);

    strcat(chemin_FR , chemin);

    strcat(chemin_FR , "Statistiques\\valeur_stat.txt");

    modif_statistique(lvl_IA , coup , resultat , temps , chemin_FR , adresse);//on récupère l'adresse du fichier temporaire



}

void affichage_statistique(char * chemin, int langue)
{

    int x[100];
    int valeur;
    char y[5];
    int i = 0;
    int j = 0;
    int k = 0;
    int caractere;

    char adresse[100] = { "" };
    char adresse_ref[100] = { "" };

    strcpy(adresse_ref, chemin);
    strcpy(adresse, chemin);

    strcat(adresse_ref, "Statistiques\\valeur_stat.txt");

    float var_float[20] = {0};
    int var_int[20] = {0};
    switch(langue)
    {
    case 0:
        strcat(adresse,"Statistiques\\stat_fr.txt");
        break;
    case 1:
        strcat(adresse,"Statistiques\\stat_en.txt");
        break;
    case 2:
        strcat(adresse,"Statistiques\\stat_es.txt");
        break;
    case 3:
        strcat(adresse,"Statistiques\\stat_de.txt");
        break;
    case 4:
        strcat(adresse,"Statistiques\\stat_it.txt");
        break;
    case 5:
        strcat(adresse,"Statistiques\\stat_is.txt");
        break;
    case 6:
        strcat(adresse,"Statistiques\\stat_ne.txt");
        break;
    }

    FILE * tete = fopen(adresse_ref, "r");
    FILE * head = fopen(adresse, "r");

//on vérifie que l'ouverture du fichier est faite
	if (tete == NULL)
        printf("HS");
    else
    {
        fscanf(tete , "%f?%f?%f?%f?%f;" , &var_float[0] , &var_float[1] , &var_float[2] , &var_float[3] , &var_float[4]);
        fscanf(tete , "%f?%f?%f?%f?%f;" , &var_float[5] , &var_float[6] , &var_float[7] , &var_float[8] , &var_float[9]);
        fscanf(tete , "%d?%d?%d?%d?%d;" , &var_int[0] , &var_int[1] , &var_int[2] , &var_int[3] , &var_int[4]);
        fscanf(tete , "%d?%d?%d?%d?%d;" , &var_int[5] , &var_int[6] , &var_int[7] , &var_int[8] , &var_int[9]);
        fscanf(tete , "%f?%f?%f?%f?%f;" , &var_float[10] , &var_float[11] , &var_float[12] , &var_float[13] , &var_float[14]);
        fscanf(tete , "%f;" , &var_float[15]);
//on récupère l'ensemble des valeur ASCII des différents caractères spéciaux situés en tête du fichier


        valeur = fgetc(head);
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
            valeur = fgetc(head);
        }
        x[i] = atoi(y);

//on lit et on affiche l'ensemble du fichier en remplaçant les %c par la valeur adaptée

        i = 0;
        j = 0;
        k = 0;
        //caractere = fgetc(tete);
        caractere = fgetc(head);
        while(caractere != EOF)
        {
            if(caractere == '%')
            {
                caractere = fgetc(head);
                caractere = fgetc(head);
                printf("%c",x[i]);
                i++;
            }
            if(caractere == '!')
            {
                printf("%.1f" , var_float[j]);
                j++;
                caractere = fgetc(head);
            }
            if(caractere == '/')
            {
                printf("%d" , var_int[k]);
                k++;
            }
            else
            {
                printf("%c",caractere);
            }
            caractere = fgetc(head);
        }
    }
    fclose(head);
    fclose(tete);
}
#else

void modif_statistique(int lvl_IA , int coup , int resultat , float temps , char * fichier_ref , char * adresse)
{
    char adresse_temp[100] = {""};

    float duree[7] = {0};
    float Coup[7] = {0};
    float ratio[7] = {0};
    int victoire[7] = {0};
    int defaite[7] = {0};

    //on crée l'adresse du nouveau fichier

    strcat(adresse_temp , adresse);
    strcat(adresse_temp , "/temp.txt");

    FILE * fichier = fopen(fichier_ref , "r");
    FILE * temp = fopen(adresse_temp , "w");

    if(temp == NULL || fichier == NULL)
    {
        printf("HELP !");
    }
    else//on récupère les statistiques existantes
    {
        fscanf(fichier , "%f?%f?%f?%f?%f;" , &duree[0] , &duree[1] , &duree[2] , &duree[3] , &duree[4]);
        fscanf(fichier , "%f?%f?%f?%f?%f;" , &Coup[0] , &Coup[1] , &Coup[2] , &Coup[3] , &Coup[4]);
        fscanf(fichier , "%d?%d?%d?%d?%d;" , &victoire[0] , &victoire[1] , &victoire[2] , &victoire[3] , &victoire[4]);
        fscanf(fichier , "%d?%d?%d?%d?%d;" , &defaite[0] , &defaite[1] , &defaite[2] , &defaite[3] , &defaite[4]);
        fscanf(fichier , "%f?%f?%f?%f?%f;" , &ratio[0] , &ratio[1] , &ratio[2] , &ratio[3] , &ratio[4]);
        fscanf(fichier , "%f;" , &duree[5]);

        switch(lvl_IA)//on les modifient
        {
        case 1:
            if(duree[0] == 0)
                duree[0] = temps;
            else
                duree[0] = (duree[0] + temps)/2;
            if(Coup[0] == 0)
                Coup[0] = coup;
            else
                Coup[0] = (Coup[0] + coup)/2;
            if(resultat == 1)
                  victoire[0] = victoire[0] + 1;

            else
                defaite[0] = defaite[0] + 1;
            if(defaite[0] == 0)
                ratio[0] = victoire[0];
            else
                ratio[0] = victoire[0] / defaite[0];

            break;
        case 2:
            if(duree[1] == 0)
                duree[1] = temps;
            else
                duree[1] = (duree[1] + temps)/2;
            if(Coup[1] == 0)
                Coup[1] = coup;
            else
                Coup[1] = (Coup[1] + coup)/2;
            if(resultat == 1)
                  victoire[1] = victoire[1] + 1;

            else
                defaite[1] = defaite[1] + 1;
            if(defaite[1] == 0)
                ratio[1] = victoire[1];
            else
                ratio[1] = victoire[1] / defaite[1];

            break;
        case 3:
            if(duree[2] == 0)
                duree[2] = temps;
            else
                duree[2] = (duree[2] + temps)/2;
            if(Coup[2] == 0)
                Coup[2] = coup;
            else
                Coup[2] = (Coup[2] + coup)/2;
            if(resultat == 1)
                  victoire[2] = victoire[2] + 1;

            else
                defaite[2] = defaite[2] + 1;
            if(defaite[2] == 0)
                ratio[2] = victoire[2];
            else
                ratio[2] = victoire[2] / defaite[2];

            break;
        case 4:
            if(duree[3] == 0)
                duree[3] = temps;
            else
                duree[3] = (duree[3] + temps)/2;
            if(Coup[3] == 0)
                Coup[3] = coup;
            else
                Coup[3] = (Coup[3] + coup)/2;
            if(resultat == 1)
                  victoire[3] = victoire[3] + 1;

            else
                defaite[3] = defaite[3] + 1;
            if(defaite[3] == 0)
                ratio[3] = victoire[3];
            else
                ratio[3] = victoire[3] / defaite[3];

            break;
        case 5:
            if(duree[4] == 0)
                duree[4] = temps;
            else
                duree[4] = (duree[4] + temps)/2;
            if(Coup[4] == 0)
                Coup[4] = coup;
            else
                Coup[4] = (Coup[4] + coup)/2;
            if(resultat == 1)
                  victoire[4] = victoire[4] + 1;

            else
                defaite[4] = defaite[4] + 1;
            if(defaite[4] == 0)
                ratio[4] = victoire[4];
            else
                ratio[4] = victoire[4] / defaite[4];

            break;
        }
        duree[5] = duree[5] + temps;
//on les remets dans le nouveau fichier
        fprintf(temp , "%.1f?%.1f?%.1f?%.1f?%.1f;\n" , duree[0] , duree[1] , duree[2] , duree[3] , duree[4]);
        fprintf(temp , "%.1f?%.1f?%.1f?%.1f?%.1f;\n" , Coup[0] , Coup[1] , Coup[2] , Coup[3] , Coup[4]);
        fprintf(temp , "%d?%d?%d?%d?%d;\n" , victoire[0] , victoire[1] , victoire[2] , victoire[3] , victoire[4]);
        fprintf(temp , "%d?%d?%d?%d?%d;\n" , defaite[0] , defaite[1] , defaite[2] , defaite[3] , defaite[4]);
        fprintf(temp , "%.1f?%.1f?%.1f?%.1f?%.1f;\n" , ratio[0] , ratio[1] , ratio[2] , ratio[3] , ratio[4]);
        fprintf(temp , "%.1f;\n" , duree[5]);

        fclose(fichier);
        fclose(temp);
    }
    remove(fichier_ref);
    rename(adresse_temp , fichier_ref);

}


void statistique(int lvl_IA , int resultat , float temps , char * adresse , int coup)
{
    char chemin[100] = {""};


    char chemin_FR[100] = {""}; //adresse du fichier d'origine

    //on crée le chemin complet du fichier d'origine

    strcat(chemin , adresse);

    strcat(chemin_FR , chemin);

    strcat(chemin_FR , "Statistiques/valeur_stat.txt");

    modif_statistique(lvl_IA , coup , resultat , temps , chemin_FR , adresse);//on récupère l'adresse du fichier temporaire



}

void affichage_statistique(char * chemin, int langue)
{

    int x[100];
    int valeur;
    char y[5];
    int i = 0;
    int j = 0;
    int k = 0;
    int caractere;

    char adresse[100] = { "" };
    char adresse_ref[100] = { "" };

    strcpy(adresse_ref, chemin);
    strcpy(adresse, chemin);

    strcat(adresse_ref, "Statistiques/valeur_stat.txt");

    float var_float[20] = {0};
    int var_int[20] = {0};
    switch(langue)
    {
    case 0:
        strcat(adresse,"Statistiques/stat_fr.txt");
        break;
    case 1:
        strcat(adresse,"Statistiques/stat_en.txt");
        break;
    case 2:
        strcat(adresse,"Statistiques/stat_es.txt");
        break;
    case 3:
        strcat(adresse,"Statistiques/stat_de.txt");
        break;
    case 4:
        strcat(adresse,"Statistiques/stat_it.txt");
        break;
    case 5:
        strcat(adresse,"Statistiques/stat_is.txt");
        break;
    case 6:
        strcat(adresse,"Statistiques/stat_ne.txt");
        break;
    }

    FILE * tete = fopen(adresse_ref, "r");
    FILE * head = fopen(adresse, "r");

//on vérifie que l'ouverture du fichier est faite
	if (tete == NULL)
        printf("HS");
    else
    {
        fscanf(tete , "%f?%f?%f?%f?%f;" , &var_float[0] , &var_float[1] , &var_float[2] , &var_float[3] , &var_float[4]);
        fscanf(tete , "%f?%f?%f?%f?%f;" , &var_float[5] , &var_float[6] , &var_float[7] , &var_float[8] , &var_float[9]);
        fscanf(tete , "%d?%d?%d?%d?%d;" , &var_int[0] , &var_int[1] , &var_int[2] , &var_int[3] , &var_int[4]);
        fscanf(tete , "%d?%d?%d?%d?%d;" , &var_int[5] , &var_int[6] , &var_int[7] , &var_int[8] , &var_int[9]);
        fscanf(tete , "%f?%f?%f?%f?%f;" , &var_float[10] , &var_float[11] , &var_float[12] , &var_float[13] , &var_float[14]);
        fscanf(tete , "%f;" , &var_float[15]);
//on récupère l'ensemble des valeur ASCII des différents caractères spéciaux situés en tête du fichier


        valeur = fgetc(head);
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
            valeur = fgetc(head);
        }
        x[i] = atoi(y);

//on lit et on affiche l'ensemble du fichier en remplaçant les %c par la valeur adaptée

        i = 0;
        j = 0;
        k = 0;
        //caractere = fgetc(tete);
        caractere = fgetc(head);
        while(caractere != EOF)
        {
            if(caractere == '%')
            {
                caractere = fgetc(head);
                caractere = fgetc(head);
                printf("%c",x[i]);
                i++;
            }
            if(caractere == '!')
            {
                printf("%.1f" , var_float[j]);
                j++;
                caractere = fgetc(head);
            }
            if(caractere == '/')
            {
                printf("%d" , var_int[k]);
                k++;
            }
            else
            {
                printf("%c",caractere);
            }
            caractere = fgetc(head);
        }
    }
    fclose(head);
    fclose(tete);
}



#endif

