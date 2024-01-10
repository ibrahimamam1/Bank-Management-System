#include "functions.hpp"
#include<iostream>
#include <limits>

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\x1B[2J\x1B[H";
#endif
}