#ifndef ARMAZENAMENTO_HPP
#define ARMAZENAMENTO_HPP
#include "comentario.hpp"
#include "comunidade.hpp"
#include "gerenciador_csv.hpp"
#include "perfil.hpp"
#include "post.hpp"
#include "usuario.hpp"
#include <string>
#include <vector>

/**
 * @file armazenamento.hpp
 * @brief Declaração do Banco de Dados em memória (Armazenamento).
 */

/**
 * @class Armazenamento
 * @brief Classe núcleo responsável por centralizar o gerenciamento de dados do sistema.
 * * Funciona como o Banco de Dados em memória RAM durante a execução do programa, controlando
 * os índices auto-incrementais, sessões de usuário ativo e orquestrando as chamadas de persistência.
 */
class Armazenamento {
  private:
    std::vector<Usuario> usuarios;
    std::vector<Perfil> perfis;
    std::vector<Comunidade> comunidades;
    std::vector<Post> posts;
    std::vector<Comentario> comentarios;

    std::string emailLogado;
    int idPerfilLogado;

    int proxIdPerfil = 1;
    int proxIdComunidade = 1;
    int proxIdPost = 1;
    int proxIdComentario = 1;

  public:
    /**
     * @brief Inicializa o sistema de armazenamento temporário com valores padrões e estado deslogado.
     */
    Armazenamento();

    /**
     * @brief Verifica se a senha atende aos requisitos mínimos de segurança (compatibilidade com testes).
     * @param senha A senha a ser avaliada.
     * @return true se for segura, false caso contrário.
     */
    bool senhaSegura(const std::string &senha) const;

    /**
     * @brief Lista todos os perfis armazenados no sistema (compatibilidade com testes).
     * @return Uma referência constante para o vetor de perfis.
     */
    const std::vector<Perfil> &listarPerfis() const;

    /**
     * @brief Adiciona diretamente um objeto Perfil ao vetor (compatibilidade com testes).
     * @param p O perfil a ser adicionado à base.
     */
    void criarPerfil(const Perfil &p);

    /**
     * @brief Lista todas as comunidades armazenadas no sistema (compatibilidade com testes).
     * @return Uma referência constante para o vetor de comunidades.
     */
    const std::vector<Comunidade> &listarComunidade() const;

    /**
     * @brief Adiciona diretamente um objeto Comunidade ao vetor (compatibilidade com testes).
     * @param c A comunidade a ser adicionada à base.
     */
    void criarComunidade(const Comunidade &c);

    /**
     * @name Controle de Ciclo de Vida do Banco
     * @brief Métodos para carregar e salvar dados invocando o GerenciadorCSV.
     * @{
     */

    /** @brief Importa todos os dados dos arquivos CSV para a memória. */
    void carregarDados();

    /** @brief Exporta o estado atual da memória para os arquivos CSV. */
    void salvarDados();

    /** @} */

    /**
     * @name Autenticação, Sessão e Validação
     * @brief Métodos para checar duplicidades, login e gerenciamento de estado do usuário ativo.
     * @{
     */

    /**
     * @brief Verifica se o email informado já existe na base de dados.
     * @param email O email a ser checado.
     * @return true se o email for único, false se já estiver em uso.
     */
    bool emailUnico(const std::string &email);

    /**
     * @brief Verifica se o nome de usuário informado já existe na base de dados.
     * @param nome O nome a ser checado.
     * @return true se o nome for único, false se já estiver em uso.
     */
    bool nomeUsuarioUnico(const std::string &nome);

    /**
     * @brief Valida credenciais e inicia a sessão de um usuário.
     * @param email Email do usuário.
     * @param senha Senha de acesso.
     * @return true se o login for bem-sucedido, false caso contrário.
     */
    bool fazerLogin(const std::string &email, const std::string &senha);

    /** @brief Encerra a sessão do usuário atual. */
    void deslogar();

    /** @brief Retorna o ID do perfil atualmente logado. @return ID do perfil. */
    int getIdPerfilLogado() const;

    /** @brief Retorna o email do usuário atualmente logado. @return String com o email. */
    std::string getEmailLogado() const { return emailLogado; }

    /** @} */

    /**
     * @name Operações de Escrita (Criar Entidades)
     * @brief Regras de negócio para inserção segura de novos registros no sistema.
     * @{
     */

    /**
     * @brief Registra um novo Usuário e seu respectivo Perfil simultaneamente.
     * @param email Email para a nova conta.
     * @param senha Senha de segurança.
     * @param nome Nome de exibição público.
     * @throw std::invalid_argument se os dados forem inválidos ou repetidos.
     */
    void criarUsuarioEPerfil(std::string email, std::string senha, std::string nome);

    /**
     * @brief Cria uma nova publicação.
     * @param texto Conteúdo do post.
     * @param idComunidade Opcional. ID da comunidade destino (Padrão: 0 para Global).
     * @throw std::invalid_argument se o texto for vazio.
     */
    void criarPost(std::string texto, int idComunidade = 0);

    /**
     * @brief Cria uma nova comunidade gerenciada pelo usuário logado.
     * @param nome Título do grupo.
     * @param descricao Informações sobre a comunidade.
     * @throw std::invalid_argument se as strings estiverem vazias.
     */
    void criarComunidade(std::string nome, std::string descricao);

    /**
     * @brief Registra um novo comentário em um post existente.
     * @param idPost ID da publicação alvo.
     * @param idAutor ID do perfil criador do comentário.
     * @param texto O texto do comentário.
     * @throw std::invalid_argument se o texto for vazio.
     */
    void criarComentarioGlobal(int idPost, int idAutor, std::string texto);
    /** @} */

    /**
     * @name Consultas Diretas (Ponteiros/Relacionamentos)
     * @brief Buscam e retornam referências a objetos específicos com base em chaves primárias.
     * @{
     */
    Perfil *getPerfil(int id);
    const Perfil *getPerfil(int id) const;

    Usuario *getUsuario(const std::string &email);
    const Usuario *getUsuario(const std::string &email) const;

    Comunidade *getComunidade(int id);
    const Comunidade *getComunidade(int id) const;

    Post *getPostMutavel(int id);
    const Post *getPost(int id) const;

    /**
     * @name Acesso Global (Apenas Leitura)
     * @brief Fornece acesso controlado aos vetores para fins de busca sem risco de alteração.
     * @{
     */
    const std::vector<Perfil> &getTodosPerfis() const;
    const std::vector<Comunidade> &getTodasComunidades() const;
    const std::vector<Post> &getTodosPosts() const;
    /** @} */

    /**
     * @name Acesso Global Mutável (Interface Interativa)
     * @brief Expõe as listas internamente para que o controlador visual (Main/Menus) possa aplicar curtidas.
     * @{
     */
    std::vector<Post> &getTodosPostsMutavel();
    std::vector<Comentario> &getTodosComentariosMutavel();
    /** @} */
};

#endif