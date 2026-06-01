#ifndef FEED_HPP
#define FEED_HPP
#include "post.hpp"
#include "comunidade.hpp"
#include <vector>

class Feed
{
public:
    void exibirPosts(std::vector<Post> posts);
    void exibirPerfis(std::vector<Perfil> perfis);
    void exibirComunidades(std::vector<Comunidade> Comunidades);
    
};

#endif