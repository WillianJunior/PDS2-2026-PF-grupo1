#include "domain/armazenamento.hpp"
#include "domain/sistema.hpp"
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

    TEST_CASE("Feed sem usuario logado (Cobertura da Linha 16)") {
        Armazenamento db;
        Sistema sys(db);
        Feed f;
        CHECK_NOTHROW(simularInteracaoFeed("", [&]() { f.verFeed(db, sys); }));
    }

    TEST_CASE("Feed Vazio e Tratamento de Erros (Cobertura de throws e restricoes)") {
        Armazenamento db;
        Sistema sys(db);
        sys.criarUsuarioEPerfil("teste@uni.br", "Senha123", "User");
        sys.fazerLogin("teste@uni.br", "Senha123");

        Feed f;
        std::string acoes = "A\nB\n\nB\nPost Valido\n\nA\nabc\nC\n";
        CHECK_NOTHROW(simularInteracaoFeed(acoes, [&]() { f.verFeed(db, sys); }));
    }

    TEST_CASE("Navegacao Completa e Inputs Invalidos Feed") {
        Armazenamento db;
        Sistema sys(db);
        sys.criarUsuarioEPerfil("a@b.c", "Senha123", "UserA");
        sys.fazerLogin("a@b.c", "Senha123");
        sys.criarPost("Geral Post", 0);
        sys.criarComunidade("Comum", "Desc");
        sys.criarPost("Comum Post", 1);
        sys.criarComentarioGlobal(1, 1, "Coment A");

        Feed f;
        std::string acoes = "Z\nA\n99\nA\n1\nF\nC\n";
        CHECK_NOTHROW(simularInteracaoFeed(acoes, [&]() { f.verFeed(db, sys); }));
    }

    TEST_CASE("Metodos Vazios de Interface") {
        Feed f;
        std::vector<Post> po;
        std::vector<Perfil> pe;
        std::vector<Comunidade> co;

        CHECK_NOTHROW(f.exibirPosts(po));
        CHECK_NOTHROW(f.exibirPerfis(pe));
        CHECK_NOTHROW(f.exibirComunidades(co));
    }
}