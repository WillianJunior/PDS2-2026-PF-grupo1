#include "console_utils.hpp"
#include <iostream>
#include <cstdlib> 

void ConsoleUtils::limparTela() {
    #if defined(_WIN32) || defined(_WIN64)
        std::system("cls");
    #else
        std::system("clear");
    #endif
}