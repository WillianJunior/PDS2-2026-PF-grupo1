#ifndef PERFIL_HPP
#define PERFIL_HPP
#include <string>
#include <vector>

class Perfil {

private:

    std::string curso;
    std::string instituicao;
    int periodo;

    std::vector<int> idsSeguidores;
    std::vector<int> idsSeguidos;
    std::vector<int> idsComunidadesQueFazParte;
    
public:

    Perfil();
    Perfil(std::string curso, std::string instituicao, int periodo);

    void seguir(int idPerfil);
    void deixarDeSeguir(int idPerfil);
    std::vector<int> listarIdSeguidores();
    std::vector<int> listarIdSeguidos();

};

#endif