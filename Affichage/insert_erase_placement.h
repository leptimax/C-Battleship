
#ifndef INSERT_ERASE_PLACEMENT_H_
#define INSERT_ERASE_PLACEMENT_H_

Out_boat *suppression_Tous_Bateaux(EnsembleC * ensemblec, Taille * liste_long);
Out_boat *suppression_Un_Bateau(Taille * liste_long, EnsembleC * ensemblec, char * chemin);

Ensemble *insertion_Ensemble_choixcoord(Ensemble *ensemble,
                                        Coordonnees *liste_coord,
                                        Coordonnees *place_dispo);

Coordonnees *insertion_Coord_Ensemble(Coordonnees *liste, Ensemble *ensemble);
Coordonnees *suppression_Coord(Coordonnees *place_dispo, int x, int y);

#endif

