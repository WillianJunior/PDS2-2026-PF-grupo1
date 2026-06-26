#include "domain/restaurar_entrada_cin.hpp" 
#include <doctest/doctest.h>
#include <iostream>
#include <sstream>

TEST_SUITE("Restaurar Entrada Cin (RAII)") {

    TEST_CASE("Garante a restauracao automatica do buffer do cin") {
        std::streambuf* bufferOriginalReal = std::cin.rdbuf();
        std::istringstream terminalFalso("entradas falsas");
        
        {
            RestaurarEntradaCin restaurador(bufferOriginalReal);
            std::cin.rdbuf(terminalFalso.rdbuf());
            CHECK(std::cin.rdbuf() == terminalFalso.rdbuf());
        }
        CHECK(std::cin.rdbuf() == bufferOriginalReal);
    }
}