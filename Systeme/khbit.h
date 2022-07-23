#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64

#else

#ifndef KHBIT_H
#define KHBIT_H

void mode_raw(int activer);
int kbhit(void);
int getch(void);

#endif




#endif // defined


