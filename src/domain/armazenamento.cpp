#include "domain/armazenamento.hpp"
#include <algorithm>
#include <cctype>

bool Armazenamento::emailUnico(std::string email) {
    (void)email; // evita warning de parâmetro não usado
    return true; // ajuste conforme a lógica real depois
}

bool Armazenamento::senhaSegura(std::string senha) {
    if (senha.size() < 8) {
        return false;
    }

    for (char caractere : senha) {
        if (std::isdigit(static_cast<unsigned char>(caractere))) {
            return true;
        }
    }

    return false;
}

void Armazenamento::mensagemSucessoErro() {}

Perfil Armazenamento::getUsuarioLogado() {
    return usuarioLogado;
}

void Armazenamento::criarPerfil(Perfil perfil) {
    perfis.push_back(std::move(perfil));
}

Perfil Armazenamento::deletarPerfil(int id) {
    (void)id; // evita warning
    return Perfil("", "", 0);
}

std::vector<Perfil> Armazenamento::listarPerfis() {
    return perfis;
}

void Armazenamento::criarComunidade(Comunidade comunidade) {
    comunidades.push_back(std::move(comunidade));
}

Comunidade Armazenamento::deletarComunidade(int id) {
    (void)id; // evita warning
    return Comunidade("", 0);
}

std::vector<Comunidade> Armazenamento::listarComunidade() {
    return comunidades;
}