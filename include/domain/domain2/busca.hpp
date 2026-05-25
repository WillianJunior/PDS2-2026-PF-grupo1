#ifndef BUSCA_HPP
#define BUSCA_HPP
#include <vector>
#include <string>
#include "comunidade.hpp"
#include "perfil.hpp"
#include "post.hpp"

class Busca {

private:

    std::vector<Perfil> perfis;
    std::vector<Comunidade> comunidades;
    std::vector<Post> posts;

public:

    void buscarPalavraChave(std::string palavraChave); //exibir tbm posts de comunidades q o user nao participa e de users q nao segue
    void exibirResultados();
    void filtrarResultados(std::string tipo);
    //exibir em ordem alfabetica na implementacao

};

#endif