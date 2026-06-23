#include "domain/armazenamento.hpp"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace {

constexpr const char *DATA_DIR = "data";

std::string caminhoCsv(const char *nomeArquivo) { return std::string(DATA_DIR) + "/" + nomeArquivo; }

void garantirDiretorioDados() { std::filesystem::create_directories(DATA_DIR); }

} // namespace

Armazenamento::Armazenamento() : emailLogado(""), idPerfilLogado(0) {
    usuarios.reserve(1000);
    perfis.reserve(1000);
    comunidades.reserve(1000);
    posts.reserve(1000);
    comentarios.reserve(1000);
}

bool Armazenamento::senhaSegura(const std::string &senha) const {
    if (senha.length() < 8)
        return false;
    bool temDigito = false;
    for (char c : senha) {
        if (std::isdigit(static_cast<unsigned char>(c)))
            temDigito = true;
    }
    return temDigito;
}

const std::vector<Perfil> &Armazenamento::listarPerfis() const { return perfis; }
void Armazenamento::criarPerfil(const Perfil &p) { perfis.push_back(p); }

const std::vector<Comunidade> &Armazenamento::listarComunidade() const { return comunidades; }
void Armazenamento::criarComunidade(const Comunidade &c) { comunidades.push_back(c); }

void Armazenamento::carregarDados() {
    usuarios = GerenciadorCSV::carregarUsuarios(caminhoCsv("usuarios.csv"));
    perfis = GerenciadorCSV::carregarPerfis(caminhoCsv("perfis.csv"));
    comunidades = GerenciadorCSV::carregarComunidades(caminhoCsv("comunidades.csv"));
    posts = GerenciadorCSV::carregarPosts(caminhoCsv("posts.csv"));
    comentarios = GerenciadorCSV::carregarComentarios(caminhoCsv("comentarios.csv"));

    for (const auto &p : perfis)
        if (p.getId() >= proxIdPerfil)
            proxIdPerfil = p.getId() + 1;
    for (const auto &c : comunidades)
        if (c.getId() >= proxIdComunidade)
            proxIdComunidade = c.getId() + 1;
    for (const auto &p : posts)
        if (p.getId() >= proxIdPost)
            proxIdPost = p.getId() + 1;
    for (const auto &c : comentarios)
        if (c.getId() >= proxIdComentario)
            proxIdComentario = c.getId() + 1;
}

void Armazenamento::salvarDados() {
    garantirDiretorioDados();
    GerenciadorCSV::salvarUsuarios(usuarios, caminhoCsv("usuarios.csv"));
    GerenciadorCSV::salvarPerfis(perfis, caminhoCsv("perfis.csv"));
    GerenciadorCSV::salvarComunidades(comunidades, caminhoCsv("comunidades.csv"));
    GerenciadorCSV::salvarPosts(posts, caminhoCsv("posts.csv"));
    GerenciadorCSV::salvarComentarios(comentarios, caminhoCsv("comentarios.csv"));
}

bool Armazenamento::emailUnico(const std::string &email) {
    for (const auto &u : usuarios)
        if (u.getEmail() == email)
            return false;
    return true;
}

bool Armazenamento::nomeUsuarioUnico(const std::string &nome) {
    for (const auto &u : usuarios)
        if (u.getNome() == nome)
            return false;
    return true;
}

bool Armazenamento::fazerLogin(const std::string &email, const std::string &senha) {
    for (const auto &u : usuarios) {
        if (u.fazerLogin(email, senha)) {
            for (const auto &p : perfis) {
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
void Armazenamento::deslogar() {
    emailLogado = "";
    idPerfilLogado = 0;
}
int Armazenamento::getIdPerfilLogado() const { return idPerfilLogado; }

void Armazenamento::criarUsuarioEPerfil(std::string email, std::string senha, std::string nome) {
    if (nome.empty()) {
        throw std::invalid_argument("O nome de usuario nao pode ser vazio.");
    }
    if (senha.length() < 8) {
        throw std::invalid_argument("A senha deve ter no minimo 8 caracteres.");
    }
    if (!emailUnico(email)) {
        throw std::invalid_argument("Este email ja esta em uso.");
    }
    if (!nomeUsuarioUnico(nome)) {
        throw std::invalid_argument("Este nome de usuario ja existe.");
    }
    if (email.find('@') == std::string::npos) {
        throw std::invalid_argument("Formato de email invalido. Deve conter '@'.");
    }
    int idNovo = proxIdPerfil++;
    usuarios.push_back(Usuario(idNovo, email, senha, nome));
    perfis.push_back(Perfil(idNovo, nome, "", "", "", 0));
}

void Armazenamento::criarPost(std::string texto, int idComunidade) {
    if (texto.empty()) {
        throw std::invalid_argument("O conteudo do post nao pode ser vazio.");
    }
    if (idPerfilLogado > 0)
        posts.push_back(Post(proxIdPost++, idPerfilLogado, idComunidade, texto));
}

void Armazenamento::criarComunidade(std::string nome, std::string descricao) {
    if (nome.empty()) {
        throw std::invalid_argument("O nome da comunidade nao pode ser vazio.");
    }
    if (idPerfilLogado > 0) {
        Comunidade comunidade(proxIdComunidade++, nome, descricao, idPerfilLogado);
        comunidades.push_back(comunidade);
        Perfil *eu = getPerfil(idPerfilLogado);
        comunidades.back().entrarComunidade(idPerfilLogado);
        if (eu) {
            eu->entrarComunidade(proxIdComunidade - 1);
        } else {
            throw std::runtime_error("Perfil logado nao encontrado ao criar comunidade.");
        }
    }
}

void Armazenamento::criarComentarioGlobal(int idPost, int idAutor, std::string texto) {
    if (texto.empty()) {
        throw std::invalid_argument("O conteudo do comentario nao pode ser vazio.");
    }
    comentarios.push_back(Comentario(proxIdComentario++, idPost, idAutor, std::move(texto)));
}

Perfil *Armazenamento::getPerfil(int id) {
    return const_cast<Perfil *>(static_cast<const Armazenamento *>(this)->getPerfil(id));
}

const Perfil *Armazenamento::getPerfil(int id) const {
    for (const auto &p : perfis) {
        if (p.getId() == id)
            return &p;
    }
    return nullptr;
}

Usuario *Armazenamento::getUsuario(const std::string &email) {
    return const_cast<Usuario *>(static_cast<const Armazenamento *>(this)->getUsuario(email));
}

const Usuario *Armazenamento::getUsuario(const std::string &email) const {
    for (const auto &u : usuarios) {
        if (u.getEmail() == email)
            return &u;
    }
    return nullptr;
}

Comunidade *Armazenamento::getComunidade(int id) {
    return const_cast<Comunidade *>(static_cast<const Armazenamento *>(this)->getComunidade(id));
}

const Comunidade *Armazenamento::getComunidade(int id) const {
    for (const auto &c : comunidades) {
        if (c.getId() == id)
            return &c;
    }
    return nullptr;
}

Post *Armazenamento::getPostMutavel(int id) { return const_cast<Post *>(getPost(id)); }

const Post *Armazenamento::getPost(int id) const {
    for (const auto &p : posts) {
        if (p.getId() == id)
            return &p;
    }
    return nullptr;
}

std::vector<Post> &Armazenamento::getTodosPostsMutavel() { return posts; }
std::vector<Comentario> &Armazenamento::getTodosComentariosMutavel() { return comentarios; }
const std::vector<Perfil> &Armazenamento::getTodosPerfis() const { return perfis; }
const std::vector<Comunidade> &Armazenamento::getTodasComunidades() const { return comunidades; }
const std::vector<Post> &Armazenamento::getTodosPosts() const { return posts; }