#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <string>

/**
 * @brief Classe que gerencia as credenciais básicas e segurança da conta.
 * * Responsável pelo controle de login, armazenamento de e-mail, senha 
 * e nome de usuário registrado no sistema.
 */

class Usuario {

private:

    std::string senha;
    std::string email;
    std::string nomeDeUsuario;

public:

    /**
     * @brief Constrói as credenciais de um novo usuário.
     * @param email O endereço de e-mail de acesso.
     * @param senha A senha de autenticação.
     * @param nomeDeUsuario O nome curto usado para login e exibição.
     */

    Usuario(std::string email, std::string senha, std::string nomeDeUsuario);

    /**
     * @brief Permite a troca de senha do usuário mediante confirmação.
     * @param senhaAtual A senha usada atualmente (para validação).
     * @param novaSenha A nova senha escolhida.
     * @return true se a alteração for bem-sucedida, false caso a senha atual esteja incorreta.
     */

    bool alterarSenha(std::string senhaAtual, std::string novaSenha);

    /**
     * @brief Permite a troca do e-mail do usuário mediante confirmação da senha.
     * @param senhaAtual A senha usada atualmente (para validação).
     * @param novoEmail O novo e-mail escolhido.
     * @return true se a alteração for bem-sucedida, false caso contrário.
     */

    bool alterarEmail(std::string senhaAtual, std::string novoEmail);

    /**
     * @brief Verifica as credenciais para permitir o acesso ao sistema.
     * @param email O e-mail informado no login.
     * @param senha A senha informada no login.
     * @return true se as credenciais estiverem corretas, false caso contrário.
     */

    bool fazerLogin(std::string email, std::string senha);

    /**
     * @brief Retorna o e-mail cadastrado pelo usuário.
     * @return Uma string contendo o e-mail.
     */

    std::string getEmail();

    /**
     * @brief Retorna o nome de usuário cadastrado.
     * @return Uma string contendo o nome de usuário.
     */

    std::string getNome();

};

#endif