#include "domain/console_utils.hpp"
#include <doctest/doctest.h>

TEST_SUITE("ConsoleUtils") {
    TEST_CASE("Garantir que chamadas de UI nao quebram nos testes") {
        CHECK_NOTHROW(ConsoleUtils::limparTela());
        CHECK_NOTHROW(ConsoleUtils::aguardarUsuario());
    }
}