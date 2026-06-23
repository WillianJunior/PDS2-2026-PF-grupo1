#include "domain/armazenamento.hpp"
#include "domain/busca.hpp"
#include <doctest/doctest.h>

TEST_SUITE("Busca") {

    TEST_CASE("Buscar perfis") {
        Armazenamento db;
        Busca b;

        db.criarUsuarioEPerfil("ana@ufmg.br", "Senha123", "Ana");
        db.criarUsuarioEPerfil("bruno@ufmg.br", "Senha123", "Bruno");

        db.getPerfil(1)->setDescricao("Programador C++");
        db.getPerfil(2)->setDescricao("Tambem estuda C++");

        auto perfis = b.buscarPerfis("C++", db);

        CHECK(perfis.size() == 2);
        CHECK(b.buscarPerfis("Inexistente", db).empty());
    }

    TEST_CASE("Buscar posts") {
        Armazenamento db;
        Busca b;

        db.criarUsuarioEPerfil("teste@teste.com", "senha123", "Alvo");
        db.fazerLogin("teste@teste.com", "senha123");

        db.criarPost("Aprendendo C++", 0);
        db.criarPost("Java avancado", 0);

        auto posts = b.buscarPosts("C++", db);

        CHECK(posts.size() == 1);
        CHECK(posts[0].getConteudo() == "Aprendendo C++");

        CHECK(b.buscarPosts("Python", db).empty());
    }

    TEST_CASE("Buscar comunidades") {
        Armazenamento db;
        Busca b;

        db.criarUsuarioEPerfil("teste@teste.com", "senha123", "Alvo");
        db.fazerLogin("teste@teste.com", "senha123");

        db.criarComunidade("C++ Fans", "Grupo de cpp");
        db.criarComunidade("Java", "Grupo java");

        auto comunidades = b.buscarComunidades("C++", db);

        CHECK(comunidades.size() == 1);
        CHECK(comunidades[0].getNome() == "C++ Fans");

        CHECK(b.buscarComunidades("Python", db).empty());
    }

    TEST_CASE("Buscar posts de uma comunidade") {
        Armazenamento db;
        Busca b;

        db.criarUsuarioEPerfil("teste@teste.com", "senha123", "Alvo");
        db.fazerLogin("teste@teste.com", "senha123");

        db.criarComunidade("Teste", "Descricao");

        int idComunidade = db.listarComunidade()[0].getId();

        db.criarPost("Post 1", idComunidade);
        db.criarPost("Post 2", idComunidade);
        db.criarPost("Post geral", 0);

        auto posts = b.buscaPosts(idComunidade, db);

        CHECK(posts.size() == 2);
        CHECK(posts[0]->getConteudo() == "Post 1"); // Acesso alterado de '.' para '->'
        CHECK(posts[1]->getConteudo() == "Post 2");
    }
}