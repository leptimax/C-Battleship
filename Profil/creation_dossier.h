
#ifndef CREATION_DOSSIER_H
#define CREATION_DOSSIER_H

void make_directory(char * name);
void vide_dossier(char * adresse);
int verif_dossier(char * pseudo);
char * creation_dossier(char pseudo[100],char * chemin);
void suppressionDossier(char * adresse);
void CreationFichier(char * chemin,char * nom,char * original);
int verif_directory_user();
#endif // CREATION_DOSSIER_H

