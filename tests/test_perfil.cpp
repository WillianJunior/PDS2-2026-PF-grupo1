#include <doctest/doctest.h>
#include "domain/perfil.hpp"

TEST_SUITE("Perfil") {
    TEST_CASE("Construtores e Getters") {
        Perfil p1(1, "Nome", "Desc", "Curso", "Inst", 5);
        CHECK(p1.getId() == 1);
        CHECK(p1.getNome() == "Nome");
        CHECK(p1.getDescricao() == "Desc");
        CHECK(p1.getCurso() == "Curso");
        CHECK(p1.getInstituicao() == "Inst");
        CHECK(p1.getPeriodo() == 5);

        Perfil p2("Curso2", "Inst2", 2);
        CHECK(p2.getId() == 0);
        CHECK(p2.getCurso() == "Curso2");
    }

    TEST_CASE("Setters") {
        Perfil p("Curso", "Inst", 1);
        p.setCurso("NovoCurso");
        p.setInstituicao("NovaInst");
        p.setDescricao("NovaDesc");
        p.setPeriodo(3);
        CHECK(p.getCurso() == "NovoCurso");
        CHECK(p.getInstituicao() == "NovaInst");
        CHECK(p.getDescricao() == "NovaDesc");
        CHECK(p.getPeriodo() == 3);

        p.setIdsSeguidores({1, 2});
        p.setIdsSeguidos({3, 4});
        p.setIdsComunidades({5, 6});
        CHECK(p.getIdsSeguidores().size() == 2);
        CHECK(p.getIdsSeguidos().size() == 2);
        CHECK(p.getIdsComunidades().size() == 2);
    }

    TEST_CASE("adicionarSeguidor e removerSeguidor") {
        Perfil p("Curso", "Inst", 1);
        p.adicionarSeguidor(2);
        p.adicionarSeguidor(2);
        CHECK(p.getIdsSeguidores().size() == 1);
        p.removerSeguidor(2);
        CHECK(p.getIdsSeguidores().size() == 0);
        CHECK_NOTHROW(p.removerSeguidor(99));
    }

    TEST_CASE("seguir e deixarDeSeguir") {
        Perfil p("Curso", "Inst", 1);
        p.seguir(2);
        p.seguir(2);
        CHECK(p.listarIdSeguidos().size() == 1);
        p.deixarDeSeguir(2);
        CHECK(p.listarIdSeguidos().size() == 0);
        CHECK_NOTHROW(p.deixarDeSeguir(99)); 
    }

    TEST_CASE("entrarComunidade e sairComunidade") {
        Perfil p("Curso", "Inst", 1);
        p.entrarComunidade(10);
        p.entrarComunidade(10);
        CHECK(p.getIdsComunidades().size() == 1);
        p.sairComunidade(10);
        CHECK(p.getIdsComunidades().size() == 0);
        CHECK_NOTHROW(p.sairComunidade(99)); 
    }
    TEST_CASE("Setters perfil simples") {
    Perfil p("Eng", "UF", 1);

    p.setCurso("TI");
    p.setInstituicao("UFMG");

    CHECK(p.getCurso() == "TI");
    CHECK(p.getInstituicao() == "UFMG");
}
}