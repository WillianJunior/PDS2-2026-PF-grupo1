#ifndef BUSCA_HPP
#define BUSCA_HPP

#include "domain/armazenamento.hpp"
#include "domain/comunidade.hpp"
#include "domain/perfil.hpp"
#include "domain/post.hpp"
#include <string>
#include <vector>

/**
 * @file busca.hpp
 * @brief Declaração da classe de pesquisa do sistema.
 */

/**
 * @class Busca
 * @brief Classe responsável pelo mecanismo de busca textual dentro da rede social.
 * Capaz de iterar sobre o banco de dados filtrando perfis, posts e comunidades
 * que correspondam aos termos solicitados pelo usuário.
 */
class Busca {
  private:
    std::vector<std::string> resultados;

  public:
    void buscarPostsComunidade(const std::string &palavraChave, const Armazenamento &db, int idComunidade);

    /**
     * @brief Apresenta os resultados coletados na última busca formatados na tela.
     */
    void exibirResultadosPesquisa() const;

    /**
     * @brief Filtra os resultados visuais da busca por uma categoria específica.
     * @param tipo O tipo de entidade desejada (ex: "Perfil", "Post", "Comunidade").
     */
    void filtrarResultados(const std::string &tipo);

    /**
     * @brief Busca especificamente por perfis cujo nome contenha a palavra-chave.
     * @param palavraChave O termo a ser procurado.
     * @param db Referência ao banco de dados.
     * @return Vetor contendo os perfis encontrados.
     */
    std::vector<Perfil> buscarPerfis(const std::string &palavraChave, const Armazenamento &db) const;

    /**
     * @brief Busca especificamente por posts cujo texto contenha a palavra-chave.
     * @param palavraChave O termo a ser procurado.
     * @param db Referência ao banco de dados.
     * @return Vetor contendo os posts encontrados.
     */
    std::vector<Post> buscarPosts(const std::string &palavraChave, const Armazenamento &db) const;

    /**
     * @brief Busca especificamente por comunidades cujo nome contenha a palavra-chave.
     * @param palavraChave O termo a ser procurado.
     * @param db Referência ao banco de dados.
     * @return Vetor contendo as comunidades encontradas.
     */
    std::vector<Comunidade> buscarComunidades(const std::string &palavraChave, const Armazenamento &db) const;

    /**
     * @brief Realiza a varredura no sistema em busca de posts pertencentes a uma comunidade específica.
     * @param idComunidade O ID da comunidade desejada.
     * @param db Referência ao banco de dados do sistema (mutável).
     * @return Vetor de ponteiros para os posts originais dentro do armazenamento.
     */
    std::vector<Post *> buscaPosts(int idComunidade, Armazenamento &db);

    /**
     * @brief Monta o feed de posts visíveis para um determinado perfil.
     * @param perfil O perfil logado.
     * @param db Referência ao banco de dados do sistema (mutável).
     * @return Vetor de ponteiros para os posts originais dentro do armazenamento.
     */
    std::vector<Post *> buscaPosts(Perfil perfil, Armazenamento &db);
    /**
     * @brief Busca e filtra as publicações criadas por um autor específico baseado nas regras de privacidade.
     * @param idAlvo Identificador único do perfil dono das publicações.
     * @param idLogado Identificador único do usuário que está solicitando a visualização.
     * @param db Referência ao banco de dados mutável do sistema.
     * @return Vetor de ponteiros para os posts originais filtrados do autor.
     */
    std::vector<Post *> buscaPostsPorAutor(int idAlvo, int idLogado, Armazenamento &db);

    /**
     * @brief Recupera de forma mutável a lista de comentários vinculados a uma publicação específica.
     * @param post Referência constante para o Post alvo.
     * @param db Referência ao banco de dados mutável do sistema.
     * @return Vetor de ponteiros para os comentários originais pertencentes ao post.
     */
    std::vector<Comentario *> comentariosDoPost(const Post &post, Armazenamento &db);

    /**
     * @brief Verifica se um determinado usuário possui vínculo ativo de membro em uma comunidade.
     * @param idUsuario Identificador único do perfil do usuário.
     * @param idComunidade Identificador único da comunidade alvo.
     * @param db Referência constante ao banco de dados para consulta.
     * @return true Se o usuário for membro ativo, false caso contrário.
     */
    bool usuarioE_MembroDaComunidade(int idUsuario, int idComunidade, const Armazenamento &db);

    /**
     * @brief Obtém o número total de membros validados que pertencem a uma comunidade específica.
     * @param idComunidade Identificador único da comunidade.
     * @param db Referência constante ao banco de dados para consulta.
     * @return Inteiro representando o total de membros vinculados.
     */
    int numeroDeMembrosDaComunidade(int idComunidade, const Armazenamento &db);

    /**
     * @brief Retorna uma lista contendo as publicações mais recentes de uma comunidade limitada por uma quantidade.
     * @param idComunidade Identificador único da comunidade.
     * @param limite Quantidade máxima de registros recentes que devem ser retornados.
     * @param db Referência ao banco de dados mutável do sistema.
     * @return Vetor de ponteiros para os posts mais recentes obedecendo ao limite.
     */
    std::vector<Post *> buscarPostsRecentesDaComunidade(int idComunidade, size_t limite, Armazenamento &db);

    /**
     * @brief Resolve de forma segura o nome associado a um ID de perfil, fornecendo um fallback de erro.
     * @param db Referência ao banco de dados mutável para varredura.
     * @param id Identificador único do perfil procurado.
     * @return String contendo o nome real do usuário ou "Desconhecido" caso o registro não exista.
     */
    std::string nomePerfil(Armazenamento &db, int id);
};
#endif