
#include "../../IA/base.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifndef GESTION_COULEUR_H
#define GESTION_COULEUR_H

Couleurs * menu_couleurs(char * bateau,char * rate, char * touche, char * chemin);
Liste_couleur * defCouleur(int x);
void raz(FILE * fichier,FILE * nouveau);
int verification_couleur(char * profil);
void definition_couleur(int x,int y,FILE * fichier,FILE * nouveau,char * nouvelle_couleur);
Color * recup_Color(char * chemin);
void daltonien(FILE * fichier,FILE * nouveau);
Color * option_couleur(int langue,char * chemin, char * profil);

#endif // GESTION_COULEUR_H
