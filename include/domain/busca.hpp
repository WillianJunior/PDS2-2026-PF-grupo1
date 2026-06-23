#ifndef BUSCA_HPP
#define BUSCA_HPP

#include "domain/armazenamento.hpp"
#include "domain/comunidade.hpp"
#include "domain/perfil.hpp"
#include "domain/post.hpp"
#include <memory>
#include <string>
#include <vector>

/**
 * @file busca.hpp
 * @brief Declaração da classe de pesquisa do sistema.
 */

/**
 * @class Busca
 * @brief Classe responsável pelo mecanismo de busca textual dentro da rede social.
 * * Capaz de iterar sobre o banco de dados filtrando perfis, posts e comunidades
 * que correspondam aos termos solicitados pelo usuário.
 */
class Busca {
  private:
    std::vector<std::string> resultados;

  public:
    /// @brief
    /// @param palavraChave
    /// @param db
    /// @param idComunidade
    /// @return
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
     * @brief Função polimofica que realiza a varredura no sistema em busca de posts pertencentes a uma comunidade específica.
     * @param palavraChave O termo textual desejado para a pesquisa.
     * @param db Referência constante ao banco de dados do sistema.
     */
    std::vector<std::shared_ptr<Post>> buscaPosts(int idComunidade, const Armazenamento &db);

    std::vector<std::shared_ptr<Post>> buscaPosts(Perfil perfil, const Armazenamento &db);
};

#endif