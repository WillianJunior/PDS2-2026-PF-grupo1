// LCOV_EXCL_START

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "armazenamento.hpp"
#include "feed.hpp"
#include "busca.hpp"
#include "menus.hpp"

namespace {

void normalizarLinha(std::string& linha) {
    while (!linha.empty() && (linha.back() == '\r' || linha.back() == '\n')) {
        linha.pop_back();
    }
}

bool lerLinha(std::string& destino) {
    if (!std::getline(std::cin, destino)) {
        return false;
    }
    normalizarLinha(destino);
    return !(destino.empty() && std::cin.eof());
}

void abortarEntradaAutomatica(const std::string& motivo) {
    std::cerr << "\n[demo] Entrada automatica interrompida: " << motivo << "\n";
    std::exit(1);
}

}  // namespace

int main(int argc, char* argv[]) {
    std::ifstream arquivoEntrada;
    std::streambuf* entradaPadrao = nullptr;
    const bool modoAutomatico = argc > 1;

    if (modoAutomatico) {
        arquivoEntrada.open(argv[1]);
        if (!arquivoEntrada.is_open()) {
            std::cerr << "[ERRO] Nao foi possivel abrir o arquivo de entrada: "
                      << argv[1] << "\n";
            return 1;
        }

        entradaPadrao = std::cin.rdbuf(arquivoEntrada.rdbuf());
        std::cout << "[demo] Lendo comandos de: " << argv[1] << "\n\n";
    }

    Armazenamento db;
    Busca busca;
    db.carregarDados();

    bool rodando = true;

    while (rodando) {
        if (db.getEmailLogado().empty()) {
            std::cout << "\n////////////////////////////////////////\n";
            std::cout << "        EDU SOCIAL TELA INICIAL         \n";
            std::cout << "////////////////////////////////////////\n";
            std::cout << "1 - Login\n";
            std::cout << "2 - Criar Usuario\n";
            std::cout << "3 - Sair\n\n";
            std::cout << "Digite sua opcao desejada: ";
            
            int opcao;
            if (!(std::cin >> opcao)) {
                if (modoAutomatico) {
                    rodando = false;
                    break;
                }
                break;
            }
            std::cin.ignore();

            if (opcao == 1) {
                while (true) {
                    std::string email, senha;
                    std::cout << "Email: ";
                    if (!lerLinha(email)) {
                        if (modoAutomatico) abortarEntradaAutomatica("fim inesperado ao ler email.");
                        break;
                    }
                    std::cout << "Senha: ";
                    if (!lerLinha(senha)) {
                        if (modoAutomatico) abortarEntradaAutomatica("fim inesperado ao ler senha.");
                        break;
                    }

                    if (db.fazerLogin(email, senha)) {
                        std::cout << "\n[SUCESSO] Login realizado!\n";
                        break;
                    }

                    if (modoAutomatico) {
                        abortarEntradaAutomatica(
                            "login falhou. Verifique email/senha no arquivo (use opcao 1, nao 2).");
                    }

                    std::cout << "\n[ERRO] Email ou senha invalidos.\n";
                    std::cout << "1 - Tentar novamente / 2 - Voltar\nEscolha: ";
                    int sub;
                    if (!(std::cin >> sub)) break;
                    std::cin.ignore();
                    if (sub == 2) break;
                }

            } else if (opcao == 2) {
                int tentativas = 0;
                const int maxTentativas = 3;

                while (tentativas < maxTentativas) {
                    std::string email, senha, nome;

                    std::cout << "Nome de usuario: ";
                    if (!lerLinha(nome)) {
                        if (modoAutomatico) abortarEntradaAutomatica("fim inesperado ao ler nome.");
                        break;
                    }

                    std::cout << "Email: ";
                    if (!lerLinha(email)) {
                        if (modoAutomatico) abortarEntradaAutomatica("fim inesperado ao ler email.");
                        break;
                    }

                    std::cout << "Senha (minimo 8 caracteres, com pelo menos 1 digito): ";
                    if (!lerLinha(senha)) {
                        if (modoAutomatico) abortarEntradaAutomatica("fim inesperado ao ler senha.");
                        break;
                    }

                    if (!db.senhaSegura(senha)) {
                        ++tentativas;
                        std::cout << "\n[ERRO] Senha invalida!\n\n";
                        if (modoAutomatico) {
                            abortarEntradaAutomatica(
                                "senha invalida (minimo 8 caracteres e 1 digito).");
                        }
                        if (tentativas >= maxTentativas) {
                            std::cout << "[AVISO] Limite de tentativas atingido. Voltando ao menu.\n";
                        }
                        continue;
                    }

                    if (!db.emailUnico(email)) {
                        ++tentativas;
                        std::cout << "\n[ERRO] Email repetido!\n\n";
                        if (modoAutomatico) {
                            std::cout << "[demo] Usuario ja existe; seguindo com login.\n";
                            return 0;
                        }
                        if (tentativas >= maxTentativas) {
                            std::cout << "[AVISO] Limite de tentativas atingido. Voltando ao menu.\n";
                        }
                        continue;
                    }

                    if (!db.nomeUsuarioUnico(nome)) {
                        ++tentativas;
                        std::cout << "\n[ERRO] Nome de usuario ja existe!\n\n";
                        if (modoAutomatico) {
                            abortarEntradaAutomatica("nome de usuario ja cadastrado.");
                        }
                        if (tentativas >= maxTentativas) {
                            std::cout << "[AVISO] Limite de tentativas atingido. Voltando ao menu.\n";
                        }
                        continue;
                    }

                    db.criarUsuarioEPerfil(email, senha, nome);
                    std::cout << "\n[SUCESSO] Conta criada!\n";
                    db.salvarDados();
                    break;
                }

            } else if (opcao == 3) {
                rodando = false;
            }

        } else {
            std::cout << "\n////////////////////////////////////////\n";
            std::cout << "           EDU SOCIAL MENU PRINCIPAL    \n";
            std::cout << "////////////////////////////////////////\n";
            std::cout << "1 - Ver Feed\n";
            std::cout << "2 - Buscar\n";
            std::cout << "3 - Ver Comunidades\n";
            std::cout << "4 - Ver Perfil\n";
            std::cout << "5 - Alterar Credenciais\n";
            std::cout << "6 - Deslogar\n\n";
            std::cout << "Digite sua opcao desejada: ";
            
            int opcao;
            if (!(std::cin >> opcao)) {
                if (modoAutomatico) {
                    rodando = false;
                    break;
                }
                break;
            }
            std::cin.ignore();

            if (opcao == 1) {
                Feed f;
                f.verFeed(db);
            }

            else if (opcao == 2) {
                std::cout << "\nO que voce quer buscar?\n";
                std::cout << "1 - Perfil\n2 - Post\n3 - Comunidade\n4 - Voltar\nEscolha: ";

                int cat;
                std::cin >> cat;
                std::cin.ignore();

                if (cat >= 1 && cat <= 3) {
                    std::string termo;
                    std::cout << "Digite o termo chave: ";
                    std::getline(std::cin, termo);

                    if (cat == 1) {
                        menuVerPerfisLista(busca.buscarPerfis(termo, db), db);
                    }

                    else if (cat == 2) {
                        menuVerPostsLista(busca.buscarPosts(termo, db), db);
                    }

                    else if (cat == 3) {
                        const auto achados = busca.buscarComunidades(termo, db);
                        menuVerComunidadesLista(db, &achados);
                    }
                }
            }

            else if (opcao == 3) {
                menuVerComunidadesLista(db, nullptr);
            }

            else if (opcao == 4) {
                if (db.getIdPerfilLogado() > 0) {
                    menuPerfil(db.getIdPerfilLogado(), db);
                } else {
                    std::cout << "\n[ERRO] Perfil logado nao encontrado.\n";
                }
            }

            else if (opcao == 5) {
                Usuario* usuario = db.getUsuario(db.getEmailLogado());
                if (!usuario) {
                    std::cout << "\n[ERRO] Usuario logado nao encontrado.\n";
                    continue;
                }

                std::cout << "\n1 - Alterar Senha\n";
                std::cout << "2 - Alterar Email\n";
                std::cout << "3 - Voltar\n";
                std::cout << "Escolha: ";

                int sub;
                std::cin >> sub;
                std::cin.ignore();

                if (sub == 1) {
                    std::string atual, nova;
                    std::cout << "Senha atual: ";
                    std::getline(std::cin, atual);
                    std::cout << "Nova senha (minimo 8 caracteres, com pelo menos 1 digito): ";
                    std::getline(std::cin, nova);
                    normalizarLinha(nova);

                    if (!db.senhaSegura(nova)) {
                        std::cout << "\n[ERRO] Senha invalida!\n";
                    } else if (usuario->alterarSenha(atual, nova)) {
                        std::cout << "\n[SUCESSO] Senha alterada!\n";
                    } else {
                        std::cout << "\n[ERRO] Senha atual incorreta.\n";
                    }
                } else if (sub == 2) {
                    std::string atual, novoEmail;
                    std::cout << "Senha atual: ";
                    std::getline(std::cin, atual);
                    std::cout << "Novo email: ";
                    std::getline(std::cin, novoEmail);

                    if (!db.emailUnico(novoEmail) && novoEmail != db.getEmailLogado()) {
                        std::cout << "\n[ERRO] Email repetido!\n";
                    } else if (usuario->alterarEmail(atual, novoEmail)) {
                        std::cout << "\n[SUCESSO] Email alterado!\n";
                    } else {
                        std::cout << "\n[ERRO] Senha atual incorreta.\n";
                    }
                }
            }

            else if (opcao == 6) {
                db.deslogar();
            }
        }

        db.salvarDados();
    }

    if (entradaPadrao != nullptr) {
        std::cin.rdbuf(entradaPadrao);
    }

    return 0;
}

// LCOV_EXCL_STOP