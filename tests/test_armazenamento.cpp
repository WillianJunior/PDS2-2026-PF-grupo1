#include "domain/armazenamento.hpp"
#include "domain/comunidade.hpp"
#include "domain/perfil.hpp"
#include <cstdio>
#include <doctest/doctest.h>
#include <filesystem>
#include <fstream>
#include <stdexcept>

TEST_SUITE("Armazenamento") {
    TEST_CASE("Autenticação e Sessão") {
        Armazenamento db;
        CHECK(db.senhaSegura("fraca") == false);
        CHECK(db.senhaSegura("SenhaSemNumero") == false);
        CHECK(db.senhaSegura("Segura123") == true);

        db.criarUsuarioEPerfil("teste@ufmg.br", "Senha123", "Tester");
        CHECK(db.emailUnico("teste@ufmg.br") == false);
        CHECK(db.nomeUsuarioUnico("Tester") == false);
        CHECK(db.emailUnico("novo@ufmg.br") == true);

        CHECK(db.fazerLogin("teste@ufmg.br", "errada") == false);
        CHECK(db.fazerLogin("errado@ufmg.br", "senha123") == false);
        CHECK(db.fazerLogin("teste@ufmg.br", "Senha123") == true);
        CHECK(db.getEmailLogado() == "teste@ufmg.br");
        CHECK(db.getIdPerfilLogado() == 1);

        db.deslogar();
        CHECK(db.getEmailLogado() == "");
        CHECK(db.getIdPerfilLogado() == 0);
    }

    TEST_CASE("Criacao e Consulta de Entidades") {
        Armazenamento db;
        db.criarUsuarioEPerfil("teste@ufmg.br", "Senha123", "Tester");
        db.fazerLogin("teste@ufmg.br", "Senha123");

        db.criarComunidade("Minha Com", "Desc");
        db.criarPost("Meu Post", 1);
        db.criarPost("Meu Post Geral", 0);
        db.criarComentarioGlobal(1, 1, "Meu Comentario");

        CHECK(db.getTodosPerfis().size() == 1);
        CHECK(db.getTodasComunidades().size() == 1);
        CHECK(db.getTodosPosts().size() == 2);

        CHECK(db.getPerfil(1) != nullptr);
        CHECK(db.getPerfil(99) == nullptr);
        CHECK(db.getUsuario("teste@ufmg.br") != nullptr);
        CHECK(db.getUsuario("invalido") == nullptr);
        CHECK(db.getComunidade(1) != nullptr);
        CHECK(db.getComunidade(99) == nullptr);

        CHECK(db.getTodosPostsMutavel().size() == 2);
        CHECK(db.getTodosComentariosMutavel().size() == 1);

        Perfil p("Eng", "UFRJ", 1);
        db.criarPerfil(p);
        CHECK(db.listarPerfis().size() == 2);

        Comunidade c("Extra", 1);
        db.criarComunidade(c);
        CHECK(db.listarComunidade().size() == 2);

    }

    TEST_CASE("Restrições sem login") {
        Armazenamento db;
        db.criarPost("Tentativa", 1);
        db.criarComunidade("Tentativa", "Desc");
        CHECK(db.getTodosPosts().empty());
        CHECK(db.getTodasComunidades().empty());
    }

    TEST_CASE("Carregar e Salvar Dados (I/O Simulado)") {
        Armazenamento db;
        db.criarUsuarioEPerfil("a@b.c", "Senha12345", "A");
        db.salvarDados();
        db.carregarDados();
        CHECK(db.getTodosPerfis().size() >= 1);
        std::remove("data/usuarios.csv");
        std::remove("data/perfis.csv");
        std::remove("data/comunidades.csv");
        std::remove("data/posts.csv");
        std::remove("data/comentarios.csv");
        std::filesystem::remove("data");
    }

    TEST_CASE("Criacao sem login nao funciona") {
        Armazenamento db;
        db.criarPost("Teste", 1);
        db.criarComunidade("Teste", "Desc");
        CHECK(db.getTodosPosts().empty());
        CHECK(db.getTodasComunidades().empty());
    }

    TEST_CASE("Salvar e carregar novamente (Forcando Linha 91 no CSV e carregarDados)") {
        {
            Armazenamento db1;
            db1.criarUsuarioEPerfil("x@x.com", "Senha12345", "X");
            db1.salvarDados();
        }
        {
            Armazenamento db2;
            db2.carregarDados();
            CHECK(db2.getTodosPerfis().size() >= 1);
        }
        std::remove("data/usuarios.csv");
        std::remove("data/perfis.csv");
        std::remove("data/comunidades.csv");
        std::remove("data/posts.csv");
        std::remove("data/comentarios.csv");
    }

    TEST_CASE("Login inexistente completo") {
        Armazenamento db;
        CHECK(db.fazerLogin("invalido", "123") == false);
    }

    TEST_CASE("Excecoes em Criacao de Entidades (Cobertura de throws)") {
        Armazenamento db;
        CHECK_THROWS_AS(db.criarUsuarioEPerfil("teste@ufmg.br", "Senha123", ""), std::invalid_argument);
        CHECK_THROWS_AS(db.criarUsuarioEPerfil("teste@ufmg.br", "123", "User"), std::invalid_argument);
        CHECK_THROWS_AS(db.criarUsuarioEPerfil("testeufmg.br", "Senha123", "User"), std::invalid_argument);

        db.criarUsuarioEPerfil("teste@ufmg.br", "Senha123", "User");
        CHECK_THROWS_AS(db.criarUsuarioEPerfil("teste@ufmg.br", "NovaSenha12", "NovoUser"), std::invalid_argument);
        CHECK_THROWS_AS(db.criarUsuarioEPerfil("novo@ufmg.br", "NovaSenha12", "User"), std::invalid_argument);

        db.fazerLogin("teste@ufmg.br", "Senha123");
        CHECK_THROWS_AS(db.criarPost(""), std::invalid_argument);
        CHECK_THROWS_AS(db.criarComunidade("", "desc"), std::invalid_argument);
        CHECK_THROWS_AS(db.criarComentarioGlobal(1, 1, ""), std::invalid_argument);
    }

    TEST_CASE("Cobrir Retornos Nulos e Mutáveis em Getters") {
        Armazenamento db;
        db.criarUsuarioEPerfil("teste@ufmg.br", "Senha123", "Tester");
        db.fazerLogin("teste@ufmg.br", "Senha123");
        db.criarComunidade("Com", "Desc");
        db.criarPost("Post", 1);

        const Armazenamento &constDb = db;
        CHECK(constDb.getUsuario("teste@ufmg.br") != nullptr);
        CHECK(constDb.getComunidade(1) != nullptr);
        CHECK(constDb.getPost(1) != nullptr);

        CHECK(db.getUsuario("teste@ufmg.br") != nullptr);
        CHECK(db.getComunidade(1) != nullptr);

        CHECK(constDb.getUsuario("invalido@ufmg.br") == nullptr);
        CHECK(constDb.getComunidade(99) == nullptr);
        CHECK(constDb.getPost(99) == nullptr);
    }

    TEST_CASE("Forcar erro de perfil logado nao encontrado ao criar comunidade") {
        Armazenamento db;
        db.criarUsuarioEPerfil("teste@ufmg.br", "Senha123", "Tester");
        db.fazerLogin("teste@ufmg.br", "Senha123");

        std::remove("data/usuarios.csv");
        std::remove("data/perfis.csv");
        std::remove("data/comunidades.csv");
        std::remove("data/posts.csv");
        std::remove("data/comentarios.csv");

        db.carregarDados();
        CHECK_THROWS_AS(db.criarComunidade("Fantasma", "Sem dono"), std::runtime_error);
    }

    TEST_CASE("Forcar corrupcao de banco: Usuario existe, mas Perfil sumiu (Linha 91)") {
        {
            Armazenamento dbPreparo;
            dbPreparo.criarUsuarioEPerfil("fantasma@uni.br", "Senha123", "Fantasma");
            dbPreparo.salvarDados();
        }

        std::ofstream("data/perfis.csv", std::ios::trunc).close();
        Armazenamento dbTeste;
        dbTeste.carregarDados();
        CHECK(dbTeste.fazerLogin("fantasma@uni.br", "Senha123") == false);
        std::remove("data/usuarios.csv");
        std::remove("data/perfis.csv");
        std::remove("data/comunidades.csv");
        std::remove("data/posts.csv");
        std::remove("data/comentarios.csv");
    }
}