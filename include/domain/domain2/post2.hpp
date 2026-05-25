#ifndef POST_HPP
#define POST_HPP
#include <string>
#include <vector>
#include <set>
#include "comentario.hpp"
#include "curtida.hpp"
#include "perfil.hpp"

class Post {

private:

    std::string texto; 
    // substituir essa lista aqui por lista de ids -> que
    std::set<int> idsCurtidas;
    std::vector<Comentario> comentarios;

public:

    Post(std::string texto, Perfil autor);

    void adicionarComentario(Comentario comentario);
    void removerComentario(int idComentario)
    
    void exibirComentarios();
    void exibirCurtidas();

    void curtir(int idUsuario);

};

#endif