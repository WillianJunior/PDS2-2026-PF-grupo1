#include <doctest/doctest.h>
#include "domain/post.hpp"
#include "domain/comentario.hpp"
#include "domain/perfil.hpp"

TEST_SUITE("Post") {
    TEST_CASE("Construtores e Getters") {
        Post p1(10, 1, 5, "Texto Completo");
        CHECK(p1.getId() == 10);
        CHECK(p1.getIdAutor() == 1);
        CHECK(p1.getIdComunidade() == 5);
        CHECK(p1.getConteudo() == "Texto Completo");

        Post p2("Texto Simples", 2);
        CHECK(p2.getId() == 0);
        CHECK(p2.getIdAutor() == 2);
        CHECK(p2.getIdComunidade() == 0);
        CHECK(p2.getConteudo() == "Texto Simples");
    }

    TEST_CASE("Curtidas e Setters") {
        Post p("Texto", 1);
        p.curtir(10);
        CHECK(p.quantidadeDeCurtidas() == 1);
        p.curtir(10); // Alterna estado (Toggle)
        CHECK(p.quantidadeDeCurtidas() == 0);

        p.setIdsCurtidas({1, 2, 3});
        CHECK(p.getIdsCurtidas().size() == 3);
    }

    TEST_CASE("Gerenciamento local de Comentarios") {
        Perfil autor("Computacao", "UFMG", 1);
        Post p("Texto", 1);
        Comentario c1("Bom post!", autor);
        Comentario c2("Gostei!", autor);
        p.adicionarComentario(c1);
        p.adicionarComentario(c2);
        CHECK(p.listarComentarios().size() == 2);
    }
}