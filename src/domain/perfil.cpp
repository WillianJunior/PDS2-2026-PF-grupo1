#include "domain/perfil.hpp"
#include <algorithm>

Perfil::Perfil(int id, std::string nome, std::string descricao,
               std::string curso, std::string instituicao, int periodo)
    : id(id), nome(std::move(nome)), descricao(std::move(descricao)),
      curso(std::move(curso)), instituicao(std::move(instituicao)),
      periodo(periodo) {}

Perfil::Perfil(std::string curso, std::string instituicao, int periodo)
    : id(0), nome(""), descricao(""), curso(std::move(curso)),
      instituicao(std::move(instituicao)), periodo(periodo) {}

void Perfil::entrarComunidade(int idComunidade) {
    if (std::find(idsComunidadesQueFazParte.begin(),
                  idsComunidadesQueFazParte.end(),
                  idComunidade) == idsComunidadesQueFazParte.end()) {
        idsComunidadesQueFazParte.push_back(idComunidade);
    }
}

void Perfil::sairComunidade(int idComunidade) {
    auto it = std::find(idsComunidadesQueFazParte.begin(),
                        idsComunidadesQueFazParte.end(), idComunidade);
    if (it != idsComunidadesQueFazParte.end())
        idsComunidadesQueFazParte.erase(it);
}

int Perfil::getId() const { return id; }

const std::string &Perfil::getNome() const { return nome; }

const std::string &Perfil::getDescricao() const { return descricao; }

const std::string &Perfil::getCurso() const { return curso; }

const std::string &Perfil::getInstituicao() const { return instituicao; }

int Perfil::getPeriodo() const { return periodo; }

const std::vector<int> &Perfil::getIdsComunidades() const {
    return idsComunidadesQueFazParte;
}

void Perfil::setIdsComunidades(const std::vector<int> &ids) {
    idsComunidadesQueFazParte = ids;
}

void Perfil::setCurso(const std::string &c) { curso = c; }

void Perfil::setInstituicao(const std::string &i) { instituicao = i; }

void Perfil::setDescricao(const std::string &d) { descricao = d; }

void Perfil::setPeriodo(int p) { periodo = p; }

bool Perfil::podeGerenciarComunidade() const {
    return false;
}