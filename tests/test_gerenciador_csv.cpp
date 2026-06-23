#include "domain/gerenciador_csv.hpp"
#include <cstdio>
#include <doctest/doctest.h>
#include <fstream>

TEST_SUITE("GerenciadorCSV") {
    TEST_CASE("Manipulacao de Strings e Inteiros") {
        auto resStr = GerenciadorCSV::separarString("a,b,c", ',');
        CHECK(resStr.size() == 3);

        auto resInt = GerenciadorCSV::separarInteiros("1|2|3", '|');
        CHECK(resInt.size() == 3);

        auto emptyInt = GerenciadorCSV::separarInteiros("", '|');
        CHECK(emptyInt.empty());

        CHECK(GerenciadorCSV::juntarInteiros({1, 2, 3}, '|') == "1|2|3");
        CHECK(GerenciadorCSV::juntarInteiros({}, '|') == "");
    }

    TEST_CASE("Exportar e Importar CSV Fisico - Entidades Completas") {
        std::vector<Usuario> usrs = {Usuario(1, "a@a.com", "senha", "UserA")};
        GerenciadorCSV::salvarUsuarios(usrs, "test_usrs.csv");
        auto uLido = GerenciadorCSV::carregarUsuarios("test_usrs.csv");
        CHECK(uLido.size() == 1);
        CHECK(uLido[0].getEmail() == "a@a.com");

        Perfil p(1, "a", "b", "c", "d", 2);
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

    TEST_CASE("Escapar e Desescapar Virgulas (Cobertura de Texto)") {
        Perfil p(1, "Nome, com virgula", "Descricao, super, com, virgula", "Curso", "Inst", 2);
        p.setIdsComunidades({1, 2});

        GerenciadorCSV::salvarPerfis({p}, "test_virgula.csv");
        auto pLido = GerenciadorCSV::carregarPerfis("test_virgula.csv");

        CHECK(pLido.size() == 1);
        CHECK(pLido[0].getNome() == "Nome, com virgula");
        CHECK(pLido[0].getDescricao() == "Descricao, super, com, virgula");
        CHECK(pLido[0].getIdsComunidades().size() == 2);

        std::remove("test_virgula.csv");
    }

    TEST_CASE("Parsing com Falhas - Arquivos Corrompidos (Cobertura dos catch)") {
        auto ints = GerenciadorCSV::separarInteiros("1|err|3", '|');
        CHECK(ints.size() == 2);
        CHECK(ints[0] == 1);
        CHECK(ints[1] == 3);

        std::ofstream("err_perfis.csv") << "id,nome,descricao,curso,instituicao,periodo,comunidades\n"
                                        << "ISSO_NAO_E_NUMERO,Nome,Desc,Curso,Inst,1,1|2\n";
        CHECK(GerenciadorCSV::carregarPerfis("err_perfis.csv").empty());

        std::ofstream("err_coms.csv") << "id,nome,descricao,idAdmin,membros\n"
                                      << "OUTRO_ERRO,Nome,Desc,1,1|2\n";
        CHECK(GerenciadorCSV::carregarComunidades("err_coms.csv").empty());

        std::ofstream("err_posts.csv") << "id,idAutor,idComunidade,texto,curtidas\n"
                                       << "MAIS_ERRO,1,1,Texto,1\n";
        CHECK(GerenciadorCSV::carregarPosts("err_posts.csv").empty());

        std::ofstream("err_coments.csv") << "id,idPost,idAutor,texto,curtidas\n"
                                         << "ERRO_FATAL,1,1,Texto,1\n";
        CHECK(GerenciadorCSV::carregarComentarios("err_coments.csv").empty());

        std::remove("err_perfis.csv");
        std::remove("err_coms.csv");
        std::remove("err_posts.csv");
        std::remove("err_coments.csv");
    }
}