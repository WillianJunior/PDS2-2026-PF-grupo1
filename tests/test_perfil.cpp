#include <doctest/doctest.h>
#include "domain/perfil.hpp"

TEST_SUITE("Perfil") {

    TEST_CASE("Construtor nao lanca excecao") {
        // Novo construtor: id, email, nome, descricao, curso, instituicao, periodo
        CHECK_NOTHROW(Perfil(1, "teste@ufmg.br", "Teste", "Bio", "Computacao", "UFMG", 3));
    }

    TEST_CASE("Novo perfil tem listas de seguidores e seguindo vazias") {
        Perfil p(1, "teste@ufmg.br", "Teste", "Bio", "Computacao", "UFMG", 3);
        CHECK(p.getIdsSeguidores().empty());
        CHECK(p.getIdsSeguidos().empty());
    }

    TEST_CASE("Consigo seguir outro perfil e getIdsSeguidos retorna o perfil seguido") {
        Perfil p(1, "teste@ufmg.br", "Teste", "Bio", "Computacao", "UFMG", 3);
        const int idOutro = 2;
        CHECK(p.getIdsSeguidos().size() == 0);
        p.seguir(idOutro);
        CHECK(p.getIdsSeguidos().size() == 1);
    }

    TEST_CASE("Consigo deixar de seguir um perfil e getIdsSeguidos nao retorna mais o perfil seguido") {
        Perfil p(1, "teste@ufmg.br", "Teste", "Bio", "Computacao", "UFMG", 3);
        const int idOutro = 2;
        p.seguir(idOutro);
        CHECK(p.getIdsSeguidos().size() == 1);
        p.deixarDeSeguir(idOutro);
        CHECK(p.getIdsSeguidos().size() == 0);    
    }

    TEST_CASE("deixarDeSeguir em id inexistente nao lanca excecao") {
        Perfil p(1, "teste@ufmg.br", "Teste", "Bio", "Computacao", "UFMG", 3);
        CHECK_NOTHROW(p.deixarDeSeguir(99));
    }

}