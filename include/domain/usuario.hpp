#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

class Usuario
{
 private:
    std::string email;
    std::string senha;
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
        std::string senhaInformada) const;

    std::string getEmail() const;
    std::string getNome() const;
    std::string getSenha() const;
};

#endif
