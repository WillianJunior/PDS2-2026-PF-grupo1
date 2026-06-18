#include "domain/perfil.hpp"
#include <algorithm>

Perfil::Perfil(int id, std::string emailUsuario, std::string nome, std::string descricao, 
               std::string curso, std::string instituicao, int periodo)
    : id(id),
      emailUsuario(std::move(emailUsuario)),
      nome(std::move(nome)),
      descricao(std::move(descricao)),
      curso(std::move(curso)),
      instituicao(std::move(instituicao)),
      periodo(periodo) {}

Perfil::Perfil(std::string curso, std::string instituicao, int periodo)
    : id(0),
      emailUsuario(""),
      nome(""),
      descricao(""),
      curso(std::move(curso)),
      instituicao(std::move(instituicao)),
      periodo(periodo) {}

void Perfil::seguir(int idPerfil) {
    if (std::find(idsSeguidos.begin(), idsSeguidos.end(), idPerfil) == idsSeguidos.end()) {
        idsSeguidos.push_back(idPerfil);
    }
}

void Perfil::entrarComunidade(int idComunidade) {
    if (std::find(idsComunidadesQueFazParte.begin(), idsComunidadesQueFazParte.end(), idComunidade)
        == idsComunidadesQueFazParte.end()) {
        idsComunidadesQueFazParte.push_back(idComunidade);
    }
}

void Perfil::deixarDeSeguir(int idPerfil) {
    auto it = std::find(idsSeguidos.begin(), idsSeguidos.end(), idPerfil);
    if (it != idsSeguidos.end())
        idsSeguidos.erase(it);
}

void Perfil::adicionarSeguidor(int idPerfil) {
    if (std::find(idsSeguidores.begin(), idsSeguidores.end(), idPerfil) == idsSeguidores.end()) {
        idsSeguidores.push_back(idPerfil);
    }
}

void Perfil::removerSeguidor(int idPerfil) {
    auto it = std::find(idsSeguidores.begin(), idsSeguidores.end(), idPerfil);
    if (it != idsSeguidores.end())
        idsSeguidores.erase(it);
}

void Perfil::sairComunidade(int idComunidade) {
    auto it = std::find(idsComunidadesQueFazParte.begin(),
                        idsComunidadesQueFazParte.end(),
                        idComunidade);
    if (it != idsComunidadesQueFazParte.end())
        idsComunidadesQueFazParte.erase(it);
}

// ✅ agora retorna referência
const std::vector<int>& Perfil::listarIdSeguidores() const {
    return idsSeguidores;
}

const std::vector<int>& Perfil::listarIdSeguidos() const {
    return idsSeguidos;
}

int Perfil::getId() const { return id; }

const std::string& Perfil::getEmailUsuario() const {
    return emailUsuario;
}

const std::string& Perfil::getNome() const {
    return nome;
}

const std::string& Perfil::getDescricao() const {
    return descricao;
}

const std::string& Perfil::getCurso() const {
    return curso;
}

const std::string& Perfil::getInstituicao() const {
    return instituicao;
}

int Perfil::getPeriodo() const {
    return periodo;
}

// ✅ agora retorna referência
const std::vector<int>& Perfil::getIdsSeguidores() const {
    return idsSeguidores;
}

const std::vector<int>& Perfil::getIdsSeguidos() const {
    return idsSeguidos;
}

const std::vector<int>& Perfil::getIdsComunidades() const {
    return idsComunidadesQueFazParte;
}

void Perfil::setIdsSeguidores(const std::vector<int>& ids) {
    idsSeguidores = ids;
}

void Perfil::setIdsSeguidos(const std::vector<int>& ids) {
    idsSeguidos = ids;
}

void Perfil::setIdsComunidades(const std::vector<int>& ids) {
    idsComunidadesQueFazParte = ids;
}

void Perfil::setCurso(const std::string& c) {
    curso = c;
}

void Perfil::setInstituicao(const std::string& i) {
    instituicao = i;
}

void Perfil::setDescricao(const std::string& d) {
    descricao = d;
}

void Perfil::setPeriodo(int p) {
    periodo = p;
}