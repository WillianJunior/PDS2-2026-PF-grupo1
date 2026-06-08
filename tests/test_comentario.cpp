#include <doctest/doctest.h>
#include "domain/comentario.hpp"

TEST_SUITE("Comentario")
{
    TEST_CASE("Criar Comentario nao lanca excecao")
    {
        // Novo construtor: Comentario(id, idPost, idAutor, texto)
        CHECK_NOTHROW(Comentario(1, 100, 2, "Otimo post!"));
    }

    TEST_CASE("getTexto retorna o texto correto")
    {
        Comentario c(1, 100, 2, "Texto de teste");
        CHECK(c.getTexto() == "Texto de teste");
    }

    TEST_CASE("quantidadeDeCurtidas inicial deve ser 0")
    {
        Comentario c(1, 100, 2, "Texto");
        CHECK(c.quantidadeDeCurtidas() == 0);
    }

    TEST_CASE("curtir adiciona e remove curtida corretamente")
    {
        Comentario c(1, 100, 2, "Texto");
        c.curtir(5); 
        CHECK(c.quantidadeDeCurtidas() == 1);
        c.curtir(5); 
        CHECK(c.quantidadeDeCurtidas() == 0);
    }
}