#include "restaurar_entrada_cin.hpp"

RestaurarEntradaCin::RestaurarEntradaCin(std::streambuf *original) 
    : original_(original) {}

RestaurarEntradaCin::~RestaurarEntradaCin() {
    std::cin.rdbuf(original_);
}