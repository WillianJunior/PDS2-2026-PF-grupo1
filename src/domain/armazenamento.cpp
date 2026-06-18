#include "domain/armazenamento.hpp"
#include <cctype>

Armazenamento::Armazenamento() : emailLogado(""), idPerfilLogado(0) {}

bool Armazenamento::senhaSegura(const std::string& senha) const {
    if (senha.length() < 6) return false;
    bool temDigito = false;
    for (char c : senha) {
        if (std::isdigit(static_cast<unsigned char>(c))) temDigito = true;
    }
    return temDigito;
}

const std::vector<Perfil>& Armazenamento::listarPerfis() const { return perfis; }
void Armazenamento::criarPerfil(const Perfil& p) { perfis.push_back(p); }

const std::vector<Comunidade>& Armazenamento::listarComunidade() const { return comunidades; }
void Armazenamento::criarComunidade(const Comunidade& c) { comunidades.push_back(c); }

void Armazenamento::mensagemSucessoErro() const {}

void Armazenamento::carregarDados() {
    usuarios = GerenciadorCSV::carregarUsuarios("usuarios.csv");
    perfis = GerenciadorCSV::carregarPerfis("perfis.csv");
    comunidades = GerenciadorCSV::carregarComunidades("comunidades.csv");
    posts = GerenciadorCSV::carregarPosts("posts.csv");
    comentarios = GerenciadorCSV::carregarComentarios("comentarios.csv");

    for (const auto& p : perfis) if (p.getId() >= proxIdPerfil) proxIdPerfil = p.getId() + 1;
    for (const auto& c : comunidades) if (c.getId() >= proxIdComunidade) proxIdComunidade = c.getId() + 1;
    for (const auto& p : posts) if (p.getId() >= proxIdPost) proxIdPost = p.getId() + 1;
    for (const auto& c : comentarios) if (c.getId() >= proxIdComentario) proxIdComentario = c.getId() + 1;
}

void Armazenamento::salvarDados() {
    GerenciadorCSV::salvarUsuarios(usuarios, "usuarios.csv");
    GerenciadorCSV::salvarPerfis(perfis, "perfis.csv");
    GerenciadorCSV::salvarComunidades(comunidades, "comunidades.csv");
    GerenciadorCSV::salvarPosts(posts, "posts.csv");
    GerenciadorCSV::salvarComentarios(comentarios, "comentarios.csv");
}

bool Armazenamento::emailUnico(const std::string& email) {
    for (const auto& u : usuarios) if (u.getEmail() == email) return false;
    return true;
}

bool Armazenamento::nomeUsuarioUnico(const std::string& nome) {
    for (const auto& u : usuarios) if (u.getNome() == nome) return false;
    return true;
}

bool Armazenamento::fazerLogin(const std::string& email, const std::string& senha) {
    for (const auto& u : usuarios) {
        if (u.fazerLogin(email, senha)) {
            emailLogado = email;
            for (const auto& p : perfis) {
                if (p.getEmailUsuario() == email) {
                    idPerfilLogado = p.getId();
                    return true;
                }
            }
        }
    }
    return false;
}

void Armazenamento::deslogar() { emailLogado = ""; idPerfilLogado = 0; }
int Armazenamento::getIdPerfilLogado() const { return idPerfilLogado; }

void Armazenamento::criarUsuarioEPerfil(std::string email, std::string senha, std::string nome) {
    usuarios.push_back(Usuario(email, senha, nome));
    perfis.push_back(Perfil(proxIdPerfil++, email, nome, "", "", "", 0));
}

void Armazenamento::criarComentarioGlobal(int idPost, int idAutor, std::string texto) {
    comentarios.push_back(Comentario(proxIdComentario++, idPost, idAutor, std::move(texto)));
}

Perfil* Armazenamento::getPerfil(int id) {
    for (auto& p : perfis) if (p.getId() == id) return &p;
    return nullptr;
}

Usuario* Armazenamento::getUsuario(const std::string& email) {
    for (auto& u : usuarios) if (u.getEmail() == email) return &u;
    return nullptr;
}

Comunidade* Armazenamento::getComunidade(int id) {
    for (auto& c : comunidades) if (c.getId() == id) return &c;
    return nullptr;
}

std::vector<Post> Armazenamento::getPostsFeed() const {
    std::vector<Post> feed;

    for (const auto& p : posts) {
        if (p.getIdComunidade() == 0) {
            feed.push_back(p);
        }
    }

    return feed;
}

void Armazenamento::criarPost(std::string texto, int idComunidade) {
    if (idPerfilLogado > 0) posts.push_back(Post(proxIdPost++, idPerfilLogado, idComunidade, texto));
}

void Armazenamento::criarComunidade(std::string nome, std::string descricao) {
    if (idPerfilLogado > 0)
        comunidades.push_back(Comunidade(proxIdComunidade++, nome, descricao, idPerfilLogado));
}
std::vector<Post>& Armazenamento::getTodosPostsMutavel() {
    return posts;
}

std::vector<Comentario>& Armazenamento::getTodosComentariosMutavel() {
    return comentarios;
}

const std::vector<Perfil>& Armazenamento::getTodosPerfis() const { return perfis; }
const std::vector<Comunidade>& Armazenamento::getTodasComunidades() const { return comunidades; }
const std::vector<Post>& Armazenamento::getTodosPosts() const { return posts; }
