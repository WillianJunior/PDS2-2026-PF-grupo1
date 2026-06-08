#ifndef BUSCA_HPP
#define BUSCA_HPP
#include <string>
#include <vector>
#include "armazenamento.hpp"

/**
 * @brief Classe responsável pelo mecanismo de busca textual dentro da rede social.
 * * Percorre dinamicamente todas as entidades indexadas para encontrar correspondências.
 */
class Busca {
private:
    std::vector<std::string> resultados;

public:
    /**
     * @brief Realiza a varredura no sistema em busca de uma palavra-chave.
     * * Pesquisa em nomes e descrições de perfis/comunidades, bem como no texto dos posts.
     * @param palavraChave O termo textual desejado para a pesquisa.
     * @param db Referência constante ao banco de dados para leitura segura das informações.
     */
    void buscarPalavraChave(const std::string& palavraChave, const Armazenamento& db);

    /**
     * @brief Apresenta os resultados coletados na última busca formatados na tela.
     */
    void exibirResultadosPesquisa() const;
};
#endif
