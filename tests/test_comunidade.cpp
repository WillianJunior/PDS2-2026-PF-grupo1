#include <doctest/doctest.h>
#include "domain/comunidade.hpp"
#include "domain/perfil.hpp"
#include "domain/post.hpp"

TEST_SUITE("Comunidade") {

TEST_CASE("Construtor nao lanca excecao") {
    Perfil adm("Computacao", "UFMG", 5);
    CHECK_NOTHROW(Comunidade("Banco de Dados", adm));
}

TEST_CASE("posts retorna lista vazia em comunidade sem postagens") {
    Perfil adm("Computacao", "UFMG", 5);
    Comunidade c("Vazia", adm);
    CHECK(c.posts().empty());
}

TEST_CASE("entrarComunidade nao lanca excecao") {
    Perfil adm("Computacao", "UFMG", 5);
    Perfil novo("Matematica", "UFOP", 2);
    Comunidade c("Algebra", adm);
    CHECK_NOTHROW(c.entrarComunidade(novo));
}

TEST_CASE("podePublicar nao lanca excecao") {
    Perfil adm("Computacao", "UFMG", 5);
    Perfil membro("Fisica", "USP", 3);
    Comunidade c("Fisica Moderna", adm);
    c.entrarComunidade(membro);
    CHECK_NOTHROW(c.podePublicar(membro));
}

TEST_CASE("buscarPosts retorna lista vazia quando nao ha posts") {
    Perfil adm("Computacao", "UFMG", 5);
    Comunidade c("IA", adm);
    CHECK(c.buscarPosts("qualquer").empty());
}

TEST_CASE("buscarPosts retorna vazio quando termo nao existe nos posts") {
    Perfil adm("Computacao", "UFMG", 5);
    Comunidade c("IA", adm);
    // sem posts cadastrados, busca deve retornar vazio
    CHECK(c.buscarPosts("blockchain").empty());
}

TEST_CASE("exibirMembrosComunidade nao lanca excecao") {
    Perfil adm("Computacao", "UFMG", 5);
    Comunidade c("Teste", adm);
    CHECK_NOTHROW(c.exibirMembrosComunidade());
}

TEST_CASE("exibirMembrosComunidade com multiplos membros nao lanca excecao") {
    Perfil adm("Computacao", "UFMG", 5);
    Comunidade c("Teste", adm);
    c.entrarComunidade(Perfil("Fisica", "USP", 1));
    c.entrarComunidade(Perfil("Quimica", "UFOP", 2));
    CHECK_NOTHROW(c.exibirMembrosComunidade());
}

}
