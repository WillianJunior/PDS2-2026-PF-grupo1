#include <doctest/doctest.h>
#include "domain/busca.hpp"
#include "domain/armazenamento.hpp"
#include <sstream>
#include <iostream>

TEST_SUITE("Busca") {
    TEST_CASE("Buscar, Exibir e Filtrar") {
        Armazenamento db;
        Busca b;
        db.criarUsuarioEPerfil("ana@uni.br", "Senha123", "Ana");
        db.fazerLogin("ana@uni.br", "Senha123");
        db.criarPost("Aprendendo testes unitarios em C++");
        db.criarComunidade("C++ Fans", "Grupo de cpp");

        b.buscarPalavraChave("C++", db);

        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        b.exibirResultadosPesquisa();
        std::string output = buffer.str();
        CHECK(output.find("Post: Aprendendo testes unitarios em C++") != std::string::npos);
        CHECK(output.find("Comunidade: C++ Fans") != std::string::npos);

        buffer.str(""); 
        b.filtrarResultados("Post");
        output = buffer.str();
        CHECK(output.find("Post: Aprendendo testes unitarios em C++") != std::string::npos);

        std::cout.rdbuf(old);
    }

    TEST_CASE("Buscar palavra inexistente") {
        Armazenamento db;
        Busca b;
        b.buscarPalavraChave("Inexistente123", db);
        
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
        b.exibirResultadosPesquisa();
        CHECK(buffer.str().find("Nenhum resultado encontrado para: Inexistente123") != std::string::npos);
        std::cout.rdbuf(old);
    }
}