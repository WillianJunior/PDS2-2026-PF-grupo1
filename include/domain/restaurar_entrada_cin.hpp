#ifndef DOMAIN_RESTAURAR_ENTRADA_CIN_HPP
#define DOMAIN_RESTAURAR_ENTRADA_CIN_HPP

#include <iostream>

/**
 * @class RestaurarEntradaCin
 * @brief Classe utilitária baseada em RAII para restaurar automaticamente o buffer do std::cin.
 */
class RestaurarEntradaCin {
public:
    /**
     * @brief Construtor que armazena o buffer original do cin.
     * @param original Ponteiro para o streambuf original obtido com std::cin.rdbuf().
     */
    explicit RestaurarEntradaCin(std::streambuf *original);

    /**
     * @brief Destrutor que devolve o buffer original salvo ao std::cin.
     */
    ~RestaurarEntradaCin();

    // Desabilita cópia e atribuição para evitar duplicação perigosa de ponteiros de buffer
    RestaurarEntradaCin(const RestaurarEntradaCin &) = delete;
    RestaurarEntradaCin &operator=(const RestaurarEntradaCin &) = delete;

private:
    std::streambuf *original_;
};

#endif