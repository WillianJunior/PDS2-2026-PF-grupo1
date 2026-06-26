#include "domain/sistema.hpp"
#include "domain/armazenamento.hpp"
#include <doctest/doctest.h>
#include <stdexcept>
#include <cstdio>

TEST_SUITE("Sistema (Service e Business Logic)") {

    TEST_CASE("Autenticação e Sessão (Casos Positivos e Negativos)") {
        Armazenamento db;
        Sistema sys(db);
        
        CHECK(sys.senhaSegura("fraca") == false);
        CHECK(sys.senhaSegura("SenhaSemNumero") == false);
        CHECK(sys.senhaSegura("Segura123") == true);

        sys.criarUsuarioEPerfil("teste@ufmg.br", "Senha123", "Tester");
        
        CHECK(sys.emailUnico("teste@ufmg.br") == false);
        CHECK(sys.nomeUsuarioUnico("Tester") == false);
        CHECK(sys.emailUnico("novo@ufmg.br") == true);

        CHECK(sys.fazerLogin("teste@ufmg.br", "errada") == false);
        CHECK(sys.fazerLogin("errado@ufmg.br", "senha123") == false);
        CHECK(sys.fazerLogin("teste@ufmg.br", "Senha123") == true);
        
        CHECK(sys.getEmailLogado() == "teste@ufmg.br");
        CHECK(sys.getIdPerfilLogado() == 1);

        sys.deslogar();
        CHECK(sys.getEmailLogado() == "");
        CHECK(sys.getIdPerfilLogado() == 0);
    }

    TEST_CASE("Simular corrupção: Fazer login com usuário sem perfil (Linha 41)") {
        Armazenamento db;
        Sistema sys(db);
        db.adicionarUsuario(Usuario(99, "fantasma@uni.br", "Senha123", "Fantasma"));
        CHECK(sys.fazerLogin("fantasma@uni.br", "Senha123") == false);
    }

    TEST_CASE("Exceção runtime_error ao criar comunidade sem perfil válido (Linha 87)") {
        Armazenamento db;
        Sistema sys(db);
        
        sys.criarUsuarioEPerfil("bug@teste.com", "Senha123", "Bug");
        sys.fazerLogin("bug@teste.com", "Senha123");
        std::remove("data/usuarios.csv");
        std::remove("data/perfis.csv");
        std::remove("data/comunidades.csv");
        db.carregarDados();
        CHECK_THROWS_AS(sys.criarComunidade("Comunidade Bug", "Vai dar erro"), std::runtime_error);
    }

    TEST_CASE("Exceções em Criação de Entidades (Cobertura de throws)") {
        Armazenamento db;
        Sistema sys(db);
        
        CHECK_THROWS_AS(sys.criarUsuarioEPerfil("teste@ufmg.br", "Senha123", ""), std::invalid_argument);
        CHECK_THROWS_AS(sys.criarUsuarioEPerfil("teste@ufmg.br", "123", "User"), std::invalid_argument);
        CHECK_THROWS_AS(sys.criarUsuarioEPerfil("testeufmg.br", "Senha123", "User"), std::invalid_argument);

        sys.criarUsuarioEPerfil("teste@ufmg.br", "Senha123", "User");
        CHECK_THROWS_AS(sys.criarUsuarioEPerfil("teste@ufmg.br", "NovaSenha12", "NovoUser"), std::invalid_argument);
        CHECK_THROWS_AS(sys.criarUsuarioEPerfil("novo@ufmg.br", "NovaSenha12", "User"), std::invalid_argument);

        sys.fazerLogin("teste@ufmg.br", "Senha123");
        CHECK_THROWS_AS(sys.criarPost(""), std::invalid_argument);
        CHECK_THROWS_AS(sys.criarComunidade("", "desc"), std::invalid_argument);
        CHECK_THROWS_AS(sys.criarComentarioGlobal(1, 1, ""), std::invalid_argument);
    }

    TEST_CASE("Restrições de ações sem login") {
        Armazenamento db;
        Sistema sys(db);
        
        sys.criarPost("Tentativa", 1);
        sys.criarComunidade("Tentativa", "Desc");
        
        CHECK(db.getTodosPosts().empty());
        CHECK(db.getTodasComunidades().empty());
    }
}