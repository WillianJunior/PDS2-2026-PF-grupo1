#ifndef APLICACAO_HPP
#define APLICACAO_HPP
#include "domain/armazenamento.hpp"
#include "domain/busca.hpp"
#include <string>
class Aplicacao {
  private:
    Armazenamento db;
    Busca busca;
    bool rodando;
    bool modoAutomatico;
    std::string mensagemAlerta;
    void exibirTelaInicial();
    void exibirMenuPrincipal();
    void executarLogin();
    void executarCriarUsuario();
    void executarFluxoPesquisa();
    void executarFluxoAlterarCredenciais();
    void executarFluxoVerPerfil();

  public:
    Aplicacao(bool modoAutomatico);
    void executar();
    void parar();
};
#endif