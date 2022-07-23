#include "gestion_couleur.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../../Affichage/fonction_affichage.h"

/*=======================================================
Fonction g�rant la gestion des changements des couleurs
========================================================*/

int gestion_couleur_complete(int choix_langue, char * chemin_langue, char * profil)
{
    Couleurs * temp = malloc(sizeof(Couleurs));

    int x_b, y_b, x_r, y_r, x_t, y_t, i, verif;
    char a, b, c;
    char * bateau = malloc(sizeof(char));
    char * rate = malloc(sizeof(char));
    char * touche = malloc(sizeof(char));

    char erreur_couleur[100] = { "" };
    char erreur[100] = { "" };

    strcpy(erreur_couleur, chemin_langue);
    strcpy(erreur, chemin_langue);

    strcat(erreur_couleur, "erreur_couleur.txt");
    strcat(erreur, "erreur.txt");

    Liste_couleur * nouvelle_couleur = malloc(sizeof(Liste_couleur));
    char * couleur = malloc(sizeof(char));
    char * color = malloc(sizeof(char));
    char * color_es = malloc(sizeof(char));
    char * color_de = malloc(sizeof(char));
    char * color_is = malloc(sizeof(char));
    char * color_it = malloc(sizeof(char));
    char * color_ne = malloc(sizeof(char));

    char parametre_joueur_fr[100] = { "" };
    char parametre_joueur_en[100] = { "" };
    char parametre_joueur_es[100] = { "" };
    char parametre_joueur_is[100] = { "" };
    char parametre_joueur_ne[100] = { "" };
    char parametre_joueur_it[100] = { "" };
    char parametre_joueur_de[100] = { "" };

    char new_fr[100] = { "" };
    char new_en[100] = { "" };
    char new_es[100] = { "" };
    char new_de[100] = { "" };
    char new_is[100] = { "" };
    char new_it[100] = { "" };
    char new_ne[100] = { "" };

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

    char daltonien_fr[] = ".\\Parametres&Langues\\FR\\DALTONIEN.txt";
    char daltonien_en[] = ".\\Parametres&Langues\\EN\\DALTONIEN.txt";
    char daltonien_es[] = ".\\Parametres&Langues\\ES\\DALTONIEN.txt";
    char daltonien_de[] = ".\\Parametres&Langues\\DE\\DALTONIEN.txt";
    char daltonien_is[] = ".\\Parametres&Langues\\IS\\DALTONIEN.txt";
    char daltonien_it[] = ".\\Parametres&Langues\\IT\\DALTONIEN.txt";
    char daltonien_ne[] = ".\\Parametres&Langues\\NE\\DALTONIEN.txt";

    char defaut_fr[100] = ".\\Parametres&Langues\\FR\\DEFAULT.txt";
    char defaut_en[100] = ".\\Parametres&Langues\\EN\\DEFAULT.txt";
    char defaut_es[100] = ".\\Parametres&Langues\\ES\\DEFAULT.txt";
    char defaut_de[100] = ".\\Parametres&Langues\\DE\\DEFAULT.txt";
    char defaut_ne[100] = ".\\Parametres&Langues\\NE\\DEFAULT.txt";
    char defaut_is[100] = ".\\Parametres&Langues\\IS\\DEFAULT.txt";
    char defaut_it[100] = ".\\Parametres&Langues\\IT\\DEFAULT.txt";

#else

    char daltonien_fr[] = "./Parametres&Langues/FR/DALTONIEN.txt";
    char daltonien_en[] = "./Parametres&Langues/EN/DALTONIEN.txt";
    char daltonien_es[] = "./Parametres&Langues/ES/DALTONIEN.txt";
    char daltonien_de[] = "./Parametres&Langues/DE/DALTONIEN.txt";
    char daltonien_is[] = "./Parametres&Langues/IS/DALTONIEN.txt";
    char daltonien_it[] = "./Parametres&Langues/IT/DALTONIEN.txt";
    char daltonien_ne[] = "./Parametres&Langues/NE/DALTONIEN.txt";

    char defaut_fr[100] = "./Parametres&Langues/FR/DEFAULT.txt";
    char defaut_en[100] = "./Parametres&Langues/EN/DEFAULT.txt";
    char defaut_es[100] = "./Parametres&Langues/ES/DEFAULT.txt";
    char defaut_de[100] = "./Parametres&Langues/DE/DEFAULT.txt";
    char defaut_ne[100] = "./Parametres&Langues/NE/DEFAULT.txt";
    char defaut_is[100] = "./Parametres&Langues/IS/DEFAULT.txt";
    char defaut_it[100] = "./Parametres&Langues/IT/DEFAULT.txt";

#endif // defined

    strcpy(parametre_joueur_fr, profil);
    strcpy(parametre_joueur_en, profil);
    strcpy(parametre_joueur_es, profil);
    strcpy(parametre_joueur_ne, profil);
    strcpy(parametre_joueur_de, profil);
    strcpy(parametre_joueur_is, profil);
    strcpy(parametre_joueur_it, profil);

    strcpy(new_fr, profil);
    strcpy(new_en, profil);
    strcpy(new_es, profil);
    strcpy(new_ne, profil);
    strcpy(new_it, profil);
    strcpy(new_is, profil);
    strcpy(new_de, profil);

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

    strcat(parametre_joueur_fr, "Parametres\\parametres_joueurs.txt");
    strcat(parametre_joueur_en, "Parametres\\parametres_joueurs_en.txt");
    strcat(parametre_joueur_es, "Parametres\\parametres_joueurs_es.txt");
    strcat(parametre_joueur_de, "Parametres\\parametres_joueurs_de.txt");
    strcat(parametre_joueur_ne, "Parametres\\parametres_joueurs_ne.txt");
    strcat(parametre_joueur_is, "Parametres\\parametres_joueurs_is.txt");
    strcat(parametre_joueur_it, "Parametres\\parametres_joueurs_it.txt");

    strcat(new_fr, "Parametres\\temp.txt");
    strcat(new_en, "Parametres\\temp_EN.txt");
    strcat(new_de, "Parametres\\temp_DE.txt");
    strcat(new_ne, "Parametres\\temp_NE.txt");
    strcat(new_es, "Parametres\\temp_ES.txt");
    strcat(new_is, "Parametres\\temp_IS.txt");
    strcat(new_it, "Parametres\\temp_IT.txt");

#else

    strcat(parametre_joueur_fr, "Parametres/parametres_joueurs.txt");
    strcat(parametre_joueur_en, "Parametres/parametres_joueurs_en.txt");
    strcat(parametre_joueur_es, "Parametres/parametres_joueurs_es.txt");
    strcat(parametre_joueur_de, "Parametres/parametres_joueurs_de.txt");
    strcat(parametre_joueur_ne, "Parametres/parametres_joueurs_ne.txt");
    strcat(parametre_joueur_is, "Parametres/parametres_joueurs_is.txt");
    strcat(parametre_joueur_it, "Parametres/parametres_joueurs_it.txt");

    strcat(new_fr, "Parametres/temp.txt");
    strcat(new_en, "Parametres/temp_EN.txt");
    strcat(new_de, "Parametres/temp_DE.txt");
    strcat(new_ne, "Parametres/temp_NE.txt");
    strcat(new_es, "Parametres/temp_ES.txt");
    strcat(new_is, "Parametres/temp_IS.txt");
    strcat(new_it, "Parametres/temp_IT.txt");

#endif // defined



    int boucle = 1;

    while (boucle == 1)
    {
    FILE * fichier = fopen(parametre_joueur_fr, "r+");
    FILE * file = fopen(parametre_joueur_en, "r+");
    FILE * file1 = fopen(parametre_joueur_es, "r+");
    FILE * file2 = fopen(parametre_joueur_ne, "r+");
    FILE * file3 = fopen(parametre_joueur_de, "r+");
    FILE * file4 = fopen(parametre_joueur_is, "r+");
    FILE * file5 = fopen(parametre_joueur_it, "r+");

    FILE * pointeur = NULL;
    switch(choix_langue)
    {
    case 0:
        pointeur = fichier;
        break;
    case 1:
        pointeur = file;
        break;
    }

/*on r�cup�re les infos du fichier parametre a afficher dans le menu*/
    if (fichier != NULL)
    {

        fscanf(pointeur, "%d %d %s %c", &x_b, &y_b, bateau, &a);
        fscanf(pointeur, "%d %d %s %c", &x_r, &y_r, rate, &b);
        fscanf(pointeur, "%d %d %s %c", &x_t, &y_t, touche, &c);


        temp = menu_couleurs(bateau, rate, touche, chemin_langue); //on affiche le menu et on r�cup�re le choix de l'utilisateur

        if(temp->y != 8)
        {
            nouvelle_couleur = defCouleur(temp->y); // on r�cup�re la nouvelle couleur

//on r�cup�re les couleurs dans chaque langue

            couleur = nouvelle_couleur->FR;
            color = nouvelle_couleur->EN;
            color_de = nouvelle_couleur->DE;
            color_es = nouvelle_couleur->ES;
            color_is = nouvelle_couleur->IS;
            color_it = nouvelle_couleur->IT;
            color_ne = nouvelle_couleur->NE;
        }


        fflush(stdout);//on vide le buffer

        switch(temp->x)
        {
            case 4 :
        {
            FILE * nouveau = fopen(new_fr, "w"); // on cr�e un nouveau fichier param�tre qui remplacera le pr�cedent
            FILE * newfile = fopen(new_en, "w");
            FILE * newfile1 = fopen(new_es, "w");
            FILE * newfile2 = fopen(new_de, "w");
            FILE * newfile3 = fopen(new_ne, "w");
            FILE * newfile4 = fopen(new_is, "w");
            FILE * newfile5 = fopen(new_it, "w");

            FILE * FR = fopen(daltonien_fr, "r+");
            FILE * EN = fopen(daltonien_en, "r+");
            FILE * ES = fopen(daltonien_es, "r+");
            FILE * NE = fopen(daltonien_ne, "r+");
            FILE * DE = fopen(daltonien_de, "r+");
            FILE * IS = fopen(daltonien_is, "r+");
            FILE * IT = fopen(daltonien_it, "r+");

            daltonien(FR, nouveau);
            daltonien(EN, newfile);
            daltonien(ES, newfile1);
            daltonien(NE, newfile3);
            daltonien(DE, newfile2);
            daltonien(IS, newfile4);
            daltonien(IT, newfile5);

            fclose(FR);
            fclose(EN);
            fclose(NE);
            fclose(DE);
            fclose(IS);
            fclose(IT);
            fclose(ES);

            fclose(nouveau);
            fclose(newfile);
            fclose(newfile1);
            fclose(newfile2);
            fclose(newfile3);
            fclose(newfile4);
            fclose(newfile5);

            fclose(fichier);
            fclose(file);
            fclose(file1);
            fclose(file2);
            fclose(file3);
            fclose(file4);
            fclose(file5);

            remove(parametre_joueur_fr);
            remove(parametre_joueur_en);
            remove(parametre_joueur_ne);
            remove(parametre_joueur_es);
            remove(parametre_joueur_de);
            remove(parametre_joueur_is);
            remove(parametre_joueur_it);

            rename(new_fr, parametre_joueur_fr);
            rename(new_en, parametre_joueur_en);
            rename(new_ne, parametre_joueur_ne);
            rename(new_de, parametre_joueur_de);
            rename(new_es, parametre_joueur_es);
            rename(new_is, parametre_joueur_is);
            rename(new_it, parametre_joueur_it);
            sleep(1);


            break;
        }
        case 5 :
        {
            FILE * nouveau = fopen(new_fr, "w"); // on cr�e un nouveau fichier param�tre qui remplacera le pr�cedent
            FILE * newfile = fopen(new_en, "w");
            FILE * newfile1 = fopen(new_es, "w");
            FILE * newfile2 = fopen(new_de, "w");
            FILE * newfile3 = fopen(new_ne, "w");
            FILE * newfile4 = fopen(new_is, "w");
            FILE * newfile5 = fopen(new_it, "w");

            FILE * FR = fopen(defaut_fr, "r+");
            FILE * EN = fopen(defaut_en, "r+");
            FILE * ES = fopen(defaut_es, "r+");
            FILE * NE = fopen(defaut_ne, "r+");
            FILE * DE = fopen(defaut_de, "r+");
            FILE * IS = fopen(defaut_is, "r+");
            FILE * IT = fopen(defaut_it, "r+");

            raz(FR, nouveau);
            raz(EN, newfile);
            raz(ES, newfile1);
            raz(DE, newfile2);
            raz(NE, newfile3);
            raz(IS, newfile4);
            raz(IT, newfile5);

            fclose(FR);
            fclose(EN);
            fclose(NE);
            fclose(DE);
            fclose(IS);
            fclose(IT);
            fclose(ES);

            fclose(nouveau);
            fclose(newfile);
            fclose(newfile1);
            fclose(newfile2);
            fclose(newfile3);
            fclose(newfile4);
            fclose(newfile5);

            fclose(fichier);
            fclose(file);
            fclose(file1);
            fclose(file2);
            fclose(file3);
            fclose(file4);
            fclose(file5);

            remove(parametre_joueur_fr);
            remove(parametre_joueur_en);
            remove(parametre_joueur_ne);
            remove(parametre_joueur_es);
            remove(parametre_joueur_de);
            remove(parametre_joueur_is);
            remove(parametre_joueur_it);

            rename(new_fr, parametre_joueur_fr);
            rename(new_en, parametre_joueur_en);
            rename(new_ne, parametre_joueur_ne);
            rename(new_de, parametre_joueur_de);
            rename(new_es, parametre_joueur_es);
            rename(new_is, parametre_joueur_is);
            rename(new_it, parametre_joueur_it);
            sleep(1);
            break;
        }
        case 6 :
        {

            verif = verification_couleur(profil);
            if (verif == 0)
            {
                cls();
                affichage_texte(erreur_couleur);
                scanf("%d", &i);
                switch (i)
                {
                case 1 :
                    {//razpour toutes les langues
                        FILE * nouveau = fopen(new_fr, "w"); // on cr�e un nouveau fichier param�tre qui remplacera le pr�cedent
                        FILE * newfile = fopen(new_en, "w");
                        FILE * newfile1 = fopen(new_es, "w");
                        FILE * newfile2 = fopen(new_de, "w");
                        FILE * newfile3 = fopen(new_ne, "w");
                        FILE * newfile4 = fopen(new_is, "w");
                        FILE * newfile5 = fopen(new_it, "w");

                        FILE * FR = fopen(defaut_fr, "r+");
                        FILE * EN = fopen(defaut_en, "r+");
                        FILE * ES = fopen(defaut_es, "r+");
                        FILE * NE = fopen(defaut_ne, "r+");
                        FILE * DE = fopen(defaut_de, "r+");
                        FILE * IS = fopen(defaut_is, "r+");
                        FILE * IT = fopen(defaut_it, "r+");

                        raz(FR, nouveau);
                        raz(EN, newfile);
                        raz(ES, newfile1);
                        raz(DE, newfile2);
                        raz(NE, newfile3);
                        raz(IS, newfile4);
                        raz(IT, newfile5);

                        fclose(FR);
                        fclose(EN);
                        fclose(NE);
                        fclose(DE);
                        fclose(IS);
                        fclose(IT);
                        fclose(ES);

                        fclose(nouveau);
                        fclose(newfile);
                        fclose(newfile1);
                        fclose(newfile2);
                        fclose(newfile3);
                        fclose(newfile4);
                        fclose(newfile5);

                        fclose(fichier);
                        fclose(file);
                        fclose(file1);
                        fclose(file2);
                        fclose(file3);
                        fclose(file4);
                        fclose(file5);

                        remove(parametre_joueur_fr);
                        remove(parametre_joueur_en);
                        remove(parametre_joueur_ne);
                        remove(parametre_joueur_es);
                        remove(parametre_joueur_de);
                        remove(parametre_joueur_is);
                        remove(parametre_joueur_it);

                        rename(new_fr, parametre_joueur_fr);
                        rename(new_en, parametre_joueur_en);
                        rename(new_ne, parametre_joueur_ne);
                        rename(new_de, parametre_joueur_de);
                        rename(new_es, parametre_joueur_es);
                        rename(new_is, parametre_joueur_is);
                        rename(new_it, parametre_joueur_it);

                        boucle = 0;
                        break;
                    }
                case 2 :
                    {
                        cls();
                        break;
                    }
                default :
                    {
                        cls();
                        sleep(1);
                        affichage_texte(erreur);
                        cls();
                        break;
                    }

                }

            }
            else
            {
                boucle = 0;
            }
            break;

        }
        default :
        {
            if(temp->y != 8)
            {
                FILE * nouveau = fopen(new_fr, "w"); // on cr�e un nouveau fichier param�tre qui remplacera le pr�cedent
                FILE * newfile = fopen(new_en, "w");
                FILE * newfile1 = fopen(new_es, "w");
                FILE * newfile2 = fopen(new_de, "w");
                FILE * newfile3 = fopen(new_ne, "w");
                FILE * newfile4 = fopen(new_is, "w");
                FILE * newfile5 = fopen(new_it, "w");

                definition_couleur(temp->x, temp->y, fichier, nouveau, couleur);
                definition_couleur(temp->x, temp->y, file, newfile, color);
                definition_couleur(temp->x, temp->y, file1, newfile1, color_es);
                definition_couleur(temp->x, temp->y, file2, newfile3, color_ne);
                definition_couleur(temp->x, temp->y, file3, newfile2, color_de);
                definition_couleur(temp->x, temp->y, file4, newfile4, color_is);
                definition_couleur(temp->x, temp->y, file5, newfile5, color_it);

                fclose(nouveau);
                fclose(newfile);
                fclose(newfile1);
                fclose(newfile2);
                fclose(newfile3);
                fclose(newfile4);
                fclose(newfile5);
                sleep(1);
                fclose(fichier);
                fclose(file);
                fclose(file1);
                fclose(file2);
                fclose(file3);
                fclose(file4);
                fclose(file5);
                sleep(1);
                remove(parametre_joueur_fr);
                remove(parametre_joueur_en);
                remove(parametre_joueur_ne);
                remove(parametre_joueur_es);
                remove(parametre_joueur_de);
                remove(parametre_joueur_is);
                remove(parametre_joueur_it);

                rename(new_fr, parametre_joueur_fr);
                rename(new_en, parametre_joueur_en);
                rename(new_ne, parametre_joueur_ne);
                rename(new_de, parametre_joueur_de);
                rename(new_es, parametre_joueur_es);
                rename(new_is, parametre_joueur_is);
                rename(new_it, parametre_joueur_it);


            }
            break;

        }

        }

        }

    }

        free(temp);
        free(nouvelle_couleur);
        free(bateau);
        free(rate);
        free(touche);


        return 0;

}

/*==============================================================
Fonction permettant d'afficher les couleurs
==============================================================*/

char * Choix_couleur(int choix)
{
    char * couleur  = malloc(sizeof(char));
	FILE * tete = NULL;

#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

    tete = fopen(".\\Parametres&Langues\\liste_couleurs.txt", "r+");

#else

    tete = fopen("./Parametres&Langues/liste_couleurs.txt", "r+");

#endif // defined


	int valeur = 0;
	if (tete == NULL)
		printf("erreur d'ouverture, fermeture du programme");

	else
	{

	// on r�cup�re la couleur s�lectionn� dans la liste
		while (valeur != choix )
		{
            fscanf(tete, "%s %d", couleur, &valeur);
		}
	}
	fclose(tete);
	return couleur;
}

