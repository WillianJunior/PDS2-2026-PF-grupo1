#ifndef POST_HPP
#define POST_HPP
#include <string>
#include <vector>

/**
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

public:
    /**
     * @brief Constrói uma nova postagem.
     * @param id O identificador único numérico da postagem.
     * @param idAutor O identificador do perfil do usuário que a criou.
     * @param idComunidade O identificador da comunidade (0 se for Feed Geral).
     * @param texto O conteúdo em texto da publicação.
     */
    Post(int id, int idAutor, int idComunidade, std::string texto);

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
     * @name Getters
     * @brief Métodos de acesso para leitura dos dados da postagem.
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
