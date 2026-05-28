#include <doctest/doctest.h>
#include "domain/perfil.hpp"

TEST_SUITE("Perfil") {

TEST_CASE("Construtor nao lanca excecao") {
    CHECK_NOTHROW(Perfil("Computacao", "UFMG", 3));
}

TEST_CASE("Novo perfil tem listas de seguidores e seguindo vazias") {
    Perfil p("Computacao", "UFMG", 3);
    CHECK(p.listarSeguidores().empty());
    CHECK(p.listarSeguindo().empty());
}

TEST_CASE("seguir nao lanca excecao") {
    Perfil p("Computacao", "UFMG", 3);
    CHECK_NOTHROW(p.seguir(42));
}

TEST_CASE("deixarDeSeguir em id existente nao lanca excecao") {
    Perfil p("Computacao", "UFMG", 3);
    p.seguir(42);
    CHECK_NOTHROW(p.deixarDeSeguir(42));
}

TEST_CASE("deixarDeSeguir em id inexistente nao lanca excecao") {
    Perfil p("Computacao", "UFMG", 3);
    CHECK_NOTHROW(p.deixarDeSeguir(99));
}

}
