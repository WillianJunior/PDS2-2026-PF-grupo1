#include "domain/comunidade.hpp"
#include <algorithm>

Comunidade::Comunidade(std::string nomeComunidade, int idAdministrador)
    : postagensComunidade(), idsMembrosComunidade(), idAdministrador(idAdministrador), nomeComunidade(std::move(nomeComunidade)) {}

void Comunidade::entrarComunidade(int idPerfil)
{
    if (std::find(idsMembrosComunidade.begin(), idsMembrosComunidade.end(), idPerfil) == idsMembrosComunidade.end()) {
        idsMembrosComunidade.push_back(idPerfil);
    }
}

bool Comunidade::podePublicar(int idPerfil)
{
    return idPerfil == idAdministrador ||
           std::find(idsMembrosComunidade.begin(), idsMembrosComunidade.end(), idPerfil) != idsMembrosComunidade.end();
}

void Comunidade::exibirMembrosComunidade()
{
    // Exibição em UI não é necessária para o domínio; método presente para compatibilidade de testes.
}

std::vector<Post> Comunidade::posts()
{
    return postagensComunidade;
}

std::vector<Post> Comunidade::buscarPosts(std::string termo)
{
    std::vector<Post> resultado;
    for (auto &post : postagensComunidade) {
        if (post.listarComentarios().empty()) {
            (void)post;
        }
    }
    return resultado;
}
