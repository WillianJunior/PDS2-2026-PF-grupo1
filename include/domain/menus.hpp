#ifndef DOMAIN_MENUS_HPP
#define DOMAIN_MENUS_HPP

#include "armazenamento.hpp"
#include "comentario.hpp"
#include "comunidade.hpp"
#include "perfil.hpp"
#include "post.hpp"
#include <string>
#include <vector>

/**
 * @class Menus
 * @brief Classe container responsável pela renderização dos menus textuais e gerenciamento da interface CLI.
 *
 * Esta classe encapsula todas as interações de prompt de comando (E/S) com o usuário,
 * delegando as regras de negócio para as classes de domínio e o motor de Busca.
 * Como funciona apenas como um container de telas, seu construtor padrão é desabilitado.
 */
class Menus {
  public:
    Menus() = delete;

    /**
     * @brief Exibe o menu principal do perfil de um usuário (próprio ou de terceiros).
     * @param idAlvo Identificador único do perfil a ser visualizado.
     * @param db Referência para o banco de dados/armazenamento do sistema.
     */
    static void menuPerfil(int idAlvo, Armazenamento &db);

    /**
     * @brief Exibe o menu interno de uma comunidade específica, mostrando descrição, membros e posts recentes.
     * @param idComunidade Identificador único da comunidade a ser acessada.
     * @param db Referência para o banco de dados/armazenamento do sistema.
     */
    static void menuComunidade(int idComunidade, Armazenamento &db);

    /**
     * @brief Gerencia a tela de edição de dados cadastrais do perfil do usuário logado.
     * @param alvo Referência para o objeto Perfil que sofrerá as alterações de biografia, curso, etc.
     */
    static void menuEditarPerfil(Perfil &alvo);

    /**
     * @brief Exibe a tela de foco em uma publicação detalhada, listando o conteúdo completo e seus comentários.
     * @param post Referência para o Post que está sendo visualizado.
     * @param db Referência para o banco de dados/armazenamento do sistema.
     */
    static void menuVisualizarPost(Post &post, Armazenamento &db);

    /**
     * @brief Renderiza uma lista paginada ou sequencial de publicações com opção de seleção por índice.
     * @param postsList Vetor contendo os objetos Post que devem ser listados na tela.
     * @param db Referência para o banco de dados/armazenamento do sistema.
     */
    static void menuVerPostsLista(const std::vector<Post> &postsList, Armazenamento &db);

    /**
     * @brief Exibe na tela uma listagem formatada de perfis de usuários cadastrados no sistema.
     * @param perfisList Vetor contendo a lista de objetos Perfil a serem mostrados.
     * @param db Referência para o banco de dados/armazenamento do sistema.
     */
    static void menuVerPerfisLista(const std::vector<Perfil> &perfisList, Armazenamento &db);

    /**
     * @brief Exibe uma lista de comunidades disponíveis no sistema com suporte a filtros opcionais.
     * @param db Referência para o banco de dados/armazenamento do sistema.
     * @param filtro Ponteiro opcional para um vetor de comunidades pré-filtradas (padrão: nullptr para trazer todas).
     */
    static void menuVerComunidadesLista(Armazenamento &db, const std::vector<Comunidade> *filtro = nullptr);

  private:
    /**
     * @brief Imprime o bloco de cabeçalho com o resumo das informações estáticas do Perfil.
     * @param alvo Referência constante para o Perfil cujos dados serão impressos.
     */
    static void exibirResumoPerfil(const Perfil &alvo);

    /**
     * @brief Imprime na tela o layout detalhado do post, indicando autor, comunidade de origem e a árvore de
     * comentários.
     * @param post Referência constante para o Post alvo da exibição.
     * @param db Referência para o banco de dados/armazenamento do sistema.
     * @param comentarios Vetor de ponteiros para os comentários associados a este post.
     */
    static void exibirPostDetalhado(const Post &post, Armazenamento &db, const std::vector<Comentario *> &comentarios);

    /**
     * @brief Sub-rotina para renderizar de forma compacta e indexada (1, 2, 3...) o conteúdo do vetor de posts.
     * @param postsList Vetor contendo a lista de objetos Post.
     * @param db Referência para o banco de dados/armazenamento do sistema.
     */
    static void exibirListaPosts(const std::vector<Post> &postsList, Armazenamento &db);

    /**
     * @brief Processa as entradas textuais de comando do menu de posts (curtir, comentar, navegar para
     * autor/comunidade).
     * @param opcao String contendo o caractere digitado pelo usuário (A, B, C, D, E, F).
     * @param post Referência para o Post que está recebendo a interação.
     * @param db Referência para o banco de dados/armazenamento do sistema.
     * @param comentarios Vetor de comentários carregados para validação de índices de curtida.
     * @param mensagem Referência para string de retorno onde mensagens de erro ou sucesso serão salvas para a próxima
     * renderização.
     * @return true Se o menu de visualização deve continuar rodando.
     * @return false Se a opção escolhida foi "Voltar/Sair" (F/f).
     */
    static bool tratarOpcaoPost(const std::string &opcao, Post &post, Armazenamento &db,
                                const std::vector<Comentario *> &comentarios, std::string &mensagem);
};

#endif // DOMAIN_MENUS_HPP