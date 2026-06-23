#include "domain/armazenamento.hpp"
#include "domain/menus.hpp"
#include "domain/post.hpp"
#include <doctest/doctest.h>
#include <iostream>
#include <sstream>

struct RedirecionarIO {
    std::istringstream input;
    std::ostringstream output;
    std::streambuf *oldCin;
    std::streambuf *oldCout;

    RedirecionarIO(const std::string &in) : input(in) {
        oldCin = std::cin.rdbuf(input.rdbuf());
        oldCout = std::cout.rdbuf(output.rdbuf());
    }
    ~RedirecionarIO() {
        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);
    }
};

Armazenamento setupDBMenus() {
    Armazenamento db;
    db.criarUsuarioEPerfil("a@a.com", "senha123", "UserA");
    db.criarUsuarioEPerfil("b@b.com", "senha123", "UserB");
    db.fazerLogin("a@a.com", "senha123");
    return db;
}

TEST_SUITE("Menus - O Desafio do 100%") {

    TEST_CASE("1. Utilitarios e Seguranca Extrema") {
        Armazenamento db = setupDBMenus();
        Perfil *p = db.getPerfil(1);

        {
            RedirecionarIO io("99999999999999999999999\n5\n");
            menuEditarPerfil(*p);
        }
        {
            RedirecionarIO io("abcdef\n5\n");
            menuEditarPerfil(*p);
        }
        Post postFantasma(1, 999, 0, "Fantasma");
        {
            RedirecionarIO io("F\n");
            menuVisualizarPost(postFantasma, db);
        }
    }

    TEST_CASE("2. menuEditarPerfil - Exploracao e EOF") {
        Armazenamento db = setupDBMenus();
        Perfil *p = db.getPerfil(1);

        {
            RedirecionarIO io("1\nBio\n2\nCur\n3\nInst\n4\n2\n5\n");
            menuEditarPerfil(*p);
        }
        {
            RedirecionarIO io("1\n");
            menuEditarPerfil(*p);
        }
        {
            RedirecionarIO io("2\n");
            menuEditarPerfil(*p);
        }
        {
            RedirecionarIO io("3\n");
            menuEditarPerfil(*p);
        }
        {
            RedirecionarIO io("4\n");
            menuEditarPerfil(*p);
        }
        {
            RedirecionarIO io("4\n-1\n5\n");
            menuEditarPerfil(*p);
        }
        {
            RedirecionarIO io("\n5\n");
            menuEditarPerfil(*p);
        }
        {
            RedirecionarIO io("6\n5\n");
            menuEditarPerfil(*p);
        }
        {
            RedirecionarIO io("V\n");
            menuEditarPerfil(*p);
        }
    }

    TEST_CASE("3. menuVisualizarPost e tratarOpcaoPost - Catch e EOFs") {
        Armazenamento db = setupDBMenus();
        db.criarPost("Global", 0);
        db.criarComentarioGlobal(1, 1, "Coment1");
        db.criarComunidade("C", "D");
        db.criarPost("Comum", 1);

        Post *pGlobal = db.getPostMutavel(1);
        Post *pComum = db.getPostMutavel(2);

        {
            RedirecionarIO io("A\nB\n1\nC\nComentarioNovo\nD\n3\nF\n");
            menuVisualizarPost(*pGlobal, db);
        }
        {
            RedirecionarIO io("B\n");
            menuVisualizarPost(*pGlobal, db);
        }
        {
            RedirecionarIO io("B\nabc\nF\n");
            menuVisualizarPost(*pGlobal, db);
        }
        {
            RedirecionarIO io("B\n99\nF\n");
            menuVisualizarPost(*pGlobal, db);
        }
        {
            RedirecionarIO io("C\n");
            menuVisualizarPost(*pGlobal, db);
        }
        {
            RedirecionarIO io("C\n\nF\n");
            menuVisualizarPost(*pGlobal, db);
        }
        {
            RedirecionarIO io("E\nZ\nF\n");
            menuVisualizarPost(*pGlobal, db);
        }
        {
            RedirecionarIO io("B\nE\n3\nF\n");
            menuVisualizarPost(*pComum, db);
        }
    }

    TEST_CASE("4. menuVerPostsLista") {
        Armazenamento db = setupDBMenus();
        db.criarPost("P1", 0);
        auto posts = db.getTodosPosts();
        {
            std::vector<Post> vazia;
            RedirecionarIO io("\n");
            menuVerPostsLista(vazia, db);
        }
        {
            RedirecionarIO io("A\n1\nF\nA\n\nA\nabc\nA\n99\nZ\n\nB\n");
            menuVerPostsLista(posts, db);
        }
    }

    TEST_CASE("5. menuVerPerfisLista") {
        Armazenamento db = setupDBMenus();
        auto perfis = db.getTodosPerfis();
        {
            std::vector<Perfil> vazia;
            RedirecionarIO io("\n");
            menuVerPerfisLista(vazia, db);
        }
        {
            RedirecionarIO io("A\n1\n3\nA\n\nA\nabc\nA\n99\nZ\n\nB\n");
            menuVerPerfisLista(perfis, db);
        }
    }

    TEST_CASE("6. menuVerComunidadesLista - Criacao e CATCH") {
        Armazenamento db = setupDBMenus();
        {
            RedirecionarIO io("A\nB\n");
            menuVerComunidadesLista(db);
        }
        {
            RedirecionarIO io("C\n\nDesc\nB\n");
            menuVerComunidadesLista(db);
        }
        {
            RedirecionarIO io("C\nNome\n\nB\n");
            menuVerComunidadesLista(db);
        }
        {
            RedirecionarIO io("C\n");
            menuVerComunidadesLista(db);
        }
        {
            RedirecionarIO io("C\nNome\n");
            menuVerComunidadesLista(db);
        }
        {
            RedirecionarIO io("C\nC1\nD1\nB\n");
            menuVerComunidadesLista(db);
        }
        {
            RedirecionarIO io("A\n1\n3\nA\n\nA\nabc\nA\n99\nZ\n\nB\n");
            menuVerComunidadesLista(db);
        }
        std::vector<Comunidade> filtro = {Comunidade(99, "F", "D", 1)};
        {
            RedirecionarIO io("B\n");
            menuVerComunidadesLista(db, &filtro);
        }
    }

    TEST_CASE("7. menuComunidade - Acessos, EOFs e CATCH") {
        Armazenamento db = setupDBMenus();
        db.criarComunidade("Com", "Desc");

        {
            RedirecionarIO io("1\nPost\n2\nB\nZ\n3\n");
            menuComunidade(1, db);
        }
        {
            RedirecionarIO io("1\n");
            menuComunidade(1, db);
        }
        {
            RedirecionarIO io("1\n\n3\n");
            menuComunidade(1, db);
        }
        {
            RedirecionarIO io("\n3\n");
            menuComunidade(1, db);
        }
        db.deslogar();
        db.fazerLogin("b@b.com", "senha123");
        {
            RedirecionarIO io("2\nB\nZ\n1\n3\n");
            menuComunidade(1, db);
        }
        db.deslogar();
        {
            RedirecionarIO io("1\n3\n");
            menuComunidade(1, db);
        }
    }

    TEST_CASE("8. menuPerfil - Visibilidade Completa") {
        Armazenamento db = setupDBMenus();
        db.criarComunidade("Com", "Desc");
        db.criarPost("Global", 0);
        db.criarPost("ComumPost", 1);
        db.getPerfil(1)->setCurso("CC");
        db.getPerfil(1)->setInstituicao("Uni");
        db.getPerfil(1)->setDescricao("Bio");

        {
            RedirecionarIO io("");
            menuPerfil(999, db);
        }
        {
            RedirecionarIO io("1\nB\n2\n5\n\nZ\n3\n");
            menuPerfil(1, db);
        }
        {
            RedirecionarIO io("");
            menuPerfil(1, db);
        }

        db.deslogar();
        db.fazerLogin("b@b.com", "senha123");
        {
            RedirecionarIO io("1\nB\n\nZ\n2\n");
            menuPerfil(1, db);
        }
        db.getComunidade(1)->adicionarMembro(2);
        db.getPerfil(2)->entrarComunidade(1);
        {
            RedirecionarIO io("1\nB\n2\n");
            menuPerfil(1, db);
        }
    }
}