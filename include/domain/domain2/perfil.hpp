#ifndef PERFIL_HPP
#define PERFIL_HPP
#include <string>
#include <vector>

class Perfil {

private:
    
    std::string senha;
    std::string email;
    std::string nomeUser;

    std::string curso;
    std::string instituicao;
    int periodo;

    std::vector<Perfil> seguidores;
    std::vector<Perfil> seguindo;

public:

    Perfil(std::string email, std::string senha, std::string nomeUser, std::string curso, std::string instituicao, int periodo);

    bool alterarSenha(std::string senhaAtual, std::string novaSenha);
    bool alterarEmail(std::string senhaAtual, std::string novoEmail);;
    bool fazerLogin(std::string email, std::string senha);
    
    std::string getEmail();
    std::string getNome();

    void seguir(Perfil& perfil);
    void deixarDeSeguir(Perfil& perfil);
    void listarSeguidores();
    void listarSeguindo();

};

#endif