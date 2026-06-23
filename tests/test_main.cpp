#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include <cstdlib>

int main(int argc, char **argv) {
#if defined(_WIN32) || defined(_WIN64)
    _putenv("AMBIENTE_DE_TESTE=1");
#else
    setenv("AMBIENTE_DE_TESTE", "1", 1);
#endif

    doctest::Context context;
    context.applyCommandLine(argc, argv);
    return context.run();
}