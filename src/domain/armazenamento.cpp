#include "domain/armazenamento.hpp"
#include <algorithm>
#include <cctype>

bool Armazenamento::emailUnico(std::string email) {
    (void)email; // evita warning de parâmetro não usado
    return true; // ajuste conforme a lógica real depois
}

bool Armazenamento::senhaSegura(std::string senha) {
    bool temMaiuscula = false;
    bool temMinuscula = false;
    bool temNumero = false;

    for (char c : senha) {
        if (std::isupper(static_cast<unsigned char>(c)))
            temMaiuscula = true;
        else if (std::islower(static_cast<unsigned char>(c)))
            temMinuscula = true;
        else if (std::isdigit(static_cast<unsigned char>(c)))
            temNumero = true;
    }

    return senha.length() >= 8 &&
           temMaiuscula &&
           temMinuscula &&
           temNumero;
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
