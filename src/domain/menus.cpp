#include "menus.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <stdexcept>

void menuVisualizarPost(Post& post, Armazenamento& db) {
    while (true) {
        std::cout << "\n////////////////Post//////////////////\n\n";
        Perfil* autor = db.getPerfil(post.getIdAutor());
        std::string nomeAutor = autor ? autor->getNome() : "Desconhecido";
        
        std::cout << "@" << nomeAutor;
        if (post.getIdComunidade() != 0) {
            Comunidade* com = db.getComunidade(post.getIdComunidade());
            if (com) std::cout << " (" << com->getNome() << ")";
        }
        std::cout << "\n" << post.getConteudo() << "\n";
        std::cout << "Curtidas: " << post.quantidadeDeCurtidas() << "\n\n";

        std::cout << "/////////////Comentarios//////////////\n\n";
        
        const auto& todosComentarios = db.getTodosComentariosMutavel();
        std::vector<Comentario> coms;

        for (const auto& c : todosComentarios) {
            if (c.getIdPost() == post.getId())
                coms.push_back(c);
        }

        if (coms.empty()) {
            std::cout << "Nenhum comentario nesta publicacao ainda.\n\n";
        } else {
            for (size_t i = 0; i < coms.size(); ++i) {
                Perfil* autorCom = db.getPerfil(coms.at(i).getIdAutor());
                std::string nomeCom = autorCom ? autorCom->getNome() : "Desconhecido";
                std::cout << (i + 1) << " - @" << nomeCom << "\n";
                std::cout << coms.at(i).getTexto() << "\n";
                std::cout << "Curtidas: " << coms.at(i).quantidadeDeCurtidas() << "\n\n";
            }
        }

        std::cout << "A) Curtir/Descurtir Post / B) Curtir/Descurtir Comentario / C) Comentar\n";
        std::cout << "D) Abrir Perfil / E) Abrir Comunidade / F) Voltar\n\n";
        std::cout << "Digite sua opcao desejada: ";
        std::string opcao;
        std::getline(std::cin, opcao);

        if (opcao == "F" || opcao == "f") break;
        else if (opcao == "A" || opcao == "a") {
            post.curtir(db.getIdPerfilLogado());
        } else if (opcao == "B" || opcao == "b") {
            if (coms.empty()) {
                std::cout << "\n[ERRO] Nao existem comentarios.\n"; continue;
            }
            std::cout << "Qual comentario deseja Curtir/Descurtir: ";
            int idx; 
            std::cin >> idx; 
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\n[ERRO] Entrada invalida!\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (idx >= 1 && idx <= static_cast<int>(coms.size())) {
                coms.at(idx - 1).curtir(db.getIdPerfilLogado());
            } else std::cout << "\n[ERRO] Indice invalido!\n";
        } else if (opcao == "C" || opcao == "c") {
            std::cout << "Digite seu comentario: ";
            std::string txt; std::getline(std::cin, txt);
            try {
                db.criarComentarioGlobal(post.getId(), db.getIdPerfilLogado(), txt);
                std::cout << "\n[SUCESSO] Comentario adicionado!\n";
            } catch (const std::invalid_argument& e) {
                std::cout << "\n[ERRO] " << e.what() << "\n";
            }
        } else if (opcao == "D" || opcao == "d") {
            menuPerfil(post.getIdAutor(), db);
        } else if (opcao == "E" || opcao == "e") {
            if (post.getIdComunidade() != 0)
                menuComunidade(post.getIdComunidade(), db);
            else
                std::cout << "\n[AVISO] Post do Feed Geral, sem comunidade.\n";
        }
    }
}

void menuVerPostsLista(const std::vector<Post>& postsList, Armazenamento& db) {
    while (true) {
        std::cout << "\n///////////////////////////////////////\n";
        std::cout << "              LISTA DE POSTS\n";
        std::cout << "///////////////////////////////////////\n\n";
        
        if (postsList.empty()) {
            std::cout << "Nenhum post encontrado.\n\n";
            std::cout << "Pressione ENTER para voltar...";
            std::cin.get();
            break;
        }

        for (size_t i = 0; i < postsList.size(); ++i) {
            Perfil* autor = db.getPerfil(postsList.at(i).getIdAutor());
            std::string nomeAutor = autor ? autor->getNome() : "Desconhecido";
            std::cout << (i + 1) << " - @" << nomeAutor << "\n";
            std::cout << postsList.at(i).getConteudo() << "\n\n";
        }

        std::cout << "A) Selecionar Post / B) Voltar\n\n";
        std::cout << "Digite sua opcao desejada: ";
        std::string opcao;
        std::getline(std::cin, opcao);

        if (opcao == "B" || opcao == "b") break;
        else if (opcao == "A" || opcao == "a") {
            std::cout << "Qual Post deseja selecionar: ";
            int idx; 
            std::cin >> idx; 
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\n[ERRO] Entrada invalida!\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (idx >= 1 && idx <= static_cast<int>(postsList.size())) {
                Post* postReal = nullptr;
                for (auto& p : db.getTodosPostsMutavel()) {
                    if (p.getId() == postsList.at(idx - 1).getId()) {
                        postReal = &p;
                        break;
                    }
                }
                if (postReal) menuVisualizarPost(*postReal, db);
            } else std::cout << "\n[ERRO] Indice invalido!\n";
        }
    }
}

void menuComunidade(int idComunidade, Armazenamento& db) {
    while (true) {
        Comunidade* com = db.getComunidade(idComunidade);
        if (!com) break;

        Perfil* admin = db.getPerfil(com->getIdAdministrador());
        Perfil* eu = db.getPerfil(db.getIdPerfilLogado());

        const auto& membros = com->getIdsMembros();
        bool isMember = std::find(membros.begin(), membros.end(), db.getIdPerfilLogado()) != membros.end();

        std::cout << "\n///////////////////////////////////////\n";
        std::cout << "        COMUNIDADE: " << com->getNome() << "\n";
        std::cout << "///////////////////////////////////////\n";
        std::cout << "Descricao: " << com->getDescricao() << "\n";
        std::cout << "Administrador: @" << (admin ? admin->getNome() : "Desconhecido") << "\n";
        std::cout << "Membros: " << membros.size() << "\n\n";

        std::vector<Post> postsDaComunidade;
        for (const auto& p : db.getTodosPosts()) {
            if (p.getIdComunidade() == idComunidade)
                postsDaComunidade.push_back(p);
        }

        std::cout << "=== POSTS RECENTES ===\n";
        if (postsDaComunidade.empty()) std::cout << "Nenhum post.\n\n";
        else {
            for (size_t i = 0; i < std::min<size_t>(3, postsDaComunidade.size()); ++i) {
                std::cout << "-> " << postsDaComunidade.at(i).getConteudo() << "\n";
            }
            std::cout << "\n";
        }

        std::cout << "\nDigite sua opcao desejada: ";
        int opcao; 
        std::cin >> opcao; 
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n[ERRO] Entrada invalida!\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (isMember || com->getIdAdministrador() == db.getIdPerfilLogado()) {
            if (opcao == 1) {
                std::cout << "Digite o texto do post para a comunidade: ";
                std::string txt;
                std::getline(std::cin, txt);
                try {
                    db.criarPost(txt, com->getId());
                    std::cout << "\n[SUCESSO] Post publicado com sucesso!\n";
                } catch (const std::invalid_argument& e) {
                    std::cout << "\n[ERRO] " << e.what() << "\n";
                }
            } else if (opcao == 2) {
                menuVerPostsLista(postsDaComunidade, db);
            } else if (opcao == 4) break;
        } else {
            if (opcao == 1) {
                com->adicionarMembro(eu->getId());
                eu->entrarComunidade(com->getId());
            } else if (opcao == 2) {
                menuVerPostsLista(postsDaComunidade, db);
            } else if (opcao == 3) break;
        }
    }
}

void menuPerfil(int idAlvo, Armazenamento& db) {
    while (true) {
        Perfil* alvo = db.getPerfil(idAlvo);
        if (!alvo) break;

        Perfil* eu = db.getPerfil(db.getIdPerfilLogado());
        bool souEu = (idAlvo == db.getIdPerfilLogado());

        std::vector<Post> postsDoUsuario;
        for (const auto& p : db.getTodosPosts()) {
            if (p.getIdAutor() == idAlvo)
                postsDoUsuario.push_back(p);
        }

        std::cout << "\nDigite sua opcao desejada: ";
        int opcao; 
        std::cin >> opcao; 
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n[ERRO] Entrada invalida!\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (souEu) {
            if (opcao == 1)
                menuVerPostsLista(postsDoUsuario, db);
            else if (opcao == 5)
                break;
        } else {
            if (opcao == 1)
                menuVerPostsLista(postsDoUsuario, db);
            else if (opcao == 3)
                break;
        }
    }
}