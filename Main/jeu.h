#ifndef JEU_H_
#define JEU_H_

void afficheTableau(char tableau_joueur[10][10], EnsembleC * ensemble, Color * couleur_applicable);
Joueur * initialisation_joueur(char tableau_joueur[10][10], char * chemin, Color * couleur_applicable);
Sortie * initialisation_variable_IA();
float conversion_time(float temps);
int choix_IA(char * chemin);
int jeu(int compteur_bateau_touche_IA, int compteur_joueur,
        char tableau_joueur[10][10],
        char tableau_ennemi[10][10], char pseudo_joueur[], char pseudo_ennemi[],
        Coordonnees * emplacement_bateau_IA,
        Coordonnees * emplacement_bateau_joueur, int lvl_IA, char * chemin, Color * couleur_applicable,
        char * chemin_profil,int langue, Joueur * bateau_joueur,Joueur * emplacement, Save * donnee_save,
        int temps_depart, Coordonnees * liste_tir_joueur, Coordonnees * coordonnee_tir_IA, Coordonnees * tir_touche_IA);

Joueur * verif_destruction_ennemi(Joueur * bateau_complet, Joueur * bateau, int x, int y,char * chemin);


#endif


