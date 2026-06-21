#include "domain/gerenciador_csv.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<std::string> GerenciadorCSV::separarString(const std::string& linha, char delimitador) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(linha);
    while (std::getline(stream, token, delimitador)) tokens.push_back(token);
    return tokens;
}

std::vector<int> GerenciadorCSV::separarInteiros(const std::string& linha, char delimitador) {
    std::vector<int> inteiros;
    if (linha.empty()) return inteiros;
    auto tokens = separarString(linha, delimitador);
    for (const auto& t : tokens) {
        try {
            if (!t.empty()) inteiros.push_back(std::stoi(t));
        } catch (const std::exception&) {
        }
    }
    return inteiros;
}

std::string GerenciadorCSV::juntarInteiros(const std::vector<int>& lista, char delimitador) {
    std::string result = "";
    for (size_t i = 0; i < lista.size(); i++) {
        result += std::to_string(lista[i]);
        if (i < lista.size() - 1) result += delimitador;
    }
    return result;
}

void GerenciadorCSV::salvarUsuarios(const std::vector<Usuario>& usuarios, const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    arquivo << "id,email,senha,nome\n";
    for (const auto& u : usuarios) {
        arquivo << u.getId() << "," << u.getEmail() << "," << u.getSenha() << "," << u.getNome() << "\n";
    }
}

std::vector<Usuario> GerenciadorCSV::carregarUsuarios(const std::string& nomeArquivo) {
    std::vector<Usuario> lista;
    std::ifstream arquivo(nomeArquivo);
    std::string linha;
    if (std::getline(arquivo, linha)) { 
        while (std::getline(arquivo, linha)) {
            auto dados = separarString(linha, ',');
            if (dados.size() >= 4) lista.push_back(Usuario(std::stoi(dados[0]), dados[1], dados[2], dados[3]));
        }
    }
    return lista;
}

void GerenciadorCSV::salvarPerfis(const std::vector<Perfil>& perfis, const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    arquivo << "id,nome,descricao,curso,instituicao,periodo,seguidores,seguidos,comunidades\n";
    for (const auto& p : perfis) {
        arquivo << p.getId() << "," << p.getNome() << ","
                << p.getDescricao() << "," << p.getCurso() << "," << p.getInstituicao() << ","
                << p.getPeriodo() << "," << juntarInteiros(p.getIdsSeguidores(), '|') << ","
                << juntarInteiros(p.getIdsSeguidos(), '|') << "," << juntarInteiros(p.getIdsComunidades(), '|') << "\n";
    }
}

std::vector<Perfil> GerenciadorCSV::carregarPerfis(const std::string& nomeArquivo) {
    std::vector<Perfil> lista;
    std::ifstream arquivo(nomeArquivo);
    std::string linha;
    if (std::getline(arquivo, linha)) {
        while (std::getline(arquivo, linha)) {
            auto dados = separarString(linha, ',');
            if (dados.size() >= 7) { 
                try {
                    Perfil p(std::stoi(dados[0]), dados[1], dados[2], dados[3], dados[4], std::stoi(dados[5]));
                    if(dados.size() > 7) p.setIdsSeguidores(separarInteiros(dados[7], '|'));
                    if(dados.size() > 8) p.setIdsSeguidos(separarInteiros(dados[8], '|'));
                    if(dados.size() > 9) p.setIdsComunidades(separarInteiros(dados[9], '|'));
                    lista.push_back(p);
                } catch (const std::exception&) {
                }
            }
        }
    }
    return lista;
}

void GerenciadorCSV::salvarComunidades(const std::vector<Comunidade>& comunidades, const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    arquivo << "id,nome,descricao,idAdmin,membros\n";
    for (const auto& c : comunidades) {
        arquivo << c.getId() << "," << c.getNome() << "," << c.getDescricao() << ","
                << c.getIdAdministrador() << "," << juntarInteiros(c.getIdsMembros(), '|') << "\n";
    }
}

std::vector<Comunidade> GerenciadorCSV::carregarComunidades(const std::string& nomeArquivo) {
    std::vector<Comunidade> lista;
    std::ifstream arquivo(nomeArquivo);
    std::string linha;
    if (std::getline(arquivo, linha)) {
        while (std::getline(arquivo, linha)) {
            auto dados = separarString(linha, ',');
            if (dados.size() >= 4) {
                try {
                    Comunidade c(std::stoi(dados[0]), dados[1], dados[2], std::stoi(dados[3]));
                    if(dados.size() > 4) c.setIdsMembros(separarInteiros(dados[4], '|'));
                    lista.push_back(c);
                } catch (const std::exception&) {}
            }
        }
    }
    return lista;
}

void GerenciadorCSV::salvarPosts(const std::vector<Post>& posts, const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    arquivo << "id,idAutor,idComunidade,texto,curtidas\n";
    for (const auto& p : posts) {
        arquivo << p.getId() << "," << p.getIdAutor() << "," << p.getIdComunidade() << ","
                << p.getConteudo() << "," << juntarInteiros(p.getIdsCurtidas(), '|') << "\n";
    }
}

std::vector<Post> GerenciadorCSV::carregarPosts(const std::string& nomeArquivo) {
    std::vector<Post> lista;
    std::ifstream arquivo(nomeArquivo);
    std::string linha;
    if (std::getline(arquivo, linha)) {
        while (std::getline(arquivo, linha)) {
            auto dados = separarString(linha, ',');
            if (dados.size() >= 4) {
                try {
                    Post p(std::stoi(dados[0]), std::stoi(dados[1]), std::stoi(dados[2]), dados[3]);
                    if(dados.size() > 4) p.setIdsCurtidas(separarInteiros(dados[4], '|'));
                    lista.push_back(p);
                } catch (const std::exception&) {}
            }
        }
    }
    return lista;
}

void GerenciadorCSV::salvarComentarios(const std::vector<Comentario>& comentarios, const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    arquivo << "id,idPost,idAutor,texto,curtidas\n";
    for (const auto& c : comentarios) {
        arquivo << c.getId() << "," << c.getIdPost() << "," << c.getIdAutor() << ","
                << c.getTexto() << "," << juntarInteiros(c.getIdsCurtidas(), '|') << "\n";
    }
}

std::vector<Comentario> GerenciadorCSV::carregarComentarios(const std::string& nomeArquivo) {
    std::vector<Comentario> lista;
    std::ifstream arquivo(nomeArquivo);
    std::string linha;
    if (std::getline(arquivo, linha)) {
        while (std::getline(arquivo, linha)) {
            auto dados = separarString(linha, ',');
            if (dados.size() >= 4) {
                try {
                    Comentario c(std::stoi(dados[0]), std::stoi(dados[1]), std::stoi(dados[2]), dados[3]);
                    if(dados.size() > 4) c.setIdsCurtidas(separarInteiros(dados[4], '|'));
                    lista.push_back(c);
                } catch (const std::exception&) {}
            }
        }
    }
    return lista;
}