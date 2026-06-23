#include "domain/perfil.hpp"
#include <doctest/doctest.h>

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
        p.setIdsComunidades({5, 6});
        CHECK(p.getIdsComunidades().size() == 2);
    }

    TEST_CASE("entrarComunidade") {
        Perfil p("Curso", "Inst", 1);
        p.entrarComunidade(10);
        p.entrarComunidade(10);
        CHECK(p.getIdsComunidades().size() == 1);
    }

    TEST_CASE("Metodos Adicionais (Cobertura total)") {
        Perfil p("Curso", "Inst", 1);
        CHECK(p.podeGerenciarComunidade() == false);
    }
}