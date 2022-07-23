#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "../IA/base.h"
#include "../Systeme/clean.h"
#include "creation_dossier.h"
#include "profil.h"
#include "../Affichage/fonction_affichage.h"

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

/*==============================================================
Fonction permettant de recuperer le pseudo du joueur
==============================================================*/

char * recup_pseudo(char * chemin)
{
    char * pseudo = malloc(100 * sizeof(char));
    char chemin_nom[100] = { "" };

    strcat(chemin_nom, chemin);
    strcat(chemin_nom, "nom.txt");

    FILE * temp = fopen(chemin_nom, "r");
    fscanf(temp, "%s", pseudo);
    fclose(temp);
    return pseudo;
}

/*============================================================================
On d�finit la fonction permettant d'afficher l'ensemble des profils existant
=============================================================================*/

int affichageProfil(char * chemin)
{
     DIR * rep = opendir(".\\User"); //permet d'afficher l'ensemble des �l�ments contenu � l'adresse sp�cifi�

/* permet de r�cup�rer le chemin absolu de l'exectuable    */

    /*char * chemin = NULL;
    chemin = getcwd(chemin,1024);
    printf("%s\n",chemin);*/
/*======================================*/

    char chemin_annonce[100] = { "" };
    char chemin_possibilite[100] = { "" };

    strcpy(chemin_annonce, chemin);
    strcpy(chemin_possibilite, chemin);

    strcat(chemin_annonce, "annonce_choix_profil.txt");
    strcat(chemin_possibilite, "annonce_possibilite_profil.txt");

    int compteur = 0;

    if (rep != NULL)
    {
        affichage_texte(chemin_annonce);
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL)
        {
            if(compteur > 1 && compteur < 12)//on n'affiche pas . et ..
                printf("%s\t\t(%d)\n", ent->d_name,compteur - 2);
            if (compteur < 12)
                compteur++;
        }
        affichage_texte(chemin_possibilite);

        closedir(rep);
    }
    return compteur-2; //on renvoie le nombre exact de profil existant

}

/*========================================================================================
On d�finit la fonction permettant de r�cup�rer l'adresse d'acc�s du profil s�lectionn�
=========================================================================================*/

char * recup_adresse(int choix)
{
    int compteur = 0;
    int i = 1;
    char * adresse = malloc(sizeof(char));
    char chemin[100] = ".\\User\\"; //on d�finit le chemin par d�faut
    DIR * rep = opendir(chemin);

    if (rep != NULL)
    {
        struct dirent * ent = readdir(rep);

    //tant qu'on a pas atteint le choix de l'utilisateur, on parcours les �l�ments

        while (i != 0 && ent != NULL )
        {
            if(compteur == choix + 2)
            {
                i = 0;
            }
            else
            {
                ent = readdir(rep);
                compteur++;
            }

        }
        adresse = ent->d_name;
        closedir(rep);
    }

    //on cr�e l'adresse compl�te du profil avant de la renvoyer

    strcat(chemin, adresse);
    strcat(chemin, "\\");
    adresse = chemin;
    return adresse;

}
/*==========================================================
Fonction permettant de supprimer un profil
==========================================================*/

void suppression_profil(char * chemin)
{
    DIR * rep = opendir(".\\User\\"); //permet d'afficher l'ensemble des �l�ments contenu � l'adresse sp�cifi�

    int compteur = 0;
    int choix = 0;
    int i = 0;
    char * adresse = malloc(sizeof(char));
    char * adresse_copie = malloc(100 * sizeof(char));

    char selection_suppression[100] = { "" };
    char retour[100] = { "" };
    char erreur[100] = { "" };

    strcpy(selection_suppression, chemin);
    strcpy(retour, chemin);
    strcpy(erreur, chemin);

    strcat(selection_suppression,"selection_suppression_profil.txt");
    strcat(retour, "retour_suppr.txt");
    strcat(erreur, "erreur.txt");

    if (rep != NULL)
    {
        affichage_texte(selection_suppression); //on affiche tous les profils disponible
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL)
        {
            if(compteur > 1)//on n'affiche pas . et ..
                printf("%s\t\t(%d)\n", ent->d_name, compteur - 2);
            compteur++;
        }
        closedir(rep);
    }
    affichage_texte(retour);

    while(i == 0)
    {
        scanf("%d",&choix);
        if(choix < 0 || choix >= 11)
            affichage_texte(erreur);
        else
        {
            if (choix == 10)
                return;
            else
            {
                adresse = recup_adresse(choix); //on r�cup�re l'adresse du profil � supprimer
                memcpy(adresse_copie, adresse, 100);//on fait une copie pour �viter la perte de l'adresse
                suppressionDossier(adresse_copie);//puis on le supprime
                i = 1;
            }
        }
    }
    return;

}

/*==============================================================
Fonction menu de choix des profils utilisateur
==============================================================*/

char * menuProfil(char * chemin)
{
    int compteur = 0;
    int i = 0;
    char pseudo[100];
    char * adresse = malloc(sizeof(char));
    char * adresse_copie = malloc(100 * sizeof(char));//pour ne pas perdre l'info en sortie de recup_adresse
    int choix = -1;

    char chemin_aucun[100] = { "" };
    char erreur[100] = { "" };
    char demande_nom[100] = { "" };
    char profil_supprime[100] = { "" };
    char nom_complet[100] = { "" };

    strcpy(chemin_aucun, chemin);
    strcpy(erreur, chemin);
    strcpy(demande_nom, chemin);
    strcpy(profil_supprime, chemin);
    strcpy(nom_complet, chemin);

    strcat(chemin_aucun, "utilisateur_inexistant.txt");
    strcat(erreur, "erreur.txt");
    strcat(demande_nom, "demande_nom_profil.txt");
    strcat(profil_supprime, "annonce_suppression_profil.txt");
    strcat(nom_complet, "annonce_profil_plein.txt");
    verif_User();

    while(i == 0)
    {
        compteur = affichageProfil(chemin);
        if (compteur <= 0)//si le compteur vaut 0, il n'y a pas de profil, il faut donc en cr�er un
        {
            cls();
            affichage_texte(chemin_aucun);
            scanf("%s", pseudo);
            adresse = creation_dossier(pseudo, chemin);
            memcpy(adresse_copie, adresse, 100);
            i = 1;
        }
        else
        {
            scanf("%d", &choix);

            if(choix < 0 || choix >=12)
                affichage_texte(erreur);

            if(choix >= 0 && choix <10)//le joueur choisit un profil existant
            {
                adresse = recup_adresse(choix);
                memcpy(adresse_copie, adresse, 100);
                i = 1;
            }


            if(choix == 10)//le joueur cr�e un profil
                {
                    if(compteur <10)
                    {
                        cls();
                        affichage_texte(demande_nom);
                        scanf("%s", pseudo);
                        adresse = creation_dossier(pseudo, chemin);
                        memcpy(adresse_copie, adresse, 100);
                        if(strcmp(adresse_copie, "a"))
                        {
                            i = 1;
                        }

                        cls();
                    }
                    else
                    {
                        cls();
                        affichage_texte(nom_complet);
                        sleep(2);
                        cls();
                    }

                }
            if(choix == 11)//le joueur supprime un profil
            {
                cls();
                suppression_profil(chemin);
                cls();
                affichage_texte(profil_supprime);
                cls();
            }

        }
    }
    return adresse_copie;
}

#else

char * recup_pseudo(char * chemin)
{
    char * pseudo = malloc(100 * sizeof(char));
    char chemin_nom[100] = { "" };

    strcat(chemin_nom, chemin);
    strcat(chemin_nom, "nom.txt");

    FILE * temp = fopen(chemin_nom, "r");
    fscanf(temp, "%s", pseudo);
    fclose(temp);

    return pseudo;
}

int affichageProfil(char * chemin)
{
     DIR * rep = opendir("./User/"); //permet d'afficher l'ensemble des �l�ments contenu � l'adresse sp�cifi�

/* permet de r�cup�rer le chemin absolu de l'exectuable    */

    /*char * chemin = NULL;
    chemin = getcwd(chemin,1024);
    printf("%s\n",chemin);*/
/*======================================*/

    char chemin_annonce[100] = { "" };
    char chemin_possibilite[100] = { "" };

    strcpy(chemin_annonce, chemin);
    strcpy(chemin_possibilite, chemin);

    strcat(chemin_annonce, "annonce_choix_profil.txt");
    strcat(chemin_possibilite, "annonce_possibilite_profil.txt");

    int compteur = 0;

    if (rep != NULL)
    {
        affichage_texte(chemin_annonce);
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL)
        {
            if(strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..") && compteur < 10)//on n'affiche pas . et ..
                {
		    printf("%s\t\t(%d)\n", ent->d_name,compteur);
		    compteur++;
		}
        }
        affichage_texte(chemin_possibilite);

        closedir(rep);
    }

    return compteur; //on renvoie le nombre exact de profil existant

}

char * recup_adresse(int choix)
{
    int compteur = 0;
    int i = 1;
    char * adresse = malloc(100 * sizeof(char));
    char chemin[100] = "./User/"; //on d�finit le chemin par d�faut
    DIR * rep = opendir(chemin);

    if (rep != NULL)
    {
        struct dirent * ent = readdir(rep);

    //tant qu'on a pas atteint le choix de l'utilisateur, on parcours les �l�ments

        while (i != 0 && ent != NULL )
        {

	    if(!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..") || compteur >= 10)
		ent = readdir(rep);
	    else{

		    if(compteur == choix)
		    {
		        i = 0;
		    }
		    else
		    {
		        compteur++;
			ent = readdir(rep);

		    }



		}

        }

        strcpy(adresse, ent->d_name);
        closedir(rep);
    }
    //on cr�e l'adresse compl�te du profil avant de la renvoyer

    strcat(chemin, adresse);
    strcat(chemin, "/");
    strcpy(adresse, chemin);
    return adresse;

}

void suppression_profil(char * chemin)
{
    DIR * rep = opendir("./User/"); //permet d'afficher l'ensemble des �l�ments contenu � l'adresse sp�cifi�

    int compteur = 0;
    int choix = 0;
    int i = 0;
    char * adresse = malloc(sizeof(char));
    char * adresse_copie = malloc(100 * sizeof(char));

    char selection_suppression[100] = { "" };
    char retour[100] = { "" };
    char erreur[100] = { "" };

    strcpy(selection_suppression, chemin);
    strcpy(retour, chemin);
    strcpy(erreur, chemin);

    strcat(selection_suppression, "selection_suppression_profil.txt");
    strcat(retour, "retour_suppr.txt");
    strcat(erreur, "erreur.txt");

    if (rep != NULL)
    {
        affichage_texte(selection_suppression); //on affiche tous les profils disponible
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL)
        {
            if(strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..") && compteur < 10)
                {
		     printf("%s\t\t(%d)\n", ent->d_name, compteur);
            	     compteur++;
		}
        }
        closedir(rep);
    }
    affichage_texte(retour);

    while(i == 0)
    {
        scanf("%d",&choix);
        if(choix < 0 || choix >= 11)
            affichage_texte(erreur);
        else
        {
            if (choix == 10)
                return;
            else
            {
                adresse = recup_adresse(choix); //on r�cup�re l'adresse du profil � supprimer
                strcpy(adresse_copie, adresse);//on fait une copie pour �viter la perte de l'adresse
                suppressionDossier(adresse_copie);//puis on le supprime
                i = 1;
            }
        }
    }
    return;

}


char * menuProfil(char * chemin)
{
    int compteur = 0;
    int i = 0;
    char pseudo[100];
    char * adresse = malloc(sizeof(char));
    char * adresse_copie = malloc(100 * sizeof(char));//pour ne pas perdre l'info en sortie de recup_adresse
    int choix = -1;

    char chemin_aucun[100] = { "" };
    char erreur[100] = { "" };
    char demande_nom[100] = { "" };
    char profil_supprime[100] = { "" };
    char nom_complet[100] = { "" };

    strcpy(chemin_aucun,chemin);
    strcpy(erreur,chemin);
    strcpy(demande_nom,chemin);
    strcpy(profil_supprime,chemin);
    strcpy(nom_complet,chemin);

    strcat(chemin_aucun, "utilisateur_inexistant.txt");
    strcat(erreur, "erreur.txt");
    strcat(demande_nom, "demande_nom_profil.txt");
    strcat(profil_supprime, "annonce_suppression_profil.txt");
    strcat(nom_complet, "annonce_profil_plein.txt");
    verif_User();

    while(i == 0)
    {
        compteur = affichageProfil(chemin);
        if (compteur <= 0)//si le compteur vaut 0, il n'y a pas de profil, il faut donc en cr�er un
        {
            cls();
            affichage_texte(chemin_aucun);
            scanf("%s", pseudo);
            adresse = creation_dossier(pseudo, chemin);
            strcpy(adresse_copie, adresse);
            i = 1;
        }
        else
        {

            scanf("%d", &choix);

            if(choix < 0 || choix >=12)
                affichage_texte(erreur);

            if(choix >= 0 && choix <10)//le joueur choisit un profil existant
            {
                adresse = recup_adresse(choix);
                strcpy(adresse_copie, adresse);
                i = 1;
            }


            if(choix == 10)//le joueur cr�e un profil
                {
                    if(compteur <10)
                    {
                        cls();
                        affichage_texte(demande_nom);
                        scanf("%s", pseudo);
                        adresse = creation_dossier(pseudo, chemin);
                        strcpy(adresse_copie, adresse);
                        if(strcmp(adresse_copie, "a"))
                        {
                            i = 1;
                        }
                        cls();
                    }
                    else
                    {
                        cls();
                        affichage_texte(nom_complet);
                        sleep(3);
                        cls();
                    }

                }
            if(choix == 11)//le joueur supprime un profil
            {
                cls();
                suppression_profil(chemin);
                cls();
                affichage_texte(profil_supprime);
                cls();
            }

        }
    }

    return adresse_copie;
}

#endif // defined

void verif_User()
{
    int verif = verif_directory_user();
    if (verif == 0)
        make_directory("User");
}
