#include <doctest/doctest.h>
#include "domain/usuario.hpp"

TEST_SUITE("Usuario") {
    TEST_CASE("Construtor e Getters") {
        Usuario u(1, "aluno@uni.br", "senha123", "AlunoTester");
        CHECK(u.getId() == 1);
        CHECK(u.getEmail() == "aluno@uni.br");
        CHECK(u.getSenha() == "senha123");
        CHECK(u.getNome() == "AlunoTester");
    }

    TEST_CASE("alterarSenha") {
        Usuario u(1, "aluno@uni.br", "senha123", "AlunoTester");
        CHECK(u.getId() == 1);
        CHECK(u.alterarSenha("errada", "nova123") == false);
        CHECK(u.alterarSenha("senha123", "nova123") == true);
        CHECK(u.getSenha() == "nova123");
    }

    TEST_CASE("alterarEmail") {
        Usuario u(1,"aluno@uni.br", "senha123", "AlunoTester");
        CHECK(u.alterarEmail("errada", "novo@uni.br") == false);
        CHECK(u.alterarEmail("senha123", "novo@uni.br") == true);
        CHECK(u.getEmail() == "novo@uni.br");
    }

    TEST_CASE("fazerLogin") {
        Usuario u(1, "aluno@uni.br", "senha123", "AlunoTester");
        CHECK(u.fazerLogin("aluno@uni.br", "errada") == false);
        CHECK(u.fazerLogin("errado@uni.br", "senha123") == false);
        CHECK(u.fazerLogin("aluno@uni.br", "senha123") == true);
    }
}