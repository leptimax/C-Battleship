#ifndef BASE_H_
#define BASE_H_

typedef struct coordonnees
{
    int x;
    int y;
    struct coordonnees * suivant;
}Coordonnees;

typedef struct joueur
{
    Coordonnees * PA;
    Coordonnees * C;
    Coordonnees * SM;
    Coordonnees * CT;
    Coordonnees * T;
    Coordonnees * emplacement_complet;
}Joueur;


struct sortie
{
    Coordonnees * liste_tir_IA;
    Coordonnees * liste_touche_IA;
    Coordonnees * coord;
    Coordonnees * cases_restantes;
    Joueur * bateau_complet;
    int compteur_touche;
    int nb_case_restante;
    int compteur_schema;
};
typedef struct sortie Sortie;

typedef struct taille
{
    int taille;
    struct taille *suivant;
}Taille;


typedef struct ensemble
{
    Coordonnees *liste_coord;
    Coordonnees *place_dispo;
    Taille *liste_long;
}Ensemble;

typedef struct ensembleC
{
    Coordonnees *coord_5;
    Coordonnees * coord_5_occupe;

    Coordonnees *coord_4;
    Coordonnees * coord_4_occupe;

    Coordonnees *coord_3_1;
    Coordonnees * coord_3_1_occupe;

    Coordonnees *coord_3_2;
    Coordonnees * coord_3_2_occupe;

    Coordonnees *coord_2;
    Coordonnees * coord_2_occupe;

    Coordonnees *place_dispo;
}EnsembleC;

typedef struct out_boat
{
    int longueur;
    Taille * liste_long;
    EnsembleC * liste;
}Out_boat;

typedef struct choix
{
    int xplus;
    int xmoin;
    int yplus;
    int ymoin;
    int verif;
}Choix;

typedef struct sortie_jeu
{
    char tableau_joueur[10][10];
    char tableau_ennemi[10][10];
    int compteur;
    int compteur_joueur;
}Sortie_jeu;

typedef struct couleurs
{
    int x;
    int y;
}Couleurs;

typedef struct color
{
    int bateau;
    int rate;
    int touche;

}Color;

typedef struct liste_couleur
{
    char * FR;
    char * EN;
    char * ES;
    char * DE;
    char * NE;
    char * IS;
    char * IT;

}Liste_couleur;

typedef struct menu_temp
{
    int x[100];
    int y[100];
    Color * couleur;
}Menu_temp;

void cls(void);
Coordonnees * insertionEnTete(Coordonnees * liste, int x, int y);
Coordonnees * ultimateSuppr(Coordonnees * tir_touche_IA);
Coordonnees * Suppression(Coordonnees * choix_possible, int emplacement);
Coordonnees * insertionEnQueu(Coordonnees * liste, int x, int y);

Taille *insertion_Taille(Taille *liste_long, int longueur);
Taille *suppression(Taille *liste_long, int longueur);
Taille * ultimateSupprTaille(Taille * tir_touche_IA);
Taille * insertion_triee_Taille(Taille * liste, int element);

int verif_liste_tir(Coordonnees * coordonnee_tir_IA, int x, int y);
int verif_bateau_joueur(Coordonnees * emplacement_bateau_joueur, int x, int y);
int compteur_coup(Coordonnees * liste);

void afficher(Coordonnees *liste);
void buffer(char input[]);
#endif
