#include "domain/armazenamento.hpp"
#include "domain/busca.hpp"
#include <doctest/doctest.h>
#include <iostream>
#include <sstream>

TEST_SUITE("Busca") {
    TEST_CASE("Buscar, Exibir e Filtrar (Cobertura Total)") {
        Armazenamento db;
        Busca b;

        db.criarUsuarioEPerfil("ana@ufmg.br", "Senha123", "Ana");
        db.criarUsuarioEPerfil("bruno@ufmg.br", "Senha123", "Bruno");

        db.fazerLogin("ana@ufmg.br", "Senha123");

        db.getPerfil(1)->setDescricao("Programador C++");
        db.getPerfil(2)->setDescricao("Tambem estuda C++");

        db.criarPost("Aprendendo testes unitarios em C++", 0);
        db.criarComunidade("C++ Fans", "Grupo de cpp");

        b.buscarPalavraChave("C++", db);

        std::stringstream buffer;
        std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

        b.exibirResultadosPesquisa();
        std::string output = buffer.str();
        CHECK(output.find("Post: Aprendendo testes unitarios em C++") != std::string::npos);
        CHECK(output.find("Comunidade: C++ Fans") != std::string::npos);
        CHECK(output.find("Perfil: Ana") != std::string::npos);
        CHECK(output.find("Perfil: Bruno") != std::string::npos);

        buffer.str("");
        b.filtrarResultados("Post");
        output = buffer.str();
        CHECK(output.find("Post: Aprendendo testes unitarios em C++") != std::string::npos);
        CHECK(output.find("Perfil") == std::string::npos);

        buffer.str("");
        b.filtrarResultados("FiltroImpossivel");
        output = buffer.str();
        CHECK(output.find("Nenhum resultado para o filtro") != std::string::npos);

        b.buscarPalavraChave("TermoInexistente", db);
        buffer.str("");
        b.exibirResultadosPesquisa();
        output = buffer.str();
        CHECK(output.find("Nenhum resultado encontrado") != std::string::npos);

        std::cout.rdbuf(old);
    }

    TEST_CASE("Chamadas Diretas Aos Metodos (Forcar Retornos)") {
        Armazenamento db;
        Busca b;

        db.criarUsuarioEPerfil("teste@teste.com", "senha123", "Alvo");

        db.fazerLogin("teste@teste.com", "senha123");

        db.criarPost("Alvo", 0);
        db.criarComunidade("Alvo", "Desc");

        std::vector<Perfil> p = b.buscarPerfis("Alvo", db);
        CHECK(p.size() == 1);

        std::vector<Post> po = b.buscarPosts("Alvo", db);
        CHECK(po.size() == 1);

        std::vector<Comunidade> c = b.buscarComunidades("Alvo", db);
        CHECK(c.size() == 1);
        CHECK(b.buscarPerfis("Invisivel", db).empty());
        CHECK(b.buscarPosts("Invisivel", db).empty());
        CHECK(b.buscarComunidades("Invisivel", db).empty());
    }
}