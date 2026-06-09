#include "domain/busca.hpp"
#include <iostream>
#include <algorithm>

static bool contemPalavra(const std::string& texto, const std::string& chave) {
    return texto.find(chave) != std::string::npos;
}

// A assinatura agora bate perfeitamente com o .hpp
void Busca::buscarPalavraChave(const std::string& palavraChave, const Armazenamento& db) {
    resultados.clear();

    // Usamos o objeto db (Armazenamento) para acessar os dados, nada de extern!
    for (const auto& perfil : db.getTodosPerfis()) {
        if (contemPalavra(perfil.getNome(), palavraChave) || contemPalavra(perfil.getDescricao(), palavraChave)) {
            resultados.push_back("Perfil: " + perfil.getNome());
        }
    }

    for (const auto& comunidade : db.getTodasComunidades()) {
        if (contemPalavra(comunidade.getNome(), palavraChave) || contemPalavra(comunidade.getDescricao(), palavraChave)) {
            resultados.push_back("Comunidade: " + comunidade.getNome());
        }
    }

    for (const auto& post : db.getTodosPosts()) {
        if (contemPalavra(post.getConteudo(), palavraChave)) {
            resultados.push_back("Post: " + post.getConteudo());
        }
    }

    if (resultados.empty()) {
        resultados.push_back("Nenhum resultado encontrado para: " + palavraChave);
    }
}

// Assinatura agora inclui o 'const' para bater com o .hpp
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