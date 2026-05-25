#ifndef FEED_HPP
#define FEED_HPP
#include "post.hpp"
#include "comunidade.hpp"
#include <vector>

class Feed {

private:

    std::vector<Post> posts;

public:

    void exibirPosts(); //fazer exibicao por ordem cronologica na implementacao
    void exibirPostsComunidade(Comunidade& comunidade);

};

#endif