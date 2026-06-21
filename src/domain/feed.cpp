#include "domain/feed.hpp"
#include "domain/menus.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <console_utils.hpp>

namespace {

bool lerInteiro(const std::string& linha, int& valor) {
    if (linha.empty()) return false;
    try {
        size_t pos = 0;
        valor = std::stoi(linha, &pos);
        return pos == linha.size();
    } catch (...) {
        return false;
    }
}

}  // namespace

void Feed::verFeed(Armazenamento& db) {
    while (true) {
        ConsoleUtils::limparTela();
        std::cout << "\n///////////////////////////////////////\n";
        std::cout << "           EDU SOCIAL FEED\n";
        std::cout << "///////////////////////////////////////\n\n";

        auto todosPosts = db.getPostsFeed();

        if (todosPosts.empty()) {
            std::cout << "Nenhum post publicado na rede ainda.\n\n";
        } else {
            int exibicaoIdx = 1;
            for (int i = static_cast<int>(todosPosts.size()) - 1; i >= 0; --i) {
                Post& p = todosPosts.at(i);
                Perfil* autor = db.getPerfil(p.getIdAutor());
                std::string nomeAutor = autor ? autor->getNome() : "Desconhecido";

                std::cout << exibicaoIdx << " - @" << nomeAutor;
                if (p.getIdComunidade() != 0) {
                    Comunidade* com = db.getComunidade(p.getIdComunidade());
                    if (com) {
                        std::cout << " (" << com->getNome() << ")";
                    }
                }
                std::cout << "\n" << p.getConteudo() << "\n\n";
                exibicaoIdx++;
            }
        }

        std::cout << "A) Selecionar Post / B) Voltar\n\n";
        std::cout << "Digite sua opcao desejada: ";
        std::string opcao;
        std::getline(std::cin, opcao);

        if (opcao == "B" || opcao == "b") {
            ConsoleUtils::limparTela();
            break;
        } else if (opcao == "A" || opcao == "a") {
            if (todosPosts.empty()) {
                std::cout << "\n[ERRO] Nao ha posts para selecionar.\n";
                continue;
            }
            std::cout << "Qual Post deseja selecionar: ";
            int escolhaIdx;
            std::string linhaIdx;
            if (!std::getline(std::cin, linhaIdx)) break;
            if (!lerInteiro(linhaIdx, escolhaIdx)) {
                std::cout << "\n[ERRO] Indice invalido!\n";
                continue;
            }

            if (escolhaIdx >= 1 && escolhaIdx <= static_cast<int>(todosPosts.size())) {
                int vetorIdx = static_cast<int>(todosPosts.size()) - escolhaIdx;
                try {
                    menuVisualizarPost(todosPosts.at(vetorIdx), db);
                } catch (const std::out_of_range&) {
                    std::cout << "\n[ERRO] Post nao acessivel operacionalmente.\n";
                }
            } else {
                std::cout << "\n[ERRO] Indice invalido!\n";
            }
        } else {
            std::cout << "\n[ERRO] Opcao invalida!\n";
        }
    }
}

void Feed::exibirPosts(const std::vector<Post>& posts) { (void)posts; }

void Feed::exibirPerfis(const std::vector<Perfil>& perfis) { (void)perfis; }

void Feed::exibirComunidades(const std::vector<Comunidade>& comunidades) {
    (void)comunidades;
}
