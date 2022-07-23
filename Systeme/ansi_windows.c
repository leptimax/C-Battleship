
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64
/* Tout le code qui suit cette condition sera compil�e uniquement si on est sur
   un syst�me Windows. */
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

static HANDLE stdoutHandle;
static DWORD outModeInit;

/*==============================================================================
   Fonction permettant de configurer le terminal Windows pour qu'il puisse
   reconnaitre les s�quences ANSI utilis�es pour la gestion des couleurs de
   printf.
==============================================================================*/

void setupConsole(void)
{
    DWORD outMode = 0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    /* gestion des erreurs si jamais pour une raison quelconque on ne peut se
       servir des Handle Windows */
    if (stdoutHandle == INVALID_HANDLE_VALUE)
    {
        exit(GetLastError());
    }

    // r�cup�ration de l'�tat actuel du terminal Windows
    if (!GetConsoleMode(stdoutHandle, &outMode))
    {
        exit(GetLastError());
    }
    outModeInit = outMode;

    // Active la reconnaissance des s�quences ANSI pour le terminal Windows
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(stdoutHandle, outMode))
    {
        exit(GetLastError());
    }
}

/*==============================================================================
   Fonction permettant de remettre le terminal Windows dans son mode de
   fonctionnement normal.
==============================================================================*/

void restoreConsole(void)
{
    /* Restaure le terminal Windows � son �tat ant�rieur � la derni�re
       utilisation de la fonction setupConsole */
    if (!SetConsoleMode(stdoutHandle, outModeInit))
    {
        exit(GetLastError());
    }
}

#else /* Si on n'est pas dans un environnement Windows, on n'a pas besoin des
         fonctions ci-dessus donc on les d�finit comme �tant vides. */
void setupConsole(void)
{
}

void restoreConsole(void)
{
}

#endif

