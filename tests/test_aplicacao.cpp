#include "domain/aplicacao.hpp"
#include <cstdio>
#include <doctest/doctest.h>
#include <filesystem>
#include <iostream>
#include <sstream>

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

TEST_SUITE("Aplicacao Principal - Protegido contra Loop Infinito") {

    TEST_CASE("1. Interativo - Erros e Criacao de Usuario") {
        std::remove("data/usuarios.csv");
        std::remove("data/perfis.csv");
        std::remove("data/comunidades.csv");
        std::remove("data/posts.csv");
        std::remove("data/comentarios.csv");
        std::string inputs = "abc\n"
                             "1\nerrado\nerrado\n2\n"
                             "2\nUser\nemail@uni.br\nSenha123\n"
                             "2\nUser2\nemail@uni.br\nSenha123\n"
                             "2\nUser2\nemail2@uni.br\nfraca\n"
                             "3\n";
        RedirecionarIOApp io(inputs);
        Aplicacao app(false);
        CHECK_NOTHROW(app.executar());
    }

    TEST_CASE("2. Interativo - Fluxo Principal e Buscas") {
        Armazenamento db;
        db.criarUsuarioEPerfil("a@a.c", "Senha123", "UserA");
        db.salvarDados();

        std::string inputs = "1\na@a.c\nSenha123\n"
                             "abc\n"
                             "1\nC\n"
                             "2\nabc\n"
                             "2\n1\nBusca\nB\n"
                             "2\n2\nBusca\n\n"
                             "2\n3\nBusca\nB\n"
                             "2\n4\n"
                             "3\nB\n"
                             "4\n3\n"
                             "6\n"
                             "3\n";
        RedirecionarIOApp io(inputs);
        Aplicacao app(false);
        CHECK_NOTHROW(app.executar());
    }

    TEST_CASE("3. Interativo - Alterar Credenciais") {
        Armazenamento db;
        db.criarUsuarioEPerfil("b@b.c", "Senha123", "UserB");
        db.salvarDados();

        std::string inputs = "1\nb@b.c\nSenha123\n"
                             "5\nabc\n"
                             "5\n1\nSenha123\nNova1234\n"
                             "5\n2\nNova1234\nsem_arroba\n"
                             "5\n2\nNova1234\nnovo@b.c\n"
                             "3\n";
        RedirecionarIOApp io(inputs);
        Aplicacao app(false);
        CHECK_NOTHROW(app.executar());
    }

    TEST_CASE("4. Modo Automatico (Demonstracao)") {
        {
            RedirecionarIOApp io("");
            Aplicacao app(true);
            CHECK_NOTHROW(app.executar());
        }
        {
            RedirecionarIOApp io("1\n");
            Aplicacao app(true);
            CHECK_THROWS_WITH(app.executar(), "EXIT_1");
        }
        {
            RedirecionarIOApp io("2\nNome\n");
            Aplicacao app(true);
            CHECK_THROWS_WITH(app.executar(), "EXIT_1");
        }
        {
            RedirecionarIOApp io("2\nNome\nEmail\nSenha\n");
            Aplicacao app(true);
            CHECK_THROWS_WITH(app.executar(), "EXIT_1");
        }

        {
            Armazenamento db;
            db.criarUsuarioEPerfil("ja@existe.com", "Senha123", "Ja Existe");
            db.salvarDados();
        }
        {
            RedirecionarIOApp io("2\nNovoNome\nja@existe.com\nSenha123\n");
            Aplicacao app(true);
            CHECK_THROWS_WITH(app.executar(), "EXIT_0");
        }
        {
            RedirecionarIOApp io("2\nJa Existe\nnovo@mail.com\nSenha123\n");
            Aplicacao app(true);
            CHECK_THROWS_WITH(app.executar(), "EXIT_1");
        }
    }

    TEST_CASE("5. Saida Limpa e Fechamento") {
        RedirecionarIOApp io("1\nja@existe.com\nSenha123\n");
        Aplicacao app(true);
        CHECK_NOTHROW(app.executar());

        std::remove("data/usuarios.csv");
        std::remove("data/perfis.csv");
        std::remove("data/comunidades.csv");
        std::remove("data/posts.csv");
        std::remove("data/comentarios.csv");
        std::filesystem::remove("data");
    }
}