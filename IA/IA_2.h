
#ifndef IA_2_H_
#define IA_2_H_

Coordonnees * emplacement_tir_annihilation_2(Coordonnees * coordonnee_tir_IA,
                                             int x, int y);
Coordonnees * annihilation_2(Coordonnees * coordonnee_tir_IA,
                             Coordonnees * emplacement_bateau_joueur, int temp,
                             Coordonnees * reference);

Sortie * gestion_coordonnees_tir_IA_2(Coordonnees * coordonnee_tir_IA,
                                      Coordonnees * tir_touche_IA,
                                      Coordonnees * emplacement_bateau_joueur);
Sortie * IA_LVL_2(int compteur_bateau_touche_IA, char tableau_joueur[][10],
                  Coordonnees * emplacement_bateau_IA,
                  Coordonnees * coordonnee_tir_IA,
                  Coordonnees * emplacement_bateau_joueur,
                  Coordonnees * tir_touche_IA, Joueur * bateau, char * chemin,
                  Joueur * bateau_complet);

#endif

