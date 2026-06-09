#ifndef COMENTARIO_HPP
#define COMENTARIO_HPP
#include <string>
#include <vector>
#include "perfil.hpp"

/**
 * @class Comentario
 * @brief Classe que representa um comentário feito em uma postagem.
 * * Vincula-se a um post específico através de IDs e gerencia suas próprias curtidas.
 */
class Comentario {
private:
    int id;
    int idPost;
    int idAutor;
    std::string texto;
    std::vector<int> idsCurtidas;

public:
    /**
     * @brief Constrói um novo comentário completo.
     * @param id O identificador único numérico do comentário.
     * @param idPost O ID do post que está recebendo este comentário.
     * @param idAutor O ID do perfil que escreveu o comentário.
     * @param texto O texto do comentário.
     */
    Comentario(int id, int idPost, int idAutor, std::string texto);

    /**
     * @brief Constrói um novo comentário associado a uma instância de Perfil (compatibilidade com testes).
     * @param texto O conteúdo de texto do comentário.
     * @param autor Referência constante ao perfil do autor.
     */
    Comentario(std::string texto, const Perfil& autor);

    /**
     * @brief Registra ou remove a curtida de um usuário no comentário (efeito Toggle).
     * @param idUsuario O identificador do perfil do usuário que interagiu.
     */
    void curtir(int idUsuario);

    /**
     * @brief Retorna o total de curtidas que este comentário recebeu.
     * @return O número de curtidas.
     */
    int quantidadeDeCurtidas() const;

    /**
     * @name Getters
     * @brief Métodos de acesso para leitura das propriedades do comentário.
     * @{
     */
    int getId() const;
    int getIdPost() const;
    int idAutorObter() const; 
    int getIdAutor() const;
    std::string getTexto() const;
    std::vector<int> getIdsCurtidas() const;
    /** @} */

    /**
     * @name Setters (Persistência)
     * @brief Métodos utilizados exclusivamente pelo GerenciadorCSV para carregar as curtidas.
     * @{
     */
    void setIdsCurtidas(const std::vector<int>& ids);
    /** @} */
};

#endif