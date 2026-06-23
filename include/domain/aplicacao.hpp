#ifndef APLICACAO_HPP
#define APLICACAO_HPP
#include "domain/armazenamento.hpp"
#include "domain/busca.hpp"
#include <string>

/**
 * @file aplicacao.hpp
 * @brief Declaração da classe principal de controle do sistema.
 */

/**
 * @class Aplicacao
 * @brief Classe orquestradora que gerencia o loop principal e as transições de tela.
 * * Controla o estado de execução (rodando ou parado), gerencia a injeção do banco 
 * de dados na memória e direciona os fluxos de menu de acordo com o estado de login do usuário.
 */
class Aplicacao {
  private:
    Armazenamento db;              /**< Referência para o banco de dados em memória. */
    Busca busca;                   /**< Instância do serviço de busca. */
    bool rodando;                  /**< Flag que mantém o loop principal ativo. */
    bool modoAutomatico;           /**< Flag para rodar em modo de teste/demonstração sem pausas. */
    std::string mensagemAlerta;    /**< Buffer para exibir mensagens de sucesso ou erro no topo das telas. */

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
     * @param modoAutomatico Se true, a aplicação aborta em caso de erros de entrada (usado para testes de integração).
     */
    Aplicacao(bool modoAutomatico);

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