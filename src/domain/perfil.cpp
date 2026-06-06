#include "domain/perfil.hpp"
#include <algorithm>

Perfil::Perfil()
    : curso(), instituicao(), periodo(0), idsSeguidores(), idsSeguidos(), idsComunidadesQueFazParte(),
      id(0), nome(), descricao() {}

Perfil::Perfil(std::string curso, std::string instituicao, int periodo)
    : curso(std::move(curso)), instituicao(std::move(instituicao)), periodo(periodo),
      idsSeguidores(), idsSeguidos(), idsComunidadesQueFazParte(),
      id(0), nome(), descricao() {}

void Perfil::seguir(int idPerfil) {
    if (std::find(idsSeguidos.begin(), idsSeguidos.end(), idPerfil) == idsSeguidos.end()) {
        idsSeguidos.push_back(idPerfil);
    }
}

void Perfil::deixarDeSeguir(int idPerfil) {
    auto it = std::find(idsSeguidos.begin(), idsSeguidos.end(), idPerfil);
    if (it != idsSeguidos.end()) {
        idsSeguidos.erase(it);
    }
}

std::vector<int> Perfil::listarIdSeguidores() {
    return idsSeguidores;
}

std::vector<int> Perfil::listarIdSeguidos() {
    return idsSeguidos;
}

int Perfil::getId() const {
    return id;
}

std::string Perfil::getNome() const {
    return nome;
}

std::string Perfil::getDescricao() const {
    return descricao;
}

std::string Perfil::getCurso() const {
    return curso;
}

std::string Perfil::getInstituicao() const {
    return instituicao;
}

int Perfil::getPeriodo() const {
    return periodo;
}

std::vector<int> Perfil::getIdsComunidades() const {
    return idsComunidadesQueFazParte;
}
