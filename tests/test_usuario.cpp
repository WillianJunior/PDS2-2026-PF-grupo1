#include "domain/usuario.hpp"
#include <doctest/doctest.h>

TEST_SUITE("Usuario") {
    TEST_CASE("Construtor e Getters") {
        Usuario u(1, "aluno@ufmg.br", "senha123", "AlunoTester");
        CHECK(u.getId() == 1);
        CHECK(u.getEmail() == "aluno@ufmg.br");
        CHECK(u.getSenha() == "senha123");
        CHECK(u.getNome() == "AlunoTester");
    }

    TEST_CASE("alterarSenha") {
        Usuario u(1, "aluno@ufmg.br", "senha123", "AlunoTester");
        CHECK(u.getId() == 1);
        CHECK(u.alterarSenha("errada", "nova123") == false);
        CHECK(u.alterarSenha("senha123", "nova123") == true);
        CHECK(u.getSenha() == "nova123");
    }

    TEST_CASE("alterarEmail") {
        Usuario u(1, "aluno@ufmg.br", "senha123", "AlunoTester");
        CHECK(u.alterarEmail("errada", "novo@ufmg.br") == false);
        CHECK(u.alterarEmail("senha123", "novo@ufmg.br") == true);
        CHECK(u.getEmail() == "novo@ufmg.br");
    }

    TEST_CASE("fazerLogin") {
        Usuario u(1, "aluno@ufmg.br", "senha123", "AlunoTester");
        CHECK(u.fazerLogin("aluno@ufmg.br", "errada") == false);
        CHECK(u.fazerLogin("errado@ufmg.br", "senha123") == false);
        CHECK(u.fazerLogin("aluno@ufmg.br", "senha123") == true);
    }
}