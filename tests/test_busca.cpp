#include "domain/busca.hpp"
#include "domain/armazenamento.hpp"
#include "domain/sistema.hpp"
#include <doctest/doctest.h>

TEST_SUITE("Busca - Rumo aos 100%") {
    
    TEST_CASE("1. Buscar Perfis (Cobertura da Linha 26 - Sort)") {
        Armazenamento db;
        Sistema sys(db);
        sys.criarUsuarioEPerfil("ana@ufmg.br", "Senha123", "Ana Silva");
        sys.criarUsuarioEPerfil("bruno@ufmg.br", "Senha123", "Bruno Silva");
        
        Busca busca;
        auto achados = busca.buscarPerfis("Silva", db);
        CHECK(achados.size() == 2);
        CHECK(achados[0].getNome() == "Ana Silva");
    }

    TEST_CASE("2. Buscar Posts") {
        Armazenamento db; Sistema sys(db);
        sys.criarUsuarioEPerfil("teste@teste.com", "senha123", "Alvo");
        sys.fazerLogin("teste@teste.com", "senha123");
        sys.criarPost("Aprendendo C++", 0);
        sys.criarPost("Java avancado", 0);
        
        Busca busca;
        auto achados = busca.buscarPosts("C++", db);
        CHECK(achados.size() == 1);
    }

    TEST_CASE("3. Buscar Comunidades") {
        Armazenamento db; Sistema sys(db);
        sys.criarUsuarioEPerfil("teste@teste.com", "senha123", "Alvo");
        sys.fazerLogin("teste@teste.com", "senha123");
        sys.criarComunidade("C++ Fans", "Grupo de cpp");
        sys.criarComunidade("Java", "Grupo java");
        
        Busca busca;
        auto achados = busca.buscarComunidades("C++", db);
        CHECK(achados.size() == 1);
    }

    TEST_CASE("4. Buscar Posts por Comunidade e Autor") {
        Armazenamento db; Sistema sys(db);
        sys.criarUsuarioEPerfil("teste@teste.com", "senha123", "Alvo");
        sys.fazerLogin("teste@teste.com", "senha123");
        sys.criarComunidade("Teste", "Descricao"); 
        sys.criarPost("Post 1", 1);
        sys.criarPost("Post 2", 1);
        sys.criarPost("Post geral", 0);
        
        Busca busca;
        auto achados = busca.buscaPosts(1, db);
        CHECK(achados.size() == 2); 
        
        auto porAutor = busca.buscaPostsPorAutor(1, db);
        CHECK(porAutor.size() == 3);
    }

    TEST_CASE("5. Buscar Feed do Usuario (Autor e Comunidades)") {
        Armazenamento db; Sistema sys(db);
        sys.criarUsuarioEPerfil("autor@teste.com", "senha123", "Autor");
        sys.criarUsuarioEPerfil("leitor@teste.com", "senha123", "Leitor");
        sys.fazerLogin("autor@teste.com", "senha123");
        sys.criarComunidade("Secreta", "Descricao"); 
        sys.criarPost("Post Publico do Autor", 0);
        sys.criarPost("Post Privado da Comunidade", 1);
        
        Busca busca;
        Perfil* leitor = db.getPerfil(2);
        auto feedLeitor = busca.buscaPosts(*leitor, db);
        CHECK(feedLeitor.size() == 1);
    }

    TEST_CASE("6. Comentarios de um Post") {
        Armazenamento db; Sistema sys(db);
        sys.criarUsuarioEPerfil("u@u.com", "senha123", "User");
        sys.fazerLogin("u@u.com", "senha123");
        sys.criarPost("Post Original", 0); 
        sys.criarComentarioGlobal(1, 1, "Primeiro Comentario");
        sys.criarComentarioGlobal(1, 1, "Segundo Comentario");
        
        Busca busca;
        Post* p = db.getPostMutavel(1);
        auto comentarios = busca.comentariosDoPost(*p, db);
        CHECK(comentarios.size() == 2);
    }

    TEST_CASE("7. Detalhes da Comunidade e Membros (Linhas 126, 134)") {
        Armazenamento db; Sistema sys(db);
        sys.criarUsuarioEPerfil("m@m.com", "senha123", "Membro"); 
        sys.fazerLogin("m@m.com", "senha123");
        sys.criarComunidade("Comunidade XP", "Desc"); 
        
        Busca busca;
        CHECK(busca.usuarioE_MembroDaComunidade(1, 1, db) == true);
        CHECK(busca.numeroDeMembrosDaComunidade(1, db) == 1);
        
        CHECK(busca.usuarioE_MembroDaComunidade(1, 999, db) == false);
        CHECK(busca.numeroDeMembrosDaComunidade(999, db) == 0);
        
        sys.criarPost("Antigo", 1);
        sys.criarPost("Meio", 1);
        sys.criarPost("Novo", 1);
        auto recentes = busca.buscarPostsRecentesDaComunidade(1, 2, db);
        CHECK(recentes.size() == 2);
    }

    TEST_CASE("8. Nome do Perfil") {
        Armazenamento db; Sistema sys(db);
        sys.criarUsuarioEPerfil("n@n.com", "senha123", "NomeValido");
        
        Busca busca;
        CHECK(busca.nomePerfil(db, 1) == "NomeValido");
        CHECK(busca.nomePerfil(db, 99) == "Desconhecido");
    }
}