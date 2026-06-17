#ifndef MENUS_HPP
#define MENUS_HPP

#include <vector>
#include "post.hpp"
#include "armazenamento.hpp"

/**
 * @file menus.hpp
 * @brief Declarações das funções auxiliares para exibição de menus interativos.
 * * Este arquivo encapsula as telas de navegação secundárias do sistema (Posts, Listas, Comunidades e Perfis).
 */

/**
 * @brief Renderiza a tela de um Post específico, permitindo interações como curtidas e comentários.
 * @param post Referência mutável ao post selecionado.
 * @param db Referência ao banco de dados central.
 */
void menuVisualizarPost(Post& post, Armazenamento& db);

/**
 * @brief Exibe uma lista de posts e permite que o usuário selecione um deles para detalhamento.
 * @param postsList Vetor contendo os posts a serem exibidos.
 * @param db Referência ao banco de dados central.
 */
void menuVerPostsLista(const std::vector<Post>& postsList, Armazenamento& db);

/**
 * @brief Exibe a interface de uma comunidade, permitindo ingresso, postagem e saída.
 * @param idComunidade O identificador da comunidade a ser aberta.
 * @param db Referência ao banco de dados central.
 */
void menuComunidade(int idComunidade, Armazenamento& db);

/**
 * @brief Exibe o perfil de um usuário (podendo ser o próprio usuário logado ou terceiros).
 * @param idAlvo O identificador do perfil a ser visualizado.
 * @param db Referência ao banco de dados central.
 */
void menuPerfil(int idAlvo, Armazenamento& db);

#endif