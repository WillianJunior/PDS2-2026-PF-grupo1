#include <doctest/doctest.h>
#include "domain/comunidade.hpp"

TEST_SUITE("Comunidade") {

    TEST_CASE("Construtor nao lanca excecao") {
        // Novo construtor: id, nome, descricao, idAdministrador
        CHECK_NOTHROW(Comunidade(1, "Banco de Dados", "Descricao", 5));
    }

    TEST_CASE("adicionarMembro adiciona ID na lista de membros") {
        Comunidade c(1, "Algebra", "Descricao", 5);
        const int idNovoPerfil = 2;
        CHECK(c.getIdsMembros().empty());
        
        c.adicionarMembro(idNovoPerfil);
        CHECK(c.getIdsMembros().size() == 1);
    }

    TEST_CASE("podePublicar retorna true para o admin") {
        const int idAdministrador = 5;
        Comunidade c(1, "Fisica Moderna", "Desc", idAdministrador);
        CHECK(c.podePublicar(idAdministrador) == true);
    }

    TEST_CASE("podePublicar retorna true para um membro") {
        Comunidade c(1, "Fisica Moderna", "Desc", 5);
        const int idMembro = 3;
        c.adicionarMembro(idMembro);
        CHECK(c.podePublicar(idMembro) == true);
    }
    
    TEST_CASE("podePublicar retorna false para quem nao e membro") {
        Comunidade c(1, "Fisica Moderna", "Desc", 5);
        const int idNaoMembro = 99;
        CHECK(c.podePublicar(idNaoMembro) == false);
    }
}