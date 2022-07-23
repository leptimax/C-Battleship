#ifndef IA_4_H_
#define IA_4_H_

Coordonnees * emplacement_tir_annihilation_4(Coordonnees * coordonnee_tir_IA,
                                             int x, int y);
Coordonnees * emplacement_tir_annihilation_IA_4(Coordonnees * coordonnee_tir_IA,
                                                Coordonnees * tir_touche_IA,
                                                int temp, int sens);
int definition_sens(Coordonnees * tir_touche_IA);
Coordonnees * annihilation_4(Coordonnees * coordonnee_tir_IA,
                             Coordonnees * tir_touche_IA,
                             Coordonnees * emplacement_bateau_joueur, int temp,
                             Coordonnees * reference);
Coordonnees * assignation_schema_lvl_4(int x, int y, int diagonale);
Coordonnees * def_diagonale(int diagonale);

Sortie * tir(Coordonnees * coordonnee_tir_IA, Coordonnees * tir_touche_IA,
             int compteur_schema);
Sortie * schema_IA_lvl_4(Coordonnees * coordonnee_tir_IA,
                         Coordonnees * tir_touche_IA,
                         Coordonnees * emplacement_bateau_joueur,
                         int compteur_schema, Coordonnees * possibilite,
                         int nb_possibilite);

Sortie * gestion_coordonnees_tir_IA_4(Coordonnees * coordonnee_tir_IA,
                                      Coordonnees * tir_touche_IA,
                                      Coordonnees * emplacement_bateau_joueur,
                                      Coordonnees * possibilite,
                                      int nb_possibilite, int compteur_schema);
Sortie * IA_LVL_4(int compteur_bateau_touche_IA, char tableau_joueur[][10],
                  Coordonnees * emplacement_bateau_IA,
                  Coordonnees * coordonnee_tir_IA,
                  Coordonnees * emplacement_bateau_joueur,
                  Coordonnees * tir_touche_IA,
                  Coordonnees * possibilite, int nb_possibilite,
                  int compteur_schema, Joueur * bateau, char * chemin,
                  Joueur * bateau_complet);



#endif


