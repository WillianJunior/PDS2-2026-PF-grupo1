#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <string>

class Usuario {

private:

    std::string senha;
    std::string email;
    std::string nomeDeUsuario;

public:

    Usuario(std::string email, std::string senha, std::string nomeDeUsuario);

    bool alterarSenha(std::string senhaAtual, std::string novaSenha);
    bool alterarEmail(std::string senhaAtual, std::string novoEmail);;
    bool fazerLogin(std::string email, std::string senha);

    std::string getEmail();
    std::string getNome();

};

#endif


