#ifndef PERFIL_HPP
#define PERFIL_HPP
#include <string>
#include <vector>
#include "comunidade.hpp"

class Perfil {

private:


    std::string curso;
    std::string instituicao;
    int periodo;

    std::vector<Perfil> seguidores;
    std::vector<Perfil> seguindo;
    std::vector<Comunidade> comunidadesQueFazParte;
    
public:

    Perfil(std::string curso, std::string instituicao, int periodo);

    void seguir(int idPerfil);
    void deixarDeSeguir(int idPerfil);
    std::vector<Perfil> listarSeguidores();
    std::vector<Perfil> listarSeguindo();

};

#endif