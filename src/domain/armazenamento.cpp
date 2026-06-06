#include "domain/armazenamento.hpp"
#include <algorithm>
#include <cctype>

bool Armazenamento::emailUnico(std::string email)
{
    return false;
}

bool Armazenamento::senhaSegura(std::string senha)
{
    return false;
}

void Armazenamento::mensagemSucessoErro() {}

Perfil Armazenamento::getUsuarioLogado()
{
    return usuarioLogado;
}

void Armazenamento::criarPerfil(Perfil perfil)
{
    perfis.push_back(std::move(perfil));
}

Perfil Armazenamento::deletarPerfil(int id)
{
    return Perfil("", "", 0);
}

std::vector<Perfil> Armazenamento::listarPerfis()
{
    return perfis;
}

void Armazenamento::criarComunidade(Comunidade comunidade)
{
    comunidades.push_back(std::move(comunidade));
}

Comunidade Armazenamento::deletarComunidade(int id)
{
    return Comunidade("", 0);
}

std::vector<Comunidade> Armazenamento::listarComunidade()
{
    return comunidades;
}
