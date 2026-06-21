#include <doctest/doctest.h>
#include "domain/gerenciador_csv.hpp"
#include <fstream>
#include <cstdio>

TEST_SUITE("GerenciadorCSV") {
    TEST_CASE("Manipulacao de Strings e Inteiros") {
        auto resStr = GerenciadorCSV::separarString("a,b,c", ',');
        CHECK(resStr.size() == 3);

        auto resInt = GerenciadorCSV::separarInteiros("1|2|3", '|');
        CHECK(resInt.size() == 3);

        auto emptyInt = GerenciadorCSV::separarInteiros("", '|');
        CHECK(emptyInt.empty());

        CHECK(GerenciadorCSV::juntarInteiros({1,2,3}, '|') == "1|2|3");
        CHECK(GerenciadorCSV::juntarInteiros({}, '|') == "");
    }

    TEST_CASE("Exportar e Importar CSV Fisico - Entidades Completas") {
        std::vector<Usuario> usrs = { Usuario(1,"a@a.com", "senha", "UserA") };
        GerenciadorCSV::salvarUsuarios(usrs, "test_usrs.csv");
        auto uLido = GerenciadorCSV::carregarUsuarios("test_usrs.csv");
        CHECK(uLido.size() == 1);
        CHECK(uLido[0].getEmail() == "a@a.com");

        Perfil p(1, "a", "b", "c", "d", 2);
        p.setIdsSeguidores({1}); p.setIdsSeguidos({2}); p.setIdsComunidades({3});
        GerenciadorCSV::salvarPerfis({p}, "test_perfis.csv");
        auto pLido = GerenciadorCSV::carregarPerfis("test_perfis.csv");
        CHECK(pLido.size() == 1);
        CHECK(pLido[0].getId() == 1);

        Comunidade c(1, "Nome", "Desc", 2);
        c.setIdsMembros({1, 2});
        GerenciadorCSV::salvarComunidades({c}, "test_coms.csv");
        auto cLido = GerenciadorCSV::carregarComunidades("test_coms.csv");
        CHECK(cLido.size() == 1);
        CHECK(cLido[0].getNome() == "Nome");

        Post post(1, 2, 3, "Texto");
        post.setIdsCurtidas({1});
        GerenciadorCSV::salvarPosts({post}, "test_posts.csv");
        auto poLido = GerenciadorCSV::carregarPosts("test_posts.csv");
        CHECK(poLido.size() == 1);
        CHECK(poLido[0].getConteudo() == "Texto");

        Comentario com(1, 2, 3, "Texto");
        com.setIdsCurtidas({1});
        GerenciadorCSV::salvarComentarios({com}, "test_coments.csv");
        auto coLido = GerenciadorCSV::carregarComentarios("test_coments.csv");
        CHECK(coLido.size() == 1);
        CHECK(coLido[0].getTexto() == "Texto");

        std::remove("test_usrs.csv");
        std::remove("test_perfis.csv");
        std::remove("test_coms.csv");
        std::remove("test_posts.csv");
        std::remove("test_coments.csv");
    }
}