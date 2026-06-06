#ifndef FEED_HPP
#define FEED_HPP
#include "post.hpp"
#include "comunidade.hpp"
#include <vector>

/**
 * @brief Classe responsável pela renderização/exibição de conteúdos para o usuário.
 * * Atua como a interface visual da linha do tempo, listando postagens,
 * sugerindo perfis e comunidades.
 */

class Feed
{
public:

    /**
     * @brief Exibe uma lista de postagens na tela.
     * @param posts O vetor de postagens a ser exibido.
     */

    void exibirPosts(std::vector<Post> posts);

    /**
     * @brief Exibe uma lista de perfis na tela (ex: resultados de busca ou sugestões).
     * @param perfis O vetor de perfis a ser exibido.
     */

    void exibirPerfis(std::vector<Perfil> perfis);

    /**
     * @brief Exibe uma lista de comunidades na tela.
     * @param Comunidades O vetor de comunidades a ser exibido.
     */

    void exibirComunidades(std::vector<Comunidade> Comunidades);
    
};

#endif