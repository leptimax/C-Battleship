#ifndef IA_3_H_
#define IA_3_H_

Coordonnees * assignation_schema(int x, int y, int sens);
Coordonnees * emplacement_tir_annihilation_3(Coordonnees * coordonnee_tir_IA,
                                             int x, int y);
Coordonnees * annihilation_3(Coordonnees * coordonnee_tir_IA,
                             Coordonnees * emplacement_bateau_joueur, int temp,
                             Coordonnees * reference);

Sortie * schema(Coordonnees * coordonnee_tir_IA, Coordonnees * tir_touche_IA,
                Coordonnees * emplacement_bateau_joueur,
                Coordonnees * cases_restantes,
                int nb_case_restante);
Sortie * gestion_coordonnees_tir_IA_3(Coordonnees * coordonnee_tir_IA,
                                      Coordonnees * tir_touche_IA,
                                      Coordonnees * emplacement_bateau_joueur,
                                      Coordonnees * cases_restantes,
                                      int nb_case_restante);
Sortie * IA_LVL_3(int compteur_bateau_touche_IA, char tableau_joueur[][10],
                  Coordonnees * emplacement_bateau_IA,
                  Coordonnees * coordonnee_tir_IA,
                  Coordonnees * emplacement_bateau_joueur,
                  Coordonnees * tir_touche_IA,
                  Coordonnees * cases_restantes, int nb_case_restante, Joueur * bateau,
                  char * chemin, Joueur * bateau_complet);

#endif


