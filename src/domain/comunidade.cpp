#include "comunidade.hpp"
#include <algorithm>

Comunidade::Comunidade(int id, std::string nome, std::string descricao, int idAdministrador)
    : id(id), nome(std::move(nome)), descricao(std::move(descricao)), idAdministrador(idAdministrador) {}

void Comunidade::adicionarMembro(int idPerfil) {
    if (std::find(idsMembros.begin(), idsMembros.end(), idPerfil) == idsMembros.end()) {
        idsMembros.push_back(idPerfil);
    }
}

void Comunidade::removerMembro(int idPerfil) {
    auto it = std::find(idsMembros.begin(), idsMembros.end(), idPerfil);
    if (it != idsMembros.end()) idsMembros.erase(it);
}

bool Comunidade::podePublicar(int idPerfil) const {
    return idPerfil == idAdministrador || std::find(idsMembros.begin(), idsMembros.end(), idPerfil) != idsMembros.end();
}

int Comunidade::getId() const { return id; }
std::string Comunidade::getNome() const { return nome; }
std::string Comunidade::getDescricao() const { return descricao; }
int Comunidade::getIdAdministrador() const { return idAdministrador; }
std::vector<int> Comunidade::getIdsMembros() const { return idsMembros; }
void Comunidade::setIdsMembros(const std::vector<int>& ids) { idsMembros = ids; }
