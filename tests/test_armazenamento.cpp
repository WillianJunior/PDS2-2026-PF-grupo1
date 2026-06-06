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

    TEST_CASE("senhaSegura retorna false para senha curta")
    {
        Armazenamento a = makeArmazenamento();
        CHECK(a.senhaSegura("Ab1") == false);
    }

    TEST_CASE("senhaSegura retorna false para senha sem digito")
    {
        Armazenamento a = makeArmazenamento();
        CHECK(a.senhaSegura("SenhaSemNumero") == false);
    }

    TEST_CASE("senhaSegura retorna true para senha valida")
    {
        Armazenamento a = makeArmazenamento();
        CHECK(a.senhaSegura("Segura99") == true);
    }

    TEST_CASE("emailUnico retorna true para lista vazia")
    {
        Armazenamento a = makeArmazenamento();
        CHECK(a.emailUnico("novo@uni.br") == true);
    }

    TEST_CASE("listarPerfis retorna lista vazia inicialmente")
    {
        Armazenamento a = makeArmazenamento();
        CHECK(a.listarPerfis().empty());
    }

    TEST_CASE("criarPerfil adiciona perfil e listarPerfis retorna um elemento")
    {
        Armazenamento a = makeArmazenamento();
        Perfil p("Matematica", "USP", 4);
        a.criarPerfil(p);
        CHECK(a.listarPerfis().size() == 1);
    }

    TEST_CASE("listarComunidade retorna lista vazia inicialmente")
    {
        Armazenamento a = makeArmazenamento();
        CHECK(a.listarComunidade().empty());
    }

    TEST_CASE("criarComunidade adiciona comunidade e listarComunidade retorna um elemento")
    {
        Armazenamento a = makeArmazenamento();
        const int idAdministrador = 5;
        Comunidade c("DevOps", idAdministrador);
        a.criarComunidade(c);
        CHECK(a.listarComunidade().size() == 1);
    }

    TEST_CASE("mensagemSucessoErro nao lanca excecao")
    {
        Armazenamento a = makeArmazenamento();
        CHECK_NOTHROW(a.mensagemSucessoErro());
    }
}
