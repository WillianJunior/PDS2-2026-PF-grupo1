#include <doctest/doctest.h>
#include "domain/usuario.hpp"

TEST_SUITE("Usuario")
{

    TEST_CASE("Construtor armazena email e nome")
    {
        Usuario u("ana@uni.br", "Senha123", "Ana");
        CHECK(u.getEmail() == "ana@uni.br");
        CHECK(u.getNome() == "Ana");
    }

    TEST_CASE("Login com credenciais corretas retorna true")
    {
        Usuario u("ana@uni.br", "Senha123", "Ana");
        CHECK(u.fazerLogin("ana@uni.br", "Senha123") == true);
    }

    TEST_CASE("Login com senha errada retorna false")
    {
        Usuario u("ana@uni.br", "Senha123", "Ana");
        CHECK(u.fazerLogin("ana@uni.br", "errada") == false);
    }

    TEST_CASE("Login com email errado retorna false")
    {
        Usuario u("ana@uni.br", "Senha123", "Ana");
        CHECK(u.fazerLogin("outro@uni.br", "Senha123") == false);
    }

    TEST_CASE("alterarSenha com senha correta retorna true e atualiza")
    {
        Usuario u("ana@uni.br", "Senha123", "Ana");
        CHECK(u.alterarSenha("Senha123", "Nova456") == true);
        CHECK(u.fazerLogin("ana@uni.br", "Nova456") == true);
    }

    TEST_CASE("alterarSenha com senha errada retorna false e nao altera")
    {
        Usuario u("ana@uni.br", "Senha123", "Ana");
        CHECK(u.alterarSenha("errada", "Nova456") == false);
        CHECK(u.fazerLogin("ana@uni.br", "Senha123") == true);
    }

    TEST_CASE("alterarEmail com senha correta retorna true e atualiza")
    {
        Usuario u("ana@uni.br", "Senha123", "Ana");
        CHECK(u.alterarEmail("Senha123", "novo@uni.br") == true);
        CHECK(u.getEmail() == "novo@uni.br");
    }

    TEST_CASE("alterarEmail com senha errada retorna false e nao altera")
    {
        Usuario u("ana@uni.br", "Senha123", "Ana");
        CHECK(u.alterarEmail("errada", "novo@uni.br") == false);
        CHECK(u.getEmail() == "ana@uni.br");
    }
}
