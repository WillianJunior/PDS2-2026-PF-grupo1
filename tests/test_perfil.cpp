#include <doctest/doctest.h>
#include "domain/perfil.hpp"

TEST_SUITE("Perfil") {

TEST_CASE("Construtor nao lanca excecao") {
    CHECK_NOTHROW(Perfil("Computacao", "UFMG", 3));
}

TEST_CASE("Novo perfil tem listas de seguidores e seguindo vazias") {
    Perfil p("Computacao", "UFMG", 3);
    CHECK(p.listarIdSeguidores().empty());
    CHECK(p.listarIdSeguidos().empty());
}

TEST_CASE("Consigo seguir outro perfil e listarIdSeguidos retorna o perfil seguido") {
    Perfil p("Computacao", "UFMG", 3);
    const int idOutro = 2;
    CHECK(p.listarIdSeguidos().size() == 0);
    p.seguir(idOutro);
    CHECK(p.listarIdSeguidos().size() == 1);
}

TEST_CASE("Consigo deixar de seguir um perfil e listarIdSeguidos nao retorna mais o perfil seguido") {
    Perfil p("Computacao", "UFMG", 3);
    const int idOutro = 2;
    p.seguir(idOutro);
    CHECK(p.listarIdSeguidos().size() == 1);
    p.deixarDeSeguir(idOutro);
    CHECK(p.listarIdSeguidos().size() == 0);    
}

TEST_CASE("deixarDeSeguir em id inexistente nao lanca excecao") {
    Perfil p("Computacao", "UFMG", 3);
    CHECK_NOTHROW(p.deixarDeSeguir(99));
}

}
