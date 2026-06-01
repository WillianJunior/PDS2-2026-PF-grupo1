#include "domain/comentario.hpp"

Comentario::Comentario(std::string texto, Perfil autor)
    : texto(std::move(texto)), autor(std::move(autor)), idsCurtidas() {}

void Comentario::curtir(int idUsuario)
{
    auto it = idsCurtidas.find(idUsuario);
    if (it == idsCurtidas.end()) {
        idsCurtidas.insert(idUsuario);
    } else {
        idsCurtidas.erase(it);
    }
}

int Comentario::quantidadeDeCurtidas()
{
    return static_cast<int>(idsCurtidas.size());
}
