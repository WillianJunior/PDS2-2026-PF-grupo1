#include <doctest/doctest.h>
#include "domain/comentario.hpp"
#include "domain/perfil.hpp"

TEST_SUITE("Comentario") {
    TEST_CASE("Construtores e Getters") {
        Comentario c1(5, 10, 2, "Texto completo");
        CHECK(c1.getId() == 5);
        CHECK(c1.getIdPost() == 10);
        CHECK(c1.getIdAutor() == 2);
        CHECK(c1.idAutorObter() == 2);
        CHECK(c1.getTexto() == "Texto completo");

        Perfil autor("Curso", "Inst", 1);
        Comentario c2("Texto simples", autor);
        CHECK(c2.getId() == 0);
    }

    TEST_CASE("Curtidas e Setters") {
        Perfil autor("Curso", "Inst", 1);
        Comentario c("Texto", autor);
        c.curtir(1);
        c.curtir(2);
        CHECK(c.quantidadeDeCurtidas() == 2);
        c.curtir(1); 
        CHECK(c.quantidadeDeCurtidas() == 1);

        c.setIdsCurtidas({5, 6, 7});
        CHECK(c.getIdsCurtidas().size() == 3);
    }
}