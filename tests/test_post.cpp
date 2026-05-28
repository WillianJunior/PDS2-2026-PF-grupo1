#include <doctest/doctest.h>
#include "domain/post.hpp"
#include "domain/comentario.hpp"
#include "domain/perfil.hpp"

TEST_SUITE("Post") {

TEST_CASE("Construtor nao lanca excecao") {
    Perfil autor("Computacao", "UFMG", 1);
    CHECK_NOTHROW(Post("Meu primeiro post", autor));
}

TEST_CASE("curtir nao lanca excecao") {
    Perfil autor("Computacao", "UFMG", 1);
    Post p("Texto", autor);
    CHECK_NOTHROW(p.curtir(10));
}

TEST_CASE("curtir mesmo usuario duas vezes nao lanca excecao") {
    Perfil autor("Computacao", "UFMG", 1);
    Post p("Texto", autor);
    p.curtir(10);
    CHECK_NOTHROW(p.curtir(10));
}

TEST_CASE("adicionarComentario nao lanca excecao") {
    Perfil autor("Computacao", "UFMG", 1);
    Post p("Texto", autor);
    Comentario c("Bom post!", autor);
    CHECK_NOTHROW(p.adicionarComentario(c));
}

TEST_CASE("removerComentario apos adicionar nao lanca excecao") {
    Perfil autor("Computacao", "UFMG", 1);
    Post p("Texto", autor);
    p.adicionarComentario(Comentario("C1", autor));
    p.adicionarComentario(Comentario("C2", autor));
    CHECK_NOTHROW(p.removerComentario(0));
}

TEST_CASE("exibirComentarios nao lanca excecao") {
    Perfil autor("Computacao", "UFMG", 1);
    Post p("Texto", autor);
    CHECK_NOTHROW(p.exibirComentarios());
}

TEST_CASE("exibirCurtidas nao lanca excecao") {
    Perfil autor("Computacao", "UFMG", 1);
    Post p("Texto", autor);
    CHECK_NOTHROW(p.exibirCurtidas());
}

TEST_CASE("exibirComentarios com comentarios nao lanca excecao") {
    Perfil autor("Computacao", "UFMG", 1);
    Post p("Texto", autor);
    p.adicionarComentario(Comentario("Muito bom!", autor));
    CHECK_NOTHROW(p.exibirComentarios());
}

}
