#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

/**
 * @file usuario.hpp
 * @brief Declaração da classe Usuario contendo dados de autenticação.
 */

/**
 * @class Usuario
 * @brief Entidade responsável por armazenar e gerenciar credenciais de acesso.
 * * Cuida das regras de negócio atreladas à segurança da conta, como validação
 * de login e alteração de senha/email mediante confirmação da senha atual.
 */
class Usuario {
  private:
    int id;                    /**< Identificador único do usuário no sistema. */
    std::string email;         /**< Email utilizado para o login. */
    std::string senha;         /**< Senha de acesso. */
    std::string nomeDeUsuario; /**< Nome cadastrado no momento da criação da conta. */

  public:
    /**
     * @brief Construtor principal da classe Usuario.
     * * @param id ID numérico único.
     * @param emailInicial Email de cadastro.
     * @param senhaInicial Senha de acesso.
     * @param nomeInicial Nome de exibição.
     */
    Usuario(int id, std::string emailInicial, std::string senhaInicial, std::string nomeInicial);

    /**
     * @brief Altera a senha do usuário após validação de segurança.
     * * @param senhaAtual A senha atual para provar a identidade.
     * @param novaSenha A nova senha a ser salva.
     * @return true se a senhaAtual for correta e a troca ocorrer, false caso contrário.
     */
    bool alterarSenha(std::string senhaAtual, std::string novaSenha);

    /**
     * @brief Altera o email do usuário após validação de segurança.
     * * @param senhaAtual A senha atual para provar a identidade.
     * @param novoEmail O novo email a ser vinculado.
     * @return true se a senhaAtual for correta e a troca ocorrer, false caso contrário.
     */
    bool alterarEmail(std::string senhaAtual, std::string novoEmail);

    /**
     * @brief Valida as credenciais para autorizar o acesso ao sistema.
     * * @param emailInformado O email digitado no login.
     * @param senhaInformada A senha digitada no login.
     * @return true se os dados coincidirem com a conta, false caso contrário.
     */
    bool fazerLogin(std::string emailInformado, std::string senhaInformada) const;

    /** @name Getters */
    /** @{ */

    /** @brief Retorna o email do usuário. */
    std::string getEmail() const;

    /** @brief Retorna o ID do usuário. */
    int getId() const;

    /** @brief Retorna o nome do usuário. */
    std::string getNome() const;

    /** @brief Retorna a senha cadastrada. */
    std::string getSenha() const;

    /** @} */
};

#endif