#ifndef COMUNIDADE_HPP
#define COMUNIDADE_HPP
#include <vector>
#include <string>
#include "post.hpp"
#include "perfil.hpp"

class Comunidade {

private:

    std::vector<Post> postagensComunidade;
    std::vector<Perfil> membrosComunidade;
    Perfil adm;
    std::string nomeComunidade;

public:

    Comunidade(std::string nomeComunidade, Perfil adm);
    void entrarComunidade(Perfil perfil);
    bool podePublicar(Perfil perfil);
    void exibirPostsComunidade();
    void exibirMembrosComunidade();

};

#endif