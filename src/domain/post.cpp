#include "domain/post.hpp"
#include <utility>

Post::Post(std::string texto, int idAutor)
    : texto(std::move(texto)), idsCurtidas(), idAutor(idAutor), comentarios() {}

void Post::adicionarComentario(Comentario comentario) {
    comentarios.push_back(std::move(comentario));
}

std::vector<Comentario> Post::listarComentarios() {
    return comentarios;
}

int Post::quantidadeDeCurtidas() {
    return static_cast<int>(idsCurtidas.size());
}

void Post::curtir(int idUsuario) {
    auto it = idsCurtidas.find(idUsuario);
    if (it == idsCurtidas.end()) {
        idsCurtidas.insert(idUsuario);
    } else {
        idsCurtidas.erase(it);
    }
}

std::string Post::getConteudo() const {
    return texto;
}

std::vector<int> Post::getIdsCurtidas() const {
    return std::vector<int>(idsCurtidas.begin(), idsCurtidas.end());
}
