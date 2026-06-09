#include "menus.hpp"
#include <iostream>
#include <string>
#include <algorithm>

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
        
        auto& todosComentarios = db.getTodosComentariosMutavel();
        std::vector<Comentario*> coms;
        for (auto& c : todosComentarios) {
            if (c.getIdPost() == post.getId()) coms.push_back(&c);
        }

        if (coms.empty()) {
            std::cout << "Nenhum comentario nesta publicacao ainda.\n\n";
        } else {
            for (size_t i = 0; i < coms.size(); ++i) {
                Perfil* autorCom = db.getPerfil(coms[i]->getIdAutor());
                std::string nomeCom = autorCom ? autorCom->getNome() : "Desconhecido";
                std::cout << (i + 1) << " - @" << nomeCom << "\n";
                std::cout << coms[i]->getTexto() << "\n";
                std::cout << "Curtidas: " << coms[i]->quantidadeDeCurtidas() << "\n\n";
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
            int idx; std::cin >> idx; std::cin.ignore();
            if (idx >= 1 && idx <= static_cast<int>(coms.size())) coms[idx - 1]->curtir(db.getIdPerfilLogado());
            else std::cout << "\n[ERRO] Indice invalido!\n";
        } else if (opcao == "C" || opcao == "c") {
            std::cout << "Digite seu comentario: ";
            std::string txt; std::getline(std::cin, txt);
            if (!txt.empty()) db.criarComentarioGlobal(post.getId(), db.getIdPerfilLogado(), txt);
        } else if (opcao == "D" || opcao == "d") {
            menuPerfil(post.getIdAutor(), db);
        } else if (opcao == "E" || opcao == "e") {
            if (post.getIdComunidade() != 0) menuComunidade(post.getIdComunidade(), db);
            else std::cout << "\n[AVISO] Post do Feed Geral, sem comunidade.\n";
        }
    }
}

void menuVerPostsLista(std::vector<Post*> postsList, Armazenamento& db) {
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
            Perfil* autor = db.getPerfil(postsList[i]->getIdAutor());
            std::string nomeAutor = autor ? autor->getNome() : "Desconhecido";
            std::cout << (i + 1) << " - @" << nomeAutor << "\n";
            std::cout << postsList[i]->getConteudo() << "\n\n";
        }

        std::cout << "A) Selecionar Post / B) Voltar\n\n";
        std::cout << "Digite sua opcao desejada: ";
        std::string opcao;
        std::getline(std::cin, opcao);

        if (opcao == "B" || opcao == "b") break;
        else if (opcao == "A" || opcao == "a") {
            std::cout << "Qual Post deseja selecionar: ";
            int idx; std::cin >> idx; std::cin.ignore();
            if (idx >= 1 && idx <= static_cast<int>(postsList.size())) {
                menuVisualizarPost(*postsList[idx - 1], db);
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
        bool isMember = (std::find(com->getIdsMembros().begin(), com->getIdsMembros().end(), db.getIdPerfilLogado()) != com->getIdsMembros().end());

        std::cout << "\n///////////////////////////////////////\n";
        std::cout << "        COMUNIDADE: " << com->getNome() << "\n";
        std::cout << "///////////////////////////////////////\n";
        std::cout << "Descricao: " << com->getDescricao() << "\n";
        std::cout << "Administrador: @" << (admin ? admin->getNome() : "Desconhecido") << "\n";
        std::cout << "Membros: " << com->getIdsMembros().size() << "\n\n";

        // Coletar posts da comunidade
        std::vector<Post*> postsDaComunidade;
        for (auto& p : db.getTodosPostsMutavel()) {
            if (p.getIdComunidade() == idComunidade) postsDaComunidade.push_back(&p);
        }

        std::cout << "=== POSTS RECENTES ===\n";
        if (postsDaComunidade.empty()) std::cout << "Nenhum post.\n\n";
        else {
            for (size_t i = 0; i < std::min<size_t>(3, postsDaComunidade.size()); ++i) {
                std::cout << "-> " << postsDaComunidade[i]->getConteudo() << "\n";
            }
            std::cout << "\n";
        }

        if (isMember || com->getIdAdministrador() == db.getIdPerfilLogado()) {
            std::cout << "1 - Postar na Comunidade\n";
            std::cout << "2 - Ver todos os posts / Entrar em um post\n";
            std::cout << "3 - Sair da Comunidade\n";
            std::cout << "4 - Voltar\n";
        } else {
            std::cout << "1 - Virar Membro\n";
            std::cout << "2 - Ver todos os posts / Entrar em um post\n";
            std::cout << "3 - Voltar\n";
        }

        std::cout << "\nDigite sua opcao desejada: ";
        int opcao; std::cin >> opcao; std::cin.ignore();

        if ((isMember || com->getIdAdministrador() == db.getIdPerfilLogado())) {
            if (opcao == 1) {
                std::cout << "Conteudo do post: ";
                std::string txt; std::getline(std::cin, txt);
                db.criarPost(txt, com->getId());
            } else if (opcao == 2) {
                menuVerPostsLista(postsDaComunidade, db);
            } else if (opcao == 3) {
                com->removerMembro(eu->getId());
                eu->sairComunidade(com->getId());
                std::cout << "\n[AVISO] Voce saiu da comunidade.\n";
            } else if (opcao == 4) break;
        } else {
            if (opcao == 1) {
                com->adicionarMembro(eu->getId());
                eu->entrarComunidade(com->getId());
                std::cout << "\n[SUCESSO] Voce agora e membro!\n";
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

        std::cout << "\n///////////////////////////////////////\n";
        std::cout << "           PERFIL: @" << alvo->getNome() << "\n";
        std::cout << "///////////////////////////////////////\n";
        std::cout << "Biografia: " << alvo->getDescricao() << "\n";
        std::cout << "Curso: " << alvo->getCurso() << "\n";
        std::cout << "Instituicao: " << alvo->getInstituicao() << "\n";
        std::cout << "Periodo: " << alvo->getPeriodo() << "\n";
        std::cout << "Seguidores: " << alvo->getIdsSeguidores().size() << " | Seguidos: " << alvo->getIdsSeguidos().size() << "\n";
        std::cout << "Comunidades associadas: " << alvo->getIdsComunidades().size() << "\n\n";

        if (souEu) {
            std::cout << "1 - Ver meus posts\n";
            std::cout << "2 - Editar perfil\n";
            std::cout << "3 - Ver Seguidores\n";
            std::cout << "4 - Ver Seguidos\n";
            std::cout << "5 - Voltar\n";
        } else {
            std::cout << "1 - Ver posts deste usuario\n";
            std::cout << "2 - Seguir / Deixar de Seguir\n";
            std::cout << "3 - Voltar\n";
        }

        std::cout << "\nDigite sua opcao desejada: ";
        int opcao; std::cin >> opcao; std::cin.ignore();

        std::vector<Post*> postsDoUsuario;
        for (auto& p : db.getTodosPostsMutavel()) {
            if (p.getIdAutor() == idAlvo) postsDoUsuario.push_back(&p);
        }

        if (souEu) {
            if (opcao == 1) menuVerPostsLista(postsDoUsuario, db);
            else if (opcao == 2) {
                std::cout << "\n--- EDITAR PERFIL ---\n";
                std::cout << "1 - Curso\n2 - Instituicao\n3 - Biografia\n4 - Periodo\nEscolha: ";
                int opEdit; std::cin >> opEdit; std::cin.ignore();
                std::string txt;
                if (opEdit == 1) { std::cout << "Novo curso: "; std::getline(std::cin, txt); eu->setCurso(txt); }
                else if (opEdit == 2) { std::cout << "Nova instituicao: "; std::getline(std::cin, txt); eu->setInstituicao(txt); }
                else if (opEdit == 3) { std::cout << "Nova biografia: "; std::getline(std::cin, txt); eu->setDescricao(txt); }
                else if (opEdit == 4) { std::cout << "Novo periodo (numero): "; int per; std::cin >> per; std::cin.ignore(); eu->setPeriodo(per); }
            } else if (opcao == 3) {
                std::cout << "\n--- SEUS SEGUIDORES ---\n";
                auto segs = eu->getIdsSeguidores();
                for (size_t i = 0; i < segs.size(); ++i) {
                    Perfil* s = db.getPerfil(segs[i]);
                    if (s) std::cout << (i+1) << " - @" << s->getNome() << "\n";
                }
                std::cout << "\nPressione ENTER para voltar..."; std::cin.get();
            } else if (opcao == 4) {
                std::cout << "\n--- VOCE SEGUE ---\n";
                auto segs = eu->getIdsSeguidos();
                for (size_t i = 0; i < segs.size(); ++i) {
                    Perfil* s = db.getPerfil(segs[i]);
                    if (s) std::cout << (i+1) << " - @" << s->getNome() << "\n";
                }
                std::cout << "A) Ver Perfil / B) Deixar de Seguir / C) Voltar\nEscolha: ";
                std::string esc; std::getline(std::cin, esc);
                if (esc == "A" || esc == "a") {
                    std::cout << "Numero: "; int num; std::cin >> num; std::cin.ignore();
                    if (num >= 1 && num <= static_cast<int>(segs.size())) menuPerfil(segs[num-1], db);
                } else if (esc == "B" || esc == "b") {
                    std::cout << "Numero: "; int num; std::cin >> num; std::cin.ignore();
                    if (num >= 1 && num <= static_cast<int>(segs.size())) {
                        int idRemover = segs[num-1];
                        eu->deixarDeSeguir(idRemover);
                        Perfil* pr = db.getPerfil(idRemover);
                        if (pr) {
                            auto rSegs = pr->getIdsSeguidores();
                            rSegs.erase(std::remove(rSegs.begin(), rSegs.end(), eu->getId()), rSegs.end());
                            pr->setIdsSeguidores(rSegs);
                        }
                    }
                }
            } else if (opcao == 5) break;
        } else {
            if (opcao == 1) menuVerPostsLista(postsDoUsuario, db);
            else if (opcao == 2) {
                auto segs = eu->getIdsSeguidos();
                if (std::find(segs.begin(), segs.end(), idAlvo) != segs.end()) {
                    std::cout << "\n[AVISO] Voce ja segue este usuario. Deseja deixar de seguir? (S/N): ";
                    std::string esc; std::getline(std::cin, esc);
                    if (esc == "S" || esc == "s") {
                        eu->deixarDeSeguir(idAlvo);
                        auto rSegs = alvo->getIdsSeguidores();
                        rSegs.erase(std::remove(rSegs.begin(), rSegs.end(), eu->getId()), rSegs.end());
                        alvo->setIdsSeguidores(rSegs);
                    }
                } else {
                    eu->seguir(idAlvo);
                    auto nSegs = alvo->getIdsSeguidores();
                    nSegs.push_back(eu->getId());
                    alvo->setIdsSeguidores(nSegs);
                    std::cout << "\n[SUCESSO] Voce agora segue @" << alvo->getNome() << "!\n";
                }
            } else if (opcao == 3) break;
        }
    }
}