#ifndef FEED_HPP
#define FEED_HPP
#include "post.hpp"
#include "perfil.hpp"
#include "comunidade.hpp"
#include "armazenamento.hpp"
#include <vector>

/**
 * @brief Classe de interface visual encarregada de exibir dados e gerenciar os menus interativos.
 * * Atua como a View interativa do Feed, processando navegação, curtidas e comentários.
 */
class Feed {
public:
    /**
     * @brief Renderiza a linha do tempo principal de forma cronológica inversa e gerencia o menu de seleção de posts.
     * @param db Referência ao banco de dados do sistema.
     */
    static void verFeed(Armazenamento& db);

    /**
     * @name Métodos de Renderização Legados
     * @{
     */
    static void exibirPosts(const std::vector<Post>& posts, Armazenamento& db);
    static void exibirPerfis(const std::vector<Perfil>& perfis);
    static void exibirComunidades(const std::vector<Comunidade>& comunidades);
    /** @} */

private:
    /**
     * @brief Renderiza a tela interna de um Post específico, exibindo seu conteúdo, curtidas e seção de comentários.
     * @param post Referência mutável ao post selecionado.
     * @param db Referência ao banco de dados do sistema.
     */
    static void exibirPostDetalhado(Post& post, Armazenamento& db);
};
#endif
