#ifndef COMUNIDADE_HPP
#define COMUNIDADE_HPP
#include <string>
#include <vector>
#include "post.hpp"

/**
 * @file comunidade.hpp
 * @brief Declaração da classe Comunidade.
 */

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

public:
    /**
     * @brief Construtor completo para instanciar uma Comunidade recuperada do banco de dados.
     * @param id Identificador único da comunidade.
     * @param nome Nome de exibição da comunidade.
     * @param descricao Descrição sobre o propósito do grupo.
     * @param idAdministrador ID do perfil do usuário criador/administrador.
     */
    Comunidade(int id, std::string nome, std::string descricao, int idAdministrador);

    /**
     * @brief Construtor para criação de uma nova comunidade no sistema.
     * @param nome Nome da nova comunidade.
     * @param idAdministrador ID do perfil que está criando e vai administrar o grupo.
     */
    Comunidade(std::string nome, int idAdministrador);

    /**
     * @brief Adiciona o ID de um perfil à lista de membros da comunidade.
     * @param idPerfil Identificador do novo membro.
     */
    void adicionarMembro(int idPerfil);

    /**
     * @brief Remove o ID de um perfil da lista de membros da comunidade.
     * @param idPerfil Identificador do membro a ser removido.
     */
    void removerMembro(int idPerfil);

    /**
     * @brief Insere um perfil na comunidade (encapsula lógica adicional de entrada, se houver).
     * @param idPerfil Identificador do perfil ingressando.
     */
    void entrarComunidade(int idPerfil);

    /**
     * @brief Valida se um usuário tem permissão para criar posts nesta comunidade.
     * @param idPerfil ID do perfil a ser verificado.
     * @return true se o usuário for membro ou administrador, false caso contrário.
     */
    bool podePublicar(int idPerfil) const;

    /**
     * @brief Exibe no console a lista atual de membros (usado para depuração ou views em texto).
     */
    void exibirMembrosComunidade() const;

    /** @name Getters */
    /** @{ */
    
    /** @brief Retorna o ID da comunidade. */
    int getId() const;
    
    /** @brief Retorna o nome da comunidade. */
    const std::string& getNome() const;
    
    /** @brief Retorna a descrição da comunidade. */
    const std::string& getDescricao() const;
    
    /** @brief Retorna o ID do administrador. */
    int getIdAdministrador() const;
    
    /** @brief Retorna a lista de IDs de todos os membros. */
    const std::vector<int>& getIdsMembros() const;
    
    /** @} */

    /** @name Setters (Persistência) */
    /** @{ */
    
    /**
     * @brief Define a lista completa de membros de uma vez (Usado pelo GerenciadorCSV).
     * @param ids Vetor contendo os IDs dos membros.
     */
    void setIdsMembros(const std::vector<int>& ids);
    
    /** @} */
};

#endif