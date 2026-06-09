#ifndef BUSCA_HPP
#define BUSCA_HPP

#include <string>
#include <vector>
#include "domain/armazenamento.hpp"

/**
 * @class Busca
 * @brief Classe responsável pelo mecanismo de busca textual dentro da rede social.
 */
class Busca {
private:
    std::vector<std::string> resultados;

public:
    /**
     * @brief Realiza a varredura no sistema em busca de uma palavra-chave.
     * @param palavraChave O termo textual desejado para a pesquisa.
     * @param db Referência constante ao banco de dados.
     */
    void buscarPalavraChave(const std::string& palavraChave, const Armazenamento& db);

    /**
     * @brief Apresenta os resultados coletados na última busca formatados na tela.
     */
    void exibirResultadosPesquisa() const;

    /**
     * @brief Filtra os resultados da busca por tipo.
     */
    void filtrarResultados(const std::string& tipo);
};

#endif