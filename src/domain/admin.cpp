#include "domain/admin.hpp"

Administrador::Administrador(int id, std::string nome, std::string descricao, std::string curso, std::string instituicao, int periodo)
    : Perfil(id, nome, descricao, curso, instituicao, periodo) {
} 

bool Administrador::podeGerenciarComunidade() const {
    return true;
}