#ifndef POST_HPP
#define POST_HPP
#include <string>
#include <vector>
#include "comentario.hpp"

/**
 * @class Post
 * @brief Classe que representa uma publicação de texto no sistema.
 * * Um post contém o texto principal, o identificador de quem o escreveu, 
 * a comunidade à qual pertence (se houver) e a lista de usuários que o curtiram.
 */
class Post {
private:
    int id;
    int idAutor;
    int idComunidade; // 0 significa que é um post no feed geral
    std::string texto;
    std::vector<int> idsCurtidas;
    std::vector<Comentario> comentariosTestes; // Armazena comentários locais exigidos pelos testes

public:
    /**
     * @brief Constrói uma nova postagem completa.
     * @param id O identificador único numérico da postagem.
     * @param idAutor O identificador do perfil do usuário que a criou.
     * @param idComunidade O identificador da comunidade (0 se for Feed Geral).
     * @param texto O conteúdo em texto da publicação.
     */
    Post(int id, int idAutor, int idComunidade, std::string texto);

    /**
     * @brief Constrói uma nova postagem simplificada (utilizado em testes).
     * @param texto O conteúdo em texto da publicação.
     * @param idAutor O identificador do perfil do autor.
     */
    Post(std::string texto, int idAutor);

    /**
     * @brief Registra ou remove a curtida de um usuário na postagem (efeito Toggle).
     * @param idUsuario O identificador do perfil do usuário que interagiu com o post.
     */
    void curtir(int idUsuario);

    /**
     * @brief Retorna o total de curtidas recebidas pela postagem.
     * @return O número de usuários que curtiram o post.
     */
    int quantidadeDeCurtidas() const;

    /**
     * @brief Adiciona um comentário diretamente ao post (compatibilidade com testes).
     * @param c O objeto do comentário a ser adicionado.
     */
    void adicionarComentario(const Comentario& c);

    /**
     * @brief Lista todos os comentários adicionados diretamente a este post (compatibilidade com testes).
     * @return Vetor contendo os comentários associados.
     */
    std::vector<Comentario> listarComentarios() const;

    /**
     * @name Getters
     * @brief Métodos de acesso para leitura das dados da postagem.
     * @{
     */
    int getId() const;
    int getIdAutor() const;
    int getIdComunidade() const;
    std::string getConteudo() const;
    std::vector<int> getIdsCurtidas() const;
    /** @} */

    /**
     * @name Setters (Persistência)
     * @brief Métodos utilizados exclusivamente pelo GerenciadorCSV para carregar curtidas.
     * @{
     */
    void setIdsCurtidas(const std::vector<int>& ids);
    /** @} */
};

#endif