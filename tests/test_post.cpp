#include <doctest/doctest.h>
#include "domain/post.hpp"
#include "domain/comentario.hpp"
#include "domain/perfil.hpp"

TEST_SUITE("Post")
{
    TEST_CASE("curtir mesmo usuario duas vezes remove curtida")
    {
        const int idAutor = 1;
        Post p("Texto", idAutor);
        p.curtir(10);
        CHECK(p.quantidadeDeCurtidas() == 1);
        p.curtir(10);
        CHECK(p.quantidadeDeCurtidas() == 0);
    }

    TEST_CASE("listarComentarios retorna lista de comentario")
    {
        Perfil autor("Computacao", "UFMG", 1);
        const int idAutor = 1;
        Post p("Texto", idAutor);
        Comentario c1("Bom post!", autor);
        Comentario c2("Gostei!", autor);
        p.adicionarComentario(c1);
        p.adicionarComentario(c2);
        std::vector<Comentario> comentarios = p.listarComentarios();
        CHECK(comentarios.size() == 2);
    }

    TEST_CASE("quantidadeDeCurtidas retorna numero correto de curtidas")
    {
        const int idAutor = 1;
        Post p("Texto", idAutor);
        p.curtir(10);
        p.curtir(20);
        CHECK(p.quantidadeDeCurtidas() == 2);
    }
    TEST_CASE("listarComentarios retorna lista de comentarios adicionados")
    {
        Perfil autor("Computacao", "UFMG", 1);
        const int idAutor = 1;
        Post p("Texto", idAutor);
        Comentario c1("Bom post!", autor);
        Comentario c2("Gostei!", autor);
        p.adicionarComentario(c1);
        p.adicionarComentario(c2);
        std::vector<Comentario> comentarios = p.listarComentarios();
        CHECK(comentarios.size() == 2);
    }
}
