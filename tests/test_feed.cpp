#include "domain/armazenamento.hpp"
#include "domain/feed.hpp"
#include <doctest/doctest.h>
#include <functional>
#include <iostream>
#include <sstream>

static void simularInteracaoFeed(const std::string &inputsProgramados, std::function<void()> menuContexto) {
    std::stringstream inputReal(inputsProgramados);
    std::stringstream outputDescartavel;
    std::streambuf *backupCin = std::cin.rdbuf(inputReal.rdbuf());
    std::streambuf *backupCout = std::cout.rdbuf(outputDescartavel.rdbuf());

    menuContexto();

    std::cin.rdbuf(backupCin);
    std::cout.rdbuf(backupCout);
}

TEST_SUITE("Feed Interativo e Metodos Auxiliares") {

    TEST_CASE("Feed Vazio e Tratamento de Erros (Cobertura de throws e restricoes)") {
        Armazenamento db;
        db.criarUsuarioEPerfil("teste@uni.br", "senha123", "User");
        db.fazerLogin("teste@uni.br", "senha123");

        Feed f;

        std::string acoes = "A\n"
                            "B\n\n"
                            "B\nPost Valido\n\n"
                            "A\nabc\n"
                            "C\n";

        CHECK_NOTHROW(simularInteracaoFeed(acoes, [&]() { f.verFeed(db); }));
    }

    TEST_CASE("Navegacao Completa e Inputs Invalidos Feed") {
        Armazenamento db;
        db.criarUsuarioEPerfil("a@b.c", "senha12345", "UserA");
        db.fazerLogin("a@b.c", "senha12345");
        db.criarPost("Geral Post", 0);
        db.criarComunidade("Comum", "Desc");
        db.criarPost("Comum Post", 1);
        db.criarComentarioGlobal(1, 1, "Coment A");

        Feed f;
        std::string acoes = "Z\n"
                            "A\n99\n"
                            "A\n1\n"
                            "F\n"
                            "C\n";

        CHECK_NOTHROW(simularInteracaoFeed(acoes, [&]() { f.verFeed(db); }));
    }

    TEST_CASE("Metodos Vazios de Interface (Cobertura 100%)") {
        Feed f;
        std::vector<Post> po;
        std::vector<Perfil> pe;
        std::vector<Comunidade> co;

        CHECK_NOTHROW(f.exibirPosts(po));
        CHECK_NOTHROW(f.exibirPerfis(pe));
        CHECK_NOTHROW(f.exibirComunidades(co));
    }
}