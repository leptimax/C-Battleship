
/* D�finition du nom de l'appel syst�me d'effacement de l'�cran actuel en
   fonction du syst�me */
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64
#define CLEAN_SCREEN "CLS"
#elif defined __linux
#define CLEAN_SCREEN "clear"
#endif

