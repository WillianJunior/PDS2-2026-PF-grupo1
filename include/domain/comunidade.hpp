#ifndef COMUNIDADE_HPP
#define COMUNIDADE_HPP
#include <vector>
#include <string>
#include "post.hpp"
#include "perfil.hpp"

/**
 * @brief Classe que representa um grupo ou fórum dentro da rede social.
 * * Comunidades agregam usuários (membros) em torno de um tema comum e 
 * possuem postagens próprias.
 */

class Comunidade {

private:

    std::vector<Post> postagensComunidade;
    std::vector<int> idsMembrosComunidade;
    int idAdministrador;
    std::string nomeComunidade;

public:

    /**
     * @brief Constrói uma nova Comunidade.
     * @param nomeComunidade O nome de exibição da comunidade.
     * @param idAdministrador O identificador do perfil criador/dono da comunidade.
     */

    Comunidade(std::string nomeComunidade, int idAdministrador);

    /**
     * @brief Adiciona um novo membro à comunidade.
     * @param idPerfil O identificador do usuário que está ingressando.
     */

    void entrarComunidade(int idPerfil);

    /**
     * @brief Verifica se um usuário tem permissão para publicar nesta comunidade.
     * @param idPerfil O identificador do usuário a ser verificado.
     * @return true se o usuário puder publicar, false caso contrário.
     */

    bool podePublicar(int idPerfil);

    /**
     * @brief Exibe na tela a lista de membros que participam da comunidade.
     */

    void exibirMembrosComunidade();

    /**
     * @brief Retorna todas as postagens feitas dentro da comunidade.
     * @return Um vetor contendo as postagens.
     */

    std::vector<Post> posts();

    /**
     * @brief Busca postagens dentro da comunidade que correspondam a um termo.
     * @param termo A palavra-chave a ser pesquisada.
     * @return Um vetor de postagens que contêm o termo buscado.
     */

    std::vector<Post> buscarPosts(std::string termo);

    std::string getNomeComunidade() const;
    int getIdAdministrador() const;
    std::vector<int> getIdsMembros() const;
    std::vector<Post> getPostagens() const;
    std::string getDescricao() const; 
    std::string getNome() const; 

};
extern std::vector<Perfil> todosPerfis;

#endif