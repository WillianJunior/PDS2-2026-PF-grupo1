#include <doctest/doctest.h>
#include "domain/comentario.hpp"
#include "domain/perfil.hpp"

TEST_SUITE("Comentario") {

TEST_CASE("Construtor nao lanca excecao") {
    Perfil autor("Computacao", "UFMG", 2);
    CHECK_NOTHROW(Comentario("Otimo post!", autor));
}

TEST_CASE("curtir nao lanca excecao") {
    Perfil autor("Computacao", "UFMG", 2);
    Comentario c("Texto", autor);
    CHECK_NOTHROW(c.curtir(1));
}

TEST_CASE("curtir com usuarios diferentes nao lanca excecao") {
    Perfil autor("Computacao", "UFMG", 2);
    Comentario c("Texto", autor);
    c.curtir(1);
    c.curtir(2);
    c.curtir(3);
    CHECK_NOTHROW(c.curtir(4));
}

TEST_CASE("curtir mesmo usuario duas vezes nao lanca excecao") {
    Perfil autor("Computacao", "UFMG", 2);
    Comentario c("Texto", autor);
    c.curtir(1);
    CHECK_NOTHROW(c.curtir(1));
}

}
