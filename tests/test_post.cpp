#include <doctest/doctest.h>
#include "domain/post.hpp"

TEST_SUITE("Post")
{
    TEST_CASE("curtir mesmo usuario duas vezes remove curtida")
    {
        // Novo construtor: id, idAutor, idComunidade, texto
        Post p(1, 10, 0, "Texto");
        p.curtir(5);
        CHECK(p.quantidadeDeCurtidas() == 1);
        p.curtir(5);
        CHECK(p.quantidadeDeCurtidas() == 0);
    }

    TEST_CASE("quantidadeDeCurtidas retorna numero correto de curtidas")
    {
        Post p(1, 10, 0, "Texto");
        p.curtir(10);
        p.curtir(20);
        CHECK(p.quantidadeDeCurtidas() == 2);
    }
}