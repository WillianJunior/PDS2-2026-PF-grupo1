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
                    std::cout << "Email: "; std::getline(std::cin, email);
                    std::cout << "Senha: "; std::getline(std::cin, senha);
                    
                    if (db.fazerLogin(email, senha)) {
                        std::cout << "\n[SUCESSO] Login realizado!\n";
                        break;
                    } else {
                        std::cout << "\n[ERRO] Email ou senha invalidos.\n";
                        std::cout << "1 - Tentar novamente / 2 - Voltar\nEscolha: ";
                        int sub; std::cin >> sub; std::cin.ignore();
                        if (sub == 2) break;
                    }
                }
            } else if (opcao == 2) {
                while(true) {
                    std::string email, senha, nome;
                    std::cout << "Nome de usuario: "; std::getline(std::cin, nome);
                    std::cout << "Email: "; std::getline(std::cin, email);
                    std::cout << "Senha (minimo 8 digitos): "; std::getline(std::cin, senha);
                    
                    if (senha.length() < 8) {
                        std::cout << "\n[ERRO] Senha invalida! Tente novamente.\n\n"; continue;
                    }
                    if (!db.emailUnico(email)) {
                        std::cout << "\n[ERRO] Email repetido! Tente novamente.\n\n"; continue;
                    }
                    if (!db.nomeUsuarioUnico(nome)) {
                        std::cout << "\n[ERRO] Alguem ja possui esse nome de usuario! Tente novamente.\n\n"; continue;
                    }
                    
                    db.criarUsuarioEPerfil(email, senha, nome);
                    std::cout << "\n[SUCESSO] Conta criada! Faca login para acessar.\n";
                    db.salvarDados();
                    break;
                }
            } else if (opcao == 3) {
                rodando = false;
            }
        } else {
            // MENU PRINCIPAL LOGADO
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
                Feed f; f.verFeed(db);
            } else if (opcao == 2) {
                std::cout << "\nO que voce quer buscar?\n1 - Perfil\n2 - Post\n3 - Comunidade\n4 - Voltar\nEscolha: ";
                int cat; std::cin >> cat; std::cin.ignore();
                if (cat >= 1 && cat <= 3) {
                    std::cout << "Digite o termo chave: ";
                    std::string termo; std::getline(std::cin, termo);
                    
                    if (cat == 1) {
                        std::vector<Perfil*> achados;
                        for(auto& p : db.getTodosPerfis()) {
                            if(p.getNome().find(termo) != std::string::npos || p.getDescricao().find(termo) != std::string::npos) 
                                achados.push_back(const_cast<Perfil*>(&p));
                        }
                        for(size_t i=0; i<achados.size(); ++i) std::cout << (i+1) << " - @" << achados[i]->getNome() << "\n";
                        std::cout << "\nA) Entrar no Perfil / B) Voltar\nEscolha: ";
                        std::string opB; std::getline(std::cin, opB);
                        if(opB == "A" || opB == "a") {
                            std::cout << "Numero: "; int n; std::cin >> n; std::cin.ignore();
                            if(n >= 1 && n <= static_cast<int>(achados.size())) menuPerfil(achados[n-1]->getId(), db);
                        }
                    } else if (cat == 2) {
                        std::vector<Post*> achados;
                        for(auto& p : db.getTodosPostsMutavel()) {
                            if(p.getConteudo().find(termo) != std::string::npos) achados.push_back(&p);
                        }
                        menuVerPostsLista(achados, db);
                    } else if (cat == 3) {
                        std::vector<Comunidade*> achados;
                        for(auto& c : db.getTodasComunidades()) {
                            if(c.getNome().find(termo) != std::string::npos || c.getDescricao().find(termo) != std::string::npos) 
                                achados.push_back(const_cast<Comunidade*>(&c));
                        }
                        for(size_t i=0; i<achados.size(); ++i) std::cout << (i+1) << " - " << achados[i]->getNome() << "\n";
                        std::cout << "\nA) Entrar na Comunidade / B) Voltar\nEscolha: ";
                        std::string opB; std::getline(std::cin, opB);
                        if(opB == "A" || opB == "a") {
                            std::cout << "Numero: "; int n; std::cin >> n; std::cin.ignore();
                            if(n >= 1 && n <= static_cast<int>(achados.size())) menuComunidade(achados[n-1]->getId(), db);
                        }
                    }
                }
            } else if (opcao == 3) {
                while(true) {
                    std::cout << "\n--- SUAS COMUNIDADES ---\n";
                    Perfil* eu = db.getPerfil(db.getIdPerfilLogado());
                    auto minhasComsIds = eu->getIdsComunidades();
                    std::vector<Comunidade*> minhasComs;
                    for (int idC : minhasComsIds) {
                        Comunidade* c = db.getComunidade(idC);
                        if(c) minhasComs.push_back(c);
                    }
                    
                    if (minhasComs.empty()) std::cout << "Voce nao participa de nenhuma comunidade ainda.\n";
                    else {
                        for(size_t i=0; i<minhasComs.size(); ++i) {
                            std::cout << (i+1) << " - " << minhasComs[i]->getNome() << "\n";
                        }
                    }

                    std::cout << "\n1 - Entrar em uma comunidade listada\n2 - Criar comunidade\n3 - Explorar todas as comunidades\n4 - Voltar\nEscolha: ";
                    int opC; std::cin >> opC; std::cin.ignore();

                    if (opC == 1) {
                        std::cout << "Numero da comunidade: "; int n; std::cin >> n; std::cin.ignore();
                        if(n >= 1 && n <= static_cast<int>(minhasComs.size())) menuComunidade(minhasComs[n-1]->getId(), db);
                    } else if (opC == 2) {
                        std::string nome, desc;
                        std::cout << "Nome da Comunidade: "; std::getline(std::cin, nome);
                        std::cout << "Descricao: "; std::getline(std::cin, desc);
                        db.criarComunidade(nome, desc);
                        // Atualiza perfis
                        int nvId = db.getTodasComunidades().back().getId();
                        db.getComunidade(nvId)->adicionarMembro(eu->getId());
                        eu->entrarComunidade(nvId);
                        std::cout << "\n[SUCESSO] Comunidade criada!\n";
                    } else if (opC == 3) {
                        auto todas = db.getTodasComunidades();
                        std::cout << "\n--- TODAS AS COMUNIDADES ---\n";
                        for(size_t i=0; i<todas.size(); ++i) std::cout << (i+1) << " - " << todas[i].getNome() << "\n";
                        std::cout << "\nA) Entrar na Comunidade / B) Voltar\nEscolha: ";
                        std::string opE; std::getline(std::cin, opE);
                        if(opE == "A" || opE == "a") {
                            std::cout << "Numero: "; int n; std::cin >> n; std::cin.ignore();
                            if(n >= 1 && n <= static_cast<int>(todas.size())) menuComunidade(todas[n-1].getId(), db);
                        }
                    } else if (opC == 4) break;
                }
            } else if (opcao == 4) {
                menuPerfil(db.getIdPerfilLogado(), db);
            } else if (opcao == 5) {
                Usuario* u = db.getUsuario(db.getEmailLogado());
                std::cout << "\n--- ALTERAR CREDENCIAIS ---\n1 - Alterar Email\n2 - Alterar Senha\n3 - Voltar\nEscolha: ";
                int opCred; std::cin >> opCred; std::cin.ignore();
                if (opCred == 1 || opCred == 2) {
                    std::cout << "Digite sua senha atual: ";
                    std::string senhaAt; std::getline(std::cin, senhaAt);
                    if (u->getSenha() == senhaAt) {
                        if (opCred == 1) {
                            std::cout << "Novo Email: "; std::string nvEm; std::getline(std::cin, nvEm);
                            u->alterarEmail(senhaAt, nvEm);
                            std::cout << "[SUCESSO] Email alterado!\n";
                        } else {
                            std::cout << "Nova Senha: "; std::string nvSe; std::getline(std::cin, nvSe);
                            if (nvSe.length() >= 8) {
                                u->alterarSenha(senhaAt, nvSe);
                                std::cout << "[SUCESSO] Senha alterada!\n";
                            } else std::cout << "[ERRO] Senha precisa ter 8 digitos!\n";
                        }
                    } else std::cout << "[ERRO] Senha atual incorreta!\n";
                }
            } else if (opcao == 6) {
                db.deslogar();
            }
        }
        db.salvarDados();
    }
    return 0;
}