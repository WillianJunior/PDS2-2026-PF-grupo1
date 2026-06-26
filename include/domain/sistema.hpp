#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include "armazenamento.hpp"
#include <string>

/**
 * @file sistema.hpp
 * @brief Declaração do Gerenciador de Sessão e Regras de Negócio (Camada de Serviço).
 */

/**
 * @class Sistema
 * @brief Classe responsável por orquestrar a lógica do aplicativo.
 * Gerencia quem está logado, valida regras de negócio (como senhas seguras e emails únicos) 
 * e envia dados validados para o Armazenamento (Banco).
 */
class Sistema {
  private:
    Armazenamento& db;            ///< Referência ao Banco de Dados central.
    std::string emailLogado;      ///< Variável de estado da sessão ativa.
    int idPerfilLogado;           ///< ID da sessão ativa.

  public:
    /**
     * @brief Construtor do sistema que recebe a instância do banco de dados.
     * @param banco Referência para a classe de armazenamento.
     */
    Sistema(Armazenamento& banco);

    /**
     * @name Validações de Regras de Negócio
     * @{
     */
    bool senhaSegura(const std::string &senha) const;
    bool emailUnico(const std::string &email) const;
    bool nomeUsuarioUnico(const std::string &nome) const;
    /** @} */

    /**
     * @name Autenticação e Sessão
     * @{
     */
    bool fazerLogin(const std::string &email, const std::string &senha);
    void deslogar();
    int getIdPerfilLogado() const;
    std::string getEmailLogado() const;
    /** @} */

    /**
     * @name Operações e Criação de Entidades
     * @brief Regras de negócio para validação e inserção segura antes de salvar no banco.
     * @{
     */
    void criarUsuarioEPerfil(std::string email, std::string senha, std::string nome);
    void criarPost(std::string texto, int idComunidade = 0);
    void criarComunidade(std::string nome, std::string descricao);
    void criarComentarioGlobal(int idPost, int idAutor, std::string texto);
    /** @} */
};

#endif