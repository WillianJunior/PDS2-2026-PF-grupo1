#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <string>

/**
 * @class Usuario
 * @brief Classe que gerencia as credenciais de acesso e segurança da conta.
 * * Responsável pelo controle de login, armazenamento do e-mail, senha 
 * e nome de usuário registrado no sistema. É uma entidade separada do 
 * Perfil para isolar dados sensíveis de dados públicos.
 */
class Usuario {
private:
    std::string email;
    std::string senha;
    std::string nomeDeUsuario;

public:
    /**
     * @brief Constrói as credenciais de um novo usuário.
     * @param email O endereço de e-mail usado para acesso.
     * @param senha A senha de autenticação.
     * @param nomeDeUsuario O nome curto ou apelido de registro no sistema.
     */
    Usuario(std::string email, std::string senha, std::string nomeDeUsuario);

    /**
     * @brief Permite a troca de senha do usuário mediante confirmação.
     * @param senhaAtual A senha usada atualmente (necessária para autorizar a troca).
     * @param novaSenha A nova senha escolhida pelo usuário.
     * @return true se a alteração for bem-sucedida, false se a senha atual estiver incorreta.
     */
    bool alterarSenha(std::string senhaAtual, std::string novaSenha);

    /**
     * @brief Permite a troca do e-mail do usuário mediante confirmação da senha.
     * @param senhaAtual A senha usada atualmente (necessária para autorizar a troca).
     * @param novoEmail O novo endereço de e-mail escolhido.
     * @return true se a alteração for bem-sucedida, false se a senha atual estiver incorreta.
     */
    bool alterarEmail(std::string senhaAtual, std::string novoEmail);

    /**
     * @brief Verifica as credenciais para permitir o acesso ao sistema.
     * @param emailInput O e-mail informado na tentativa de login.
     * @param senhaInput A senha informada na tentativa de login.
     * @return true se o e-mail e a senha baterem com os dados salvos, false caso contrário.
     */
    bool fazerLogin(std::string emailInput, std::string senhaInput) const;

    /**
     * @name Getters
     * @brief Métodos de acesso exclusivo para leitura dos atributos do usuário.
     * @{
     */
    std::string getEmail() const;
    std::string getNome() const;
    std::string getSenha() const;
    /** @} */
};

#endif