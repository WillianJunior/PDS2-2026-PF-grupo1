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

public:
    Comunidade(int id, std::string nome, std::string descricao, int idAdministrador);
    Comunidade(std::string nome, int idAdministrador);

    void adicionarMembro(int idPerfil);
    void removerMembro(int idPerfil);
    void entrarComunidade(int idPerfil);

    bool podePublicar(int idPerfil) const;

    void exibirMembrosComunidade() const;

    /**
     * @name Getters
     */
    int getId() const;
    const std::string& getNome() const;
    const std::string& getDescricao() const;
    int getIdAdministrador() const;
    const std::vector<int>& getIdsMembros() const;

    /**
     * @name Setters (Persistência)
     */
    void setIdsMembros(const std::vector<int>& ids);
};

#endif
