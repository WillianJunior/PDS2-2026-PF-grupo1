#ifndef POST_HPP
#define POST_HPP
#include <string>
#include <vector>
#include <set>
#include "comentario.hpp"
#include "perfil.hpp"

/**
 * @brief Classe que representa uma publicação no sistema.
 * * Um post contém texto, uma lista de quem o curtiu, seu autor, 
 * e uma coleção de comentários associados a ele.
 */

class Post {

private:

    std::string texto; 
    std::set<int> idsCurtidas;
    int idAutor;
    std::vector<Comentario> comentarios;

public:

    /**
     * @brief Constrói uma nova postagem.
     * @param texto O conteúdo principal da postagem.
     * @param idAutor O identificador do usuário que a criou.
     */

    Post(std::string texto, int idAutor);

    /**
     * @brief Anexa um novo comentário à publicação.
     * @param comentario O objeto Comentario a ser adicionado.
     */

    void adicionarComentario(Comentario comentario);

    /**
     * @brief Retorna todos os comentários feitos nesta postagem.
     * @return Um vetor contendo os comentários.
     */

    std::vector<Comentario> listarComentarios();

    /**
     * @brief Retorna o total de curtidas recebidas pela postagem.
     * @return O número de curtidas.
     */

    int quantidadeDeCurtidas();

    /**
     * @brief Registra a curtida de um usuário na postagem.
     * @param idUsuario O identificador do usuário que curtiu.
     */

    void curtir(int idUsuario);

};

#endif