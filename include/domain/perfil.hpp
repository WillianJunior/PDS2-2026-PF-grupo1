#ifndef PERFIL_HPP
#define PERFIL_HPP
#include <string>
#include <vector>

/**
 * @file perfil.hpp
 * @brief Declaração da classe Perfil.
 */

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

    std::vector<int> idsComunidadesQueFazParte;

public:
    /**
     * @brief Construtor completo para recuperar um Perfil do banco de dados.
     * @param id ID único do perfil.
     * @param nome Nome de exibição.
     * @param descricao Biografia ou descrição pessoal.
     * @param curso Curso de graduação ou estudo.
     * @param instituicao Instituição de ensino.
     * @param periodo Período (semestre) atual.
     */
    Perfil(int id, std::string nome, std::string descricao, 
           std::string curso, std::string instituicao, int periodo);

    /**
     * @brief Construtor simplificado para edição de dados básicos.
     * @param curso Curso do usuário.
     * @param instituicao Instituição de ensino.
     * @param periodo Período (semestre).
     */
    Perfil(std::string curso, std::string instituicao, int periodo);

    /**
     * @brief Vincula o perfil a uma nova comunidade.
     * @param idComunidade O identificador da comunidade a ser ingressada.
     */
    void entrarComunidade(int idComunidade);

    /**
     * @brief Remove o vínculo do perfil com uma comunidade.
     * @param idComunidade O identificador da comunidade a ser deixada.
     */
    void sairComunidade(int idComunidade);

    /**
     * @brief Verifica se o perfil tem privilégios de gerenciamento.
     * @return false por padrão. Subclasses (como Administrador) sobrescrevem para true.
     */
    virtual bool podeGerenciarComunidade() const;
    
    /** @brief Destrutor virtual padrão. */
    virtual ~Perfil() = default;

    /** @name Getters */
    /** @{ */
    int getId() const;
    const std::string& getNome() const;
    const std::string& getDescricao() const;
    const std::string& getCurso() const;
    const std::string& getInstituicao() const;
    int getPeriodo() const;
    const std::vector<int>& getIdsComunidades() const;
    /** @} */
    
    /** @name Setters (Edição de Perfil) */
    /** @{ */
    void setCurso(const std::string& c);
    void setInstituicao(const std::string& i);
    void setDescricao(const std::string& d);
    void setPeriodo(int p);
    /** @} */

    /** @name Setters (Persistência) */
    /** @{ */
    /**
     * @brief Define a lista de comunidades do usuário (Usado ao carregar do CSV).
     * @param ids Vetor de IDs das comunidades.
     */
    void setIdsComunidades(const std::vector<int>& ids);
    /** @} */
};

#endif