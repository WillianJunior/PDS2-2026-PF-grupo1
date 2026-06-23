#include "domain/busca.hpp"
#include <iostream>
#include <algorithm>
#include <cctype> 

static bool contemPalavra(const std::string& texto, const std::string& chave) {
    std::string textoMin = texto;
    std::string chaveMin = chave;

    std::transform(textoMin.begin(), textoMin.end(), textoMin.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    
    std::transform(chaveMin.begin(), chaveMin.end(), chaveMin.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    return textoMin.find(chaveMin) != std::string::npos;
}

std::vector<Perfil> Busca::buscarPerfis(const std::string& palavraChave, const Armazenamento& db) const {
    std::vector<Perfil> achados;

    for (const auto& perfil : db.getTodosPerfis()) {
        if (contemPalavra(perfil.getNome(), palavraChave) ||
            contemPalavra(perfil.getDescricao(), palavraChave)) {
            achados.push_back(perfil);
        }
    }
    std::sort(achados.begin(), achados.end(), [](const Perfil& a, const Perfil& b) {
        return a.getNome() < b.getNome();
    });
    return achados;
}

std::vector<Post> Busca::buscarPosts(const std::string& palavraChave, const Armazenamento& db) const {
    std::vector<Post> achados;

    for (const auto& post : db.getTodosPosts()) {
        if (contemPalavra(post.getConteudo(), palavraChave)) {
            achados.push_back(post);
        }
    }
    return achados;
}

std::vector<Comunidade> Busca::buscarComunidades(const std::string& palavraChave, const Armazenamento& db) const {
    std::vector<Comunidade> achados;

    for (const auto& comunidade : db.getTodasComunidades()) {
        if (contemPalavra(comunidade.getNome(), palavraChave) ||
            contemPalavra(comunidade.getDescricao(), palavraChave)) {
            achados.push_back(comunidade);
        }
    }

    return achados;
}

void Busca::buscarPalavraChave(const std::string& palavraChave, const Armazenamento& db) {
    resultados.clear();

    for (const auto& perfil : buscarPerfis(palavraChave, db)) {
        resultados.push_back("Perfil: " + perfil.getNome());
    }
    std::sort(resultados.begin(), resultados.end());
    for (const auto& comunidade : buscarComunidades(palavraChave, db)) {
        resultados.push_back("Comunidade: " + comunidade.getNome());
    }

    for (const auto& post : buscarPosts(palavraChave, db)) {
        resultados.push_back("Post: " + post.getConteudo());
    }

    if (resultados.empty()) {
        resultados.push_back("Nenhum resultado encontrado para: " + palavraChave);
    }
}

void Busca::exibirResultadosPesquisa() const {
    std::cout << "=== Resultados da Pesquisa ===" << std::endl;
    for (const auto& r : resultados) {
        std::cout << r << std::endl;
    }
}

void Busca::filtrarResultados(const std::string& tipo) {
    std::vector<std::string> resultadosFiltrados;

    for (const auto& r : resultados) {
        if (r.find(tipo) != std::string::npos) {
            resultadosFiltrados.push_back(r);
        }
    }

    std::sort(resultadosFiltrados.begin(), resultadosFiltrados.end());

    std::cout << "=== Resultados filtrados por tipo: " << tipo << " ===" << std::endl;
    for (const auto& rf : resultadosFiltrados) {
        std::cout << rf << std::endl;
    }
}
