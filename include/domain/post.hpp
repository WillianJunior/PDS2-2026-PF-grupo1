#ifndef POST_HPP
#define POST_HPP
#include "comentario.hpp"
#include <string>
#include <vector>

/**
 * @file post.hpp
 * @brief Declaração da classe Post.
 */

/**
 * @class Post
 * @brief Classe que representa uma publicação de texto no sistema.
 * * Um post contém o texto principal, o identificador de quem o escreveu,
 * a comunidade à qual pertence (se houver) e a lista de usuários que o
 * curtiram.
 */
class Post {
  private:
    int id;
    int idAutor;
    int idComunidade;
    std::string texto;
    std::vector<int> idsCurtidas;

  public:
    /**
     * @brief Construtor completo para instanciar um Post recuperado do banco de dados.
     * @param id Identificador único do post.
     * @param idAutor ID do perfil que criou o post.
     * @param idComunidade ID da comunidade (0 se for um post global).
     * @param texto Conteúdo principal da publicação.
     */
    Post(int id, int idAutor, int idComunidade, std::string texto);

    /**
     * @brief Construtor para criar um novo Post global (sem comunidade associada).
     * @param texto Conteúdo principal da publicação.
     * @param idAutor ID do perfil que está criando o post.
     */
    Post(std::string texto, int idAutor);

    /**
     * @brief Adiciona ou remove a curtida de um usuário no post (Toggle).
     * @param idUsuario O identificador do perfil que está curtindo/descurtindo.
     */
    void curtir(int idUsuario);

    /**
     * @brief Retorna a quantidade total de curtidas que o post recebeu.
     * @return O número de curtidas (tamanho do vetor de curtidas).
     */
    int quantidadeDeCurtidas() const;

    /**
     * @brief Retorna a lista de comentários associados a este post.
     * @return Uma referência constante para o vetor de comentários.
     */
    const std::vector<Comentario> &listarComentarios() const;

    /** @name Getters */
    /** @{ */
    
    /** @brief Obtém o ID do post. */
    int getId() const;
    
    /** @brief Obtém o ID do autor do post. */
    int getIdAutor() const;
    
    /** @brief Obtém o ID da comunidade do post (0 para global). */
    int getIdComunidade() const;
    
    /** @brief Obtém o conteúdo de texto do post. */
    const std::string &getConteudo() const;
    
    /** @brief Obtém a lista de IDs dos usuários que curtiram o post. */
    const std::vector<int> &getIdsCurtidas() const;
    
    /** @} */

    /** @name Setters (Persistência) */
    /** @{ */
    
    /**
     * @brief Define a lista de curtidas de uma vez (Usado ao carregar do CSV).
     * @param ids Vetor contendo os IDs dos usuários que curtiram.
     */
    void setIdsCurtidas(const std::vector<int> &ids);
    
    /** @} */
};

#endif