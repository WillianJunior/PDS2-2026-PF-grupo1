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
        CHECK(posts[0]->getConteudo() == "Post 1");
        CHECK(posts[1]->getConteudo() == "Post 2");
    }
    TEST_CASE("buscaPostsPorAutor com regras de privacidade") {
        Armazenamento db;
        Busca b;

        db.criarUsuarioEPerfil("autor@teste.com", "senha123", "Autor");
        db.criarUsuarioEPerfil("leitor@teste.com", "senha123", "Leitor");

        db.fazerLogin("autor@teste.com", "senha123");
        db.criarComunidade("Secreta", "Descricao");
        db.criarPost("Post Publico do Autor", 0);
        db.criarPost("Post Privado da Comunidade", 1);

        auto postsParaSiMesmo = b.buscaPostsPorAutor(1, db);
        CHECK(postsParaSiMesmo.size() == 2);

        auto postsParaEstranho = b.buscaPostsPorAutor(1, db);
        CHECK(postsParaEstranho.size() == 2);
        CHECK(postsParaEstranho[0]->getConteudo() == "Post Publico do Autor");

        db.getComunidade(1)->adicionarMembro(2);
        auto PerfilLeitor = db.getPerfil(2);
        if (PerfilLeitor)
            PerfilLeitor->entrarComunidade(1);

        auto postsParaMembro = b.buscaPostsPorAutor(1, db);
        CHECK(postsParaMembro.size() == 2);
    }

    TEST_CASE("comentariosDoPost") {
        Armazenamento db;
        Busca b;

        db.criarUsuarioEPerfil("u@u.com", "senha123", "User");
        db.fazerLogin("u@u.com", "senha123");
        db.criarPost("Post Original", 0);

        db.criarComentarioGlobal(1, 1, "Primeiro Comentario");
        db.criarComentarioGlobal(1, 1, "Segundo Comentario");

        auto postReal = db.getPostMutavel(1);
        REQUIRE(postReal != nullptr);

        auto comentarios = b.comentariosDoPost(*postReal, db);
        CHECK(comentarios.size() == 2);
        CHECK(comentarios[0]->getTexto() == "Primeiro Comentario");
        CHECK(comentarios[1]->getTexto() == "Segundo Comentario");
    }

    TEST_CASE("Membros da Comunidade e Limite de Recentes") {
        Armazenamento db;
        Busca b;

        db.criarUsuarioEPerfil("m@m.com", "senha123", "Membro");
        db.fazerLogin("m@m.com", "senha123");
        db.criarComunidade("Comunidade XP", "Desc");

        CHECK_FALSE(b.usuarioE_MembroDaComunidade(1, 999, db));
        CHECK(b.numeroDeMembrosDaComunidade(999, db) == 0);

        db.getComunidade(1)->adicionarMembro(1);
        CHECK(b.usuarioE_MembroDaComunidade(1, 1, db));
        CHECK(b.numeroDeMembrosDaComunidade(1, db) == 1);

        db.criarPost("Antigo", 1);
        db.criarPost("Meio", 1);
        db.criarPost("Novo", 1);

        auto recentes = b.buscarPostsRecentesDaComunidade(1, 2, db);
        REQUIRE(recentes.size() == 2);
        CHECK(recentes[0]->getConteudo() == "Novo");
        CHECK(recentes[1]->getConteudo() == "Meio");
    }

    TEST_CASE("Fallback de nomePerfil") {
        Armazenamento db;
        Busca b;

        db.criarUsuarioEPerfil("n@n.com", "senha123", "NomeValido");
        CHECK(b.nomePerfil(db, 1) == "NomeValido");
        CHECK(b.nomePerfil(db, 999) == "Desconhecido"); 
    }
}