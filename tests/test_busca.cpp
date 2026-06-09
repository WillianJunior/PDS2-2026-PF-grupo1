#include <doctest/doctest.h>
#include "busca.hpp"
#include "armazenamento.hpp"

TEST_SUITE("Busca") {
    TEST_CASE("buscarPalavraChave e exibirResultadosPesquisa nao lancam excecoes") {
        Armazenamento db;
        Busca b;
        
        db.criarUsuarioEPerfil("ana@uni.br", "Senha123", "Ana");
        db.fazerLogin("ana@uni.br", "Senha123");
        db.criarPost("Aprendendo testes unitarios em C++");
    
        CHECK_NOTHROW(b.buscarPalavraChave("C++", db));
        CHECK_NOTHROW(b.exibirResultadosPesquisa());
    }
}