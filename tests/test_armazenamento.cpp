#include <doctest/doctest.h>
#include "domain/armazenamento.hpp"
#include "domain/perfil.hpp"
#include "domain/comunidade.hpp"
#include <cstdio>
#include <filesystem>

TEST_SUITE("Armazenamento") {
    TEST_CASE("Autenticação e Sessão") {
        Armazenamento db;
        CHECK(db.senhaSegura("fraca") == false);
        CHECK(db.senhaSegura("SenhaSemNumero") == false);
        CHECK(db.senhaSegura("Segura123") == true);

        db.criarUsuarioEPerfil("teste@uni.br", "Senha123", "Tester");
        CHECK(db.emailUnico("teste@uni.br") == false);
        CHECK(db.nomeUsuarioUnico("Tester") == false);
        CHECK(db.emailUnico("novo@uni.br") == true);
        
        CHECK(db.fazerLogin("teste@uni.br", "errada") == false);
        CHECK(db.fazerLogin("errado@uni.br", "senha123") == false);
        CHECK(db.fazerLogin("teste@uni.br", "Senha123") == true);
        CHECK(db.getEmailLogado() == "teste@uni.br");
        CHECK(db.getIdPerfilLogado() == 1);

        db.deslogar();
        CHECK(db.getEmailLogado() == "");
        CHECK(db.getIdPerfilLogado() == 0);
    }

    TEST_CASE("Criacao e Consulta de Entidades") {
        Armazenamento db;
        db.criarUsuarioEPerfil("teste@uni.br", "Senha123", "Tester");
        db.fazerLogin("teste@uni.br", "Senha123");

        db.criarComunidade("Minha Com", "Desc");
        db.criarPost("Meu Post", 1);
        db.criarPost("Meu Post Geral", 0); 
        db.criarComentarioGlobal(1, 1, "Meu Comentario");

        CHECK(db.getTodosPerfis().size() == 1);
        CHECK(db.getTodasComunidades().size() == 1);
        CHECK(db.getTodosPosts().size() == 2);
        CHECK(db.getPostsFeed().size() == 2); 

        CHECK(db.getPerfil(1) != nullptr);
        CHECK(db.getPerfil(99) == nullptr);
        CHECK(db.getUsuario("teste@uni.br") != nullptr);
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

        CHECK_NOTHROW(db.mensagemSucessoErro());
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
TEST_CASE("Salvar e carregar novamente") {
    Armazenamento db;

    db.criarUsuarioEPerfil("x@x.com", "Senha12345", "X");
    db.salvarDados();
    db.carregarDados();

    CHECK(db.getTodosPerfis().size() >= 1);
}
TEST_CASE("Login inexistente completo") {
    Armazenamento db;

    CHECK(db.fazerLogin("invalido", "123") == false);
}
}