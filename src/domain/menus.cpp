#include "menus.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include "domain/comunidade.hpp"
#include "domain/perfil.hpp"
#include <console_utils.hpp>

namespace {

bool opcaoVoltar(const std::string& linha) {
    return linha == "B" || linha == "b" || linha == "V" || linha == "v";
}

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
void exibirResumoPerfil(const Perfil& alvo) {
    std::cout << "\n====================================\n";
    std::cout << "         PERFIL DE @" << alvo.getNome() << "\n";
    std::cout << "====================================\n";
    std::cout << "Curso: "
              << (alvo.getCurso().empty() ? "(nao informado)" : alvo.getCurso()) << "\n";
    std::cout << "Instituicao: "
              << (alvo.getInstituicao().empty() ? "(nao informado)" : alvo.getInstituicao())
              << "\n";
    std::cout << "Periodo: " << alvo.getPeriodo() << " Semestre\n";
    std::cout << "Biografia: "
              << (alvo.getDescricao().empty() ? "(nao informado)" : alvo.getDescricao()) << "\n";
    std::cout << "Seguidores: " << alvo.getIdsSeguidores().size() << "\n";
    std::cout << "Seguindo: " << alvo.getIdsSeguidos().size() << "\n";
    std::cout << "====================================\n\n";
}

bool perfilSegue(const Perfil& seguidor, int idAlvo) {
    const auto& ids = seguidor.getIdsSeguidos();
    return std::find(ids.begin(), ids.end(), idAlvo) != ids.end();
}

void alternarSeguir(Perfil& eu, Perfil& alvo) {
    if (eu.getId() == alvo.getId()) {
        std::cout << "\n[ERRO] Voce nao pode seguir a si mesmo.\n";
        return;
    }

    if (perfilSegue(eu, alvo.getId())) {
        eu.deixarDeSeguir(alvo.getId());
        alvo.removerSeguidor(eu.getId());
        std::cout << "\n[SUCESSO] Voce deixou de seguir @" << alvo.getNome() << ".\n";
    } else {
        eu.seguir(alvo.getId());
        alvo.adicionarSeguidor(eu.getId());
        std::cout << "\n[SUCESSO] Voce agora segue @" << alvo.getNome() << ".\n";
    }
}

void menuEditarPerfil(Perfil& alvo) {
    while (true) {
        ConsoleUtils::limparTela();
        std::cout << "--- EDITAR PERFIL ---\n";
        std::cout << "1 - Biografia\n";
        std::cout << "2 - Curso\n";
        std::cout << "3 - Instituicao\n";
        std::cout << "4 - Periodo\n";
        std::cout << "5 - Voltar\n\n";
        std::cout << "Escolha: ";

        std::string linha;
        if (!std::getline(std::cin, linha)) break;
        if (opcaoVoltar(linha)) break;

        int opcao;
        if (!lerInteiro(linha, opcao)) {
            std::cout << "\n[ERRO] Opcao invalida.\n";
            continue;
        }

        if (opcao == 5) break;

        if (opcao == 1) {
            std::cout << "Nova biografia: ";
            std::string bio;
            if (!std::getline(std::cin, bio)) break;
            alvo.setDescricao(bio);
            std::cout << "\n[SUCESSO] Biografia atualizada!\n";
            ConsoleUtils::aguardarUsuario();
        } else if (opcao == 2) {
            std::cout << "Novo curso: ";
            std::string curso;
            if (!std::getline(std::cin, curso)) break;
            alvo.setCurso(curso);
            std::cout << "\n[SUCESSO] Curso atualizado!\n";
            ConsoleUtils::aguardarUsuario();
        } else if (opcao == 3) {
            std::cout << "Nova instituicao: ";
            std::string inst;
            if (!std::getline(std::cin, inst)) break;
            alvo.setInstituicao(inst);
            std::cout << "\n[SUCESSO] Instituicao atualizada!\n";
            ConsoleUtils::aguardarUsuario();
        } else if (opcao == 4) {
            std::cout << "Novo periodo (semestre): ";
            std::string linhaPeriodo;
            if (!std::getline(std::cin, linhaPeriodo)) break;
            int periodo;
            if (!lerInteiro(linhaPeriodo, periodo) || periodo < 1) {
                std::cout << "\n[ERRO] Periodo invalido.\n";
                continue;
            }
            alvo.setPeriodo(periodo);
            std::cout << "\n[SUCESSO] Periodo atualizado!\n";
            ConsoleUtils::aguardarUsuario();
        } else {
            std::cout << "\n[ERRO] Opcao invalida.\n";
        }
    }
}

}  // namespace

void menuVisualizarPost(Post& post, Armazenamento& db) {
    while (true) {
        ConsoleUtils::limparTela();
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
                Comentario* c = coms[i];
                Perfil* autorCom = db.getPerfil(c->getIdAutor());
                std::string nomeCom = autorCom ? autorCom->getNome() : "Desconhecido";
                std::cout << (i + 1) << " - @" << nomeCom << "\n";
                std::cout << c->getTexto() << "\n";
                std::cout << "Curtidas: " << c->quantidadeDeCurtidas() << "\n\n";
            }
        }

        std::cout << "A) Curtir/Descurtir Post / B) Curtir/Descurtir Comentario / C) Comentar\n";
        std::cout << "D) Abrir Perfil / E) Abrir Comunidade / F) Voltar\n\n";
        std::cout << "Digite sua opcao desejada: ";
        std::string opcao;
        std::getline(std::cin, opcao);

        if (opcao == "F" || opcao == "f") break;
        if (opcao == "A" || opcao == "a") {
            post.curtir(db.getIdPerfilLogado());
        } else if (opcao == "B" || opcao == "b") {
            if (coms.empty()) {
                std::cout << "\n[ERRO] Nao existem comentarios.\n";
                continue;
            }
            std::cout << "Qual comentario deseja Curtir/Descurtir: ";
            int idx;
            std::string linhaIdx;
            if (!std::getline(std::cin, linhaIdx) || !lerInteiro(linhaIdx, idx)) break;
            if (idx >= 1 && idx <= static_cast<int>(coms.size())) {
                coms.at(static_cast<size_t>(idx - 1))->curtir(db.getIdPerfilLogado());
            } else {
                std::cout << "\n[ERRO] Indice invalido!\n";
            }
        } else if (opcao == "C" || opcao == "c") {
            std::cout << "Digite seu comentario: ";
            std::string txt;
            std::getline(std::cin, txt);
            try {
                db.criarComentarioGlobal(post.getId(), db.getIdPerfilLogado(), txt);
                std::cout << "\n[SUCESSO] Comentario adicionado!\n";
            } catch (const std::invalid_argument& e) {
                std::cout << "\n[ERRO] " << e.what() << "\n";
            }
        } else if (opcao == "D" || opcao == "d") {
            menuPerfil(post.getIdAutor(), db);
        } else if (opcao == "E" || opcao == "e") {
            if (post.getIdComunidade() != 0) {
                menuComunidade(post.getIdComunidade(), db);
            } else {
                std::cout << "\n[AVISO] Post do Feed Geral, sem comunidade.\n";
            }
        }
    }
}

void menuVerPostsLista(const std::vector<Post>& postsList, Armazenamento& db) {
    while (true) {
        ConsoleUtils::limparTela();
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
            Perfil* autor = db.getPerfil(postsList[i].getIdAutor());
            std::string nomeAutor = autor ? autor->getNome() : "Desconhecido";
            std::cout << (i + 1) << " - @" << nomeAutor << "\n";
            std::cout << postsList[i].getConteudo() << "\n\n";
        }

        std::cout << "A) Selecionar Post / B) Voltar\n\n";
        std::cout << "Digite sua opcao desejada: ";
        std::string opcao;
        std::getline(std::cin, opcao);

        if (opcao == "B" || opcao == "b") break;
        if (opcao == "A" || opcao == "a") {
            std::cout << "Qual Post deseja selecionar: ";
            int idx;
            std::string linhaIdx;
            if (!std::getline(std::cin, linhaIdx) || !lerInteiro(linhaIdx, idx)) break;
            if (idx >= 1 && idx <= static_cast<int>(postsList.size())) {
                Post* postReal = db.getPostMutavel(postsList[static_cast<size_t>(idx - 1)].getId());
                if (postReal) menuVisualizarPost(*postReal, db);
            } else {
                std::cout << "\n[ERRO] Indice invalido!\n";
            }
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
        bool isMember =
            std::find(membros.begin(), membros.end(), db.getIdPerfilLogado()) != membros.end();
        ConsoleUtils::limparTela();
        std::cout << "\n///////////////////////////////////////\n";
        std::cout << "        COMUNIDADE: " << com->getNome() << "\n";
        std::cout << "///////////////////////////////////////\n";
        std::cout << "Descricao: " << com->getDescricao() << "\n";
        std::cout << "Administrador: @" << (admin ? admin->getNome() : "Desconhecido") << "\n";
        std::cout << "Membros: " << membros.size() << "\n\n";

        std::vector<Post> postsDaComunidade;
        for (const auto& p : db.getTodosPosts()) {
            if (p.getIdComunidade() == idComunidade) postsDaComunidade.push_back(p);
        }

        std::cout << "=== POSTS RECENTES ===\n";
        if (postsDaComunidade.empty()) {
            std::cout << "Nenhum post.\n\n";
        } else {
            auto it = postsDaComunidade.rbegin();
            for (size_t i = 0; i < std::min<size_t>(3, postsDaComunidade.size()); ++i) {
                std::cout << "-> " << it->getConteudo() << "\n";
                ++it;
            }
            std::cout << "\n";
        }

        if (isMember) {
            std::cout << "1 - Criar Post\n2 - Ver Posts\n4 - Voltar\n\n";
        } else {
            std::cout << "1 - Entrar na Comunidade\n2 - Ver Posts\n3 - Voltar\n\n";
        }

        std::cout << "Digite sua opcao desejada: ";
        std::string linha;
        if (!std::getline(std::cin, linha)) break;

        int opcao;
        if (!lerInteiro(linha, opcao)) {
            std::cout << "\n[ERRO] Opcao invalida.\n";
            continue;
        }

        if (isMember) {
            if (opcao == 1) {
                std::string txt;
                std::cout << "Texto do post: ";
                if (!std::getline(std::cin, txt)) break;
                try {
                    db.criarPost(txt, com->getId());
                    std::cout << "\n[SUCESSO] Post publicado com sucesso!\n";
                } catch (const std::invalid_argument& e) {
                    std::cout << "\n[ERRO] " << e.what() << "\n";
                }
            } else if (opcao == 2) {
                menuVerPostsLista(postsDaComunidade, db);
            } else if (opcao == 4) {
                break;
            } else {
                std::cout << "\n[ERRO] Opcao invalida.\n";
            }
        } else {
            if (opcao == 1) {
                if (!eu) {
                    std::cout << "\n[ERRO] Perfil logado nao encontrado.\n";
                    continue;
                }
                com->adicionarMembro(eu->getId());
                eu->entrarComunidade(com->getId());
            } else if (opcao == 2) {
                menuVerPostsLista(postsDaComunidade, db);
            } else if (opcao == 3) {
                break;
            } else {
                std::cout << "\n[ERRO] Opcao invalida.\n";
            }
        }
    }
}

void menuVerPerfisLista(const std::vector<Perfil>& perfisList, Armazenamento& db) {
    while (true) {
        ConsoleUtils::limparTela();
        std::cout << "\n///////////////////////////////////////\n";
        std::cout << "              LISTA DE PERFIS\n";
        std::cout << "///////////////////////////////////////\n\n";

        if (perfisList.empty()) {
            std::cout << "Nenhum perfil encontrado.\n\n";
            std::cout << "Pressione ENTER para voltar...";
            std::cin.get();
            break;
        }

        for (size_t i = 0; i < perfisList.size(); ++i) {
            std::cout << (i + 1) << " - @" << perfisList[i].getNome() << "\n";
            if (!perfisList[i].getDescricao().empty()) {
                std::cout << perfisList[i].getDescricao() << "\n";
            }
            std::cout << "\n";
        }

        std::cout << "A) Selecionar Perfil / B) Voltar\n\n";
        std::cout << "Digite sua opcao desejada: ";
        std::string opcao;
        std::getline(std::cin, opcao);

        if (opcao == "B" || opcao == "b") break;
        if (opcao == "A" || opcao == "a") {
            std::cout << "Qual Perfil deseja selecionar: ";
            int idx;
            std::string linhaIdx;
            if (!std::getline(std::cin, linhaIdx) || !lerInteiro(linhaIdx, idx)) break;
            if (idx >= 1 && idx <= static_cast<int>(perfisList.size())) {
                menuPerfil(perfisList[static_cast<size_t>(idx - 1)].getId(), db);
            } else {
                std::cout << "\n[ERRO] Indice invalido!\n";
            }
        } else if (!opcao.empty()) {
            std::cout << "\n[ERRO] Opcao invalida.\n";
        }
    }
}

void menuVerComunidadesLista(Armazenamento& db, const std::vector<Comunidade>* filtro) {
    while (true) {
        ConsoleUtils::limparTela();
        const std::vector<Comunidade>& lista =
            filtro != nullptr ? *filtro : db.getTodasComunidades();

        std::cout << "\n///////////////////////////////////////\n";
        std::cout << "            LISTA DE COMUNIDADES\n";
        std::cout << "///////////////////////////////////////\n\n";

        if (lista.empty()) {
            std::cout << "Nenhuma comunidade encontrada.\n\n";
        } else {
            for (size_t i = 0; i < lista.size(); ++i) {
                std::cout << (i + 1) << " - " << lista[i].getNome() << "\n";
                std::cout << lista[i].getDescricao() << "\n\n";
            }
        }

        std::cout << "A) Selecionar Comunidade / B) Voltar / C) Criar Comunidade\n\n";
        std::cout << "Digite sua opcao desejada: ";
        std::string opcao;
        if (!std::getline(std::cin, opcao)) break;

        if (opcao == "B" || opcao == "b") break;

        if (opcao == "C" || opcao == "c") {
            std::string nome;
            std::string descricao;
            std::cout << "Nome da comunidade: ";
            if (!std::getline(std::cin, nome)) break;
            std::cout << "Descricao: ";
            if (!std::getline(std::cin, descricao)) break;
            try {
                if (!nome.empty()) {
                    db.criarComunidade(nome, descricao);
                    std::cout << "\n[SUCESSO] Comunidade criada!\n";
                }
            } catch (const std::invalid_argument& e) {
                std::cout << "\n[ERRO] " << e.what() << "\n";
            }
            continue;
        }

        if (opcao == "A" || opcao == "a") {
            if (lista.empty()) {
                std::cout << "\n[ERRO] Nenhuma comunidade disponivel.\n";
                continue;
            }

            std::cout << "Qual Comunidade deseja selecionar: ";
            int idx;
            std::string linhaIdx;
            if (!std::getline(std::cin, linhaIdx) || !lerInteiro(linhaIdx, idx)) break;
            if (idx >= 1 && idx <= static_cast<int>(lista.size())) {
                menuComunidade(lista[static_cast<size_t>(idx - 1)].getId(), db);
            } else {
                std::cout << "\n[ERRO] Indice invalido!\n";
            }
        } else if (!opcao.empty()) {
            std::cout << "\n[ERRO] Opcao invalida. Use A, B ou C.\n";
        }
    }
}

void menuPerfil(int idAlvo, Armazenamento& db) {
    while (true) {
        ConsoleUtils::limparTela();
        Perfil* alvo = db.getPerfil(idAlvo);
        if (!alvo) break;

        bool souEu = (idAlvo == db.getIdPerfilLogado());

        std::vector<Post> postsDoUsuario;
        for (const auto& p : db.getTodosPosts()) {
            if (p.getIdAutor() == idAlvo) postsDoUsuario.push_back(p);
        }

        exibirResumoPerfil(*alvo);

        if (souEu) {
            std::cout << "1 - Ver Posts\n";
            std::cout << "2 - Editar Perfil\n";
            std::cout << "5 - Voltar\n\n";
        } else {
            Perfil* eu = db.getPerfil(db.getIdPerfilLogado());
            std::cout << "1 - Ver Posts\n";
            if (eu && perfilSegue(*eu, idAlvo)) {
                std::cout << "2 - Deixar de Seguir\n";
            } else {
                std::cout << "2 - Seguir\n";
            }
            std::cout << "3 - Voltar\n\n";
        }

        std::cout << "Digite sua opcao desejada: ";
        std::string linha;
        if (!std::getline(std::cin, linha)) break;
        if (opcaoVoltar(linha)) break;

        int opcao;
        if (!lerInteiro(linha, opcao)) {
            std::cout << "\n[ERRO] Opcao invalida.\n";
            continue;
        }

        if (souEu) {
            if (opcao == 1) {
                menuVerPostsLista(postsDoUsuario, db);
            } else if (opcao == 2) {
                menuEditarPerfil(*alvo);
            } else if (opcao == 5) {
                break;
            } else {
                std::cout << "\n[ERRO] Opcao invalida.\n";
            }
        } else {
            if (opcao == 1) {
                menuVerPostsLista(postsDoUsuario, db);
            } else if (opcao == 2) {
                Perfil* eu = db.getPerfil(db.getIdPerfilLogado());
                if (!eu) {
                    std::cout << "\n[ERRO] Perfil logado nao encontrado.\n";
                } else {
                    alternarSeguir(*eu, *alvo);
                }
            } else if (opcao == 3) {
                break;
            } else {
                std::cout << "\n[ERRO] Opcao invalida.\n";
            }
        }
    }
}