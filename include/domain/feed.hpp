#ifndef FEED_HPP
#define FEED_HPP

#include "armazenamento.hpp"
#include "sistema.hpp"
#include "comunidade.hpp"
#include "perfil.hpp"
#include "post.hpp"
#include <vector>

/**
 * @file feed.hpp
 * @brief Declaração da classe Feed.
 */

/**
 * @class Feed
 * @brief Classe encarregada de exibir dados e gerenciar os menus interativos da linha do tempo.
 */
class Feed {
  public:
    /**
     * @brief Renderiza a linha do tempo principal e gerencia o menu de seleção de posts.
     * @param db Referência ao banco de dados do sistema (apenas leitura).
     * @param sys Referência ao sistema para validação de curtidas e novos posts.
     */
    void verFeed(Armazenamento &db, Sistema &sys);

    /**
     * @brief Exibe na tela uma lista de publicações (compatibilidade com testes).
     */
    void exibirPosts(const std::vector<Post> &posts);

    /**
     * @brief Exibe na tela uma lista de perfis de usuários (compatibilidade com testes).
     */
    void exibirPerfis(const std::vector<Perfil> &perfis);

    /**
     * @brief Exibe na tela uma lista de comunidades (compatibilidade com testes).
     */
    void exibirComunidades(const std::vector<Comunidade> &comunidades);
};
#endif