
#ifndef FONCTION_AFFICHAGE_H_
#define FONCTION_AFFICHAGE_H_
#include "../Systeme/ansi_windows.h"
int Definition_Couleur(char couleur, Color * couleur_applicable);
void affichage(char tableau_joueur[10][10], char tableau_ennemi[10][10],
               char pseudo_joueur[], char pseudo_ennemi[],Color * couleur_applicable);
void affichageInitialisation(char tableau_joueur[10][10],Color * couleur_applicale);
void affichage_texte(char * chemin);

#endif

