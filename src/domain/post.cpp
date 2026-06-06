#include "domain/post.hpp"

Post::Post(std::string texto, int Idautor)
    : texto(std::move(texto)), idsCurtidas(), idAutor(Idautor), comentarios() {}

void Post::adicionarComentario(Comentario comentario)
{
    comentarios.push_back(std::move(comentario));
}

std::vector<Comentario> Post::listarComentarios()
{
    return comentarios;
}

int Post::quantidadeDeCurtidas()
{
    return static_cast<int>(idsCurtidas.size());
}

void Post::curtir(int idUsuario)
{
    auto it = idsCurtidas.find(idUsuario);
    if (it == idsCurtidas.end()) {
        idsCurtidas.insert(idUsuario);
    } else {
        idsCurtidas.erase(it);
    }
}
