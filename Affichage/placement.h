#ifndef PLACEMENT_H_
#define PLACEMENT_H_

/*==============================================================================
        Fonctions de gestion de la liste des coordonnées
==============================================================================*/


//void afficher(Coordonnees *liste);


/*==============================================================================
        Fonctions de gestion pour la fonction Taille
==============================================================================*/


Out_boat * choix_Taille(Taille *liste_long, EnsembleC * ensemblec,
                        char tableau_joueur[10][10], char * chemin,Color * couleur_applicable);


/*==============================================================================
        Structures pour modifier les listes en même temps
==============================================================================*/


EnsembleC *placement_bateau(EnsembleC * ensemblec, int taille,
                            Ensemble *ensemble, Coordonnees *coord_5,
                            Coordonnees *coord_4,
                            Coordonnees *coord_3_1, Coordonnees *coord_3_2,
                            Coordonnees *coord_2, char * chemin);


/*==============================================================================
        Fonctions pour la fonction Choix_Coord
==============================================================================*/

int CoordonneeX(char * chemin);
int CoordonneeY(char * chemin);
int espace_vide(Coordonnees *place, int x, int y, int X, int Y);


//Ensemble *choix_Coord(int x, int y, int k, Coordonnees *liste, Coordonnees *place);


#endif


