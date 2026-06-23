// LCOV_EXCL_START

#include "aplicacao.hpp"
#include "console_utils.hpp"
#include "domain/restaurar_entrada_cin.hpp" 
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
    std::ifstream arquivoEntrada;
    std::streambuf *const entradaOriginal = std::cin.rdbuf();
    const bool modoAutomatico = argc > 1;

    if (modoAutomatico) {
        arquivoEntrada.open(argv[1]);
        if (!arquivoEntrada.is_open()) {
            ConsoleUtils::limparTela();
            std::cerr << "[ERRO] Nao foi possivel abrir o arquivo de entrada: " << argv[1] << "\n";
            return 1;
        }

        std::cin.rdbuf(arquivoEntrada.rdbuf());
        std::cout << "[demo] Lendo comandos de: " << argv[1] << "\n\n";
    }

    RestaurarEntradaCin restaurarEntrada{entradaOriginal};

    Aplicacao app(modoAutomatico);
    app.executar();

    return 0;
}

// LCOV_EXCL_STOP