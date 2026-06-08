#include "doctest/doctest.h"
#include "domain/armazenamento.hpp"
#include "domain/perfil.hpp"
#include "domain/comunidade.hpp"

static Armazenamento makeArmazenamento()
{
    return Armazenamento();
}

TEST_SUITE("Armazenamento")
{
    TEST_CASE("emailUnico retorna true para lista vazia")
    {
        Armazenamento a = makeArmazenamento();
        CHECK(a.emailUnico("novo@uni.br") == true);
    }

    TEST_CASE("getTodosPerfis retorna lista vazia inicialmente")
    {
        Armazenamento a = makeArmazenamento();
        CHECK(a.getTodosPerfis().empty());
    }

    TEST_CASE("criarUsuarioEPerfil adiciona perfil e getTodosPerfis retorna um elemento")
    {
        Armazenamento a = makeArmazenamento();
        a.criarUsuarioEPerfil("teste@usp.br", "senha123", "teste_user");
        CHECK(a.getTodosPerfis().size() == 1);
    }

    TEST_CASE("getTodasComunidades retorna lista vazia inicialmente")
    {
        Armazenamento a = makeArmazenamento();
        CHECK(a.getTodasComunidades().empty());
    }

    TEST_CASE("criarComunidade adiciona comunidade quando logado")
    {
        Armazenamento a = makeArmazenamento();
        
        // Simula a criacao e o login para ter permissao de criar comunidade
        a.criarUsuarioEPerfil("admin@devops.com", "senha123", "admin_devops");
        a.fazerLogin("admin@devops.com", "senha123"); 
        
        a.criarComunidade("DevOps", "Comunidade de tecnologia");
        
        CHECK(a.getTodasComunidades().size() == 1);
    }
}