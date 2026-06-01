#include <doctest/doctest.h>
#include "domain/comentario.hpp"
#include "domain/perfil.hpp"

TEST_SUITE("Comentario")
{

    TEST_CASE("Construtor nao lanca excecao")
    {
        Perfil autor("Computacao", "UFMG", 2);
        CHECK_NOTHROW(Comentario("Otimo post!", autor));
    }

    TEST_CASE("Consigo curtir um comentario")
    {
        Perfil autor("Computacao", "UFMG", 2);
        Comentario c("Texto", autor);
        c.curtir(1);
        CHECK(c.quantidadeDeCurtidas() == 1);
    }

    TEST_CASE("curtir com usuarios diferentes nao lanca excecao")
    {
        Perfil autor("Computacao", "UFMG", 2);
        Comentario c("Texto", autor);
        c.curtir(1);
        c.curtir(2);
        c.curtir(3);
        CHECK_NOTHROW(c.curtir(4));
    }

    TEST_CASE("curtir mesmo usuario duas vezes remove curtida")
    {
        Perfil autor("Computacao", "UFMG", 2);
        Comentario c("Texto", autor);
        c.curtir(1);
        CHECK(c.quantidadeDeCurtidas() == 1);
        c.curtir(1);
        CHECK(c.quantidadeDeCurtidas() == 0);
    }
    
}
