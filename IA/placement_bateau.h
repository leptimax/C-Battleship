
#ifndef PLACEMENT_BATEAU_H_
#define PLACEMENT_BATEAU_H_

//Coordonnees * insertionEnTete(Coordonnees * liste,int x,int y);
Coordonnees * insertion_bateau_IA(Coordonnees * emplacement_bateau_IA,
                                  int debut, int fin, int sens, int coord_2);

Coordonnees * ajout_case_impossible(Coordonnees * cases_impossible, int debut,
                                    int fin, int sens, int coord_2);
int test_collision(Coordonnees * emplacement_bateau_IA, int debut, int fin,
                   int sens, int coord_2);
Sortie * placement_bateau_IA(Coordonnees * emplacement_bateau_IA,
                             Coordonnees * cases_impossible);

#endif

