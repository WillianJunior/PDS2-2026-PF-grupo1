#ifndef GERENCIADOR_CSV_HPP
#define GERENCIADOR_CSV_HPP
#include <string>
#include <vector>
#include "usuario.hpp"
#include "perfil.hpp"
#include "comunidade.hpp"
#include "post.hpp"
#include "comentario.hpp"

/**
 * @class GerenciadorCSV
 * @brief Classe estática utilitária responsável pela leitura e escrita dos dados em arquivos CSV.
 * * Atua como o mecanismo de conversão entre arquivos físicos de texto e objetos em memória,
 * simulando o comportamento de um banco de dados relacional simplificado.
 */
class GerenciadorCSV {
public:
    /**
     * @name Utilitários de String
     * @brief Métodos auxiliares para parsing de linhas de texto e listas de inteiros.
     * @{
     */
    static std::vector<std::string> separarString(const std::string& linha, char delimitador);
    static std::string juntarInteiros(const std::vector<int>& lista, char delimitador);
    static std::vector<int> separarInteiros(const std::string& linha, char delimitador);
    /** @} */

    /**
     * @name Operações de Escrita (Salvar)
     * @brief Exportam os vetores de objetos da memória para seus respectivos arquivos .csv.
     * @{
     */
    static void salvarUsuarios(const std::vector<Usuario>& usuarios, const std::string& arquivo);
    static void salvarPerfis(const std::vector<Perfil>& perfis, const std::string& arquivo);
    static void salvarComunidades(const std::vector<Comunidade>& comunidades, const std::string& arquivo);
    static void salvarPosts(const std::vector<Post>& posts, const std::string& arquivo);
    static void salvarComentarios(const std::vector<Comentario>& comentarios, const std::string& arquivo);
    /** @} */

    /**
     * @name Operações de Leitura (Carregar)
     * @brief Importam os dados dos arquivos .csv e os convertem de volta em vetores de objetos.
     * @{
     */
    static std::vector<Usuario> carregarUsuarios(const std::string& arquivo);
    static std::vector<Perfil> carregarPerfis(const std::string& arquivo);
    static std::vector<Comunidade> carregarComunidades(const std::string& arquivo);
    static std::vector<Post> carregarPosts(const std::string& arquivo);
    static std::vector<Comentario> carregarComentarios(const std::string& arquivo);
    /** @} */
};
#endif