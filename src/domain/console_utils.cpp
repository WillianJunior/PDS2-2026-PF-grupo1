#include "console_utils.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

void ConsoleUtils::limparTela() {
    if (std::getenv("AMBIENTE_DE_TESTE") != nullptr)
        return;

#if defined(_WIN32) || defined(_WIN64)
    std::system("cls"); // LCOV_EXCL_LINE
#else
    std::system("ls"); // LCOV_EXCL_LINE
#endif
}

void ConsoleUtils::aguardarUsuario() {
    if (std::getenv("AMBIENTE_DE_TESTE") != nullptr)
        return;

    std::cout << "Pressione Enter para continuar..."; // LCOV_EXCL_LINE
    std::cin.get();                                   // LCOV_EXCL_LINE
}

bool ConsoleUtils::lerInteiro(const std::string &linha, int &valor) {
    if (linha.empty())
        return false;
    try {
        size_t pos = 0;
        valor = std::stoi(linha, &pos);
        return pos == linha.size();
    } catch (...) {
        return false;
    }
}

void ConsoleUtils::mostrarCabecalho(const std::string &titulo) {
    std::cout << "\n///////////////////////////////////////\n";
    std::cout << "         " << titulo << "\n";
    std::cout << "\n///////////////////////////////////////\n";
}

void ConsoleUtils::exibirMensagem(const std::string &mensagem) {
    if (!mensagem.empty()) {
        std::cout << mensagem << "\n\n";
    }
}
