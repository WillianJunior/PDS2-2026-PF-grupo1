#include "domain/busca.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


static std::vector<std::string> resultados;
static std::vector<std::string> resultadosFiltrados;


static bool contemPalavra(const std::string& texto, const std::string& chave) {
    return texto.find(chave) != std::string::npos;
}

void Busca::buscarPalavraChave(std::string palavraChave) {
    resultados.clear();

    
    extern std::vector<Perfil> todosPerfis;
    extern std::vector<Comunidade> todasComunidades;
    extern std::vector<Feed> todosPosts;

   
    for (const auto& perfil : todosPerfis) {
        if (contemPalavra(perfil.getNome(), palavraChave) || contemPalavra(perfil.getDescricao(), palavraChave)) {
            resultados.push_back("Perfil: " + perfil.getNome());
        }
    }

    
    for (const auto& comunidade : todasComunidades) {
        if (contemPalavra(comunidade.getNome(), palavraChave) || contemPalavra(comunidade.getDescricao(), palavraChave)) {
            resultados.push_back("Comunidade: " + comunidade.getNome());
        }
    }

    
    for (const auto& post : todosPosts) {
        if (contemPalavra(post.getConteudo(), palavraChave)) {
            resultados.push_back("Post: " + post.getConteudo());
        }
    }

    if (resultados.empty()) {
        resultados.push_back("Nenhum resultado encontrado para: " + palavraChave);
    }
}

void Busca::exibirResultadosPesquisa() {
    std::cout << "=== Resultados da Pesquisa ===" << std::endl;
    for (const auto& r : resultados) {
        std::cout << r << std::endl;
    }
}

void Busca::filtrarResultados(std::string tipo) {
    resultadosFiltrados.clear();

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
