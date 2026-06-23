#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP
#include "domain/perfil.hpp"

/**
 * @file admin.hpp
 * @brief Declaração da classe Administrador.
 */

/**
 * @class Administrador
 * @brief Representa um perfil com privilégios elevados dentro do sistema.
 * * Herda da classe Perfil e possui permissões especiais, como a capacidade
 * de gerenciar o sistema ou atuar como administrador em comunidades.
 */
class Administrador : public Perfil {
public:
    /**
     * @brief Construtor da classe Administrador.
     * * @param id Identificador único do administrador.
     * @param nome Nome do administrador.
     * @param descricao Biografia ou descrição do perfil.
     * @param curso Curso ao qual está vinculado.
     * @param instituicao Instituição de ensino.
     * @param periodo Período (semestre) atual.
     */
    Administrador(
        int id,
        std::string nome,
        std::string descricao,
        std::string curso,
        std::string instituicao,
        int periodo
    );

    /**
     * @brief Verifica se o usuário tem permissões de gerenciamento.
     * * @return true Sempre retorna verdadeiro para objetos desta classe.
     */
    bool podeGerenciarComunidade() const override;
};

#endif