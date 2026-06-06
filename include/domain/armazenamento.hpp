#ifndef ARMAZENAMENTO_HPP
#define ARMAZENAMENTO_HPP
#include "perfil.hpp"
#include "feed.hpp"
#include "comunidade.hpp"

/**
 * @brief Classe responsável por gerenciar o armazenamento em memória do sistema.
 * * Atua como um "banco de dados" temporário, guardando as listas de perfis, 
 * comunidades e o estado do usuário logado atualmente.
 */

class Armazenamento {

private:

    std::vector<Perfil> perfis;
    std::vector<Comunidade> comunidades;
    Perfil usuarioLogado;

public:

    /**
     * @brief Verifica se um e-mail já está cadastrado no sistema.
     * @param email O e-mail a ser verificado.
     * @return true se o e-mail for único (não cadastrado), false caso contrário.
     */

    bool emailUnico(std::string email);

    /**
     * @brief Valida se a senha atende aos critérios de segurança do sistema.
     * @param senha A senha a ser validada.
     * @return true se a senha for segura, false caso contrário.
     */

    bool senhaSegura(std::string senha);

    /**
     * @brief Exibe uma mensagem genérica de sucesso ou erro no terminal.
     */

    void mensagemSucessoErro();

    /**
     * @brief Obtém os dados do perfil do usuário que está atualmente logado.
     * @return O objeto Perfil do usuário logado.
     */

    Perfil getUsuarioLogado();

    /**
     * @brief Adiciona um novo perfil ao armazenamento do sistema.
     * @param perfil O objeto Perfil a ser salvo.
     */

    void criarPerfil(Perfil perfil);

    /**
     * @brief Remove um perfil do sistema com base no seu ID.
     * @param id O identificador do perfil a ser deletado.
     * @return O objeto Perfil que foi deletado (para fins de log ou desfazimento).
     */

    Perfil deletarPerfil(int id);

    /**
     * @brief Retorna a lista de todos os perfis cadastrados.
     * @return Um vetor contendo todos os objetos Perfil do sistema.
     */

    std::vector<Perfil> listarPerfis();

    /**
     * @brief Adiciona uma nova comunidade ao armazenamento do sistema.
     * @param comunidade O objeto Comunidade a ser salvo.
     */

    void criarComunidade(Comunidade comunidade);

    /**
     * @brief Remove uma comunidade do sistema com base no seu ID.
     * @param id O identificador da comunidade a ser deletada.
     * @return O objeto Comunidade que foi deletado.
     */

    Comunidade deletarComunidade(int id);

    /**
     * @brief Retorna a lista de todas as comunidades cadastradas.
     * @return Um vetor contendo todos os objetos Comunidade do sistema.
     */

    std::vector<Comunidade> listarComunidade();
    
};
#endif