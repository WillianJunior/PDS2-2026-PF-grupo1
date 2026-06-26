#include "domain/armazenamento.hpp"
#include "domain/sistema.hpp"
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
        std::cin.clear(); 
        oldCin = std::cin.rdbuf(input.rdbuf());
        oldCout = std::cout.rdbuf(output.rdbuf());
    }
    ~RedirecionarIO() {
        std::cin.clear(); 
        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);
    }
};

void setupDBMenus(Armazenamento &db, Sistema &sys) {
    sys.criarUsuarioEPerfil("a@a.com", "Senha123", "UserA");
    sys.criarUsuarioEPerfil("b@b.com", "Senha123", "UserB");
    sys.fazerLogin("a@a.com", "Senha123");
}

TEST_SUITE("Menus - O Chefão Final (100%)") {

    TEST_CASE("1. menuEditarPerfil") {
        Armazenamento db; Sistema sys(db); setupDBMenus(db, sys);
        Perfil *p = db.getPerfil(1);
        std::string inputs = 
            "abc\n"     
            "99\n"      
            "1\nNova Bio\n"
            "2\nNovo Curso\n"
            "3\nNova Inst\n"
            "4\n-1\n"   
            "4\n5\n"    
            "5\n";      
        RedirecionarIO io(inputs);
        Menus::menuEditarPerfil(*p);
        RedirecionarIO io2("B\n");
        Menus::menuEditarPerfil(*p);

        RedirecionarIO io3("1\n"); 
        Menus::menuEditarPerfil(*p);
    }

    TEST_CASE("2. menuVisualizarPost") {
        Armazenamento db; Sistema sys(db); setupDBMenus(db, sys);
        sys.criarPost("Global", 0);
        sys.criarComentarioGlobal(1, 1, "Coment1");
        sys.criarComunidade("C", "D"); 
        sys.criarPost("Comum", 1);    

        Post *pGlobal = db.getPostMutavel(1);
        Post *pComum = db.getPostMutavel(2);

        std::string in1 = 
            "Z\n"      
            "A\n"       
            "B\n99\n"   
            "B\n1\n"    
            "B\nabc\n"  
            "C\nNovo\n" 
            "C\n\n"     
            "D\n3\n"    
            "E\n"       
            "F\n";      
        { RedirecionarIO io(in1); Menus::menuVisualizarPost(*pGlobal, db, sys); }

        std::string in2 = 
            "E\n3\n"    
            "F\n";      
        { RedirecionarIO io(in2); Menus::menuVisualizarPost(*pComum, db, sys); }
        { RedirecionarIO io("B\n"); Menus::menuVisualizarPost(*pGlobal, db, sys); }
        { RedirecionarIO io("C\n"); Menus::menuVisualizarPost(*pGlobal, db, sys); }
        sys.criarPost("Sem coment", 0);
        Post *pSem = db.getPostMutavel(3);
        { RedirecionarIO io("B\nF\n"); Menus::menuVisualizarPost(*pSem, db, sys); }
    }

    TEST_CASE("3. menuVerPostsLista") {
        Armazenamento db; Sistema sys(db); setupDBMenus(db, sys);
        sys.criarPost("P1", 0);
        auto posts = db.getTodosPosts();
        
        { 
            std::vector<Post> vazia; 
            RedirecionarIO io("\n"); 
            Menus::menuVerPostsLista(vazia, db, sys); 
        }
        { 
            std::string in = 
                "Z\n"      
                "A\nabc\n"  
                "A\n99\n"   
                "A\n1\nF\n" 
                "B\n";      
            RedirecionarIO io(in); 
            Menus::menuVerPostsLista(posts, db, sys); 
        }
        { RedirecionarIO io("A\n"); Menus::menuVerPostsLista(posts, db, sys); }
    }

    TEST_CASE("4. menuComunidade") {
        Armazenamento db; Sistema sys(db); setupDBMenus(db, sys);
        sys.criarComunidade("Com", "Desc"); 
        {
            std::string in = 
                "abc\n"         
                "99\n"         
                "1\nMeu post\n" 
                "1\n\n"        
                "2\nB\n"        
                "3\n";          
            RedirecionarIO io(in); 
            Menus::menuComunidade(1, db, sys);
        }
        sys.deslogar();
        sys.fazerLogin("b@b.com", "Senha123");
        {
            std::string in = 
                "99\n"      
                "2\nB\n"    
                "1\n"       
                "3\n";     
            RedirecionarIO io(in); 
            Menus::menuComunidade(1, db, sys);
        }
        sys.deslogar();
        sys.fazerLogin("a@a.com", "Senha123");
        { RedirecionarIO io("1\n"); Menus::menuComunidade(1, db, sys); }
        { RedirecionarIO io(""); Menus::menuComunidade(99, db, sys); }
    }

    TEST_CASE("5. menuVerPerfisLista") {
        Armazenamento db; Sistema sys(db); setupDBMenus(db, sys);
        auto perfis = db.getTodosPerfis();
        
        { 
            std::vector<Perfil> vazia; 
            RedirecionarIO io("\n"); 
            Menus::menuVerPerfisLista(vazia, db, sys); 
        }
        {
            std::string in = 
                "Z\n"       
                "A\nabc\n" 
                "A\n99\n"   
                "A\n1\n3\n" 
                "B\n";    
            RedirecionarIO io(in); 
            Menus::menuVerPerfisLista(perfis, db, sys); 
        }
        { RedirecionarIO io("A\n"); Menus::menuVerPerfisLista(perfis, db, sys); }
    }

    TEST_CASE("6. menuVerComunidadesLista") {
        Armazenamento db; Sistema sys(db); setupDBMenus(db, sys);
        
        { 
            RedirecionarIO io("Z\nB\n"); 
            Menus::menuVerComunidadesLista(db, sys); 
        }
        {
            std::string in = 
                "C\nNova\nDesc\n" 
                "C\n\nDesc\n"    
                "A\nabc\n"       
                "A\n99\n"         
                "A\n1\n3\n"       
                "B\n";            
            RedirecionarIO io(in); 
            Menus::menuVerComunidadesLista(db, sys); 
        }
        { RedirecionarIO io("C\nNova\n"); Menus::menuVerComunidadesLista(db, sys); }
        { RedirecionarIO io("A\n"); Menus::menuVerComunidadesLista(db, sys); }
    }

    TEST_CASE("7. menuPerfil") {
        Armazenamento db; Sistema sys(db); setupDBMenus(db, sys);
        { RedirecionarIO io(""); Menus::menuPerfil(99, db, sys); }

        {
            std::string in = 
                "B\n"       
                "abc\n"     
                "99\n"     
                "1\nB\n"    
                "2\n5\n"   
                "3\n";     
            RedirecionarIO io(in);
            Menus::menuPerfil(1, db, sys);
        }

        {
            std::string in = 
                "99\n"     
                "1\nB\n"    
                "2\n";      
            RedirecionarIO io(in);
            Menus::menuPerfil(2, db, sys);
        }
        
        { RedirecionarIO io(""); Menus::menuPerfil(1, db, sys); }
    }
}