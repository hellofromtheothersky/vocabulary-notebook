#include "screen.h"
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}
void textcolor(int x)
{
    HANDLE mau;
    mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau, x);
}
void ERROR_TO_CLOSE()
{
    system("pause"); exit(0);
}
void Print_arow()
{
    textcolor(14);
    std::cout << "-->";
}
void space(int k)
{
    for (int i = 0; i < k; i++) std::cout << " ";
}