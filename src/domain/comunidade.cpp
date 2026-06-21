#include "domain/comunidade.hpp"
#include <algorithm>

Comunidade::Comunidade(int id, std::string nome, std::string descricao, int idAdministrador)
    : id(id), nome(std::move(nome)), descricao(std::move(descricao)), idAdministrador(idAdministrador) {}

Comunidade::Comunidade(std::string nome, int idAdministrador)
    : id(0), nome(std::move(nome)), descricao(""), idAdministrador(idAdministrador) {}

void Comunidade::adicionarMembro(int idPerfil) {
    if (std::find(idsMembros.begin(), idsMembros.end(), idPerfil) == idsMembros.end()) {
        idsMembros.push_back(idPerfil);
    }
}

void Comunidade::removerMembro(int idPerfil) {
    auto it = std::find(idsMembros.begin(), idsMembros.end(), idPerfil);
    if (it != idsMembros.end()) idsMembros.erase(it);
}

void Comunidade::entrarComunidade(int idPerfil) {
    adicionarMembro(idPerfil);
}

bool Comunidade::podePublicar(int idPerfil) const {
    return idPerfil == idAdministrador ||
           std::find(idsMembros.begin(), idsMembros.end(), idPerfil) != idsMembros.end();
}

void Comunidade::exibirMembrosComunidade() const {}

int Comunidade::getId() const { return id; }

const std::string& Comunidade::getNome() const { return nome; }

const std::string& Comunidade::getDescricao() const { return descricao; }

int Comunidade::getIdAdministrador() const { return idAdministrador; }

const std::vector<int>& Comunidade::getIdsMembros() const { return idsMembros; }

void Comunidade::setIdsMembros(const std::vector<int>& ids) {
    idsMembros = ids;
}