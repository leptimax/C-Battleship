#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

#else

#include <stdio.h>
#include <time.h>

#include <unistd.h>   //  kbhit
#include <sys/time.h> //  kbhit

#include <termios.h>  //  raw
#include <unistd.h>   //  raw


void mode_raw(int activer)                             // passer le terminal en mode brut permet de détecter l'arrivée de caractères dès leur frappe, comme avec _kbhit, sans attendre "entrée"
{
    static struct termios cooked;
    static int raw_actif = 0;

    if (raw_actif == activer)
        return;

    if (activer)
    {
        struct termios raw;

        tcgetattr(STDIN_FILENO, &cooked);

        raw = cooked;
        cfmakeraw(&raw);
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    }
    else
        tcsetattr(STDIN_FILENO, TCSANOW, &cooked);

    raw_actif = activer;
}



int getch(void)
{
        int ch;
        struct termios oldt, newt;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON|ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return ch;
}


int kbhit(void)
{
    struct timeval tv = { 0, 0 };
    fd_set readfds;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    return select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv) == 1;
}

#endif // defined
