

#ifndef HIT_h
#define HIT_H

/*#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

Sortie_coordonnee * CoordonneeX_jeu(char * chemin, int compteur);
int CoordonneeY_jeu(char * chemin, int compteur, int compteur_test);

#else

Sortie_coordonnee * CoordonneeX_jeu(char * chemin, int compteur);
int CoordonneeY_jeu(char * chemin, int compteur);

#endif */// defined

int verification(Coordonnees * liste, int x, int y);
int toucherTir(Coordonnees *liste, int x, int y, char * chemin);
Menu_temp * Tir(Coordonnees * liste, char tableau_joueur[10][10],
                char tableau_ennemi[10][10], char pseudo_joueur[],
                char pseudo_ennemi[],char * chemin,Color * couleur_applicable,
                char * chemin_profil,int langue, Save * donnee_save, int temps_ref, int compteur);




#endif
