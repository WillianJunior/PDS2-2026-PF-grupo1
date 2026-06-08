#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "armazenamento.hpp"

using namespace std;

void printHeader(const string& title);
void telaInicial(Armazenamento& db);
void telaBackend(Armazenamento& db);
void telaFeed(Armazenamento& db);
void telaPost(Armazenamento& db, int idPost);
void telaComunidades(Armazenamento& db);
void telaComunidadeAberta(Armazenamento& db, int idComunidade);
void telaAlterarCredenciais(Armazenamento& db);
void telaPerfil(Armazenamento& db, int idPerfil);
void telaBusca(Armazenamento& db);

void limparBuffer() {
    if(cin.fail()) { cin.clear(); }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void printHeader(const string& title) {
    cout << "\n////////////////////////////////////////\n";
    cout << "         " << title << "\n";
    cout << "////////////////////////////////////////\n\n";
}

int main() {
    Armazenamento db;
    db.carregarDados();
    telaInicial(db);
    db.salvarDados();
    return 0;
}

void telaInicial(Armazenamento& db) {
    while (true) {
        printHeader("EDU SOCIAL TELA INICIAL");
        cout << "1 - Login\n2 - Criar Usuario\n3 - Sair\n\n";
        cout << "Digite sua opcao desejada: ";
        string op; getline(cin, op);

        if (op == "3") {
            break;
        } 
        else if (op == "1") {
            while (true) {
                printHeader("EDU SOCIAL LOGIN");
                string email, senha;
                cout << "Email: "; getline(cin, email);
                cout << "Senha: "; getline(cin, senha);

                if (db.fazerLogin(email, senha)) {
                    telaBackend(db); 
                    break;           
                } else {
                    cout << "\n[ERRO] Email ou senha invalidos.\n\n";
                    cout << "1 - Tentar Novamente / 2 - Voltar\n";
                    cout << "Digite sua opcao desejada: ";
                    string subOp; getline(cin, subOp);
                    if (subOp == "2") break;
                }
            }
        } 
        else if (op == "2") {
            while (true) {
                printHeader("EDU SOCIAL CRIAR CONTA");
                string email, senha, user;
                
                cout << "Email: "; getline(cin, email);
                if (!db.emailUnico(email)) {
                    cout << "\n[ERRO] Ja existe uma conta com este email.\n\n";
                    cout << "1 - Tentar Novamente / 2 - Voltar\nDigite: ";
                    string sub; getline(cin, sub); if (sub == "2") break; continue;
                }

                cout << "Usuario: @"; getline(cin, user);
                if (!db.nomeUsuarioUnico(user)) {
                    cout << "\n[ERRO] Este usuario ja existe. Escolha outro.\n\n";
                    cout << "1 - Tentar Novamente / 2 - Voltar\nDigite: ";
                    string sub; getline(cin, sub); if (sub == "2") break; continue;
                }

                cout << "Senha (min 8 digitos): "; getline(cin, senha);
                if (senha.length() < 8) {
                    cout << "\n[ERRO] Senha invalida! Minimo de 8 caracteres.\n\n";
                    cout << "1 - Tentar Novamente / 2 - Voltar\nDigite: ";
                    string sub; getline(cin, sub); if (sub == "2") break; continue;
                }

                db.criarUsuarioEPerfil(email, senha, user);
                cout << "\n[SUCESSO] Conta criada! Faca login para acessar.\n";
                break;
            }
        }
    }
}

void telaBackend(Armazenamento& db) {
    while (true) {
        printHeader("EDU SOCIAL MENU");
        cout << "1 - Ver Feed\n2 - Buscar\n3 - Ver Comunidades\n4 - Ver Perfil\n5 - Alterar Credenciais\n6 - Deslogar\n\n";
        cout << "Digite sua opcao desejada: ";
        string op; getline(cin, op);

        if (op == "6") {
            db.deslogar();
            cout << "\nDeslogando...\n";
            break;
        }
        else if (op == "1") telaFeed(db);
        else if (op == "2") telaBusca(db);
        else if (op == "3") telaComunidades(db);
        else if (op == "4") telaPerfil(db, db.getIdPerfilLogado());
        else if (op == "5") telaAlterarCredenciais(db);
    }
}

void telaFeed(Armazenamento& db) {
    while (true) {
        printHeader("EDU SOCIAL FEED");
        auto& posts = db.getTodosPostsMutavel();
        vector<Post*> postsCronologicos;
        
        for (int i = static_cast<int>(posts.size()) - 1; i >= 0; --i) {
            if (posts[i].getIdComunidade() == 0) { 
                postsCronologicos.push_back(&posts[i]);
            }
        }

        if (postsCronologicos.empty()) {
            cout << "O feed esta vazio. Seja o primeiro a postar!\n\n";
        } else {
            for (size_t i = 0; i < postsCronologicos.size(); ++i) {
                Post* p = postsCronologicos[i];
                Perfil* autor = db.getPerfil(p->getIdAutor());
                cout << (i + 1) << " - @" << (autor ? autor->getNome() : "desconhecido") << "\n";
                cout << p->getConteudo() << "\n\n";
            }
        }

        cout << "A) Selecionar Post / B) Novo Post / C) Voltar\n\n";
        cout << "Digite sua opcao desejada: ";
        string op; getline(cin, op);

        if (op == "C" || op == "c") break;
        else if (op == "B" || op == "b") {
            cout << "No que voce esta pensando?\n> ";
            string txt; getline(cin, txt);
            if (!txt.empty()) db.criarPost(txt, 0);
        }
        else if (op == "A" || op == "a") {
            if (postsCronologicos.empty()) continue;
            cout << "Qual Post deseja selecionar: ";
            int idx; cin >> idx; limparBuffer();
            if (idx >= 1 && idx <= static_cast<int>(postsCronologicos.size())) {
                telaPost(db, postsCronologicos[idx - 1]->getId());
            } else {
                cout << "[ERRO] Indice invalido!\n";
            }
        }
    }
}

void telaPost(Armazenamento& db, int idPost) {
    while (true) {
        Post* p = nullptr;
        for(auto& postRef : db.getTodosPostsMutavel()) {
            if(postRef.getId() == idPost) { p = &postRef; break; }
        }
        if(!p) break;

        printHeader("Post");
        Perfil* autor = db.getPerfil(p->getIdAutor());
        cout << "@" << (autor ? autor->getNome() : "desconhecido");
        
        if (p->getIdComunidade() != 0) {
            Comunidade* c = db.getComunidade(p->getIdComunidade());
            if (c) cout << " (" << c->getNome() << ")";
        }
        cout << "\n" << p->getConteudo() << "\nCurtidas: " << p->quantidadeDeCurtidas() << "\n\n";

        cout << "/////////////Comentarios//////////////\n\n";
        auto& todosComentarios = db.getTodosComentariosMutavel();
        vector<Comentario*> comentariosDoPost;
        for (auto& c : todosComentarios) {
            if (c.getIdPost() == p->getId()) comentariosDoPost.push_back(&c);
        }

        for (size_t i = 0; i < comentariosDoPost.size(); ++i) {
            Comentario* c = comentariosDoPost[i];
            Perfil* autorC = db.getPerfil(c->getIdAutor());
            cout << (i + 1) << " - @" << (autorC ? autorC->getNome() : "desconhecido") << "\n";
            cout << c->getTexto() << "\nCurtidas: " << c->quantidadeDeCurtidas() << "\n\n";
        }

        cout << "A) Curtir/Descurtir Post / B) Curtir/Descurtir Comentario / C) Comentar\n";
        cout << "D) Abrir Perfil / E) Abrir Comunidade / F) Voltar\n\n";
        cout << "Digite sua opcao desejada: ";
        string op; getline(cin, op);

        if (op == "F" || op == "f") break;
        else if (op == "A" || op == "a") p->curtir(db.getIdPerfilLogado());
        else if (op == "B" || op == "b") {
            if(comentariosDoPost.empty()) continue;
            cout << "Qual comentario deseja Curtir/Descurtir: ";
            int idx; cin >> idx; limparBuffer();
            if(idx >= 1 && idx <= static_cast<int>(comentariosDoPost.size())) {
                comentariosDoPost[idx-1]->curtir(db.getIdPerfilLogado());
            }
        }
        else if (op == "C" || op == "c") {
            cout << "Comentario: "; string txt; getline(cin, txt);
            if(!txt.empty()) db.criarComentarioGlobal(p->getId(), db.getIdPerfilLogado(), txt);
        }
        else if (op == "D" || op == "d") {
            telaPerfil(db, p->getIdAutor());
        }
        else if (op == "E" || op == "e") {
            if (p->getIdComunidade() != 0) telaComunidadeAberta(db, p->getIdComunidade());
            else cout << "\n[AVISO] Este post nao pertence a uma comunidade.\n";
        }
    }
}

void telaComunidades(Armazenamento& db) {
    while (true) {
        printHeader("EDU SOCIAL COMUNIDADES");
        int me = db.getIdPerfilLogado();
        vector<Comunidade*> minhasComunidades;

        for (auto& c : db.getTodasComunidades()) {
            Comunidade* comMutavel = db.getComunidade(c.getId());
            if (comMutavel && (comMutavel->getIdAdministrador() == me || comMutavel->podePublicar(me))) {
                minhasComunidades.push_back(comMutavel);
            }
        }

        for (size_t i = 0; i < minhasComunidades.size(); ++i) {
            cout << (i + 1) << " - " << minhasComunidades[i]->getNome();
            if (minhasComunidades[i]->getIdAdministrador() == me) cout << " (Admin)";
            cout << "\n";
        }

        cout << "\nA) Explorar Comunidade / B) Criar Comunidade / C) Voltar\n\n";
        cout << "Digite sua opcao desejada: ";
        string op; getline(cin, op);

        if (op == "C" || op == "c") break;
        else if (op == "B" || op == "b") {
            string nome, desc;
            cout << "Nome da Comunidade: "; getline(cin, nome);
            cout << "Descricao: "; getline(cin, desc);
            db.criarComunidade(nome, desc);
        }
        else if (op == "A" || op == "a") {
            cout << "\nTodas as Comunidades da Rede:\n";
            int count = 1;
            for (const auto& c : db.getTodasComunidades()) {
                cout << count++ << " - " << c.getNome() << "\n";
            }
            cout << "Qual deseja explorar? (Digite o indice): ";
            int idx; cin >> idx; limparBuffer();
            if (idx >= 1 && idx <= static_cast<int>(db.getTodasComunidades().size())) {
                telaComunidadeAberta(db, db.getTodasComunidades()[idx-1].getId());
            }
        }
    }
}

void telaComunidadeAberta(Armazenamento& db, int idComunidade) {
    while (true) {
        Comunidade* c = db.getComunidade(idComunidade);
        if (!c) break;

        printHeader("COMUNIDADE: " + c->getNome());
        Perfil* admin = db.getPerfil(c->getIdAdministrador());
        cout << "Admin: @" << (admin ? admin->getNome() : "desconhecido") << "\n";
        cout << "Descricao: " << c->getDescricao() << "\n\n";

        cout << "--- Posts da Comunidade ---\n";
        auto& posts = db.getTodosPostsMutavel();
        vector<Post*> postsCom;
        for (int i = static_cast<int>(posts.size()) - 1; i >= 0; --i) {
            if (posts[i].getIdComunidade() == c->getId()) postsCom.push_back(&posts[i]);
        }

        for (size_t i = 0; i < postsCom.size(); ++i) {
            Perfil* autor = db.getPerfil(postsCom[i]->getIdAutor());
            cout << (i + 1) << " - @" << (autor ? autor->getNome() : "desconhecido") << "\n";
            cout << postsCom[i]->getConteudo() << "\n\n";
        }

        bool ehMembro = c->podePublicar(db.getIdPerfilLogado()) && c->getIdAdministrador() != db.getIdPerfilLogado();
        
        cout << "A) " << (ehMembro ? "Sair da Comunidade" : "Virar Membro") << "\n";
        cout << "B) Postar / C) Entrar no Post / D) Voltar\n\n";
        cout << "Digite sua opcao desejada: ";
        string op; getline(cin, op);

        if (op == "D" || op == "d") break;
        else if (op == "A" || op == "a") {
            if (c->getIdAdministrador() == db.getIdPerfilLogado()) {
                cout << "[AVISO] O Admin nao pode sair da propria comunidade.\n";
            } else {
                if (ehMembro) { c->removerMembro(db.getIdPerfilLogado()); db.getPerfil(db.getIdPerfilLogado())->sairComunidade(c->getId()); }
                else { c->adicionarMembro(db.getIdPerfilLogado()); db.getPerfil(db.getIdPerfilLogado())->entrarComunidade(c->getId()); }
            }
        }
        else if (op == "B" || op == "b") {
            if (c->podePublicar(db.getIdPerfilLogado())) {
                cout << "Conteudo do post: "; string txt; getline(cin, txt);
                if (!txt.empty()) db.criarPost(txt, c->getId());
            } else {
                cout << "[ERRO] Apenas membros podem postar.\n";
            }
        }
        else if (op == "C" || op == "c") {
            if (postsCom.empty()) continue;
            cout << "Qual Post deseja selecionar: ";
            int idx; cin >> idx; limparBuffer();
            if (idx >= 1 && idx <= static_cast<int>(postsCom.size())) {
                telaPost(db, postsCom[idx - 1]->getId());
            }
        }
    }
}

void telaPerfil(Armazenamento& db, int idPerfil) {
    while (true) {
        Perfil* p = db.getPerfil(idPerfil);
        if (!p) break;
        
        bool ehMeuPerfil = (idPerfil == db.getIdPerfilLogado());
        
        printHeader("EDU SOCIAL PERFIL");
        cout << "@" << p->getNome() << "\n";
        cout << "Bio: " << (p->getDescricao().empty() ? "-" : p->getDescricao()) << "\n";
        cout << "Curso: " << (p->getCurso().empty() ? "-" : p->getCurso()) << "\n";
        cout << "Instituicao: " << (p->getInstituicao().empty() ? "-" : p->getInstituicao()) << "\n";
        cout << "Periodo: " << (p->getPeriodo() == 0 ? "-" : to_string(p->getPeriodo())) << "\n";
        cout << "Seguidores: " << p->getIdsSeguidores().size() << " | Seguidos: " << p->getIdsSeguidos().size() << "\n";
        cout << "Comunidades: " << p->getIdsComunidades().size() << "\n\n";

        if (ehMeuPerfil) {
            cout << "A) Ver meus posts / B) Editar Perfil / C) Ver Seguidores\n";
            cout << "D) Ver Seguidos / E) Voltar\n\n";
        } else {
            cout << "A) Ver posts deste usuario / B) Seguir ou Deixar de Seguir / C) Voltar\n\n";
        }
        
        cout << "Digite sua opcao desejada: ";
        string op; getline(cin, op);

        if (op == "E" || op == "e" || (!ehMeuPerfil && (op == "C" || op == "c"))) break;
        
        else if (op == "A" || op == "a") {
            cout << "\n--- Posts de @" << p->getNome() << " ---\n";
            for (const auto& post : db.getTodosPosts()) {
                if (post.getIdAutor() == p->getId()) {
                    cout << "- " << post.getConteudo() << "\n";
                }
            }
            cout << "\nPressione ENTER para voltar..."; cin.get();
        }
        
        else if (ehMeuPerfil && (op == "B" || op == "b")) { 
            cout << "\n1 - Curso | 2 - Instituicao | 3 - Biografia | 4 - Periodo\nEscolha: ";
            int subOp; cin >> subOp; limparBuffer();
            if (subOp == 1) { cout << "Novo curso: "; string txt; getline(cin, txt); p->setCurso(txt); }
            else if (subOp == 2) { cout << "Nova intituicao: "; string txt; getline(cin, txt); p->setInstituicao(txt); }
            else if (subOp == 3) { cout << "Nova bio: "; string txt; getline(cin, txt); p->setDescricao(txt); }
            else if (subOp == 4) { cout << "Novo periodo: "; int per; cin >> per; limparBuffer(); p->setPeriodo(per); }
        }
        
        else if (ehMeuPerfil && (op == "C" || op == "c")) { 
            auto seguidores = p->getIdsSeguidores();
            cout << "\n--- Seus Seguidores ---\n";
            for (size_t i = 0; i < seguidores.size(); i++) {
                Perfil* seg = db.getPerfil(seguidores[i]);
                if (seg) cout << (i+1) << " - @" << seg->getNome() << "\n";
            }
            cout << "Pressione ENTER para voltar..."; cin.get();
        }
        
        else if (ehMeuPerfil && (op == "D" || op == "d")) {
            while (true) {
                auto seguidos = p->getIdsSeguidos();
                cout << "\n--- Pessoas que voce segue ---\n";
                for (size_t i = 0; i < seguidos.size(); i++) {
                    Perfil* seg = db.getPerfil(seguidos[i]);
                    if (seg) cout << (i+1) << " - @" << seg->getNome() << "\n";
                }
                cout << "\nA) Ver Perfil / B) Deixar de Seguir / C) Voltar\nEscolha: ";
                string subOp; getline(cin, subOp);
                if (subOp == "C" || subOp == "c") break;
                else if (subOp == "A" || subOp == "a" || subOp == "B" || subOp == "b") {
                    if (seguidos.empty()) continue;
                    cout << "Qual numero da lista: "; int num; cin >> num; limparBuffer();
                    if (num >= 1 && num <= static_cast<int>(seguidos.size())) {
                        if (subOp == "A" || subOp == "a") telaPerfil(db, seguidos[num-1]);
                        else if (subOp == "B" || subOp == "b") p->deixarDeSeguir(seguidos[num-1]);
                    }
                }
            }
        }
        
        else if (!ehMeuPerfil && (op == "B" || op == "b")) { 
            Perfil* eu = db.getPerfil(db.getIdPerfilLogado());
            auto meusSeguidos = eu->getIdsSeguidos();
            bool jaSegue = false;
            for(int id : meusSeguidos) if(id == idPerfil) jaSegue = true;
            
            if (jaSegue) {
                eu->deixarDeSeguir(idPerfil);
                cout << "[INFO] Voce deixou de seguir @" << p->getNome() << ".\n";
            } else {
                eu->seguir(idPerfil);
                cout << "[INFO] Voce agora esta seguindo @" << p->getNome() << "!\n";
            }
            cout << "Pressione ENTER para continuar..."; cin.get();
        }
    }
}

void telaBusca(Armazenamento& db) {
    while (true) {
        printHeader("EDU SOCIAL BUSCA");
        cout << "O que voce deseja buscar?\n1 - Perfil\n2 - Comunidade\n3 - Voltar\n\n";
        cout << "Digite sua opcao desejada: ";
        string op; getline(cin, op);

        if (op == "3") break;
        if (op == "1" || op == "2") {
            cout << "Digite a palavra-chave: ";
            string chave; getline(cin, chave);
            
            cout << "\nResultados:\n";
            int contador = 1;
            vector<int> idsEncontrados;

            if (op == "1") {
                for (const auto& p : db.getTodosPerfis()) {
                    if (p.getNome().find(chave) != string::npos) {
                        cout << contador++ << " - @" << p.getNome() << "\n";
                        idsEncontrados.push_back(p.getId());
                    }
                }
            } else if (op == "2") {
                for (const auto& c : db.getTodasComunidades()) {
                    if (c.getNome().find(chave) != string::npos) {
                        cout << contador++ << " - " << c.getNome() << "\n";
                        idsEncontrados.push_back(c.getId());
                    }
                }
            }

            if (idsEncontrados.empty()) {
                cout << "Nenhum resultado encontrado.\n";
                cout << "Pressione ENTER para voltar..."; cin.get();
            } else {
                cout << "\nA) Selecionar / B) Voltar\nEscolha: ";
                string subOp; getline(cin, subOp);
                if (subOp == "A" || subOp == "a") {
                    cout << "Qual numero deseja abrir: ";
                    int idx; cin >> idx; limparBuffer();
                    if (idx >= 1 && idx <= static_cast<int>(idsEncontrados.size())) {
                        if (op == "1") telaPerfil(db, idsEncontrados[idx-1]);
                        else telaComunidadeAberta(db, idsEncontrados[idx-1]);
                    }
                }
            }
        }
    }
}

void telaAlterarCredenciais(Armazenamento& db) {
    printHeader("ALTERAR CREDENCIAIS");
    Usuario* u = db.getUsuario(db.getEmailLogado());
    if (!u) return;

    cout << "1 - Alterar Email\n2 - Alterar Senha\n3 - Voltar\n\nEscolha: ";
    string op; getline(cin, op);

    if (op == "1" || op == "2") {
        cout << "Confirme sua senha atual: "; string atual; getline(cin, atual);
        if (op == "1") {
            cout << "Novo email: "; string nEmail; getline(cin, nEmail);
            if(u->alterarEmail(atual, nEmail)) cout << "[SUCESSO] Email alterado!\n";
            else cout << "[ERRO] Senha atual incorreta!\n";
        } else {
            cout << "Nova senha: "; string nSenha; getline(cin, nSenha);
            if(u->alterarSenha(atual, nSenha)) cout << "[SUCESSO] Senha alterada!\n";
            else cout << "[ERRO] Senha atual incorreta!\n";
        }
        cout << "Pressione ENTER..."; cin.get();
    }
}
