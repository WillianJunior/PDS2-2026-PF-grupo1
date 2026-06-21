#include "domain/post.hpp"
#include <algorithm>

Post::Post(int id, int idAutor, int idComunidade, std::string texto)
    : id(id),
      idAutor(idAutor),
      idComunidade(idComunidade),
      texto(std::move(texto)) {}

Post::Post(std::string texto, int idAutor)
    : id(0),
      idAutor(idAutor),
      idComunidade(0),
      texto(std::move(texto)) {}

void Post::curtir(int idUsuario) {
    auto it = std::find(idsCurtidas.begin(), idsCurtidas.end(), idUsuario);
    if (it == idsCurtidas.end())
        idsCurtidas.push_back(idUsuario);
    else
        idsCurtidas.erase(it);
}

int Post::quantidadeDeCurtidas() const {
    return idsCurtidas.size();
}

int Post::getId() const {
    return id;
}

int Post::getIdAutor() const {
    return idAutor;
}

int Post::getIdComunidade() const {
    return idComunidade;
}


const std::string& Post::getConteudo() const {
    return texto;
}


const std::vector<int>& Post::getIdsCurtidas() const {
    return idsCurtidas;
}

void Post::setIdsCurtidas(const std::vector<int>& ids) {
    idsCurtidas = ids;
}