#ifndef DOMAIN_MENUS_HPP
#define DOMAIN_MENUS_HPP

#include "armazenamento.hpp"
#include "sistema.hpp"
#include "comentario.hpp"
#include "comunidade.hpp"
#include "perfil.hpp"
#include "post.hpp"
#include <string>
#include <vector>

/**
 * @class Menus
 * @brief Classe container responsável pela renderização dos menus textuais CLI.
 */
class Menus {
  public:
    Menus() = delete;

    /**
     * @brief Exibe o menu principal do perfil de um usuário.
     * @param idAlvo Identificador único do perfil a ser visualizado.
     * @param db Referência para o banco de dados.
     * @param sys Referência para as regras de negócio e sessão ativa.
     */
    static void menuPerfil(int idAlvo, Armazenamento &db, Sistema &sys);

    /**
     * @brief Exibe o menu interno de uma comunidade específica.
     */
    static void menuComunidade(int idComunidade, Armazenamento &db, Sistema &sys);

    /**
     * @brief Gerencia a tela de edição de dados cadastrais do perfil do usuário logado.
     */
    static void menuEditarPerfil(Perfil &alvo);

    /**
     * @brief Exibe a tela detalhada de uma publicação com seus comentários.
     */
    static void menuVisualizarPost(Post &post, Armazenamento &db, Sistema &sys);

    /**
     * @brief Renderiza uma lista de publicações com opção de seleção por índice.
     */
    static void menuVerPostsLista(const std::vector<Post> &postsList, Armazenamento &db, Sistema &sys);

    /**
     * @brief Exibe na tela uma listagem formatada de perfis de usuários cadastrados.
     */
    static void menuVerPerfisLista(const std::vector<Perfil> &perfisList, Armazenamento &db, Sistema &sys);

    /**
     * @brief Exibe uma lista de comunidades disponíveis no sistema com suporte a filtros.
     */
    static void menuVerComunidadesLista(Armazenamento &db, Sistema &sys, const std::vector<Comunidade> *filtro = nullptr);

  private:
    static void exibirResumoPerfil(const Perfil &alvo);
    static void exibirPostDetalhado(const Post &post, Armazenamento &db, const std::vector<Comentario *> &comentarios);
    static void exibirListaPosts(const std::vector<Post> &postsList, Armazenamento &db);
    static bool tratarOpcaoPost(const std::string &opcao, Post &post, Armazenamento &db, Sistema &sys,
                                const std::vector<Comentario *> &comentarios, std::string &mensagem);
};
#endif