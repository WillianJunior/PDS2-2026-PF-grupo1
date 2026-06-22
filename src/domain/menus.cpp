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

void exibirMensagem(const std::string& mensagem) {
    if (!mensagem.empty()) {
        std::cout << mensagem << "\n\n";
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
    std::cout << "====================================\n\n";
}

void menuEditarPerfil(Perfil& alvo) {
    std::string mensagem;
    while (true) {
        exibirMensagem(mensagem);
        mensagem.clear();

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
            mensagem = "[ERRO] Opcao invalida.";
            continue;
        }

        if (opcao == 5) break;

        if (opcao == 1) {
            std::cout << "Nova biografia: ";
            std::string bio;
            if (!std::getline(std::cin, bio)) break;
            alvo.setDescricao(bio);
            mensagem = "[SUCESSO] Biografia atualizada!";
        } else if (opcao == 2) {
            std::cout << "Novo curso: ";
            std::string curso;
            if (!std::getline(std::cin, curso)) break;
            alvo.setCurso(curso);
            mensagem = "[SUCESSO] Curso atualizado!";
        } else if (opcao == 3) {
            std::cout << "Nova instituicao: ";
            std::string inst;
            if (!std::getline(std::cin, inst)) break;
            alvo.setInstituicao(inst);
            mensagem = "[SUCESSO] Instituicao atualizada!";
        } else if (opcao == 4) {
            std::cout << "Novo periodo (semestre): ";
            std::string linhaPeriodo;
            if (!std::getline(std::cin, linhaPeriodo)) break;
            int periodo;
            if (!lerInteiro(linhaPeriodo, periodo) || periodo < 1) {
                mensagem = "[ERRO] Periodo invalido.";
                continue;
            }
            alvo.setPeriodo(periodo);
            mensagem = "[SUCESSO] Periodo atualizado!";
        } else {
            mensagem = "[ERRO] Opcao invalida.";
        }
    }
}

}  // namespace
void menuVisualizarPost(Post& post, Armazenamento& db) {
    std::string mensagem;
    while (true) {
        ConsoleUtils::limparTela();
        exibirMensagem(mensagem);
        mensagem.clear();

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
            size_t contadorVisual = 1;
            for (auto it = coms.rbegin(); it != coms.rend(); ++it) {
                Comentario* c = *it;
                Perfil* autorCom = db.getPerfil(c->getIdAutor());
                std::string nomeCom = autorCom ? autorCom->getNome() : "Desconhecido";
                
                std::cout << contadorVisual << " - @" << nomeCom << "\n";
                std::cout << c->getTexto() << "\n";
                std::cout << "Curtidas: " << c->quantidadeDeCurtidas() << "\n\n";
                contadorVisual++;
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
                mensagem = "[ERRO] Nao existem comentarios.";
                continue;
            }
            std::cout << "Qual comentario deseja Curtir/Descurtir: ";
            int idx;
            std::string linhaIdx;
            if (!std::getline(std::cin, linhaIdx) || !lerInteiro(linhaIdx, idx)) break;
            if (idx >= 1 && idx <= static_cast<int>(coms.size())) {
                size_t idxReal = coms.size() - static_cast<size_t>(idx);
                coms.at(idxReal)->curtir(db.getIdPerfilLogado());
            } else {
                mensagem = "[ERRO] Indice invalido!";
            }
        } else if (opcao == "C" || opcao == "c") {
            std::cout << "Digite seu comentario: ";
            std::string txt;
            std::getline(std::cin, txt);
            try {
                db.criarComentarioGlobal(post.getId(), db.getIdPerfilLogado(), txt);
                mensagem = "[SUCESSO] Comentario adicionado!";
            } catch (const std::invalid_argument& e) {
                mensagem = std::string("[ERRO] ") + e.what();
            }
        } else if (opcao == "D" || opcao == "d") {
            menuPerfil(post.getIdAutor(), db);
        } else if (opcao == "E" || opcao == "e") {
            if (post.getIdComunidade() != 0) {
                menuComunidade(post.getIdComunidade(), db);
            } else {
                mensagem = "[AVISO] Post do Feed Geral, sem comunidade.";
            }
        }
    }
}

void menuVerPostsLista(const std::vector<Post>& postsList, Armazenamento& db) {
    std::string mensagem;
    while (true) {
        ConsoleUtils::limparTela();
        exibirMensagem(mensagem);
        mensagem.clear();

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
            size_t idxReverso = postsList.size() - 1 - i; 
            Perfil* autor = db.getPerfil(postsList[idxReverso].getIdAutor());
            std::string nomeAutor = autor ? autor->getNome() : "Desconhecido";
            std::cout << (i + 1) << " - @" << nomeAutor << "\n";
            std::cout << postsList[idxReverso].getConteudo() << "\n\n";
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
                size_t idxReal = postsList.size() - static_cast<size_t>(idx);
                Post* postReal = db.getPostMutavel(postsList[idxReal].getId());
                if (postReal) menuVisualizarPost(*postReal, db);
            } else {
                mensagem = "[ERRO] Indice invalido!";
            }
        }
    }
}

void menuComunidade(int idComunidade, Armazenamento& db) {
    std::string mensagem;
    while (true) {
        Comunidade* com = db.getComunidade(idComunidade);
        if (!com) break;

        Perfil* admin = db.getPerfil(com->getIdAdministrador());
        Perfil* eu = db.getPerfil(db.getIdPerfilLogado());

        const auto& membros = com->getIdsMembros();
        bool isMember =
            std::find(membros.begin(), membros.end(), db.getIdPerfilLogado()) != membros.end();

        ConsoleUtils::limparTela();
        exibirMensagem(mensagem);
        mensagem.clear();

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
            mensagem = "[ERRO] Opcao invalida.";
            continue;
        }

        if (isMember) {
            if (opcao == 1) {
                std::string txt;
                std::cout << "Texto do post: ";
                if (!std::getline(std::cin, txt)) break;
                try {
                    db.criarPost(txt, com->getId());
                    mensagem = "[SUCESSO] Post publicado com sucesso!";
                } catch (const std::invalid_argument& e) {
                    mensagem = std::string("[ERRO] ") + e.what();
                }
            } else if (opcao == 2) {
                menuVerPostsLista(postsDaComunidade, db);
            } else if (opcao == 4) {
                break;
            } else {
                mensagem = "[ERRO] Opcao invalida.";
            }
        } else {
            if (opcao == 1) {
                if (!eu) {
                    mensagem = "[ERRO] Perfil logado nao encontrado.";
                    continue;
                }
                com->adicionarMembro(eu->getId());
                eu->entrarComunidade(com->getId());
                mensagem = "[SUCESSO] Voce entrou na comunidade!";
            } else if (opcao == 2) {
                menuVerPostsLista(postsDaComunidade, db);
            } else if (opcao == 3) {
                break;
            } else {
                mensagem = "[ERRO] Opcao invalida.";
            }
        }
    }
}

void menuVerPerfisLista(const std::vector<Perfil>& perfisList, Armazenamento& db) {
    std::string mensagem;
    while (true) {
        ConsoleUtils::limparTela();
        exibirMensagem(mensagem);
        mensagem.clear();

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
                mensagem = "[ERRO] Indice invalido!";
            }
        } else if (!opcao.empty()) {
            mensagem = "[ERRO] Opcao invalida.";
        }
    }
}

void menuVerComunidadesLista(Armazenamento& db, const std::vector<Comunidade>* filtro) {
    std::string mensagem;
    while (true) {
        ConsoleUtils::limparTela();
        exibirMensagem(mensagem);
        mensagem.clear();

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
                    mensagem = "[SUCESSO] Comunidade criada!";
                }
            } catch (const std::invalid_argument& e) {
                mensagem = std::string("[ERRO] ") + e.what();
            }
            continue;
        }

        if (opcao == "A" || opcao == "a") {
            if (lista.empty()) {
                mensagem = "[ERRO] Nenhuma comunidade disponivel.";
                continue;
            }

            std::cout << "Qual Comunidade deseja selecionar: ";
            int idx;
            std::string linhaIdx;
            if (!std::getline(std::cin, linhaIdx) || !lerInteiro(linhaIdx, idx)) break;
            if (idx >= 1 && idx <= static_cast<int>(lista.size())) {
                menuComunidade(lista[static_cast<size_t>(idx - 1)].getId(), db);
            } else {
                mensagem = "[ERRO] Indice invalido!";
            }
        } else if (!opcao.empty()) {
            mensagem = "[ERRO] Opcao invalida. Use A, B ou C.";
        }
    }
}

void menuPerfil(int idAlvo, Armazenamento& db) {
    std::string mensagem;
    while (true) {
        ConsoleUtils::limparTela();
        Perfil* alvo = db.getPerfil(idAlvo);
        if (!alvo) break;

        exibirMensagem(mensagem);
        mensagem.clear();

        bool souEu = (idAlvo == db.getIdPerfilLogado());

        std::vector<Post> postsDoUsuario;
        for (const auto& p : db.getTodosPosts()) {
            if (p.getIdAutor() == idAlvo) postsDoUsuario.push_back(p);
        }

        exibirResumoPerfil(*alvo);

        if (souEu) {
            std::cout << "1 - Ver Posts\n";
            std::cout << "2 - Editar Perfil\n";
            std::cout << "3 - Voltar\n\n";
        } else {
            Perfil* eu = db.getPerfil(db.getIdPerfilLogado());
            std::cout << "1 - Ver Posts\n";
            std::cout << "3 - Voltar\n\n";
        }

        std::cout << "Digite sua opcao desejada: ";
        std::string linha;
        if (!std::getline(std::cin, linha)) break;
        if (opcaoVoltar(linha)) break;

        int opcao;
        if (!lerInteiro(linha, opcao)) {
            mensagem = "[ERRO] Opcao invalida.";
            continue;
        }

        if (souEu) {
            if (opcao == 1) {
                menuVerPostsLista(postsDoUsuario, db);
            } else if (opcao == 2) {
                menuEditarPerfil(*alvo);
            } else if (opcao == 3) {
                break;
            } else {
                mensagem = "[ERRO] Opcao invalida.";
            }
        } else {
            if (opcao == 1) {
                menuVerPostsLista(postsDoUsuario, db);
            } else if (opcao == 2) {
                Perfil* eu = db.getPerfil(db.getIdPerfilLogado());
                if (!eu) {
                    mensagem = "[ERRO] Perfil logado nao encontrado.";
                }
            } else if (opcao == 3) {
                break;
            } else {
                mensagem = "[ERRO] Opcao invalida.";
            }
        }
    }
}