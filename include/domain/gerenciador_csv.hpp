#ifndef GERENCIADOR_CSV_HPP
#define GERENCIADOR_CSV_HPP
#include "comentario.hpp"
#include "comunidade.hpp"
#include "perfil.hpp"
#include "post.hpp"
#include "usuario.hpp"
#include <string>
#include <vector>

/**
 * @file gerenciador_csv.hpp
 * @brief Declaração da classe estática de persistência de dados em arquivos CSV.
 */

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

    /**
     * @brief Separa uma string em vários pedaços usando um delimitador específico.
     * @param linha O texto bruto a ser cortado.
     * @param delimitador O caractere usado como separador (ex: ',').
     * @return Um vetor de strings com os itens separados.
     */
    static std::vector<std::string> separarString(const std::string &linha, char delimitador);

    /**
     * @brief Junta um vetor de inteiros em uma única string de texto.
     * @param lista O vetor de inteiros.
     * @param delimitador O caractere usado para unir os números (ex: '|').
     * @return A string formatada.
     */
    static std::string juntarInteiros(const std::vector<int> &lista, char delimitador);

    /**
     * @brief Converte uma string com delimitadores em um vetor de inteiros.
     * @param linha O texto bruto contendo números.
     * @param delimitador O caractere usado como separador.
     * @return Um vetor de inteiros extraídos do texto.
     */
    static std::vector<int> separarInteiros(const std::string &linha, char delimitador);
    /** @} */

    /**
     * @name Operações de Escrita (Salvar)
     * @brief Exportam os vetores de objetos da memória para seus respectivos arquivos .csv.
     * @{
     */
    static void salvarUsuarios(const std::vector<Usuario> &usuarios, const std::string &arquivo);
    static void salvarPerfis(const std::vector<Perfil> &perfis, const std::string &arquivo);
    static void salvarComunidades(const std::vector<Comunidade> &comunidades, const std::string &arquivo);
    static void salvarPosts(const std::vector<Post> &posts, const std::string &arquivo);
    static void salvarComentarios(const std::vector<Comentario> &comentarios, const std::string &arquivo);
    /** @} */

    /**
     * @name Operações de Leitura (Carregar)
     * @brief Importam os dados dos arquivos .csv e os convertem de volta em vetores de objetos.
     * @{
     */
    static std::vector<Usuario> carregarUsuarios(const std::string &arquivo);
    static std::vector<Perfil> carregarPerfis(const std::string &arquivo);
    static std::vector<Comunidade> carregarComunidades(const std::string &arquivo);
    static std::vector<Post> carregarPosts(const std::string &arquivo);
    static std::vector<Comentario> carregarComentarios(const std::string &arquivo);
    /** @} */
};
#endif