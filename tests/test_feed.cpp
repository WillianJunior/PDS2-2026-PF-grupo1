#include <doctest/doctest.h>
#include "domain/feed.hpp"
#include "domain/perfil.hpp"
#include "domain/post.hpp"
#include "domain/comunidade.hpp"
#include "domain/armazenamento.hpp"

TEST_SUITE("Feed") {

    TEST_CASE("exibirPosts com lista vazia nao lanca excecao") {
        Feed f;
        Armazenamento db;
        std::vector<Post> lista;
        CHECK_NOTHROW(f.exibirPosts(lista, db));
    }

    TEST_CASE("exibirPosts com multiplos posts nao lanca excecao") {
        Feed f;
        Armazenamento db;
        std::vector<Post> lista = {
            Post(1, 10, 0, "Post 1"),
            Post(2, 10, 0, "Post 2")
        };
        CHECK_NOTHROW(f.exibirPosts(lista, db));
    }

    TEST_CASE("exibirPerfis com lista vazia nao lanca excecao") {
        Feed f;
        CHECK_NOTHROW(f.exibirPerfis({}));
    }

    TEST_CASE("exibirPerfis com perfis nao lanca excecao") {
        Feed f;
        std::vector<Perfil> lista = {
            Perfil(1, "a@b.com", "Fisica", "Bio", "C", "I", 1),
            Perfil(2, "c@d.com", "Matematica", "Bio", "C", "I", 2)
        };
        CHECK_NOTHROW(f.exibirPerfis(lista));
    }

    TEST_CASE("exibirComunidades com comunidades nao lanca excecao") {
        Feed f;
        std::vector<Comunidade> lista = {
            Comunidade(1, "IA", "Desc", 1),
            Comunidade(2, "DevOps", "Desc", 1)
        };
        CHECK_NOTHROW(f.exibirComunidades(lista));
    }
}