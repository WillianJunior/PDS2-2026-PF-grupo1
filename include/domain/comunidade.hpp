#ifndef COMUNIDADE_HPP
#define COMUNIDADE_HPP
#include <vector>
#include <string>
#include "post.hpp"
#include "perfil.hpp"

class Comunidade {

private:

    std::vector<Post> postagensComunidade;
    std::vector<int> idsMembrosComunidade;
    int idAdministrador;
    std::string nomeComunidade;

public:

    Comunidade(std::string nomeComunidade, int idAdministrador);
    void entrarComunidade(int idPerfil);
    bool podePublicar(int idPerfil);
    void exibirMembrosComunidade();
    std::vector<Post> posts();
    std::vector<Post> buscarPosts(std::string termo);
};

#endif