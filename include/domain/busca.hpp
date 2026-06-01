#ifndef BUSCA_HPP
#define BUSCA_HPP
#include <vector>
#include <string>
#include "comunidade.hpp"
#include "perfil.hpp"
#include "feed.hpp"

class Busca {


public:

    void buscarPalavraChave(std::string palavraChave); //exibir tbm posts de comunidades q o user nao participa e de users q nao segue
    void exibirResultadosPesquisa(); // Exibir cabeçalho e depois mostrar um feed junto
    void filtrarResultados(std::string tipo);
    //exibir em ordem alfabetica na implementacao

};

#endif