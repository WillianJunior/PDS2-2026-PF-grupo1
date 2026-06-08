#include "domain/usuario.hpp"

#include <utility>

Usuario::Usuario(
    std::string emailInicial,
    std::string senhaInicial,
    std::string nomeInicial
)
    : senha(std::move(senhaInicial)),
      email(std::move(emailInicial)),
      nomeDeUsuario(std::move(nomeInicial))
{
}

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

bool Usuario::fazerLogin(
    std::string emailInformado,
    std::string senhaInformada
)
{
    return emailInformado == email && senhaInformada == senha;
}

std::string Usuario::getEmail()
{
    return email;
}

std::string Usuario::getNome()
{
    return nomeDeUsuario;
}