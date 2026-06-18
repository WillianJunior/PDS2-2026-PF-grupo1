// LCOV_EXCL_START

#include <iostream>
#include <string>
#include <vector>
#include "armazenamento.hpp"
#include "feed.hpp"
#include "busca.hpp"
#include "menus.hpp"

int main() {
    Armazenamento db;
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
            std::cin >> opcao;
            std::cin.ignore();

            if (opcao == 1) {
                while(true) {
                    std::string email, senha;
                    std::cout << "Email: ";
                    std::getline(std::cin, email);
                    std::cout << "Senha: ";
                    std::getline(std::cin, senha);
                    
                    if (db.fazerLogin(email, senha)) {
                        std::cout << "\n[SUCESSO] Login realizado!\n";
                        break;
                    } else {
                        std::cout << "\n[ERRO] Email ou senha invalidos.\n";
                        std::cout << "1 - Tentar novamente / 2 - Voltar\nEscolha: ";
                        int sub;
                        std::cin >> sub;
                        std::cin.ignore();
                        if (sub == 2) break;
                    }
                }

            } else if (opcao == 2) {
                while(true) {
                    std::string email, senha, nome;

                    std::cout << "Nome de usuario: ";
                    std::getline(std::cin, nome);
                    std::cout << "Email: ";
                    std::getline(std::cin, email);
                    std::cout << "Senha (minimo 8 digitos): ";
                    std::getline(std::cin, senha);
                    
                    if (senha.length() < 8) {
                        std::cout << "\n[ERRO] Senha invalida!\n\n";
                        continue;
                    }

                    if (!db.emailUnico(email)) {
                        std::cout << "\n[ERRO] Email repetido!\n\n";
                        continue;
                    }

                    if (!db.nomeUsuarioUnico(nome)) {
                        std::cout << "\n[ERRO] Nome de usuario ja existe!\n\n";
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
            std::cin >> opcao;
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
                        std::vector<Perfil> achados;
                        for (const auto& p : db.getTodosPerfis()) {
                            if (p.getNome().find(termo) != std::string::npos ||
                                p.getDescricao().find(termo) != std::string::npos)
                                achados.push_back(p);
                        }
                        for (size_t i = 0; i < achados.size(); ++i)
                            std::cout << (i+1) << " - @" << achados[i].getNome() << "\n";
                    }

                    else if (cat == 2) {
                        std::vector<Post> achados;
                        for (const auto& p : db.getTodosPosts()) {
                            if (p.getConteudo().find(termo) != std::string::npos)
                                achados.push_back(p);
                        }
                        menuVerPostsLista(achados, db);
                    }

                    else if (cat == 3) {
                        std::vector<Comunidade> achados;
                        for (const auto& c : db.getTodasComunidades()) {
                            if (c.getNome().find(termo) != std::string::npos ||
                                c.getDescricao().find(termo) != std::string::npos)
                                achados.push_back(c);
                        }
                    }
                }
            }

            else if (opcao == 6) {
                db.deslogar();
            }
        }

        db.salvarDados();
    }

    return 0;
}

// LCOV_EXCL_STOP