#ifndef COMENTARIO_HPP
#define COMENTARIO_HPP
#include "perfil.hpp"
#include <string>
#include <vector>

/**
 * @file comentario.hpp
 * @brief Declaração da classe Comentario.
 */

/**
 * @class Comentario
 * @brief Classe que representa um comentário feito em uma postagem.
 * * Vincula-se a um post específico através de IDs e gerencia suas próprias curtidas.
 */
class Comentario {
  private:
    int id;
    int idPost;
    int idAutor;
    std::string texto;
    std::vector<int> idsCurtidas;

  public:
    /**
     * @brief Constrói um novo comentário completo (Geralmente oriundo do Banco de Dados).
     * @param id O identificador único numérico do comentário.
     * @param idPost O ID do post que está recebendo este comentário.
     * @param idAutor O ID do perfil que escreveu o comentário.
     * @param texto O conteúdo em texto do comentário.
     */
    Comentario(int id, int idPost, int idAutor, std::string texto);

    /**
     * @brief Constrói um novo comentário associado a uma instância de Perfil (compatibilidade com testes).
     * @param texto O conteúdo de texto do comentário.
     * @param autor Referência constante ao perfil do autor.
     */
    Comentario(std::string texto, const Perfil &autor);

    /**
     * @brief Registra ou remove a curtida de um usuário no comentário (efeito Toggle).
     * @param idUsuario O identificador do perfil do usuário que interagiu.
     */
    void curtir(int idUsuario);

    /**
     * @brief Retorna o total de curtidas que este comentário recebeu.
     * @return O número total de curtidas.
     */
    int quantidadeDeCurtidas() const;

    /**
     * @name Getters
     * @brief Métodos de acesso para leitura das propriedades do comentário.
     * @{
     */

    /** @brief Retorna o ID único do comentário. */
    int getId() const;

    /** @brief Retorna o ID do Post pai deste comentário. */
    int getIdPost() const;

    /** @brief Retorna o ID do autor (alias para idAutorObter). */
    int idAutorObter() const;

    /** @brief Retorna o ID do perfil que escreveu o comentário. */
    int getIdAutor() const;

    /** @brief Retorna o conteúdo textual do comentário. */
    std::string getTexto() const;

    /** @brief Retorna o vetor contendo os IDs dos usuários que curtiram. */
    std::vector<int> getIdsCurtidas() const;

    /** @} */

    /**
     * @name Setters (Persistência)
     * @brief Métodos utilizados exclusivamente pelo GerenciadorCSV para carregar estados.
     * @{
     */

    /**
     * @brief Restaura a lista de curtidas a partir dos dados em disco.
     * @param ids Vetor contendo os IDs dos usuários curtidores.
     */
    void setIdsCurtidas(const std::vector<int> &ids);

    /** @} */
};

#endif