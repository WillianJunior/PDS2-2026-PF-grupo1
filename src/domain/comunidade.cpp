#include "domain/comunidade.hpp"
#include <algorithm>
#include <iostream>


 std::vector<Perfil> todosPerfis;

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
    std::cout << "=== Membros da Comunidade: " << nomeComunidade << " ===" << std::endl;
    if (idsMembrosComunidade.empty()) {
        std::cout << "Nenhum membro na comunidade." << std::endl;
    } else {
        for (int id : idsMembrosComunidade) {
            auto it = std::find_if(todosPerfis.begin(), todosPerfis.end(),
                                   [id](const Perfil& p) { return p.getId() == id; });

            if (it != todosPerfis.end()) {
                std::cout << "Membro: " << it->getNome() << " (ID: " << id << ")" << std::endl;
            } else {
                std::cout << "Membro com ID " << id << " não encontrado nos perfis." << std::endl;
            }
        }
    }
}


std::vector<Post> Comunidade::posts()
{
    return postagensComunidade;
}


std::vector<Post> Comunidade::buscarPosts(std::string termo)
{
    std::vector<Post> resultado;
    for (auto &post : postagensComunidade) {
        
        if (post.getConteudo().find(termo) != std::string::npos) {
            resultado.push_back(post);
        }
    }
    return resultado;
}


std::string Comunidade::getNomeComunidade() const {
    return nomeComunidade;
}


int Comunidade::getIdAdministrador() const {
    return idAdministrador;
}


std::vector<int> Comunidade::getIdsMembros() const {
    return idsMembrosComunidade;
}


std::vector<Post> Comunidade::getPostagens() const {
    return postagensComunidade;
}

std::string Comunidade::getNome() const {
    return nomeComunidade;
}
