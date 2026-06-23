#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP
#include "domain/perfil.hpp"

class Administrador : public Perfil {
public:
    Administrador(
        int id,
        std::string nome,
        std::string descricao,
        std::string curso,
        std::string instituicao,
        int periodo
    );

    bool podeGerenciarComunidade() const override;
};

#endif