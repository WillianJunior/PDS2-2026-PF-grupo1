#include "domain/feed.hpp"
#include <iostream>
#include <string>

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
        std::cout << "\n///////////////////////////////////////\n";
        std::cout << "           EDU SOCIAL FEED\n";
        std::cout << "///////////////////////////////////////\n\n";

        auto& todosPosts = db.getTodosPostsMutavel();

        if (todosPosts.empty()) {
            std::cout << "Nenhum post publicado na rede ainda.\n\n";
        } else {
            int exibicaoIdx = 1;
            for (int i = static_cast<int>(todosPosts.size()) - 1; i >= 0; --i) {
                Post& p = todosPosts[i];
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
                exibirPostDetalhado(todosPosts[vetorIdx], db);
            } else {
                std::cout << "\n[ERRO] Indice invalido!\n";
            }
        } else {
            std::cout << "\n[ERRO] Opcao invalida!\n";
        }
    }
}

void Feed::exibirPostDetalhado(Post& post, Armazenamento& db) {
    while (true) {
        std::cout << "\n////////////////Post//////////////////\n\n";
        Perfil* autorPost = db.getPerfil(post.getIdAutor());
        std::string nomeAutorPost = autorPost ? autorPost->getNome() : "Desconhecido";
        
        std::cout << "@" << nomeAutorPost;
        if (post.getIdComunidade() != 0) {
            Comunidade* com = db.getComunidade(post.getIdComunidade());
            if (com) std::cout << " (" << com->getNome() << ")";
        }
        std::cout << "\n" << post.getConteudo() << "\n";
        std::cout << "Curtidas: " << post.quantidadeDeCurtidas() << "\n\n";

        std::cout << "/////////////Comentarios//////////////\n\n";
        
        auto& todosComentarios = db.getTodosComentariosMutavel();
        std::vector<Comentario*> comentariosDoPost;
        
        for (auto& c : todosComentarios) {
            if (c.getIdPost() == post.getId()) {
                comentariosDoPost.push_back(&c);
            }
        }

        if (comentariosDoPost.empty()) {
            std::cout << "Nenhum comentario nesta publicacao ainda.\n\n";
        } else {
            for (size_t i = 0; i < comentariosDoPost.size(); ++i) {
                Comentario* c = comentariosDoPost[i];
                Perfil* autorCom = db.getPerfil(c->getIdAutor());
                std::string nomeAutorCom = autorCom ? autorCom->getNome() : "Desconhecido";
                std::cout << (i + 1) << " - @" << nomeAutorCom << "\n";
                std::cout << c->getTexto() << "\n";
                std::cout << "Curtidas: " << c->quantidadeDeCurtidas() << "\n\n";
            }
        }

        std::cout << "A) Curtir/Descurtir Post / B) Curtir/Descurtir Comentario / C) Comentar\n";
        std::cout << "D) Abrir Perfil / E) Abrir Comunidade / F) Voltar\n\n";
        std::cout << "Digite sua opcao desejada: ";
        std::string opcao;
        std::getline(std::cin, opcao);

        if (opcao == "F" || opcao == "f") {
            break;
        } else if (opcao == "A" || opcao == "a") {
            post.curtir(db.getIdPerfilLogado());
        } else if (opcao == "B" || opcao == "b") {
            if (comentariosDoPost.empty()) {
                std::cout << "\n[ERRO] Nao existem comentarios para interagir.\n";
                continue;
            }
            std::cout << "Qual comentario deseja Curtir/Descurtir: ";
            int comIdx;
            std::string linhaIdx;
            if (!std::getline(std::cin, linhaIdx) || !lerInteiro(linhaIdx, comIdx)) break;

            if (comIdx >= 1 && comIdx <= static_cast<int>(comentariosDoPost.size())) {
                comentariosDoPost[comIdx - 1]->curtir(db.getIdPerfilLogado());
            } else {
                std::cout << "\n[ERRO] Comentario nao encontrado!\n";
            }
        } else if (opcao == "C" || opcao == "c") {
            std::cout << "Digite seu comentario: ";
            std::string textoComentario;
            std::getline(std::cin, textoComentario);
            
            if (!textoComentario.empty()) {
                db.criarComentarioGlobal(post.getId(), db.getIdPerfilLogado(), textoComentario);
                std::cout << "\n[SUCESSO] Comentario adicionado!\n";
            }
        } else if (opcao == "D" || opcao == "d") {
            if (autorPost) {
                std::cout << "\n====================================\n";
                std::cout << "         PERFIL DE @" << autorPost->getNome() << "\n";
                std::cout << "====================================\n";
                std::cout << "Curso: " << autorPost->getCurso() << "\n";
                std::cout << "Instituicao: " << autorPost->getInstituicao() << "\n";
                std::cout << "Periodo: " << autorPost->getPeriodo() << " Semestre\n";
                std::cout << "Biografia: " << autorPost->getDescricao() << "\n";
                std::cout << "====================================\n";
                std::cout << "Pressione ENTER para retornar...";
                std::cin.get();
            }
        } else if (opcao == "E" || opcao == "e") {
            if (post.getIdComunidade() != 0) {
                Comunidade* com = db.getComunidade(post.getIdComunidade());
                if (com) {
                    std::cout << "\n====================================\n";
                    std::cout << "      COMUNIDADE: " << com->getNome() << "\n";
                    std::cout << "====================================\n";
                    std::cout << "Descricao: " << com->getDescricao() << "\n";
                    std::cout << "Quantidade de Membros: " << com->getIdsMembros().size() << "\n";
                    std::cout << "====================================\n";
                    std::cout << "Pressione ENTER para retornar...";
                    std::cin.get();
                }
            } else {
                std::cout << "\n[AVISO] Este post pertence ao feed geral e nao possui comunidade.\n";
            }
        } else {
            std::cout << "\n[ERRO] Opcao invalida!\n";
        }
    }
}

void Feed::exibirPosts(const std::vector<Post>& posts) { (void)posts; }
void Feed::exibirPerfis(const std::vector<Perfil>& perfis) { (void)perfis; }
void Feed::exibirComunidades(const std::vector<Comunidade>& comunidades) { (void)comunidades; }