#include "domain/aplicacao.hpp"

#include "domain/feed.hpp"
#include "domain/menus.hpp"
#include "domain/usuario.hpp"
#include <console_utils.hpp>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {

void normalizarLinha(std::string &linha) {
    while (!linha.empty() && (linha.back() == '\r' || linha.back() == '\n')) {
        linha.pop_back();
    }
}

bool lerLinha(std::string &destino) {
    if (!std::getline(std::cin, destino)) {
        return false;
    }
    normalizarLinha(destino);
    return !(destino.empty() && std::cin.eof());
}

void abortarEntradaAutomatica(const std::string &motivo) {
    std::cerr << "\n[demo] Entrada automatica interrompida: " << motivo << "\n";
    if (std::getenv("AMBIENTE_DE_TESTE") != nullptr) throw std::runtime_error("EXIT_1");
    std::exit(1); // LCOV_EXCL_LINE
}

void exibirMensagem(const std::string &mensagem) {
    if (!mensagem.empty()) {
        std::cout << mensagem << "\n\n";
    }
}

bool lerOpcaoNumerica(int &valor, bool modoAutomatico, std::string &mensagemErro) {
    if (!(std::cin >> valor)) {
        if (std::cin.eof()) return false; 
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (!modoAutomatico) {
            mensagemErro = "[ERRO] Entrada invalida! Digite um numero.";
        }
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

}  // namespace

Aplicacao::Aplicacao(bool modoAutomatico)
    : db(), busca(), rodando(true), modoAutomatico(modoAutomatico), mensagemAlerta("") {}

void Aplicacao::parar() { rodando = false; }

void Aplicacao::executar() {
    db.carregarDados();

    while (rodando) {
        if (db.getEmailLogado().empty()) {
            exibirTelaInicial();
        } else {
            exibirMenuPrincipal();
        }
        db.salvarDados();
    }
}

void Aplicacao::exibirTelaInicial() {
    ConsoleUtils::limparTela();
    exibirMensagem(mensagemAlerta);
    mensagemAlerta.clear();

    std::cout << "\n////////////////////////////////////////\n";
    std::cout << "        EDU SOCIAL TELA INICIAL         \n";
    std::cout << "////////////////////////////////////////\n";
    std::cout << "1 - Login\n";
    std::cout << "2 - Criar Usuario\n";
    std::cout << "3 - Sair\n\n";
    std::cout << "Digite sua opcao desejada: ";

    int opcao;
    if (!lerOpcaoNumerica(opcao, modoAutomatico, mensagemAlerta)) {
        if (modoAutomatico || std::cin.eof()) { 
            parar();
        }
        return;
    }

    if (opcao == 1) {
        executarLogin();
    } else if (opcao == 2) {
        executarCriarUsuario();
    } else if (opcao == 3) {
        parar();
    }
}

void Aplicacao::exibirMenuPrincipal() {
    ConsoleUtils::limparTela();
    exibirMensagem(mensagemAlerta);
    mensagemAlerta.clear();

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
    if (!lerOpcaoNumerica(opcao, modoAutomatico, mensagemAlerta)) {
        if (modoAutomatico || std::cin.eof()) { 
            parar();
        }
        return;
    }

    ConsoleUtils::limparTela();

    if (opcao == 1) {
        Feed f;
        f.verFeed(db);
    } else if (opcao == 2) {
        executarFluxoPesquisa();
    } else if (opcao == 3) {
        menuVerComunidadesLista(db, nullptr);
    } else if (opcao == 4) {
        executarFluxoVerPerfil();
    } else if (opcao == 5) {
        executarFluxoAlterarCredenciais();
    } else if (opcao == 6) {
        db.deslogar();
    }
}

void Aplicacao::executarLogin() {
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
            mensagemAlerta = "[SUCESSO] Login realizado!";
            break;
        }

        if (modoAutomatico) {
            abortarEntradaAutomatica(
                "login falhou. Verifique email/senha no arquivo (use opcao 1, nao 2).");
        }

        std::cout << "\n[ERRO] Email ou senha invalidos.\n";
        std::cout << "1 - Tentar novamente / 2 - Voltar\nEscolha: ";
        int sub;
        if (!lerOpcaoNumerica(sub, modoAutomatico, mensagemAlerta)) break;
        if (sub == 2) break;
    }
}

void Aplicacao::executarCriarUsuario() {
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
                abortarEntradaAutomatica("senha invalida (minimo 8 caracteres e 1 digito).");
            }
            if (tentativas >= maxTentativas) {
                mensagemAlerta = "[AVISO] Limite de tentativas atingido. Voltando ao menu.";
            }
            continue;
        }

        try {
            db.criarUsuarioEPerfil(email, senha, nome);
            mensagemAlerta = "[SUCESSO] Conta criada!";
            db.salvarDados();
            break;
        } catch (const std::invalid_argument &e) {
            ++tentativas;
            std::cout << "\n[ERRO] " << e.what() << "\n\n";
            if (modoAutomatico) {
                const std::string msg = e.what();
                if (msg.find("email") != std::string::npos) {
                    std::cout << "[demo] Usuario ja existe; seguindo com login.\n";
                    if (std::getenv("AMBIENTE_DE_TESTE") != nullptr) throw std::runtime_error("EXIT_0");
                    std::exit(0); // LCOV_EXCL_LINE
                }
                abortarEntradaAutomatica(msg);
            }
            if (tentativas >= maxTentativas) {
                mensagemAlerta = "[AVISO] Limite de tentativas atingido. Voltando ao menu.";
            }
        }
    }
}

void Aplicacao::executarFluxoPesquisa() {
    std::cout << "\n////////////////////////////////////////\n";
    std::cout << "           EDU SOCIAL - PESQUISA    \n";
    std::cout << "////////////////////////////////////////\n";

    std::cout << "\nO que voce quer buscar?\n";
    std::cout << "1 - Perfil\n2 - Post\n3 - Comunidade\n4 - Voltar\nEscolha: ";

    int cat;
    if (!lerOpcaoNumerica(cat, modoAutomatico, mensagemAlerta)) return;

    if (cat >= 1 && cat <= 3) {
        std::string termo;
        std::cout << "Digite o termo chave: ";
        std::getline(std::cin, termo);

        if (cat == 1) {
            menuVerPerfisLista(busca.buscarPerfis(termo, db), db);
        } else if (cat == 2) {
            menuVerPostsLista(busca.buscarPosts(termo, db), db);
        } else if (cat == 3) {
            const auto achados = busca.buscarComunidades(termo, db);
            menuVerComunidadesLista(db, &achados);
        }
    }
}

void Aplicacao::executarFluxoAlterarCredenciais() {
    Usuario *usuario = db.getUsuario(db.getEmailLogado());
    if (!usuario) { // LCOV_EXCL_LINE 
        mensagemAlerta = "[ERRO] Usuario logado nao encontrado."; // LCOV_EXCL_LINE
        return; // LCOV_EXCL_LINE
    } // LCOV_EXCL_LINE

    std::cout << "\n1 - Alterar Senha\n";
    std::cout << "2 - Alterar Email\n";
    std::cout << "3 - Voltar\n";
    std::cout << "Escolha: ";

    int sub;
    if (!lerOpcaoNumerica(sub, modoAutomatico, mensagemAlerta)) return;

    if (sub == 1) {
        std::string atual, nova;
        std::cout << "Senha atual: ";
        std::getline(std::cin, atual);
        std::cout << "Nova senha (minimo 8 caracteres, com pelo menos 1 digito): ";
        std::getline(std::cin, nova);
        normalizarLinha(nova);

        if (!db.senhaSegura(nova)) {
            mensagemAlerta = "[ERRO] Senha invalida!";
        } else if (usuario->alterarSenha(atual, nova)) {
            mensagemAlerta = "[SUCESSO] Senha alterada!";
        } else {
            mensagemAlerta = "[ERRO] Senha atual incorreta.";
        }
    } else if (sub == 2) {
        std::string atual, novoEmail;
        std::cout << "Senha atual: ";
        std::getline(std::cin, atual);
        std::cout << "Novo email: ";
        std::getline(std::cin, novoEmail);

        if (novoEmail.find('@') == std::string::npos) {
            mensagemAlerta = "[ERRO] Formato de email invalido. Deve conter '@'.";
        } 
        else if (!db.emailUnico(novoEmail) && novoEmail != db.getEmailLogado()) {
            mensagemAlerta = "[ERRO] Email repetido ou ja em uso!";
        } else if (usuario->alterarEmail(atual, novoEmail)) {
            mensagemAlerta = "[SUCESSO] Email alterado! Faca login novamente com o novo email.";
            db.deslogar(); 
        } else {
            mensagemAlerta = "[ERRO] Senha atual incorreta.";
        }
    }
}
void Aplicacao::executarFluxoVerPerfil() {
    if (db.getIdPerfilLogado() > 0) {
        menuPerfil(db.getIdPerfilLogado(), db);
    } else { // LCOV_EXCL_LINE 
        mensagemAlerta = "[ERRO] Perfil logado nao encontrado."; // LCOV_EXCL_LINE
    } // LCOV_EXCL_LINE
}