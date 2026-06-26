#include "domain/admin.hpp"

Administrador::Administrador(int id, std::string nome, std::string descricao, std::string curso,
                             std::string instituicao, int periodo)
    : Perfil(id, nome, descricao, curso, instituicao, periodo) {}

bool Administrador::podeGerenciarComunidade() const { return true; }

bool Administrador::validarAdministracao(
        const Comunidade& comunidade) const {
    return comunidade.getIdAdministrador() == getId();
    }

bool Administrador::editarDescricaoComunidade(
        Comunidade& comunidade,
        const std::string& descricao) const {
    if (!validarAdministracao(comunidade))
        return false;
    comunidade.setDescricao(descricao);
    return true;
    }

bool Administrador::editarNomeComunidade(
        Comunidade& comunidade,
        const std::string& nome) const {
    if (!validarAdministracao(comunidade))
        return false;
    comunidade.setNome(nome);
    return true;
    }