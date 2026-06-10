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
}