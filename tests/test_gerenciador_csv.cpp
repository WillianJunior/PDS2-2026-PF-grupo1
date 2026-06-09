#include <doctest/doctest.h>
#include "gerenciador_csv.hpp"

TEST_SUITE("GerenciadorCSV") {
    TEST_CASE("separarString divide string corretamente") {
        std::string linha = "teste,de,csv";
        auto resultado = GerenciadorCSV::separarString(linha, ',');
        CHECK(resultado.size() == 3);
        CHECK(resultado[0] == "teste");
        CHECK(resultado[1] == "de");
        CHECK(resultado[2] == "csv");
    }

    TEST_CASE("juntarInteiros une vetor de forma correta") {
        std::vector<int> lista = {10, 20, 30};
        std::string texto = GerenciadorCSV::juntarInteiros(lista, '|');
        CHECK(texto == "10|20|30");
    }

    TEST_CASE("separarInteiros recupera lista corretamente") {
        std::string texto = "5|15|25";
        auto lista = GerenciadorCSV::separarInteiros(texto, '|');
        CHECK(lista.size() == 3);
        CHECK(lista[0] == 5);
        CHECK(lista[1] == 15);
        CHECK(lista[2] == 25);
    }

    TEST_CASE("separarInteiros lida com string vazia") {
        auto lista = GerenciadorCSV::separarInteiros("", '|');
        CHECK(lista.empty() == true);
    }
}