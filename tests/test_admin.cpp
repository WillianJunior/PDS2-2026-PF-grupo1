#include <doctest/doctest.h>
#include "domain/admin.hpp"

TEST_SUITE("Administrador") {
    TEST_CASE("Criacao e verificacao de privilegios do Admin") {
        Administrador admin(1, "Admin Supremo", "Gerencia tudo", "Engenharia de Sistemas", "UFMG", 5);
        CHECK(admin.getId() == 1);
        CHECK(admin.getNome() == "Admin Supremo");
        CHECK(admin.getCurso() == "Engenharia de Sistemas");
        CHECK(admin.podeGerenciarComunidade() == true);
    }
}