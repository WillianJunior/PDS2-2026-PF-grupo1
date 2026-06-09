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
    std::string emailUsuario; 
    std::string nome;
    std::string descricao;
    std::string curso;
    std::string instituicao;
    int periodo;

    std::vector<int> idsSeguidores;
    std::vector<int> idsSeguidos;
    std::vector<int> idsComunidadesQueFazParte;

public:
    /**
     * @brief Constrói um novo Perfil de usuário completo.
     * @param id O identificador único numérico do perfil.
     * @param emailUsuario O e-mail que liga este perfil ao seu Usuário correspondente.
     * @param nome O nome de exibição público.
     * @param descricao Uma breve biografia do perfil.
     * @param curso O curso acadêmico que o aluno frequenta.
     * @param instituicao A faculdade ou universidade.
     * @param periodo O período ou semestre atual.
     */
    Perfil(int id, std::string emailUsuario, std::string nome, std::string descricao, 
           std::string curso, std::string instituicao, int periodo);

    /**
     * @brief Constrói um novo Perfil simplificado (utilizado principalmente em testes).
     * @param curso O curso acadêmico.
     * @param instituicao A faculdade ou universidade.
     * @param periodo O período ou semestre atual.
     */
    Perfil(std::string curso, std::string instituicao, int periodo);

    /**
     * @brief Adiciona o ID de outro perfil à lista de seguidos.
     * @param idPerfil O identificador do perfil que será seguido.
     */
    void seguir(int idPerfil);

    /**
     * @brief Remove o ID de um perfil da lista de seguidos.
     * @param idPerfil O identificador do perfil que deixará de ser seguido.
     */
    void deixarDeSeguir(int idPerfil);

    /**
     * @brief Adiciona o ID de uma comunidade à lista de comunidades do usuário.
     * @param idComunidade O identificador da comunidade na qual o usuário está entrando.
     */
    void entrarComunidade(int idComunidade);

    /**
     * @brief Remove o ID de uma comunidade da lista do usuário.
     * @param idComunidade O identificador da comunidade da qual o usuário está saindo.
     */
    void sairComunidade(int idComunidade);

    /**
     * @brief Retorna a lista de IDs dos seguidores do perfil (compatibilidade com testes).
     * @return Vetor de inteiros contendo os IDs dos seguidores.
     */
    std::vector<int> listarIdSeguidores() const;

    /**
     * @brief Retorna a lista de IDs dos perfis que este usuário segue (compatibilidade com testes).
     * @return Vetor de inteiros contendo os IDs dos perfis seguidos.
     */
    std::vector<int> listarIdSeguidos() const;

    /**
     * @name Getters
     * @brief Métodos de acesso para leitura dos dados do perfil e suas relações.
     * @{
     */
    int getId() const;
    std::string getEmailUsuario() const;
    std::string getNome() const;
    std::string getDescricao() const;
    std::string getCurso() const;
    std::string getInstituicao() const;
    int getPeriodo() const;
    std::vector<int> getIdsSeguidores() const;
    std::vector<int> getIdsSeguidos() const;
    std::vector<int> getIdsComunidades() const;
    /** @} */

    /**
     * @name Setters (Edição de Perfil)
     * @{
     */
    void setCurso(const std::string& c);
    void setInstituicao(const std::string& i);
    void setDescricao(const std::string& d);
    void setPeriodo(int p);
    /** @} */

    /**
     * @name Setters (Persistência)
     * @brief Métodos utilizados exclusivamente pelo GerenciadorCSV para reconstruir as listas.
     * @{
     */
    void setIdsSeguidores(const std::vector<int>& ids);
    void setIdsSeguidos(const std::vector<int>& ids);
    void setIdsComunidades(const std::vector<int>& ids);
    /** @} */
};

#endif