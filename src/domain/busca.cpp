#include "domain/busca.hpp"
#include "busca.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>

static bool contemPalavra(const std::string &texto, const std::string &chave) {
    std::string textoMin = texto;
    std::string chaveMin = chave;

    std::transform(textoMin.begin(), textoMin.end(), textoMin.begin(), [](unsigned char c) { return std::tolower(c); });
    std::transform(chaveMin.begin(), chaveMin.end(), chaveMin.begin(), [](unsigned char c) { return std::tolower(c); });

    return textoMin.find(chaveMin) != std::string::npos;
}

std::vector<Perfil> Busca::buscarPerfis(const std::string &palavraChave, const Armazenamento &db) const {
    std::vector<Perfil> achados;

    for (const auto &perfil : db.listarPerfis()) {
        if (contemPalavra(perfil.getNome(), palavraChave) || contemPalavra(perfil.getDescricao(), palavraChave)) {
            achados.push_back(perfil);
        }
    }
    std::sort(achados.begin(), achados.end(),
              [](const Perfil &a, const Perfil &b) { return a.getNome() < b.getNome(); });
    return achados;
} // LCOV_EXCL_LINE

std::vector<Post> Busca::buscarPosts(const std::string &palavraChave, const Armazenamento &db) const {
    std::vector<Post> achados;

    for (const auto &post : db.getTodosPosts()) {
        if (contemPalavra(post.getConteudo(), palavraChave)) {
            achados.push_back(post);
        }
    }
    return achados;
} // LCOV_EXCL_LINE

std::vector<Comunidade> Busca::buscarComunidades(const std::string &palavraChave, const Armazenamento &db) const {
    std::vector<Comunidade> achados;

    for (const auto &comunidade : db.listarComunidade()) {
        if (contemPalavra(comunidade.getNome(), palavraChave) ||
            contemPalavra(comunidade.getDescricao(), palavraChave)) {
            achados.push_back(comunidade);
        }
    }
    return achados;
} // LCOV_EXCL_LINE

std::vector<Post*> Busca::buscaPosts(int idComunidade, Armazenamento &db) {
    std::vector<Post*> achados;

    // Iteramos por referência mutável para conseguir o endereço real do vetor interno
    for (auto &post : db.getTodosPostsMutavel()) {
        if (post.getIdComunidade() == idComunidade) {
            achados.push_back(&post);
        }
    }
    return achados;
}

void Busca::exibirResultadosPesquisa() const {
    std::cout << "=== Resultados da Pesquisa ===" << std::endl;
    for (const auto &r : resultados) {
        std::cout << r << std::endl;
    }
}

void Busca::filtrarResultados(const std::string &tipo) {
    std::vector<std::string> resultadosFiltrados;

    for (const auto &r : resultados) {
        if (r.find(tipo) != std::string::npos) {
            resultadosFiltrados.push_back(r);
        }
    }

    if (resultadosFiltrados.empty()) {
        std::cout << "Nenhum resultado para o filtro: " << tipo << std::endl;
    } else {
        std::cout << "=== Resultados Filtrados (" << tipo << ") ===" << std::endl;
        for (const auto &r : resultadosFiltrados) {
            std::cout << r << std::endl;
        }
    }
}

std::vector<Post*> Busca::buscaPosts(Perfil perfil, Armazenamento &db) {
    std::vector<Post*> feed;
    const auto &comunidadesUsuario = perfil.getIdsComunidades();

    // Iteramos por referência mutável para apontar para a única fonte da verdade
    for (auto &post : db.getTodosPostsMutavel()) {
        if (post.getIdComunidade() == 0 || std::find(comunidadesUsuario.begin(), comunidadesUsuario.end(),
                                                     post.getIdComunidade()) != comunidadesUsuario.end()) {
            feed.push_back(&post);
        }
    }
    return feed;
}