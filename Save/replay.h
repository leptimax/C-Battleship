#ifndef REPLAY_H
#define REPLAY_H

int * liste_save_replay(char * chemin);
int delete_saveslot_replay(int save_number, char * chemin);
int selection_replay();
Color * pause_replay(char * chemin, char * chemin_profil, int langue, Color * couleur_applicable);
Color * replay(char * chemin, Save_replay * donnee_replay, Color * couleur_applicable, char * pseudo_joueur,
            int langue, char * chemin_profil);
int load_replay(char * chemin, Save_replay * ssave, int save_number);
void make_saveslot_replay(FILE * file, int save_number, Save_replay * ssave);
int replace_replayfile(char * chemin, Save_replay * save );
int modif_nom(char * nom, int nb, char * temp);
int save_replay(Save_replay * ssave, char * chemin, char * chemin_langue);
Saveslots_Info * get_saveslots_info_replay(char * chemin);

#endif // REPLAY_H

