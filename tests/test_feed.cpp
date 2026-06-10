#include <doctest/doctest.h>
#include "domain/feed.hpp"
#include "domain/armazenamento.hpp"
#include <sstream>
#include <iostream>
#include <functional> 

static void simularInteracaoFeed(const std::string& inputsProgramados, std::function<void()> menuContexto) {
    std::stringstream inputReal(inputsProgramados);
    std::stringstream outputDescartavel;
    std::streambuf* backupCin = std::cin.rdbuf(inputReal.rdbuf());
    std::streambuf* backupCout = std::cout.rdbuf(outputDescartavel.rdbuf());
    
    menuContexto();
    
    std::cin.rdbuf(backupCin);
    std::cout.rdbuf(backupCout);
}

TEST_SUITE("Feed Interativo") {
    TEST_CASE("Exibir Listagens Diretas") {
        Feed f;
        CHECK_NOTHROW(f.exibirPosts({}));
        CHECK_NOTHROW(f.exibirPerfis({}));
        CHECK_NOTHROW(f.exibirComunidades({}));
    }

    TEST_CASE("Navegacao Completa e Inputs Invalidos Feed") {
        Armazenamento db;
        db.criarUsuarioEPerfil("a@b.c", "123456", "UserA");
        db.fazerLogin("a@b.c", "123456");
        db.criarPost("Geral Post", 0);
        db.criarComunidade("Comum", "Desc");
        db.criarPost("Comum Post", 1);
        db.criarComentarioGlobal(1, 1, "Coment A");
        
        Feed f;
        std::string acoes = 
            "Z\n"               
            "A\n99\n"           
            "A\n2\n"            
            "A\n"               
            "B\n1\n"          
            "C\nNovo Teste\n"   
            "D\n\n"             
            "E\n"              
            "F\n"              
            "A\n1\n"           
            "E\n\n"           
            "B\n99\n"          
            "X\n"             
            "F\n"              
            "B\n";              
            
        CHECK_NOTHROW(simularInteracaoFeed(acoes, [&](){ f.verFeed(db); }));
    }
}