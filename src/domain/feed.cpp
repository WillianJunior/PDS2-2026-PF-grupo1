#include "domain/feed.hpp"
#include "domain/menus.hpp"
#include <console_utils.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <busca.hpp>

void Feed::verFeed(Armazenamento &db, Sistema &sys) {
    Busca busca = Busca();
    while (true) {
        ConsoleUtils::limparTela();
        ConsoleUtils::mostrarCabecalho("EDU SOCIAL FEED");
        Perfil *perfilLogado = db.getPerfil(sys.getIdPerfilLogado());
        if (!perfilLogado) {
            std::cout << "Perfil logado nao encontrado.\n";
            break;
        }
        auto todosPosts = busca.buscaPosts(*perfilLogado, db);

        if (todosPosts.empty()) {
            std::cout << "Nenhum post publicado na rede ainda.\n\n";
        } else {
            int exibicaoIdx = 1;
            for (int i = static_cast<int>(todosPosts.size()) - 1; i >= 0; --i) {
                const auto &postPtr = todosPosts.at(i);
                if (!postPtr) { // LCOV_EXCL_LINE
                    continue; // LCOV_EXCL_LINE
                } // LCOV_EXCL_LINE
                const Post &p = *postPtr;
                Perfil *autor = db.getPerfil(p.getIdAutor());
                std::string nomeAutor = autor ? autor->getNome() : "Desconhecido";

                std::cout << exibicaoIdx << " - @" << nomeAutor;
                if (p.getIdComunidade() != 0) {
                    Comunidade *com = db.getComunidade(p.getIdComunidade());
                    if (com) {
                        std::cout << " (" << com->getNome() << ")";
                    }
                }
                std::cout << "\n" << p.getConteudo() << "\n\n";
                exibicaoIdx++;
            }
        }

        std::cout << "A) Selecionar Post / B) Criar Post Global / C) Voltar\n\n";
        std::cout << "Digite sua opcao desejada: ";
        std::string opcao;
        std::getline(std::cin, opcao);

        if (opcao == "C" || opcao == "c") {
            ConsoleUtils::limparTela();
            break;
        } else if (opcao == "B" || opcao == "b") {
            std::cout << "Digite o texto do seu post global: ";
            std::string txt;
            if (std::getline(std::cin, txt)) {
                try {
                    sys.criarPost(txt, 0);
                    std::cout << "\n[SUCESSO] Post global publicado! Pressione ENTER para recarregar...";
                    std::cin.get();
                } catch (const std::invalid_argument &e) {
                    std::cout << "\n[ERRO] " << e.what() << "\n";
                }
            }
            continue;
        } else if (opcao == "A" || opcao == "a") {
            if (todosPosts.empty()) {
                std::cout << "\n[ERRO] Nao ha posts para selecionar.\n";
                continue;
            }
            std::cout << "Qual Post deseja selecionar: ";
            int escolhaIdx;
            std::string linhaIdx;
            if (!std::getline(std::cin, linhaIdx)) // LCOV_EXCL_LINE
                break; // LCOV_EXCL_LINE
            if (!ConsoleUtils::lerInteiro(linhaIdx, escolhaIdx)) {
                std::cout << "\n[ERRO] Indice invalido!\n";
                continue;
            }

            if (escolhaIdx >= 1 && escolhaIdx <= static_cast<int>(todosPosts.size())) {
                int vetorIdx = static_cast<int>(todosPosts.size()) - escolhaIdx;
                const auto &postPtr = todosPosts.at(vetorIdx);

                if (postPtr) {
                    Post *postOriginal = db.getPostMutavel(postPtr->getId());
                    if (postOriginal) {
                        Menus::menuVisualizarPost(*postOriginal, db, sys);
                    } else {
                        std::cout << "\n[ERRO] Post nao acessivel operacionalmente.\n"; // LCOV_EXCL_LINE
                    } // LCOV_EXCL_LINE
                } else { // LCOV_EXCL_LINE
                    std::cout << "\n[ERRO] Post nao encontrado.\n"; // LCOV_EXCL_LINE
                } // LCOV_EXCL_LINE
            } else {
                std::cout << "\n[ERRO] Indice invalido!\n";
            }
        } else {
            std::cout << "\n[ERRO] Opcao invalida!\n";
        }
    }
} // LCOV_EXCL_LINE

void Feed::exibirPosts(const std::vector<Post> &posts) { (void)posts; }
void Feed::exibirPerfis(const std::vector<Perfil> &perfis) { (void)perfis; }
void Feed::exibirComunidades(const std::vector<Comunidade> &comunidades) { (void)comunidades; }