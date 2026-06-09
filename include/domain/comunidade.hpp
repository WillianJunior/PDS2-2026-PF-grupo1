#ifndef COMUNIDADE_HPP
#define COMUNIDADE_HPP
#include <string>
#include <vector>
#include "post.hpp"

/**
 * @class Comunidade
 * @brief Classe que representa um grupo ou fórum dentro da rede social.
 * * Comunidades agregam usuários (membros) em torno de um tema comum.
 * Elas possuem um administrador responsável e regras de permissão para postagens.
 */
class Comunidade {
private:
    int id;
    std::string nome;
    std::string descricao;
    int idAdministrador;
    std::vector<int> idsMembros;
    std::vector<Post> postsTestes; // Armazena publicações locais exigidas pelos testes

public:
    /**
     * @brief Constrói uma nova Comunidade completa.
     * @param id O identificador único numérico da comunidade.
     * @param nome O nome de exibição do grupo.
     * @param descricao O texto explicativo sobre o propósito do grupo.
     * @param idAdministrador O ID do perfil do usuário criador/dono da comunidade.
     */
    Comunidade(int id, std::string nome, std::string descricao, int idAdministrador);

    /**
     * @brief Constrói uma nova Comunidade simplificada (compatibilidade com testes).
     * @param nome O nome do grupo.
     * @param idAdministrador O ID do perfil do administrador.
     */
    Comunidade(std::string nome, int idAdministrador);

    /**
     * @brief Adiciona o ID de um perfil à lista de membros da comunidade.
     * @param idPerfil O identificador do usuário que está ingressando.
     */
    void adicionarMembro(int idPerfil);

    /**
     * @brief Remove o ID de um perfil da lista de membros.
     * @param idPerfil O identificador do usuário que está deixando a comunidade.
     */
    void removerMembro(int idPerfil);

    /**
     * @brief Inscreve um perfil na comunidade (compatibilidade com testes).
     * @param idPerfil O identificador do usuário que está entrando.
     */
    void entrarComunidade(int idPerfil);

    /**
     * @brief Verifica se um usuário tem permissão para realizar publicações na comunidade.
     * @param idPerfil O identificador do usuário que está tentando postar.
     * @return true se o usuário for o admin ou um membro ativo, false caso contrário.
     */
    bool podePublicar(int idPerfil) const;

    /**
     * @brief Retorna a lista de posts publicados localmente na comunidade (compatibilidade com testes).
     * @return Vetor de objetos Post.
     */
    std::vector<Post> posts() const;

    /**
     * @brief Busca posts internamente por palavra-chave (compatibilidade com testes).
     * @param termo O termo textual de busca.
     * @return Vetor de objetos Post que contêm o termo.
     */
    std::vector<Post> buscarPosts(const std::string& termo) const;

    /**
     * @brief Exibe na tela os membros da comunidade (compatibilidade com testes).
     */
    void exibirMembrosComunidade() const;

    /**
     * @name Getters
     * @brief Métodos de acesso para leitura das propriedades da comunidade.
     * @{
     */
    int getId() const;
    std::string getNome() const;
    std::string getDescricao() const;
    int getIdAdministrador() const;
    std::vector<int> getIdsMembros() const;
    /** @} */

    /**
     * @name Setters (Persistência)
     * @brief Métodos utilizados exclusivamente pelo GerenciadorCSV para carregar os membros.
     * @{
     */
    void setIdsMembros(const std::vector<int>& ids);
    /** @} */
};

#endif