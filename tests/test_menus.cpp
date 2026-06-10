#include <doctest/doctest.h>
#include "menus.hpp"
#include "domain/armazenamento.hpp"
#include <sstream>
#include <iostream>
#include <functional> 

static void simularInteracaoMenus(const std::string& inputsProgramados, std::function<void()> menuContexto) {
    std::stringstream inputReal(inputsProgramados);
    std::stringstream outputDescartavel;
    std::streambuf* backupCin = std::cin.rdbuf(inputReal.rdbuf());
    std::streambuf* backupCout = std::cout.rdbuf(outputDescartavel.rdbuf());
    
    menuContexto();
    
    std::cin.rdbuf(backupCin);
    std::cout.rdbuf(backupCout);
}

TEST_SUITE("Menus UI") {
    TEST_CASE("menuVerPostsLista - Iteracao Base") {
        Armazenamento db;
        db.criarUsuarioEPerfil("a@b", "123", "User");
        db.fazerLogin("a@b", "123");
        db.criarPost("Teste", 0);
        
        std::vector<Post*> lista = { &db.getTodosPostsMutavel()[0] };
        
        std::string fluxo = "A\n99\nA\n1\nF\nB\n";
        CHECK_NOTHROW(simularInteracaoMenus(fluxo, [&](){ menuVerPostsLista(lista, db); }));
        
        CHECK_NOTHROW(simularInteracaoMenus("\n", [&](){ std::vector<Post*> l2; menuVerPostsLista(l2, db); }));
    }

    TEST_CASE("menuComunidade - Como Admin e Membro") {
        Armazenamento db;
        db.criarUsuarioEPerfil("a@b", "123", "User");
        db.fazerLogin("a@b", "123");
        db.criarComunidade("Minha", "D");
        
        std::string fluxoAdmin = "1\nOi postado\n2\nB\n3\n4\n";
        CHECK_NOTHROW(simularInteracaoMenus(fluxoAdmin, [&](){ menuComunidade(1, db); }));
        
        db.criarUsuarioEPerfil("z@z", "123", "Outro");
        db.fazerLogin("z@z", "123");
        std::string fluxoTerceiro = "1\n2\nB\n3\n";
        CHECK_NOTHROW(simularInteracaoMenus(fluxoTerceiro, [&](){ menuComunidade(1, db); }));
    }

    TEST_CASE("menuPerfil - Visualizar a Si e Outro") {
        Armazenamento db;
        db.criarUsuarioEPerfil("x@x", "123", "X");
        db.fazerLogin("x@x", "123");
        db.criarUsuarioEPerfil("y@y", "123", "Y");
        
        
        std::string fluxoMeu = "2\n1\nNovoC\n2\n4\n5\n5\n";
        CHECK_NOTHROW(simularInteracaoMenus(fluxoMeu, [&](){ menuPerfil(1, db); }));

        std::string fluxoOutro = "2\n2\nS\n3\n";
        CHECK_NOTHROW(simularInteracaoMenus(fluxoOutro, [&](){ menuPerfil(2, db); }));
    }
}