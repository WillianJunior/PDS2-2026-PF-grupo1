#ifndef ARMAZENAMENTO_HPP
#define ARMAZENAMENTO_HPP
#include "perfil.hpp"
#include "feed.hpp"
#include "comunidade.hpp"

class Armazenamento
{
private:
    std::vector<Perfil> perfis;
    std::vector<Comunidade> comunidades;
    Perfil usuarioLogado;
public:
    bool emailUnico(std::string email);
    bool senhaSegura(std::string senha);
    void mensagemSucessoErro();
    Perfil getUsuarioLogado();
    void criarPerfil(Perfil perfil);
    Perfil deletarPerfil(int id);
    std::vector<Perfil> listarPerfis();
    void criarComunidade(Comunidade comunidade);
    Comunidade deletarComunidade(int id);
    std::vector<Comunidade> listarComunidade();
};
#endif ARMAZENAMENTO_HPP