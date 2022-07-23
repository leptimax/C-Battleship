
/* Définition du nom de l'appel système d'effacement de l'écran actuel en
   fonction du système */
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64
#define CLEAN_SCREEN "CLS"
#elif defined __linux
#define CLEAN_SCREEN "clear"
#endif

