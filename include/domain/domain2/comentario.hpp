#ifndef COMENTARIO_HPP
#define COMENTARIO_HPP
#include <string>
#include <set>
#include "perfil.hpp"

class Comentario {

private:
    
    std::string texto;
    Perfil autor;
    std::set<int> idsCurtidas;

public:

    Comentario(std::string texto, Perfil autor);
    void curtir(int idUsuario);

};

#endif