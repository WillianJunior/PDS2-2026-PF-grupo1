#ifndef PERFIL_HPP
#define PERFIL_HPP
#include <string>
#include <vector>

/**
 * @class Perfil
 * @brief Classe que armazena os dados públicos, acadêmicos e sociais de um usuário.
 * * Representa a identidade do usuário dentro da rede educacional. É responsável 
 * por gerenciar atributos visíveis (como nome, curso e biografia) e as relações 
 * sociais (quem ele segue, seus seguidores e as comunidades em que ingressou).
 */
class Perfil {
private:
    int id;
    std::string nome;
    std::string descricao;
    std::string curso;
    std::string instituicao;
    int periodo;

    std::vector<int> idsSeguidores;
    std::vector<int> idsSeguidos;
    std::vector<int> idsComunidadesQueFazParte;

public:
    Perfil(int id, std::string nome, std::string descricao, 
           std::string curso, std::string instituicao, int periodo);

    Perfil(std::string curso, std::string instituicao, int periodo);

    void seguir(int idPerfil);
    void deixarDeSeguir(int idPerfil);
    void adicionarSeguidor(int idPerfil);
    void removerSeguidor(int idPerfil);
    void entrarComunidade(int idComunidade);
    void sairComunidade(int idComunidade);

    const std::vector<int>& listarIdSeguidores() const;
    const std::vector<int>& listarIdSeguidos() const;

    /**
     * @name Getters
     */
    int getId() const;
    const std::string& getNome() const;
    const std::string& getDescricao() const;
    const std::string& getCurso() const;
    const std::string& getInstituicao() const;
    int getPeriodo() const;
    const std::vector<int>& getIdsSeguidores() const;
    const std::vector<int>& getIdsSeguidos() const;
    const std::vector<int>& getIdsComunidades() const;

    /**
     * @name Setters (Edição de Perfil)
     */
    void setCurso(const std::string& c);
    void setInstituicao(const std::string& i);
    void setDescricao(const std::string& d);
    void setPeriodo(int p);

    /**
     * @name Setters (Persistência)
     */
    void setIdsSeguidores(const std::vector<int>& ids);
    void setIdsSeguidos(const std::vector<int>& ids);
    void setIdsComunidades(const std::vector<int>& ids);
};

#endif