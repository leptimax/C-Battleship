#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "../../IA/base.h"
#include "gestion_couleur.h"
#include "../../Affichage/fonction_affichage.h"
#include "gestion_couleur_annexe.h"

/*=================================================
on définit le menu des options couleurs
=================================================*/

Couleurs * menu_couleurs(char * bateau,char * rate, char * touche, char * chemin)
{
    int x;
    int y = -1;
    int boucle = 1;
    Couleurs * out = malloc(sizeof(Couleurs));
    char menu_option_1[100] = { "" };
    char menu_option_2[100] = { "" };
    char menu_option_3[100] = { "" };
    char menu_option_4[100] = { "" };
    char liste_couleur[100] = { "" };
    char erreur[100] = { "" };

    strcpy(menu_option_1, chemin);
    strcpy(menu_option_2, chemin);
    strcpy(menu_option_3, chemin);
    strcpy(menu_option_4, chemin);
    strcpy(liste_couleur, chemin);
    strcpy(erreur, chemin);

    strcat(menu_option_1, "menu_option_couleur_1.txt");
    strcat(menu_option_2, "menu_option_couleur_2.txt");
    strcat(menu_option_3, "menu_option_couleur_3.txt");
    strcat(menu_option_4, "menu_option_couleur_4.txt");
    strcat(liste_couleur, "liste_couleur_menu.txt");
    strcat(erreur, "erreur.txt");

    //on affiche les 3 options modifiable ainsi que la couleur associé

    affichage_texte(menu_option_1);
    printf("%s", bateau);
    affichage_texte(menu_option_2);
    printf("%s", rate);
    affichage_texte(menu_option_3);
    printf("%s", touche);
    affichage_texte(menu_option_4);

    scanf("%d", &x);
    cls();
    switch (x)
        {
        case 1 ://couleur bateau
            {

               while(boucle == 1)
               {
                  affichage_texte(liste_couleur);
                  scanf("%d", &y);
                  if(y > 0 && y < 9 )
                    boucle = 0;
                  else
                  {
                      cls();
                      affichage_texte(erreur);
                      sleep(1);
                      cls();
                  }
               }

               break;
            }
        case 2 ://couleur rate
            {
                while(boucle == 1)
               {
                  affichage_texte(liste_couleur);
                  scanf("%d", &y);
                  if(y > 0 && y < 9 )
                    boucle = 0;
                  else
                  {
                      cls();
                      affichage_texte(erreur);
                      sleep(1);
                      cls();
                  }
               }
                break;
            }
        case 3 ://couleur touche
            {
                while(boucle == 1)
               {
                  affichage_texte(liste_couleur);
                  scanf("%d", &y);
                  if(y > 0 && y < 9 )
                    boucle = 0;
                  else
                  {
                      cls();
                      affichage_texte(erreur);
                      sleep(1);
                      cls();
                  }
               }
                break;
            }
        case 4 : //mode daltonien
            {
                break;
            }
        case 5 ://couleur par défaut
            {
                break;
            }
        case 6 :// quitter menu couleurs
            {
                break;
            }
        default :
            affichage_texte(erreur);
            sleep(1);
            cls();
            menu_couleurs(bateau, rate, touche, chemin);
            break;
        }
    cls();


    out->x = x;
    out->y = y;

    return out; //on retourne le choix de l'utilisateur

}

//on définit la fonction qui va aller chercher le code couleur désiré pour l'appliquer

/*==================================================================================================================
on définit la fonction qui va permettre de recuperer le nom de la couleur à modifier dans le fichier parametre
===================================================================================================================*/

Liste_couleur * defCouleur(int x)
{
    char * temp = malloc(sizeof(char));
    char * temp_EN = malloc(sizeof(char));
    char * temp_DE = malloc(sizeof(char));
    char * temp_ES= malloc(sizeof(char));
    char * temp_IT = malloc(sizeof(char));
    char * temp_IS = malloc(sizeof(char));
    char * temp_NE = malloc(sizeof(char));
    Liste_couleur * out = malloc(sizeof(Liste_couleur));

    switch (x)
    {
        case 1 :
            {
                temp = "Blanc !";
                temp_EN = "White !";
                temp_DE = "Weiss !";
                temp_ES = "Blanco !";
                temp_IS = "Hvitt !";
                temp_IT = "Bianca !";
                temp_NE = "Wit !";
                break;
            }
        case 2 :
            {
                temp = "Rouge !";
                temp_EN = "Red !";
                temp_DE = "Rot !";
                temp_ES = "Rojo !";
                temp_IS = "Rautt !";
                temp_IS = "Rosso !";
                temp_NE = "Rood !";
                break;
            }
        case 3 :
            {
                temp = "vert !";
                temp_EN = "green !";
                temp_DE = "Grun !";
                temp_ES = "Verde !";
                temp_ES = "Graenn !";
                temp_IT = "Verde !";
                temp_NE = "Groen !";
                break;
            }
        case 4 :
            {
                temp = "Jaune !";
                temp_EN = "Yellow !";
                temp_DE = "Gelb !";
                temp_ES = "Amarillo !";
                temp_IS = "Gulur !";
                temp_IT = "Giallo !";
                temp_NE = "Geel !";
                break;
            }
        case 5 :
            {
                temp = "Bleu !";
                temp_EN = "Blue !";
                temp_DE = "Blau !";
                temp_ES = "Azul !";
                temp_IS = "Blatt !";
                temp_IT = "Blu !";
                temp_NE = "Blauw !";
                break;
            }
        case 6 :
            {
                temp = "Magenta !";
                temp_EN = "Magenta !";
                temp_DE = "Magenta !";
                temp_ES = "Magenta !";
                temp_IS = "Magenta !";
                temp_IT = "Magenta !";
                temp_NE = "Magenta !";
                break;
            }
        case 7 :
            {
                temp = "Cyan !";
                temp_EN = "Cyan !";
                temp_DE = "Cyan !";
                temp_ES = "Cian !";
                temp_IS = "Blagraent !";
                temp_IT = "Ciano !";
                temp_NE = "Cyaan !";
                break;
            }
    }
    out->FR = temp;
    out->EN = temp_EN;
    out->ES = temp_ES;
    out->DE = temp_DE;
    out->NE = temp_NE;
    out->IS = temp_IS;
    out->IT = temp_IT;
    return out;
}

/*===============================================
Fonction pour remettre les couleurs par défaut
================================================*/

void raz(FILE * fichier,FILE * nouveau)
{
    char caractere;
    caractere = fgetc(fichier);
    while (caractere != EOF)
    {
        fputc(caractere,nouveau);
        caractere = fgetc(fichier);

    }

}
/*==============================================================================
fonction qui permet de vérifier que l'utilisateur a bien 3 couleurs différentes
================================================================================*/

int verification_couleur(char * profil)
{
    int x_b,y_b,x_r,y_r,x_t,y_t;
    char a,b,c;
    char * bateau = malloc(sizeof(char));
    char * rate = malloc(sizeof(char));
    char * touche = malloc(sizeof(char));

    char chemin_profil[100] = { "" };

    strcpy(chemin_profil, profil);

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

    strcat(chemin_profil, "Parametres\\parametres_joueurs.txt");

#else

    strcat(chemin_profil, "Parametres/parametres_joueurs.txt");

#endif // defined

    FILE * fichier = fopen(chemin_profil, "r+");
    if (fichier != NULL) //on recupere les couleurs
    {
        fscanf(fichier, "%d %d %s %c", &x_b, &y_b, bateau, &a);
        fscanf(fichier, "%d %d %s %c", &x_r, &y_r, rate, &b);
        fscanf(fichier, "%d %d %s %c", &x_t, &y_t, touche, &c);

        if (y_b == y_r || y_b == y_t || y_r == y_t) //si elles sont différentes on quitte
        {
            free(bateau);
            free(rate);
            free(touche);
            fclose(fichier);

            return 0;
        }

        else //sinon on indique le pb
        {
            free(bateau);
            free(rate);
            free(touche);
            fclose(fichier);
            return 1;

        }
    }
    else
    {
        printf("erreur critique ! fermeture de l'application");
        return 1;
    }
}

/*========================================================================================
Fonction permettant de lancer la modification des couleurs dans les fichiers parametres
=========================================================================================*/

void definition_couleur(int x, int y, FILE * fichier, FILE * nouveau, char * nouvelle_couleur)
{
    int caractere = ' ';
    int i = 0;
    switch (x)
    {
    case 1 : //si il souhaite changer la première couleur
        {
//on crée tous les nouveaux fichiers dans chaque langue

            fseek(fichier, 0, SEEK_SET);
            fseek(nouveau, 0, SEEK_SET);
            fprintf(nouveau, "1 %d %s\n", y, nouvelle_couleur); //on insère la nouvelle couleur dans le nouveau fichier

            while(caractere != '!')//on saute la première ligne de l'ancien fichier paramètre pour ne pas la recopier
                caractere = fgetc(fichier);
            fseek(nouveau, -2, SEEK_CUR);
            caractere = fgetc(fichier);
            i=0;
            while(caractere != EOF ) //on recopie le reste du fichier paramètre
            {

                fputc(caractere,nouveau);
                caractere = fgetc(fichier);
                i++;
            }
            break;


        }
    case 2 :
        {

            fseek(nouveau, 0, SEEK_SET);
            fseek(fichier, 0, SEEK_SET);
            while (caractere != '!')
            {
                caractere = fgetc(fichier);
                fputc(caractere, nouveau);
            }
            fprintf(nouveau, "\n2 %d %s", y, nouvelle_couleur);
            caractere = fgetc(fichier);
            while(caractere != '!')
                {
                    caractere = fgetc(fichier);
                }

            caractere = fgetc(fichier);
            while(caractere != EOF)
            {

                fputc(caractere,nouveau);
                caractere = fgetc(fichier);


            }
            break;

        }
    case 3 :
        {
            fseek(fichier, 0, SEEK_SET);
            fseek(nouveau, 0, SEEK_SET);
            caractere = fgetc(fichier);
            while (caractere != '!')
            {
                fputc(caractere,nouveau);
                caractere = fgetc(fichier);
            }
            fputc(caractere, nouveau);
            caractere = fgetc(fichier);
            while (caractere != '!')
            {
                fputc(caractere, nouveau);
                caractere = fgetc(fichier);
            }
            fputc(caractere, nouveau);
            fprintf(nouveau, "\n3 %d %s\n", y, nouvelle_couleur);
            caractere = fgetc(fichier);
            while(caractere != '!')
                caractere = fgetc(fichier);

            caractere = fgetc(fichier);
            while (caractere != EOF)
            {
                fputc(caractere, nouveau);
                caractere = fgetc(fichier);
            }


            break;
        }


    }
}

/*==============================================================
Fonction permettant de récupérer le code couleur à appliquer
===============================================================*/


Color * recup_Color(char * chemin)
{
    char parametre_joueur_fr[100] = { "" };
    strcpy(parametre_joueur_fr, chemin);

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

    strcat(parametre_joueur_fr, "Parametres\\parametres_joueurs.txt");

#else

    strcat(parametre_joueur_fr, "Parametres/parametres_joueurs.txt");

#endif // defined

    FILE * tete = fopen(parametre_joueur_fr, "r+");
    if(tete != NULL)
    {

    Color * out = malloc(sizeof(Color));

    char * couleur1 = malloc(sizeof(char));
    char * couleur2 = malloc(sizeof(char));
    char * couleur3 = malloc(sizeof(char));

    int a,b,c,bateau,rate,touche;
    char x,y,z;

    fscanf(tete, "%d %d %s %c", &a, &bateau, couleur1, &x);
    fscanf(tete, "%d %d %s %c", &b, &rate, couleur2, &y);
    fscanf(tete, "%d %d %s %c", &c, &touche, couleur3, &z);
    out->bateau = bateau;
    out->rate = rate;
    out->touche = touche;

    free(couleur1);
    free(couleur2);
    free(couleur3);
    fclose(tete);

    return out;
    }
    else
        printf("help");
    return NULL;

}
/*=======================================
Fonction gérant le mode daltonien
=======================================*/

void daltonien(FILE * fichier, FILE * nouveau)
{
    char caractere;
    if (fichier != NULL && nouveau != NULL)
    {
        caractere = fgetc(fichier);
        while (caractere != EOF)
        {
            fputc(caractere, nouveau);
            caractere = fgetc(fichier);

        }
    }
}

/*====================================================
Fonction gérant l'intégralité des options couleurs
=====================================================*/

Color * option_couleur(int langue, char * chemin, char * profil)
{
    Color * temp = malloc(sizeof(Color));
	gestion_couleur_complete(langue, chemin, profil);
	temp = recup_Color(profil);
	return temp;
}

