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
 * @brief Declaração do Banco de Dados em memória (Camada de Dados).
 */

/**
 * @class Armazenamento
 * @brief Classe responsável unicamente por guardar os vetores de dados e gerenciar a persistência.
 * Não contém regras de negócio ou sessão de usuário, operando estritamente como um repositório (Repository Pattern).
 */
class Armazenamento {
  private:
    std::vector<Usuario> usuarios;
    std::vector<Perfil> perfis;
    std::vector<Comunidade> comunidades;
    std::vector<Post> posts;
    std::vector<Comentario> comentarios;

    int proxIdPerfil = 1;
    int proxIdComunidade = 1;
    int proxIdPost = 1;
    int proxIdComentario = 1;

  public:
    /**
     * @brief Inicializa os vetores do banco de dados em memória.
     */
    Armazenamento();

    /**
     * @name Controle de Ciclo de Vida do Banco
     * @brief Métodos para carregar e salvar dados invocando o GerenciadorCSV.
     * @{
     */
    void carregarDados();
    void salvarDados();
    /** @} */

    /**
     * @name Geradores de ID (Auto-Incremento)
     * @brief Fornece chaves primárias únicas para a criação de novas entidades.
     * @{
     */
    int gerarIdPerfil();
    int gerarIdComunidade();
    int gerarIdPost();
    int gerarIdComentario();
    /** @} */

    /**
     * @name Operações de Inserção Direta (Raw Adders)
     * @brief Insere objetos instanciados diretamente nos vetores.
     * @{
     */
    void adicionarUsuario(const Usuario& u);
    void adicionarPerfil(const Perfil& p);
    void adicionarComunidade(const Comunidade& c);
    void adicionarPost(const Post& p);
    void adicionarComentario(const Comentario& c);
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
    /** @} */

    /**
     * @name Acesso Global (Listagens Constantes)
     * @brief Retorna os vetores para fins de busca sem risco de alteração.
     * @{
     */
    const std::vector<Usuario> &getTodosUsuarios() const;
    const std::vector<Perfil> &getTodosPerfis() const;
    const std::vector<Comunidade> &getTodasComunidades() const;
    const std::vector<Post> &getTodosPosts() const;
    
    // Mantidos para compatibilidade exata com seus testes antigos
    const std::vector<Perfil> &listarPerfis() const;
    const std::vector<Comunidade> &listarComunidade() const;
    /** @} */

    /**
     * @name Acesso Global Mutável (Interface Interativa)
     * @brief Expõe as listas internamente para aplicações de curtidas e alterações.
     * @{
     */
    std::vector<Post> &getTodosPostsMutavel();
    std::vector<Comentario> &getTodosComentariosMutavel();
    /** @} */
};

#endif