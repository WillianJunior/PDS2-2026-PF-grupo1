#ifndef COMENTARIO_HPP
#define COMENTARIO_HPP
#include <string>
#include <set>
#include "perfil.hpp"

/**
 * @brief Classe que representa um comentário feito em uma postagem.
 */

class Comentario {

private:
    
    std::string texto;
    Perfil autor;
    std::set<int> idsCurtidas;

public:

    /**
     * @brief Constrói um novo comentário.
     * @param texto O conteúdo em texto do comentário.
     * @param autor O objeto Perfil representando quem escreveu o comentário.
     */

    Comentario(std::string texto, Perfil autor);

    /**
     * @brief Registra uma curtida no comentário feita por um usuário.
     * @param idUsuario O identificador do usuário que curtiu.
     */

    void curtir(int idUsuario);

    /**
     * @brief Retorna o total de curtidas que este comentário recebeu.
     * @return O número de curtidas.
     */
    
    int quantidadeDeCurtidas();

};

#endif