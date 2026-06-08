#include "usuario.hpp"

Usuario::Usuario(std::string email, std::string senha, std::string nomeDeUsuario)
    : email(std::move(email)), senha(std::move(senha)), nomeDeUsuario(std::move(nomeDeUsuario)) {} 
  
bool Usuario::alterarSenha(std::string senhaAtual, std::string novaSenha) {
    if (senhaAtual != senha) return false;
    senha = std::move(novaSenha);
    return true;
}

bool Usuario::alterarEmail(std::string senhaAtual, std::string novoEmail) {
    if (senhaAtual != senha) return false;
    email = std::move(novoEmail);
    return true;
}

bool Usuario::fazerLogin(std::string emailInput, std::string senhaInput) const {
    return this->email == emailInput && this->senha == senhaInput;
}

std::string Usuario::getEmail() const { return email; }
std::string Usuario::getNome() const { return nomeDeUsuario; }
std::string Usuario::getSenha() const { return senha; }
