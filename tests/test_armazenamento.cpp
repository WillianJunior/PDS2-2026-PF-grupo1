#include "domain/armazenamento.hpp"
#include "domain/comunidade.hpp"
#include "domain/perfil.hpp"
#include <cstdio>
#include <doctest/doctest.h>
#include <filesystem>
#include <fstream>

TEST_SUITE("Armazenamento (Repository)") {

    TEST_CASE("Criacao e Consulta de Entidades Diretas") {
        Armazenamento db;
        
        db.adicionarUsuario(Usuario(1, "teste@ufmg.br", "123", "Tester"));
        db.adicionarPerfil(Perfil(1, "Tester", "", "", "", 0));
        db.adicionarComunidade(Comunidade(1, "Minha Com", "Desc", 1));
        db.adicionarPost(Post(1, 1, 0, "Meu Post Geral"));
        db.adicionarComentario(Comentario(1, 1, 1, "Meu Comentario"));

        CHECK(db.getTodosPerfis().size() == 1);
        CHECK(db.getTodasComunidades().size() == 1);
        CHECK(db.getTodosPosts().size() == 1);

        CHECK(db.getPerfil(1) != nullptr);
        CHECK(db.getPerfil(99) == nullptr);
        CHECK(db.getUsuario("teste@ufmg.br") != nullptr);
        CHECK(db.getUsuario("invalido") == nullptr);
        CHECK(db.getComunidade(1) != nullptr);
        CHECK(db.getComunidade(99) == nullptr);

        CHECK(db.getTodosPostsMutavel().size() == 1);
        CHECK(db.getTodosComentariosMutavel().size() == 1);
    }

    TEST_CASE("Garantir atualização de Auto-Incremento no carregarDados (Linhas 29, 31, 33)") {
        Armazenamento dbOrigem;
        dbOrigem.adicionarUsuario(Usuario(5, "a@b.c", "123", "A"));
        dbOrigem.adicionarPerfil(Perfil(5, "A", "Bio", "C", "I", 1));
        dbOrigem.adicionarComunidade(Comunidade(10, "Com", "Desc", 5));
        dbOrigem.adicionarPost(Post(15, 5, 0, "Post"));
        dbOrigem.adicionarComentario(Comentario(20, 15, 5, "Coment"));
        
        dbOrigem.salvarDados();
        
        Armazenamento dbDestino;
        
        dbDestino.carregarDados();
        
        CHECK(dbDestino.getTodosPerfis().size() == 1);
        CHECK(dbDestino.getTodasComunidades().size() == 1);
        
        std::remove("data/usuarios.csv");
        std::remove("data/perfis.csv");
        std::remove("data/comunidades.csv");
        std::remove("data/posts.csv");
        std::remove("data/comentarios.csv");
    }

    TEST_CASE("Carregar e Salvar Dados (I/O Simulado)") {
        Armazenamento db;
        db.adicionarUsuario(Usuario(1, "a@b.c", "123", "A"));
        db.adicionarPerfil(Perfil(1, "A", "", "", "", 0));
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

    TEST_CASE("Cobrir Retornos Nulos e Mutáveis em Getters") {
        Armazenamento db;
        db.adicionarUsuario(Usuario(1, "teste@ufmg.br", "123", "Tester"));
        db.adicionarComunidade(Comunidade(1, "Com", "Desc", 1));
        db.adicionarPost(Post(1, 1, 0, "Post"));

        const Armazenamento &constDb = db;
        CHECK(constDb.getUsuario("teste@ufmg.br") != nullptr);
        CHECK(constDb.getComunidade(1) != nullptr);
        CHECK(constDb.getPost(1) != nullptr);

        CHECK(constDb.getUsuario("invalido@ufmg.br") == nullptr);
        CHECK(constDb.getComunidade(99) == nullptr);
        CHECK(constDb.getPost(99) == nullptr);
    }
}