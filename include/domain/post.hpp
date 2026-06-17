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
    Post(int id, int idAutor, int idComunidade, std::string texto);
    Post(std::string texto, int idAutor);

    void curtir(int idUsuario);
    int quantidadeDeCurtidas() const;

    void adicionarComentario(const Comentario& c);

    /**
     * ✅ Agora retorna referência
     */
    const std::vector<Comentario>& listarComentarios() const;

    /**
     * @name Getters
     */
    int getId() const;
    int getIdAutor() const;
    int getIdComunidade() const;
    const std::string& getConteudo() const;
    const std::vector<int>& getIdsCurtidas() const;

    /**
     * @name Setters (Persistência)
     */
    void setIdsCurtidas(const std::vector<int>& ids);
};

#endif