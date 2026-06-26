#include "domain/console_utils.hpp"
#include <doctest/doctest.h>

TEST_SUITE("ConsoleUtils") {
    TEST_CASE("Garantir que chamadas de UI nao quebram nos testes") {
        CHECK_NOTHROW(ConsoleUtils::limparTela());
        CHECK_NOTHROW(ConsoleUtils::aguardarUsuario());
    }

    TEST_CASE("lerInteiro - Validacoes e Excecoes (Linha 27)") {
        int val = 0;
        CHECK(ConsoleUtils::lerInteiro("123", val) == true);
        CHECK(val == 123);
        CHECK(ConsoleUtils::lerInteiro("", val) == false);
        CHECK(ConsoleUtils::lerInteiro("123a", val) == false);
        CHECK(ConsoleUtils::lerInteiro("abc", val) == false);
        CHECK(ConsoleUtils::lerInteiro("9999999999999999999999999999", val) == false);
    }
}