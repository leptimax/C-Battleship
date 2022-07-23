
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

/*====================================================
Fonction permettant de récupérer la langue en cours
=====================================================*/

int language()
{
    int langue;
    FILE * temp = fopen(".\\Parametres&Langues\\langue.txt", "r");
    fscanf(temp, "%d;", &langue);
    fclose(temp);
    if(langue < 0 || langue > 6) //au cas où la langue aurait été modifié par le systeme
       return 0;
    return langue;
}

/*=======================================================================
Fonction permettant de récupérer le chemin pour afficher le bon langage
========================================================================*/

char * chemin_langue(int langue)
{
    char * chemin_copie = malloc(100 * sizeof(char));
    char chemin[100] = { "" };
    strcat(chemin, ".\\Parametres&Langues\\");

    switch(langue)
    {
    case 0:
        strcat(chemin, "FR\\");
        break;
    case 1:
        strcat(chemin, "EN\\");
        break;
    case 2:
        strcat(chemin, "ES\\");
        break;
    case 3:
        strcat(chemin, "DE\\");
        break;
    case 4:
        strcat(chemin, "IT\\");
        break;
    case 5:
        strcat(chemin, "IS\\");
        break;
    case 6:
        strcat(chemin, "NE\\");
        break;
    }
    strcpy(chemin_copie, chemin);

    return chemin_copie;
}
#else

int language()
{
    int langue;
    FILE * temp = fopen("./Parametres&Langues/langue.txt", "r");
    fscanf(temp, "%d;", &langue);
    fclose(temp);
    return langue;
}

char * chemin_langue(int langue)
{

    char * chemin_copie = malloc(100 * sizeof(char));
    char chemin[100] = { "" };
    strcat(chemin, "./Parametres&Langues/");

    switch(langue)
    {
    case 0:
        strcat(chemin, "FR/");
        break;
    case 1:
        strcat(chemin, "EN/");
        break;
    case 2:
        strcat(chemin, "ES/");
        break;
    case 3:
        strcat(chemin, "DE/");
        break;
    case 4:
        strcat(chemin, "IT/");
        break;
    case 5:
        strcat(chemin, "IS/");
        break;
    case 6:
        strcat(chemin, "NE/");
        break;
    }
    strcpy(chemin_copie, chemin);
    return chemin_copie;
}

#endif // defined
