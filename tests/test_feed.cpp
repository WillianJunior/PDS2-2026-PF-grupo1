#include <doctest/doctest.h>
#include "domain/feed.hpp"
#include "domain/perfil.hpp"
#include "domain/post.hpp"
#include "domain/comunidade.hpp"

TEST_SUITE("Feed") {

TEST_CASE("exibirPosts com lista vazia nao lanca excecao") {
    Feed f;
    CHECK_NOTHROW(f.exibirPosts({}));
}

TEST_CASE("exibirPosts com um post nao lanca excecao") {
    Feed f;
    const int idAutor = 1;
    std::vector<Post> lista = { Post("Introducao a grafos", idAutor) };
    CHECK_NOTHROW(f.exibirPosts(lista));
}

TEST_CASE("exibirPosts com multiplos posts nao lanca excecao") {
    Feed f;
    const int idAutor = 1;
    std::vector<Post> lista = {
        Post("Post 1", idAutor),
        Post("Post 2", idAutor),
        Post("Post 3", idAutor)
    };
    CHECK_NOTHROW(f.exibirPosts(lista));
}

TEST_CASE("exibirPerfis com lista vazia nao lanca excecao") {
    Feed f;
    CHECK_NOTHROW(f.exibirPerfis({}));
}

TEST_CASE("exibirPerfis com perfis nao lanca excecao") {
    Feed f;
    std::vector<Perfil> lista = {
        Perfil("Fisica",     "USP",  2),
        Perfil("Matematica", "UFMG", 4)
    };
    CHECK_NOTHROW(f.exibirPerfis(lista));
}

TEST_CASE("exibirComunidades com lista vazia nao lanca excecao") {
    Feed f;
    CHECK_NOTHROW(f.exibirComunidades({}));
}

TEST_CASE("exibirComunidades com comunidades nao lanca excecao") {
    Feed f;
    const int idAdministrador = 1;
    std::vector<Comunidade> lista = {
        Comunidade("IA",     idAdministrador),
        Comunidade("DevOps", idAdministrador)
    };
    CHECK_NOTHROW(f.exibirComunidades(lista));
}

}
