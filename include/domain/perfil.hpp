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

    // 🔹 Atributos básicos para suportar os getters usados no código
    int id;
    std::string nome;
    std::string descricao;
    
public:

    Perfil();
    Perfil(std::string curso, std::string instituicao, int periodo);

    void seguir(int idPerfil);
    void deixarDeSeguir(int idPerfil);

    std::vector<int> listarIdSeguidores();
    std::vector<int> listarIdSeguidos();

    // Getters principais
    int getId() const;
    std::string getNome() const;
    std::string getDescricao() const;

    std::string getCurso() const;
    std::string getInstituicao() const;
    int getPeriodo() const;
    std::vector<int> getIdsComunidades() const;
};

#endif
