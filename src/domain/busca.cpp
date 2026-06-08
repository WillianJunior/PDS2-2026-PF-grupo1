#include "busca.hpp"
#include <iostream>

static bool contemPalavra(const std::string& texto, const std::string& chave) {
    return texto.find(chave) != std::string::npos;
}

void Busca::buscarPalavraChave(const std::string& palavraChave, const Armazenamento& db) {
    resultados.clear();
    
    for (const auto& p : db.getTodosPerfis()) {
        if (contemPalavra(p.getNome(), palavraChave) || contemPalavra(p.getDescricao(), palavraChave)) {
            resultados.push_back("[Perfil] " + p.getNome() + " (ID: " + std::to_string(p.getId()) + ")");
        }
    }
    for (const auto& c : db.getTodasComunidades()) {
        if (contemPalavra(c.getNome(), palavraChave) || contemPalavra(c.getDescricao(), palavraChave)) {
            resultados.push_back("[Comunidade] " + c.getNome() + " (ID: " + std::to_string(c.getId()) + ")");
        }
    }
    for (const auto& post : db.getTodosPosts()) {
        if (contemPalavra(post.getConteudo(), palavraChave)) {
            resultados.push_back("[Post] " + post.getConteudo());
        }
    }
    if (resultados.empty()) {
        resultados.push_back("Nenhum resultado encontrado para o termo: " + palavraChave);
    }
}

void Busca::exibirResultadosPesquisa() const {
    std::cout << "\n=== RESULTADOS DA BUSCA ===\n";
    for (const auto& r : resultados) std::cout << r << "\n";
    std::cout << "===========================\n";
}
