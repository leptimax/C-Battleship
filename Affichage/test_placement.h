
#ifndef TEST_PLACEMENT_H_
#define TEST_PLACEMENT_H_

Coordonnees * defEmplacement(Coordonnees * liste, Coordonnees * emplacement);
int collision(Coordonnees * place_dispo, int x, int y, int fin, int sens);
Choix * affichageChoix(int xplus, int xmoin, int yplus, int ymoin, int verifxp,
                       int verifxm, int verifyp, int verifym, int x, int y, char * chemin);
Ensemble * ajoutCaseBateau(Coordonnees * place_dispo, Coordonnees * liste_coord,
                           int x, int y, int k, int choix);
EnsembleC *choix_Coord(int k, EnsembleC * ensemble,char * chemin);

#endif


