#include <doctest/doctest.h>
#include "domain/comunidade.hpp"
#include "domain/perfil.hpp"
#include "domain/post.hpp"

TEST_SUITE("Comunidade") {

TEST_CASE("Construtor nao lanca excecao") {
    const int idAdministrador = 5;
    CHECK_NOTHROW(Comunidade("Banco de Dados", idAdministrador));
}

TEST_CASE("posts retorna lista vazia em comunidade sem postagens") {
    const int idAdministrador = 5;
    Comunidade c("Vazia", idAdministrador);
    CHECK(c.posts().empty());
}

TEST_CASE("entrarComunidade nao lanca excecao") {
    const int idAdministrador = 5;
    const int idNovoPerfil = 2;
    Comunidade c("Algebra", idAdministrador);
    CHECK_NOTHROW(c.entrarComunidade(idNovoPerfil));
}

TEST_CASE("podePublicar nao lanca excecao") {
    const int idAdministrador = 5;
    const int idMembro = 3;
    Comunidade c("Fisica Moderna", idAdministrador);
    c.entrarComunidade(idMembro);
    CHECK_NOTHROW(c.podePublicar(idMembro));
}

TEST_CASE("buscarPosts retorna lista vazia quando nao ha posts") {
    const int idAdministrador = 5;
    Comunidade c("IA", idAdministrador);
    CHECK(c.buscarPosts("qualquer").empty());
}

TEST_CASE("buscarPosts retorna vazio quando termo nao existe nos posts") {
    const int idAdministrador = 5;
    Comunidade c("IA", idAdministrador);
    CHECK(c.buscarPosts("blockchain").empty());
}

TEST_CASE("exibirMembrosComunidade nao lanca excecao") {
    const int idAdministrador = 5;
    Comunidade c("Teste", idAdministrador);
    CHECK_NOTHROW(c.exibirMembrosComunidade());
}

TEST_CASE("exibirMembrosComunidade com multiplos membros nao lanca excecao") {
    const int idAdministrador = 5;
    Comunidade c("Teste", idAdministrador);
    c.entrarComunidade(1);
    c.entrarComunidade(2);
    CHECK_NOTHROW(c.exibirMembrosComunidade());
}

}
