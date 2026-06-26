#include "domain/aplicacao.hpp"
#include "domain/armazenamento.hpp"
#include "domain/sistema.hpp"
#include <cstdio>
#include <cstdlib>
#include <doctest/doctest.h>
#include <filesystem>
#include <iostream>
#include <sstream>

#if defined(_WIN32) || defined(_WIN64)
    #define SET_TEST_ENV() _putenv("AMBIENTE_DE_TESTE=1")
#else
    #define SET_TEST_ENV() setenv("AMBIENTE_DE_TESTE", "1", 1)
#endif

struct RedirecionarIOApp {
    std::istringstream input;
    std::ostringstream output;
    std::streambuf *oldCin;
    std::streambuf *oldCout;

    RedirecionarIOApp(const std::string &in) : input(in) {
        std::cin.clear();
        oldCin = std::cin.rdbuf(input.rdbuf());
        oldCout = std::cout.rdbuf(output.rdbuf());
    }
    ~RedirecionarIOApp() {
        std::cin.clear();
        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);
    }
};

TEST_SUITE("Aplicacao Principal - Cobertura de 100%") {

    TEST_CASE("1. Interativo - Erros e Criacao de Usuario") {
        std::remove("data/usuarios.csv");
        std::remove("data/perfis.csv");
        std::string inputs = "abc\n"
                             "1\nerrado\nerrado\n2\n"
                             "2\nUser\nemail@uni.br\nSenha123\r\n"
                             "2\nUser2\nemail@uni.br\nSenha123\n"
                             "3\n";
        RedirecionarIOApp io(inputs);
        Aplicacao app(false);
        CHECK_NOTHROW(app.executar());
    }

    TEST_CASE("2. Interativo - Fluxo Principal e Buscas") {
        Armazenamento db; Sistema sys(db);
        sys.criarUsuarioEPerfil("a@a.c", "Senha123", "UserA");
        db.salvarDados();

        std::string inputs = "1\na@a.c\nSenha123\n"
                             "abc\n1\nC\n2\nabc\n"
                             "2\n1\nBusca\nB\n"
                             "2\n2\nBusca\n\n"
                             "2\n3\nBusca\nB\n"
                             "2\n4\n3\nB\n"
                             "4\n3\n6\n3\n";
        RedirecionarIOApp io(inputs);
        Aplicacao app(false);
        CHECK_NOTHROW(app.executar());
    }

    TEST_CASE("3. Interativo - Alterar Credenciais Completo") {
        Armazenamento db; Sistema sys(db);
        sys.criarUsuarioEPerfil("userA@uni.br", "Senha123", "UserA");
        sys.criarUsuarioEPerfil("userB@uni.br", "Senha123", "UserB");
        db.salvarDados();

        std::string inputs = 
            "1\nuserA@uni.br\nSenha123\n"
            "5\n1\nSenha123\nfraca\n"
            "5\n1\nerrada\nNova1234\n"
            "5\n2\nSenha123\nsem_arroba\n"
            "5\n2\nSenha123\nuserB@uni.br\n"
            "5\n2\nerrada\nnovo@uni.br\n"
            "5\n1\nSenha123\nNova1234\n"
            "5\n2\nNova1234\nnovo@uni.br\n"
            "3\n";
        RedirecionarIOApp io(inputs);
        Aplicacao app(false);
        CHECK_NOTHROW(app.executar());
    }

    TEST_CASE("4. Interativo - Limite de 3 Tentativas na Criacao") {
        Armazenamento db; Sistema sys(db);
        sys.criarUsuarioEPerfil("existe@uni.br", "Senha123", "Existe");
        db.salvarDados();

        std::string inputSenha = "2\nN1\nE1\nfraca\nN2\nE2\nfraca\nN3\nE3\nfraca\n3\n";
        {
            RedirecionarIOApp io(inputSenha);
            Aplicacao app(false);
            CHECK_NOTHROW(app.executar());
        }

        std::string inputArgs = "2\nN1\nexiste@uni.br\nSenha123\nN2\nexiste@uni.br\nSenha123\nN3\nexiste@uni.br\nSenha123\n3\n";
        {
            RedirecionarIOApp io(inputArgs);
            Aplicacao app(false);
            CHECK_NOTHROW(app.executar());
        }
    }

    TEST_CASE("5. Interativo - EOF Abrupto nos Menus (Simula fechamento de terminal)") {
        { RedirecionarIOApp io("1\n"); Aplicacao app(false); CHECK_NOTHROW(app.executar()); } 
        { RedirecionarIOApp io("1\nem\n"); Aplicacao app(false); CHECK_NOTHROW(app.executar()); } 
        { RedirecionarIOApp io("2\n"); Aplicacao app(false); CHECK_NOTHROW(app.executar()); } 
        { RedirecionarIOApp io("2\nN\n"); Aplicacao app(false); CHECK_NOTHROW(app.executar()); } 
        { RedirecionarIOApp io("2\nN\nE\n"); Aplicacao app(false); CHECK_NOTHROW(app.executar()); } 
    }

    TEST_CASE("6. Modo Automatico - Excecoes Abruptas") {
        SET_TEST_ENV();
        { RedirecionarIOApp io("1\n"); Aplicacao app(true); CHECK_THROWS_WITH(app.executar(), "EXIT_1"); }
        { RedirecionarIOApp io("1\nemail\n"); Aplicacao app(true); CHECK_THROWS_WITH(app.executar(), "EXIT_1"); }
        { RedirecionarIOApp io("1\nerrado\nerrado\n"); Aplicacao app(true); CHECK_THROWS_WITH(app.executar(), "EXIT_1"); }
        
        { RedirecionarIOApp io("2\n"); Aplicacao app(true); CHECK_THROWS_WITH(app.executar(), "EXIT_1"); }
        { RedirecionarIOApp io("2\nNome\n"); Aplicacao app(true); CHECK_THROWS_WITH(app.executar(), "EXIT_1"); }
        { RedirecionarIOApp io("2\nNome\nEmail\n"); Aplicacao app(true); CHECK_THROWS_WITH(app.executar(), "EXIT_1"); }
        { RedirecionarIOApp io("2\nNome\nEmail\nfraca\n"); Aplicacao app(true); CHECK_THROWS_WITH(app.executar(), "EXIT_1"); }
    }

    TEST_CASE("7. Saida Limpa") {
        std::remove("data/usuarios.csv");
        std::remove("data/perfis.csv");
        std::remove("data/comunidades.csv");
        std::remove("data/posts.csv");
        std::remove("data/comentarios.csv");
    }
}