#include "console_utils.hpp"
#include <cstdlib>
#include <iostream>

void ConsoleUtils::limparTela() {
    if (std::getenv("AMBIENTE_DE_TESTE") != nullptr)
        return;

#if defined(_WIN32) || defined(_WIN64)
    std::system("cls"); // LCOV_EXCL_LINE
#else
    std::system("clear"); // LCOV_EXCL_LINE
#endif
}

void ConsoleUtils::aguardarUsuario() {
    if (std::getenv("AMBIENTE_DE_TESTE") != nullptr)
        return;

    std::cout << "Pressione Enter para continuar..."; // LCOV_EXCL_LINE
    std::cin.get();                                   // LCOV_EXCL_LINE
}