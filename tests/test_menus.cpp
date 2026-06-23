#include "domain/armazenamento.hpp"
#include "domain/menus.hpp"
#include "domain/post.hpp"
#include <doctest/doctest.h>
#include <iostream>
#include <sstream>

TEST_SUITE("Menus") {

    TEST_CASE("menuVerPostsLista sem travar (vazio)") {
        Armazenamento db;
        std::vector<Post> lista;

        std::istringstream input("\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVerPostsLista(lista, db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista voltar sem travar") {
        Armazenamento db;

        Post p1("Post 1", 1);
        std::vector<Post> lista{p1};

        std::istringstream input("B\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVerPostsLista(lista, db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost sair direto") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarPost("Teste", 0);

        auto posts = db.getTodosPosts();
        Post *postReal = db.getPostMutavel(posts[0].getId());

        std::istringstream input("F\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        if (postReal) {
            CHECK_NOTHROW(menuVisualizarPost(*postReal, db));
        }
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuPerfil sair direto") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");

        std::istringstream input("3\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuPerfil(db.getIdPerfilLogado(), db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuComunidade sair direto") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarComunidade("Com", "Desc");

        std::istringstream input("4\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuComunidade(1, db));
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuComunidade sair da comunidade") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarComunidade("Com", "Desc");

        Perfil *eu = db.getPerfil(db.getIdPerfilLogado());
        REQUIRE(eu != nullptr);
        CHECK(eu->getIdsComunidades().size() == 1);

        std::istringstream input("3\n4\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuComunidade(1, db));
        CHECK(eu->getIdsComunidades().empty());
        CHECK(db.getComunidade(1)->getIdsMembros().empty());

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost curtir e descurtir") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarPost("Teste", 0);

        auto posts = db.getTodosPosts();
        Post *postReal = db.getPostMutavel(posts[0].getId());

        std::istringstream input("A\nA\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        if (postReal) {
            CHECK_NOTHROW(menuVisualizarPost(*postReal, db));
        }
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost comentar") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarPost("Teste", 0);

        auto posts = db.getTodosPosts();
        Post *postReal = db.getPostMutavel(posts[0].getId());

        std::istringstream input("C\nMeu comentario\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        if (postReal) {
            CHECK_NOTHROW(menuVisualizarPost(*postReal, db));
        }
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost curtir comentario") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");

        db.criarPost("Teste", 0);
        db.criarComentarioGlobal(1, 1, "Comentario teste");

        auto posts = db.getTodosPosts();
        Post *postReal = db.getPostMutavel(posts[0].getId());

        std::istringstream input("B\n1\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        if (postReal) {
            CHECK_NOTHROW(menuVisualizarPost(*postReal, db));
        }
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost abrir perfil") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarPost("Teste", 0);

        auto posts = db.getTodosPosts();
        Post *postReal = db.getPostMutavel(posts[0].getId());

        std::istringstream input("D\n3\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        if (postReal) {
            CHECK_NOTHROW(menuVisualizarPost(*postReal, db));
        }
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuComunidade criar post") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarComunidade("Com", "Desc");

        std::istringstream input("1\nMeu post\n4\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuComunidade(1, db));
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost erro sem comentarios") {
        Armazenamento db;

        db.criarUsuarioEPerfil("x@x.com", "senha12345", "X");
        db.fazerLogin("x@x.com", "senha12345");
        db.criarPost("Teste", 0);

        auto posts = db.getTodosPosts();
        Post *postReal = db.getPostMutavel(posts[0].getId());

        std::istringstream input("B\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        if (postReal) {
            CHECK_NOTHROW(menuVisualizarPost(*postReal, db));
        }
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista opcao invalida") {
        Armazenamento db;
        std::vector<Post> lista{Post("Teste", 1)};

        std::istringstream input("Z\nB\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVerPostsLista(lista, db));
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista selecionar e sair") {
        Armazenamento db;

        db.criarUsuarioEPerfil("x@x.com", "senha12345", "X");
        db.fazerLogin("x@x.com", "senha12345");
        db.criarPost("Teste", 0);

        auto lista = db.getTodosPosts();

        std::istringstream input("A\n1\nF\nB\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVerPostsLista(lista, db));
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuPerfil abrir e sair imediato") {
        Armazenamento db;
        db.criarUsuarioEPerfil("x@x.com", "senha12345", "X");
        db.fazerLogin("x@x.com", "senha12345");

        std::istringstream input("3\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuPerfil(1, db));
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista indice invalido erro") {
        Armazenamento db;
        std::vector<Post> lista{Post("Teste", 1)};

        std::istringstream input("A\n999\nB\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVerPostsLista(lista, db));
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost opcao invalida") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarPost("Teste", 0);

        auto posts = db.getTodosPosts();
        Post *postReal = db.getPostMutavel(posts[0].getId());

        std::istringstream input("Z\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        if (postReal) {
            CHECK_NOTHROW(menuVisualizarPost(*postReal, db));
        }
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuPerfil opcao invalida") {
        Armazenamento db;
        db.criarUsuarioEPerfil("x@x.com", "senha12345", "X");
        db.fazerLogin("x@x.com", "senha12345");

        std::istringstream input("99\n3\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuPerfil(1, db));
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost abrir comunidade inexistente") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarPost("Teste", 0); 

        auto posts = db.getTodosPosts();
        Post *postReal = db.getPostMutavel(posts[0].getId());

        std::istringstream input("E\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        if (postReal) {
            CHECK_NOTHROW(menuVisualizarPost(*postReal, db));
        }
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuComunidade id invalido") {
        Armazenamento db;

        std::istringstream input("3\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        // Se a comunidade não existe, o menu dá break imediatamente por segurança.
        CHECK_NOTHROW(menuComunidade(999, db));
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuPerfil id invalido") {
        Armazenamento db;

        std::istringstream input("3\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        // Perfil inválido quebra o loop no início do código original.
        CHECK_NOTHROW(menuPerfil(999, db));
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuPerfil invalido e sair") {
        Armazenamento db;
        db.criarUsuarioEPerfil("g@g.com", "senha12345", "G");
        db.fazerLogin("g@g.com", "senha12345");

        // Testando opção inválida '0' seguida do botão de sair '3'
        std::istringstream input("0\n3\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuPerfil(1, db));
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista cobre lista vazia FORCADO") {
        Armazenamento db;
        std::vector<Post> lista;
        
        std::istringstream input("\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVerPostsLista(lista, db));
        std::cin.rdbuf(old);
    }
}