#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

/**
 * @brief Classe que gerencia as credenciais básicas e segurança da conta.
 *
 * Responsável pelo controle de login, armazenamento de e-mail, senha
 * e nome de usuário registrado no sistema.
 */
class Usuario
{

 private:
    std::string senha;
    std::string email;
    std::string nomeDeUsuario;

 public:
    Usuario(
        std::string emailInicial,
        std::string senhaInicial,
        std::string nomeInicial);

    bool alterarSenha(std::string senhaAtual, std::string novaSenha);

    bool alterarEmail(std::string senhaAtual, std::string novoEmail);

    bool fazerLogin(
        std::string emailInformado,
        std::string senhaInformada);

    std::string getEmail();

    std::string getNome();
};

#endif