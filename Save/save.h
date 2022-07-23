#ifndef SAVE_H
#define SAVE_H

typedef struct save
{
    char * time;
    char * pseudo_ennemi;
    int lvl_IA;
    int nb_case_restante;
    int compteur_schema;

    int compteur_bateau_touche_IA;
    int compteur_joueur;
    int temps_jeu;

    Joueur * verif_bateau_joueur;
    Joueur * verif_bateau_IA;
    Joueur * bateau_joueur;
    Joueur * bateau_IA;

    Coordonnees * emplacement_bateau_joueur;
    Coordonnees * emplacement_bateau_IA;
    Coordonnees * liste_tir_joueur;
    Coordonnees * coordonnee_tir_IA;
    Coordonnees * tir_touche_IA;
    Coordonnees * cases_restantes;
}Save;

typedef struct save_replay
{
    char * time;
    char * pseudo_ennemi;
    int lvl_IA;
    int nb_coup;
    int victoire;
    Coordonnees * emplacement_bateau_joueur;
    Coordonnees * emplacement_bateau_IA;
    Coordonnees * liste_tir_joueur;
    Coordonnees * coordonnee_tir_IA;

}Save_replay;

typedef struct saveslots_info
{
    int saveslot_number;
    char * time;
    char * pseudo_ennemi;
    int lvl_IA;
    struct saveslots_info * suivant;
}Saveslots_Info;

typedef struct sortie_coordonnee
{
    int x;
    int compteur;
}Sortie_coordonnee;

typedef struct infos_saveslot_sortie
{
    Saveslots_Info * SSinfo;
    Saveslots_Info * SSinfo_tail;
}Infos_saveslot_sortie;

void affichage_quicksave(int * save, Saveslots_Info * SSinfo, char * chemin);
void affichage_save_suppr(int * save, Saveslots_Info * SSinfo, char * chemin);
void affichage_save(int * save, Saveslots_Info * SSinfo, char * chemin);
int * liste_save(char * chemin);
int quicksave(Save * ssave, char* chemin, char * chemin_langue);
int delete_saveslot(int numero_saveslot, char * chemin);
int save_game(int save_number, Save * ssave, char * chemin, char * chemin_langue);
int replace_savefile(char * file, int save_number, Save * ssave, char * chemin);
void make_saveslot(FILE * file, int save_number, Save * ssave);
void save_joueur(FILE * savefile, Joueur * player);
void save_coord(FILE * savefile, Coordonnees * coord);
int verif_saveslot(char * chemin, char * savefile_name);

#endif // SAVE_H
