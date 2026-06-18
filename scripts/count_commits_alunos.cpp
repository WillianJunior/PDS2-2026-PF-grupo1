#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#define POPEN _popen
#define PCLOSE _pclose
#else
#define POPEN popen
#define PCLOSE pclose
#endif

namespace fs = std::filesystem;

constexpr int kLineWidth = 62;
constexpr int kEmailColumnWidth = 34;

struct Aluno {
    std::string nome;
    std::vector<std::string> emails;
};

struct ResultadoAluno {
    std::string nome;
    int total;
    std::vector<std::pair<std::string, int>> detalhes;
};

void configurarSaidaUtf8() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
    std::ios_base::sync_with_stdio(false);
}

std::string repetir(char c, int n) {
    return std::string(static_cast<std::size_t>(n), c);
}

std::string padDireita(const std::string& texto, int largura) {
    if (static_cast<int>(texto.size()) >= largura) {
        return texto;
    }
    return texto + std::string(static_cast<std::size_t>(largura - texto.size()), ' ');
}

std::string padEsquerda(const std::string& texto, int largura) {
    if (static_cast<int>(texto.size()) >= largura) {
        return texto;
    }
    return std::string(static_cast<std::size_t>(largura - texto.size()), ' ') + texto;
}

std::string executarComando(const std::string& comando) {
    std::string saida;
    char buffer[256];

    FILE* pipe = POPEN(comando.c_str(), "r");
    if (pipe == nullptr) {
        throw std::runtime_error("Falha ao executar comando: " + comando);
    }

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        saida += buffer;
    }

    if (PCLOSE(pipe) != 0 && saida.empty()) {
        throw std::runtime_error("Comando retornou erro: " + comando);
    }

    while (!saida.empty() && (saida.back() == '\n' || saida.back() == '\r')) {
        saida.pop_back();
    }

    return saida;
}

int contarCommits(const std::string& email) {
#ifdef _WIN32
    const std::string redirecionarErro = " 2>nul";
#else
    const std::string redirecionarErro = " 2>/dev/null";
#endif
    const std::string comando =
        "git rev-list --all --author=\"" + email + "\" --count" + redirecionarErro;

    try {
        const std::string resultado = executarComando(comando);
        if (resultado.empty()) {
            return 0;
        }
        return std::stoi(resultado);
    } catch (const std::exception&) {
        throw std::runtime_error("Erro ao consultar git para " + email);
    }
}

std::string nomeRepositorio() {
#ifdef _WIN32
    const std::string redirecionarErro = " 2>nul";
#else
    const std::string redirecionarErro = " 2>/dev/null";
#endif
    try {
        const std::string topo =
            executarComando("git rev-parse --show-toplevel" + redirecionarErro);
        if (topo.empty()) {
            return fs::current_path().filename().string();
        }
        return fs::path(topo).filename().string();
    } catch (const std::exception&) {
        return fs::current_path().filename().string();
    }
}

std::vector<Aluno> carregarAlunos(const fs::path& caminho) {
    if (!fs::exists(caminho)) {
        throw std::runtime_error("Arquivo de configuracao nao encontrado: " + caminho.string());
    }

    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir: " + caminho.string());
    }

    std::ostringstream buffer;
    buffer << arquivo.rdbuf();
    const std::string conteudo = buffer.str();

    std::vector<Aluno> alunos;
    std::size_t pos = 0;

    while ((pos = conteudo.find("\"nome\"", pos)) != std::string::npos) {
        Aluno aluno;

        pos = conteudo.find(':', pos);
        pos = conteudo.find('"', pos) + 1;
        const std::size_t fimNome = conteudo.find('"', pos);
        aluno.nome = conteudo.substr(pos, fimNome - pos);

        pos = conteudo.find("\"emails\"", fimNome);
        pos = conteudo.find('[', pos);
        const std::size_t fimLista = conteudo.find(']', pos);
        const std::string blocoEmails = conteudo.substr(pos, fimLista - pos);

        std::size_t cursor = 0;
        while ((cursor = blocoEmails.find('"', cursor + 1)) != std::string::npos) {
            const std::size_t fimEmail = blocoEmails.find('"', cursor + 1);
            if (fimEmail == std::string::npos) {
                break;
            }
            aluno.emails.push_back(blocoEmails.substr(cursor + 1, fimEmail - cursor - 1));
            cursor = fimEmail;
        }

        alunos.push_back(aluno);
        pos = fimLista;
    }

    if (alunos.empty()) {
        throw std::runtime_error("Nenhum integrante encontrado em: " + caminho.string());
    }

    return alunos;
}

void imprimirCabecalho(const std::string& repo, const fs::path& config) {
    const std::string linhaDupla = repetir('=', kLineWidth);

    std::cout << '\n';
    std::cout << linhaDupla << '\n';
    std::cout << "  CONTAGEM DE COMMITS POR INTEGRANTE\n";
    std::cout << linhaDupla << '\n';
    std::cout << "  Repositório : " << repo << '\n';
    std::cout << "  Escopo      : todas as branches (--all)\n";
    std::cout << "  Método      : git rev-list --all --author=<email> --count\n";
    std::cout << "  Config      : " << config.string() << '\n';
    std::cout << linhaDupla << "\n\n";
}

void imprimirDetalheIntegrante(const ResultadoAluno& resultado) {
    const std::string linha = repetir('-', kLineWidth);

    std::cout << "  " << resultado.nome << '\n';
    std::cout << "  " << linha << '\n';

    for (const auto& [email, quantidade] : resultado.detalhes) {
        std::cout << "    - " << padDireita(email, kEmailColumnWidth) << ' '
                  << padEsquerda(std::to_string(quantidade), 4) << " commit(s)\n";
    }

    std::ostringstream rotulo;
    rotulo << "    Total do integrante";
    const std::string textoRotulo = rotulo.str();
    std::cout << textoRotulo;
    const int pontos = 36 - static_cast<int>(textoRotulo.size());
    if (pontos > 0) {
        std::cout << std::string(static_cast<std::size_t>(pontos), '.');
    }
    std::cout << ' ' << padEsquerda(std::to_string(resultado.total), 4) << " commit(s)\n\n";
}

void imprimirResumo(const std::vector<ResultadoAluno>& resultados, int totalGeral) {
    const std::string linhaDupla = repetir('=', kLineWidth);
    const std::string linha = repetir('-', kLineWidth);

    int larguraNome = static_cast<int>(std::string("Integrante").size());
    for (const auto& resultado : resultados) {
        larguraNome = std::max(larguraNome, static_cast<int>(resultado.nome.size()));
    }

    std::cout << linhaDupla << '\n';
    std::cout << "  " << padDireita("Integrante", larguraNome) << "   "
              << padEsquerda("Commits", 8) << '\n';
    std::cout << linha << '\n';

    for (const auto& resultado : resultados) {
        std::cout << "  " << padDireita(resultado.nome, larguraNome) << "   "
                  << padEsquerda(std::to_string(resultado.total), 8) << '\n';
    }

    std::cout << linha << '\n';
    std::cout << "  " << padDireita("TOTAL GERAL", larguraNome) << "   "
              << padEsquerda(std::to_string(totalGeral), 8) << '\n';
    std::cout << linhaDupla << "\n\n";
}

int main(int argc, char* argv[]) {
    try {
        configurarSaidaUtf8();

        const fs::path config =
            (argc > 1) ? fs::path(argv[1]) : fs::path("scripts/alunos.json");

        const std::vector<Aluno> alunos = carregarAlunos(config);
        const std::string repo = nomeRepositorio();

        imprimirCabecalho(repo, config);

        std::vector<ResultadoAluno> resultados;
        int totalGeral = 0;

        for (const Aluno& aluno : alunos) {
            ResultadoAluno resultado;
            resultado.nome = aluno.nome;
            resultado.total = 0;

            for (const std::string& email : aluno.emails) {
                const int quantidade = contarCommits(email);
                resultado.detalhes.emplace_back(email, quantidade);
                resultado.total += quantidade;
            }

            totalGeral += resultado.total;
            resultados.push_back(resultado);
            imprimirDetalheIntegrante(resultado);
        }

        imprimirResumo(resultados, totalGeral);
        return 0;
    } catch (const std::exception& excecao) {
        std::cerr << "Erro: " << excecao.what() << '\n';
        return 1;
    }
}
