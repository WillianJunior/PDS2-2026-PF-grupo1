#include <doctest/doctest.h>
#include "domain/comunidade.hpp"

TEST_SUITE("Comunidade") {
    TEST_CASE("Construtores e Getters") {
        Comunidade c1(10, "DevOps", "Descricao", 1);
        CHECK(c1.getId() == 10);
        CHECK(c1.getNome() == "DevOps");
        CHECK(c1.getDescricao() == "Descricao");
        CHECK(c1.getIdAdministrador() == 1);

        Comunidade c2("IA", 2);
        CHECK(c2.getId() == 0);
    }

    TEST_CASE("Gerenciamento de Membros") {
        Comunidade c("Teste", 1);
        c.adicionarMembro(10);
        c.entrarComunidade(10); 
        CHECK(c.getIdsMembros().size() == 1);
        
        c.removerMembro(10);
        CHECK(c.getIdsMembros().size() == 0);
        CHECK_NOTHROW(c.removerMembro(99));

        c.setIdsMembros({5, 6});
        CHECK(c.getIdsMembros().size() == 2);
    }

    TEST_CASE("Permissao para publicar e Posts Locais") {
        Comunidade c("Teste", 1); 
        c.adicionarMembro(2);     
        CHECK(c.podePublicar(1) == true);
        CHECK(c.podePublicar(2) == true);
        CHECK(c.podePublicar(3) == false); 

        CHECK(c.posts().empty());
        CHECK(c.buscarPosts("algo").empty());
    }

    TEST_CASE("exibirMembrosComunidade") {
        Comunidade c("Teste", 1);
        c.adicionarMembro(2);
        CHECK_NOTHROW(c.exibirMembrosComunidade());
    }
    TEST_CASE("Nao adiciona membro duplicado") {
    Comunidade c("Teste", 1);

    c.adicionarMembro(10);
    c.adicionarMembro(10); // repetido

    CHECK(c.getIdsMembros().size() == 1);
}
TEST_CASE("Remover membro inexistente") {
    Comunidade c("Teste", 1);

    c.adicionarMembro(5);

    CHECK_NOTHROW(c.removerMembro(99));
    CHECK(c.getIdsMembros().size() == 1);
}
TEST_CASE("podePublicar sem membros") {
    Comunidade c("Teste", 1);

    CHECK(c.podePublicar(1) == true);  // admin sempre pode
    CHECK(c.podePublicar(999) == false);
}
TEST_CASE("setIdsMembros sobrescreve lista") {
    Comunidade c("Teste", 1);

    c.adicionarMembro(1);
    c.setIdsMembros({7, 8, 9});

    CHECK(c.getIdsMembros().size() == 3);
    CHECK(c.getIdsMembros()[0] == 7);
}
TEST_CASE("buscarPosts sem correspondencia") {
    Comunidade c("Teste", 1);

    auto resultado = c.buscarPosts("inexistente");

    CHECK(resultado.empty());
}
TEST_CASE("posts permanece vazio") {
    Comunidade c("Teste", 1);

    CHECK(c.posts().size() == 0);
    CHECK(c.posts().empty());
}
TEST_CASE("Adicionar e remover varios membros sequencialmente") {
    Comunidade c("Teste", 1);

    c.adicionarMembro(1);
    c.adicionarMembro(2);
    c.adicionarMembro(3);

    CHECK(c.getIdsMembros().size() == 3);

    c.removerMembro(2);
    CHECK(c.getIdsMembros().size() == 2);
}
TEST_CASE("entrarComunidade membro ja existente") {
    Comunidade c("Teste", 1);

    c.entrarComunidade(5);
    c.entrarComunidade(5);

    CHECK(c.getIdsMembros().size() == 1);
}
TEST_CASE("setIdsMembros vazio") {
    Comunidade c("Teste", 1);

    c.adicionarMembro(1);
    c.setIdsMembros({});

    CHECK(c.getIdsMembros().empty());
}
TEST_CASE("podePublicar apos remover membro") {
    Comunidade c("Teste", 1);

    c.adicionarMembro(10);
    c.removerMembro(10);

    CHECK(c.podePublicar(10) == false);
}
TEST_CASE("buscarPosts string vazia") {
    Comunidade c("Teste", 1);

    auto resultado = c.buscarPosts("");

    CHECK(resultado.empty());
}
TEST_CASE("administrador nao eh automaticamente membro") {
    Comunidade c("Teste", 1);

    CHECK(c.getIdsMembros().empty());
    CHECK(c.podePublicar(1) == true);
}
TEST_CASE("administrador nao eh automaticamente membro") {
    Comunidade c("Teste", 1);

    CHECK(c.getIdsMembros().empty());
    CHECK(c.podePublicar(1) == true);
}
TEST_CASE("remover de lista vazia") {
    Comunidade c("Teste", 1);

    CHECK_NOTHROW(c.removerMembro(1));
    CHECK(c.getIdsMembros().empty());
}
TEST_CASE("adicionar e depois sobrescrever membros") {
    Comunidade c("Teste", 1);

    c.adicionarMembro(1);
    c.adicionarMembro(2);

    c.setIdsMembros({9});

    CHECK(c.getIdsMembros().size() == 1);
    CHECK(c.getIdsMembros()[0] == 9);
}
}