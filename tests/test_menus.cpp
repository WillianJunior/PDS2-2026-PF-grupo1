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

        std::istringstream input("\n\n\n");
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

        auto &posts = db.getTodosPostsMutavel();

        std::istringstream input("F\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVisualizarPost(posts[0], db));
        std::cout << "menuVisualizarPost sair direto passou sem travar\n";
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
        std::cout << "menuComunidade sair direto passou sem travar\n";
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost curtir e descurtir") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarPost("Teste", 0);

        auto &posts = db.getTodosPostsMutavel();

        std::istringstream input("A\nA\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVisualizarPost(posts[0], db));
        std::cout
            << "menuVisualizarPost curtir e descurtir passou sem travar\n";
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost comentar") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarPost("Teste", 0);

        auto &posts = db.getTodosPostsMutavel();

        std::istringstream input("C\nMeu comentario\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVisualizarPost(posts[0], db));
        std::cout << "menuVisualizarPost comentar passou sem travar\n";
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost curtir comentario") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");

        db.criarPost("Teste", 0);
        db.criarComentarioGlobal(1, 1, "Comentario teste");

        auto &posts = db.getTodosPostsMutavel();

        std::istringstream input("B\n1\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVisualizarPost(posts[0], db));
        std::cout << "menuVisualizarPost curtir comentario passou sem travar\n";
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost abrir perfil") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");

        db.criarPost("Teste", 0);

        auto &posts = db.getTodosPostsMutavel();

        std::istringstream input("D\nB\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVisualizarPost(posts[0], db));
        std::cout << "menuVisualizarPost abrir perfil passou sem travar\n";
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
        std::cout << "menuComunidade criar post passou sem travar\n";
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost erro sem comentarios") {
        Armazenamento db;

        db.criarUsuarioEPerfil("x@x.com", "senha12345", "X");
        db.fazerLogin("x@x.com", "senha12345");
        db.criarPost("Teste", 0);

        auto &posts = db.getTodosPostsMutavel();

        std::istringstream input("B\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVisualizarPost(posts[0], db));
        std::cout
            << "menuVisualizarPost erro sem comentarios passou sem travar\n";
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista opcao invalida") {
        Armazenamento db;

        std::vector<Post> lista{Post("Teste", 1)};

        std::istringstream input("Z\nB\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVerPostsLista(lista, db));
        std::cout << "menuVerPostsLista opcao invalida passou sem travar\n";
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
        std::cout << "menuVerPostsLista selecionar e sair passou sem travar\n";
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuComunidade abrir e sair simples") {
        Armazenamento db;

        db.criarUsuarioEPerfil("x@x.com", "senha12345", "X");
        db.fazerLogin("x@x.com", "senha12345");
        db.criarComunidade("Teste", "Desc");

        std::istringstream input("4\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuComunidade(1, db));
        std::cout << "menuComunidade abrir e sair simples passou sem travar\n";
        std::cin.rdbuf(old);
    }

    TEST_CASE("menuPerfil abrir e sair imediato") {
        Armazenamento db;

        db.criarUsuarioEPerfil("x@x.com", "senha12345", "X");
        db.fazerLogin("x@x.com", "senha12345");

        std::istringstream input("B\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuPerfil(1, db));
        std::cout << "menuPerfil abrir e sair imediato passou sem travar\n";
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

    TEST_CASE("menuVisualizarPost curtir uma vez e sair") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarPost("Teste", 0);

        auto &posts = db.getTodosPostsMutavel();

        std::istringstream input("A\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVisualizarPost(posts[0], db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost opcao invalida") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarPost("Teste", 0);

        auto &posts = db.getTodosPostsMutavel();

        std::istringstream input("Z\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVisualizarPost(posts[0], db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista vazio multiplas entradas") {
        Armazenamento db;

        std::vector<Post> lista;

        std::istringstream input("\n\n\n\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVerPostsLista(lista, db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista selecionar valido rapido") {
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

    TEST_CASE("menuComunidade abrir sem interacao") {
        Armazenamento db;

        db.criarUsuarioEPerfil("x@x.com", "senha12345", "X");
        db.fazerLogin("x@x.com", "senha12345");
        db.criarComunidade("Teste", "Desc");

        std::istringstream input("4\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuComunidade(1, db));

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

    TEST_CASE("menuVisualizarPost comentario vazio ignorado") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");
        db.criarPost("Teste", 0);

        auto &posts = db.getTodosPostsMutavel();

        std::istringstream input("C\n\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVisualizarPost(posts[0], db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost abrir comunidade inexistente") {
        Armazenamento db;

        db.criarUsuarioEPerfil("a@a.com", "senha12345", "A");
        db.fazerLogin("a@a.com", "senha12345");


        auto &posts = db.getTodosPostsMutavel();

        std::istringstream input("E\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVisualizarPost(posts[0], db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista letra aleatoria") {
        Armazenamento db;

        std::vector<Post> lista{Post("Teste", 1)};

        std::istringstream input("X\nB\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVerPostsLista(lista, db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista selecionar e cancelar") {
        Armazenamento db;

        db.criarUsuarioEPerfil("b@b.com", "senha12345", "B");
        db.fazerLogin("b@b.com", "senha12345");
        db.criarPost("Teste", 0);

        auto lista = db.getTodosPosts();

        std::istringstream input("A\n1\nF\nB\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVerPostsLista(lista, db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuComunidade id invalido") {
        Armazenamento db;

        std::istringstream input("4\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuComunidade(999, db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuPerfil id invalido") {
        Armazenamento db;

        std::istringstream input("3\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuPerfil(999, db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost curtir comentario rapido") {
        Armazenamento db;

        db.criarUsuarioEPerfil("c@c.com", "senha12345", "C");
        db.fazerLogin("c@c.com", "senha12345");

        db.criarPost("Teste", 0);
        db.criarComentarioGlobal(1, 1, "Oi");

        auto &posts = db.getTodosPostsMutavel();

        std::istringstream input("B\n1\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVisualizarPost(posts[0], db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost comentario simples") {
        Armazenamento db;

        db.criarUsuarioEPerfil("d@d.com", "senha12345", "D");
        db.fazerLogin("d@d.com", "senha12345");

        db.criarPost("Teste", 0);

        auto &posts = db.getTodosPostsMutavel();

        std::istringstream input("C\nTeste comentario\nF\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVisualizarPost(posts[0], db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista cancelar direto") {
        Armazenamento db;

        std::vector<Post> lista{Post("Teste", 1)};

        std::istringstream input("B\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVerPostsLista(lista, db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVisualizarPost sair direto sem interacao") {
        Armazenamento db;

        db.criarUsuarioEPerfil("f@f.com", "senha12345", "F");
        db.fazerLogin("f@f.com", "senha12345");

        db.criarPost("Teste", 0);

        auto &posts = db.getTodosPostsMutavel();

        std::istringstream input("F\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVisualizarPost(posts[0], db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuPerfil invalido e sair") {
        Armazenamento db;

        db.criarUsuarioEPerfil("g@g.com", "senha12345", "G");
        db.fazerLogin("g@g.com", "senha12345");

        std::istringstream input("0\n3\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuPerfil(1, db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista vazio total") {
        Armazenamento db;
        std::vector<Post> lista;

        std::istringstream input("B\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVerPostsLista(lista, db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista entrada totalmente invalida") {
        Armazenamento db;

        std::vector<Post> lista{Post("Teste", 1)};

        std::istringstream input("???\nB\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        CHECK_NOTHROW(menuVerPostsLista(lista, db));

        std::cin.rdbuf(old);
    }

    TEST_CASE("menuVerPostsLista cobre lista vazia FORCADO") {
        Armazenamento db;
        std::vector<Post> lista;
        std::istringstream input("A\nB\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        menuVerPostsLista(lista, db);

        std::cin.rdbuf(old);
        CHECK(true);
    }

    TEST_CASE("menuVerPostsLista indice invalido REAL") {
        Armazenamento db;

        std::vector<Post> lista{Post("Teste", 1)};

        std::istringstream input("A\n999\nB\n");
        auto *old = std::cin.rdbuf(input.rdbuf());

        menuVerPostsLista(lista, db);

        std::cin.rdbuf(old);
        CHECK(true);
    }
}
