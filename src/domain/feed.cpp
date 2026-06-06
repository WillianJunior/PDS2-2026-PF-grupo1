#include "domain/feed.hpp"

void Feed::exibirPosts(std::vector<Post> posts) {
    (void)posts; // evita warning até implementar
}

void Feed::exibirPerfis(std::vector<Perfil> perfis) {
    (void)perfis;
}

void Feed::exibirComunidades(std::vector<Comunidade> comunidades) {
    (void)comunidades;
}

std::string Feed::getConteudo() const {
    return conteudo;
}
