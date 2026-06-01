#ifndef POST_HPP
#define POST_HPP
#include <string>
#include <vector>
#include <set>
#include "comentario.hpp"
#include "perfil.hpp"

class Post {

private:

    std::string texto; 
    std::set<int> idsCurtidas;
    int idAutor;
    std::vector<Comentario> comentarios;

public:

    Post(std::string texto, int idAutor);

    void adicionarComentario(Comentario comentario);
    std::vector<Comentario> listarComentarios();
    int quantidadeDeCurtidas();
    void curtir(int idUsuario);

};

#endif