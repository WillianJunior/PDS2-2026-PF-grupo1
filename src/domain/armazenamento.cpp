#include "domain/armazenamento.hpp"
#include <filesystem>
#include <iostream>

namespace {
constexpr const char *DATA_DIR = "data";
std::string caminhoCsv(const char *nomeArquivo) { return std::string(DATA_DIR) + "/" + nomeArquivo; }
void garantirDiretorioDados() { std::filesystem::create_directories(DATA_DIR); }
} // namespace

Armazenamento::Armazenamento() {
    usuarios.reserve(1000);
    perfis.reserve(1000);
    comunidades.reserve(1000);
    posts.reserve(1000);
    comentarios.reserve(1000);
}

void Armazenamento::carregarDados() {
    usuarios = GerenciadorCSV::carregarUsuarios(caminhoCsv("usuarios.csv"));
    perfis = GerenciadorCSV::carregarPerfis(caminhoCsv("perfis.csv"));
    comunidades = GerenciadorCSV::carregarComunidades(caminhoCsv("comunidades.csv"));
    posts = GerenciadorCSV::carregarPosts(caminhoCsv("posts.csv"));
    comentarios = GerenciadorCSV::carregarComentarios(caminhoCsv("comentarios.csv"));

    for (const auto &p : perfis)
        if (p.getId() >= proxIdPerfil) proxIdPerfil = p.getId() + 1;
    for (const auto &c : comunidades)
        if (c.getId() >= proxIdComunidade) proxIdComunidade = c.getId() + 1;
    for (const auto &p : posts)
        if (p.getId() >= proxIdPost) proxIdPost = p.getId() + 1;
    for (const auto &c : comentarios)
        if (c.getId() >= proxIdComentario) proxIdComentario = c.getId() + 1;
}

void Armazenamento::salvarDados() {
    garantirDiretorioDados();
    GerenciadorCSV::salvarUsuarios(usuarios, caminhoCsv("usuarios.csv"));
    GerenciadorCSV::salvarPerfis(perfis, caminhoCsv("perfis.csv"));
    GerenciadorCSV::salvarComunidades(comunidades, caminhoCsv("comunidades.csv"));
    GerenciadorCSV::salvarPosts(posts, caminhoCsv("posts.csv"));
    GerenciadorCSV::salvarComentarios(comentarios, caminhoCsv("comentarios.csv"));
}

int Armazenamento::gerarIdPerfil() { return proxIdPerfil++; }
int Armazenamento::gerarIdComunidade() { return proxIdComunidade++; }
int Armazenamento::gerarIdPost() { return proxIdPost++; }
int Armazenamento::gerarIdComentario() { return proxIdComentario++; }

void Armazenamento::adicionarUsuario(const Usuario& u) { usuarios.push_back(u); }
void Armazenamento::adicionarPerfil(const Perfil& p) { perfis.push_back(p); }
void Armazenamento::adicionarComunidade(const Comunidade& c) { comunidades.push_back(c); }
void Armazenamento::adicionarPost(const Post& p) { posts.push_back(p); }
void Armazenamento::adicionarComentario(const Comentario& c) { comentarios.push_back(c); }

Perfil *Armazenamento::getPerfil(int id) {
    return const_cast<Perfil *>(static_cast<const Armazenamento *>(this)->getPerfil(id));
}

const Perfil *Armazenamento::getPerfil(int id) const {
    for (const auto &p : perfis) {
        if (p.getId() == id) return &p;
    }
    return nullptr;
}

Usuario *Armazenamento::getUsuario(const std::string &email) {
    return const_cast<Usuario *>(static_cast<const Armazenamento *>(this)->getUsuario(email));
}

const Usuario *Armazenamento::getUsuario(const std::string &email) const {
    for (const auto &u : usuarios) {
        if (u.getEmail() == email) return &u;
    }
    return nullptr;
}

Comunidade *Armazenamento::getComunidade(int id) {
    return const_cast<Comunidade *>(static_cast<const Armazenamento *>(this)->getComunidade(id));
}

const Comunidade *Armazenamento::getComunidade(int id) const {
    for (const auto &c : comunidades) {
        if (c.getId() == id) return &c;
    }
    return nullptr;
}

Post *Armazenamento::getPostMutavel(int id) { return const_cast<Post *>(getPost(id)); }
const Post *Armazenamento::getPost(int id) const {
    for (const auto &p : posts) {
        if (p.getId() == id) return &p;
    }
    return nullptr;
}

const std::vector<Usuario> &Armazenamento::getTodosUsuarios() const { return usuarios; }
const std::vector<Perfil> &Armazenamento::getTodosPerfis() const { return perfis; }
const std::vector<Comunidade> &Armazenamento::getTodasComunidades() const { return comunidades; }
const std::vector<Post> &Armazenamento::getTodosPosts() const { return posts; }
std::vector<Post> &Armazenamento::getTodosPostsMutavel() { return posts; }
std::vector<Comentario> &Armazenamento::getTodosComentariosMutavel() { return comentarios; }

const std::vector<Perfil> &Armazenamento::listarPerfis() const { return perfis; }
const std::vector<Comunidade> &Armazenamento::listarComunidade() const { return comunidades; }