#include "domain/sistema.hpp"
#include <algorithm>
#include <cctype>
#include <stdexcept>

Sistema::Sistema(Armazenamento& banco) : db(banco), emailLogado(""), idPerfilLogado(0) {}

bool Sistema::senhaSegura(const std::string &senha) const {
    if (senha.length() < 8) return false;
    bool temDigito = false;
    for (char c : senha) {
        if (std::isdigit(static_cast<unsigned char>(c))) temDigito = true;
    }
    return temDigito;
}

bool Sistema::emailUnico(const std::string &email) const {
    for (const auto &u : db.getTodosUsuarios()) {
        if (u.getEmail() == email) return false;
    }
    return true;
}

bool Sistema::nomeUsuarioUnico(const std::string &nome) const {
    for (const auto &u : db.getTodosUsuarios()) {
        if (u.getNome() == nome) return false;
    }
    return true;
}

bool Sistema::fazerLogin(const std::string &email, const std::string &senha) {
    for (const auto &u : db.getTodosUsuarios()) {
        if (u.fazerLogin(email, senha)) {
            for (const auto &p : db.getTodosPerfis()) {
                if (p.getId() == u.getId()) {
                    emailLogado = email;
                    idPerfilLogado = p.getId();
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}

void Sistema::deslogar() {
    emailLogado = "";
    idPerfilLogado = 0;
}

int Sistema::getIdPerfilLogado() const { return idPerfilLogado; }
std::string Sistema::getEmailLogado() const { return emailLogado; }

void Sistema::criarUsuarioEPerfil(std::string email, std::string senha, std::string nome) {
    if (nome.empty()) throw std::invalid_argument("O nome de usuario nao pode ser vazio.");
    if (senha.length() < 8) throw std::invalid_argument("A senha deve ter no minimo 8 caracteres.");
    if (!emailUnico(email)) throw std::invalid_argument("Este email ja esta em uso.");
    if (!nomeUsuarioUnico(nome)) throw std::invalid_argument("Este nome de usuario ja existe.");
    if (email.find('@') == std::string::npos) throw std::invalid_argument("Formato de email invalido. Deve conter '@'.");

    int idNovo = db.gerarIdPerfil();
    db.adicionarUsuario(Usuario(idNovo, email, senha, nome));
    db.adicionarPerfil(Perfil(idNovo, nome, "", "", "", 0));
}

void Sistema::criarPost(std::string texto, int idComunidade) {
    if (texto.empty()) throw std::invalid_argument("O conteudo do post nao pode ser vazio.");
    if (idPerfilLogado > 0) {
        db.adicionarPost(Post(db.gerarIdPost(), idPerfilLogado, idComunidade, texto));
    }
}

void Sistema::criarComunidade(std::string nome, std::string descricao) {
    if (nome.empty()) throw std::invalid_argument("O nome da comunidade nao pode ser vazio.");
    if (idPerfilLogado > 0) {
        int novoId = db.gerarIdComunidade();
        Comunidade comunidade(novoId, nome, descricao, idPerfilLogado);
        
        comunidade.entrarComunidade(idPerfilLogado);
        db.adicionarComunidade(comunidade);

        Perfil *eu = db.getPerfil(idPerfilLogado);
        if (eu) {
            eu->entrarComunidade(novoId);
        } else {
            throw std::runtime_error("Perfil logado nao encontrado ao criar comunidade.");
        }
    }
}

void Sistema::criarComentarioGlobal(int idPost, int idAutor, std::string texto) {
    if (texto.empty()) throw std::invalid_argument("O conteudo do comentario nao pode ser vazio.");
    db.adicionarComentario(Comentario(db.gerarIdComentario(), idPost, idAutor, std::move(texto)));
}