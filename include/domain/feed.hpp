#ifndef FEED_HPP
#define FEED_HPP
#include "post.hpp"
#include "perfil.hpp"
#include "comunidade.hpp"
#include "armazenamento.hpp"
#include <vector>

/**
 * @file feed.hpp
 * @brief Declaração da classe Feed.
 */

/**
 * @class Feed
 * @brief Classe de interface visual encarregada de exibir dados e gerenciar os menus interativos.
 * * Atua como a View interativa do Feed, processando navegação, curtidas e comentários de maneira encapsulada.
 */
class Feed {
public:
    /**
     * @brief Renderiza a linha do tempo principal de forma cronológica inversa e gerencia o menu de seleção de posts.
     * @param db Referência ao banco de dados do sistema.
     */
    void verFeed(Armazenamento& db);

    /**
     * @brief Exibe na tela uma lista de publicações (compatibilidade com testes).
     * @param posts Vetor contendo os posts a serem exibidos.
     */
    void exibirPosts(const std::vector<Post>& posts);

    /**
     * @brief Exibe na tela uma lista de perfis de usuários (compatibilidade com testes).
     * @param perfis Vetor contendo os perfis a serem exibidos.
     */
    void exibirPerfis(const std::vector<Perfil>& perfis);

    /**
     * @brief Exibe na tela uma lista de comunidades (compatibilidade com testes).
     * @param comunidades Vetor contendo as comunidades a serem exibidas.
     */
    void exibirComunidades(const std::vector<Comunidade>& comunidades);
};
#endif