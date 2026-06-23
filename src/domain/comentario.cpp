#include "domain/comentario.hpp"
#include <algorithm>

Comentario::Comentario(int id, int idPost, int idAutor, std::string texto)
    : id(id), idPost(idPost), idAutor(idAutor), texto(std::move(texto)) {}

Comentario::Comentario(std::string texto, const Perfil &autor)
    : id(0), idPost(0), idAutor(autor.getId()), texto(std::move(texto)) {}

void Comentario::curtir(int idUsuario) {
    auto it = std::find(idsCurtidas.begin(), idsCurtidas.end(), idUsuario);
    if (it == idsCurtidas.end())
        idsCurtidas.push_back(idUsuario);
    else
        idsCurtidas.erase(it);
}

int Comentario::quantidadeDeCurtidas() const { return idsCurtidas.size(); }
int Comentario::getId() const { return id; }
int Comentario::getIdPost() const { return idPost; }
int Comentario::idAutorObter() const { return idAutor; }
int Comentario::getIdAutor() const { return idAutor; }
std::string Comentario::getTexto() const { return texto; }
std::vector<int> Comentario::getIdsCurtidas() const { return idsCurtidas; }
void Comentario::setIdsCurtidas(const std::vector<int> &ids) { idsCurtidas = ids; }