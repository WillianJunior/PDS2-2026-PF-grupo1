#include "domain/usuario.hpp"

Usuario::Usuario(std::string email, std::string senha, std::string nomeDeUsuario)
    : senha(std::move(senha)), email(std::move(email)), nomeDeUsuario(std::move(nomeDeUsuario)) {}

bool Usuario::alterarSenha(std::string senhaAtual, std::string novaSenha)
{
    if (senhaAtual != senha) {
        return false;
    }
    senha = std::move(novaSenha);
    return true;
}

bool Usuario::alterarEmail(std::string senhaAtual, std::string novoEmail)
{
    if (senhaAtual != senha) {
        return false;
    }
    email = std::move(novoEmail);
    return true;
}

bool Usuario::fazerLogin(std::string email, std::string senha)
{
    return email == this->email && senha == this->senha;
}

std::string Usuario::getEmail()
{
    return email;
}

std::string Usuario::getNome()
{
    return nomeDeUsuario;
}
