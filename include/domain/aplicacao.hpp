#ifndef APLICACAO_HPP
#define APLICACAO_HPP

#include "armazenamento.hpp"
#include "sistema.hpp"
#include "busca.hpp"
#include <string>

/**
 * @file aplicacao.hpp
 * @brief Declaração da classe principal de controle do sistema.
 */

/**
 * @class Aplicacao
 * @brief Classe orquestradora que gerencia o loop principal e as transições de tela.
 * * Controla o estado de execução (rodando ou parado), gerencia a inicialização do banco
 * de dados (Armazenamento) e do motor de regras de negócio (Sistema).
 */
class Aplicacao {
  private:
    Armazenamento db;           /**< Referência para o banco de dados em memória. */
    Sistema sys;                /**< Motor de regras de negócio e controle de sessão. */
    Busca busca;                /**< Instância do serviço de busca. */
    bool rodando;               /**< Flag que mantém o loop principal ativo. */
    bool modoAutomatico;        /**< Flag para rodar em modo de teste sem pausas. */
    std::string mensagemAlerta; /**< Buffer para exibir mensagens no topo das telas. */

    /** @name Fluxos de Tela */
    /** @{ */
    void exibirTelaInicial();
    void exibirMenuPrincipal();
    void executarLogin();
    void executarCriarUsuario();
    void executarFluxoPesquisa();
    void executarFluxoAlterarCredenciais();
    void executarFluxoVerPerfil();
    /** @} */

  public:
    /**
     * @brief Inicializa a aplicação, configurando o ambiente.
     * @param modoAutomatico Se true, aborta em caso de erros de entrada (testes).
     */
    Aplicacao(bool modoAutomatico = false);

    /**
     * @brief Inicia o loop principal de execução e renderização da aplicação.
     */
    void executar();

    /**
     * @brief Sinaliza a aplicação para quebrar o loop principal e encerrar.
     */
    void parar();
};
#endif