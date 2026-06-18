#ifndef ARMAZENAMENTO_HPP
#define ARMAZENAMENTO_HPP
#include "usuario.hpp"
#include "perfil.hpp"
#include "comunidade.hpp"
#include "post.hpp"
#include "comentario.hpp"
#include "gerenciador_csv.hpp"
#include <vector>
#include <string>

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
     * @brief Inicializa o sistema de armazenamento temporário com valores padrões e deslogado.
     */
    Armazenamento();

    /**
     * @brief Verifica se a senha atende aos requisitos mínimos de segurança (compatibilidade com testes).
     * @param senha A senha a ser avaliada.
     * @return true se for segura, false caso contrário.
     */
    bool senhaSegura(const std::string& senha) const;

    /**
     * @brief Lista todos os perfis armazenados no sistema (compatibilidade com testes).
     * @return Vetor contendo cópias dos perfis.
     */
    const std::vector<Perfil>& listarPerfis() const;

    /**
     * @brief Adiciona diretamente um objeto Perfil ao vetor (compatibilidade com testes).
     * @param p O perfil a ser adicionado.
     */
    void criarPerfil(const Perfil& p);

    /**
     * @brief Lista todas as comunidades armazenadas no sistema (compatibilidade com testes).
     * @return Vetor contendo cópias das comunidades.
     */
    const std::vector<Comunidade>& listarComunidade() const;

    /**
     * @brief Adiciona diretamente um objeto Comunidade ao vetor (compatibilidade com testes).
     * @param c A comunidade a ser adicionada.
     */
    void criarComunidade(const Comunidade& c);

    /**
     * @brief Método utilitário fictício para feedbacks sem lançar exceções (compatibilidade com testes).
     */
    void mensagemSucessoErro() const;

    /**
     * @name Controle de Ciclo de Vida do Banco
     * @brief Métodos para carregar e salvar dados invocando o GerenciadorCSV.
     * @{
     */
    void carregarDados();
    void salvarDados();
    /** @} */

    /**
     * @name Autenticação, Sessão e Validação
     * @brief Métodos para checar duplicidades, login e gerenciamento de estado do usuário ativo.
     * @{
     */
    bool emailUnico(const std::string& email);
    bool nomeUsuarioUnico(const std::string& nome);
    bool fazerLogin(const std::string& email, const std::string& senha);
    void deslogar();
    int getIdPerfilLogado() const;
    std::string getEmailLogado() const { return emailLogado; }
    /** @} */

    /**
     * @name Operações de Escrita (Criar Entidades)
     * @brief Regras de negócio para inserção segura de novos registros no sistema.
     * @{
     */
    void criarUsuarioEPerfil(std::string email, std::string senha, std::string nome);
    void criarPost(std::string texto, int idComunidade = 0);
    void criarComunidade(std::string nome, std::string descricao);
    void criarComentarioGlobal(int idPost, int idAutor, std::string texto);
    /** @} */
    
    /**
     * @name Consultas Diretas (Ponteiros/Relacionamentos)
     * @brief Buscam e retornam referências a objetos específicos com base em chaves primárias.
     * @{
     */
    Perfil* getPerfil(int id);
    const Perfil* getPerfil(int id) const;

    Usuario* getUsuario(const std::string& email);
    const Usuario* getUsuario(const std::string& email) const;

    Comunidade* getComunidade(int id);
    const Comunidade* getComunidade(int id) const;

    Post* getPostMutavel(int id);
    const Post* getPost(int id) const;

   std::vector<Post> getPostsFeed() const;
    /** @} */

    /**
     * @name Acesso Global (Apenas Leitura)
     * @brief Fornece acesso controlado aos vetores para fins de busca sem risco de alteração.
     * @{
     */
    const std::vector<Perfil>& getTodosPerfis() const;
    const std::vector<Comunidade>& getTodasComunidades() const;
    const std::vector<Post>& getTodosPosts() const;
    /** @} */

    /**
     * @name Acesso Global Mutável (Interface Interativa)
     * @brief Expõe as listas internamente para que o controlador visual (Main) possa aplicar curtidas.
     * @{
     */
    std::vector<Post>& getTodosPostsMutavel();
    std::vector<Comentario>& getTodosComentariosMutavel();
    /** @} */
};

#endif