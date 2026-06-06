#ifndef BUSCA_HPP
#define BUSCA_HPP
#include <vector>
#include <string>
#include "comunidade.hpp"
#include "perfil.hpp"
#include "feed.hpp"

/**
 * @brief Classe responsável por orquestrar as pesquisas dentro da rede social.
 * * Permite encontrar postagens, perfis e comunidades com base em palavras-chave.
 */

class Busca {

public:

    /**
     * @brief Realiza uma busca no sistema baseada em uma palavra-chave.
     * * Pesquisa postagens (mesmo de comunidades ou usuários que o usuário não segue), 
     * perfis e comunidades que correspondam ao termo.
     * * @param palavraChave O termo que deseja buscar.
     */

    void buscarPalavraChave(std::string palavraChave);

    /**
     * @brief Apresenta os resultados da pesquisa formatados na tela.
     * * Exibe um cabeçalho e, em seguida, mostra os resultados integrados a um Feed.
     */

    void exibirResultadosPesquisa();

    /**
     * @brief Filtra os resultados da busca por categoria.
     * * Os resultados filtrados podem ser exibidos em ordem alfabética.
     * * @param tipo O tipo de filtro a ser aplicado (ex: "post", "perfil", "comunidade").
     */

    void filtrarResultados(std::string tipo);

};

#endif