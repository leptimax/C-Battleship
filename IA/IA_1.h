
#ifndef IA_1_H_
#define IA_1_H_

Sortie * gestion_coordonnees_tir_LVL1(Coordonnees * coordonnee_tir_IA,char * chemin);
Sortie * IA_LVL_1(int compteur_bateau_touche_IA, char tableau_joueur[][10],
                  Coordonnees * emplacement_bateau_IA,
                  Coordonnees * coordonnee_tir_IA,
                  Coordonnees * emplacement_bateau_joueur,Joueur * bateau,char * chemin,
                  Joueur * bateau_complet);

Joueur * verif_destruction(Joueur * bateau_complet, Joueur * bateau, int x, int y,char * chemin);
#endif

