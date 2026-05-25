#ifndef SISTEMA_HPP
#define SISTEMA_HPP
#include <string>
#include <vector>
#include "comunidade.hpp"

class Sistema {

private:

    std::vector<Comunidade> comunidades;

public:

    void excluirPerfil(Perfil perfil);
    bool comunidadeNomeUnico(std::string nomeComunidade);
    void removerPostsPerfilDeletado(Perfil perfil);
    void removerComentariosPerfilDeletado(Perfil perfil);

};

#endif