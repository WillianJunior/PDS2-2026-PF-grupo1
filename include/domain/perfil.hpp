#ifndef PERFIL_HPP
#define PERFIL_HPP
#include <string>
#include <vector>

/**
 * @brief Classe que armazena os dados acadêmicos e sociais de um usuário.
 * * Representa a identidade pública do usuário dentro da rede educacional, 
 * controlando quem ele segue, seus seguidores e as comunidades das quais participa.
 */

class Perfil {

private:

    std::string curso;
    std::string instituicao;
    int periodo;

    std::vector<int> idsSeguidores;
    std::vector<int> idsSeguidos;
    std::vector<int> idsComunidadesQueFazParte;
    
public:

    /**
     * @brief Construtor padrão do perfil.
     */

    Perfil();

    /**
     * @brief Constrói um perfil com as informações acadêmicas.
     * @param curso Nome do curso do aluno.
     * @param instituicao Instituição de ensino à qual está vinculado.
     * @param periodo Período ou semestre atual do aluno.
     */

    Perfil(std::string curso, std::string instituicao, int periodo);

    /**
     * @brief Adiciona um perfil à lista de seguidos.
     * @param idPerfil Identificador do usuário que se deseja seguir.
     */

    void seguir(int idPerfil);

    /**
     * @brief Remove um perfil da lista de seguidos.
     * @param idPerfil Identificador do usuário que se deseja deixar de seguir.
     */

    void deixarDeSeguir(int idPerfil);

    /**
     * @brief Retorna os identificadores dos perfis que seguem este usuário.
     * @return Um vetor com os IDs dos seguidores.
     */

    std::vector<int> listarIdSeguidores();

    /**
     * @brief Retorna os identificadores dos perfis que este usuário segue.
     * @return Um vetor com os IDs dos usuários seguidos.
     */

    std::vector<int> listarIdSeguidos();

};

#endif