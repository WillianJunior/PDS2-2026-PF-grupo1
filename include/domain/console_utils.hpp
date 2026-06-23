#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

/**
 * @file console_utils.hpp
 * @brief Funções utilitárias estáticas para manipulação da interface de linha de comando.
 */

/**
 * @class ConsoleUtils
 * @brief Classe utilitária que encapsula comandos do sistema operacional.
 * * Fornece métodos independentes de plataforma para limpar a tela e pausar a execução,
 * além de possuir proteções embutidas para não interferir em ambientes de teste.
 */
class ConsoleUtils {
public:
    /**
     * @brief Limpa o terminal do usuário (cross-platform: clear/cls).
     * @note Se a variável de ambiente AMBIENTE_DE_TESTE estiver ativa, a função é ignorada.
     */
    static void limparTela();

    /**
     * @brief Pausa a execução do programa e aguarda a tecla ENTER ser pressionada.
     * @note Se a variável de ambiente AMBIENTE_DE_TESTE estiver ativa, a função é ignorada.
     */
    static void aguardarUsuario();
};

#endif