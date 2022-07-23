#ifndef LOAD_H
#define LOAD_H

int load_save(int save_number, char * chemin, Save * ssave, char * chemin_langue);
Coordonnees * get_coord(Coordonnees * coord, char * buf);
Saveslots_Info * get_saveslots_info(char * chemin);
Infos_saveslot_sortie * get_info(Saveslots_Info * SSinfo, Saveslots_Info * SSinfo_tail, char * file);

#endif // LOAD_H



