cmake_minimum_required(VERSION 3.10)
project(EduSocial)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define onde salvar os executáveis (pasta bin na raiz)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Adiciona as pastas de headers para que o compilador encontre os arquivos em "domain"
include_directories(include include/domain tests)

# 1. Coleta todos os arquivos .cpp de implementação (src/ e src/domain/)
file(GLOB_RECURSE ALL_SRC "src/*.cpp")

# Remove a main.cpp do aplicativo da lista de fontes das classes
# (para evitar conflito quando formos compilar os testes)
list(REMOVE_ITEM ALL_SRC "${CMAKE_SOURCE_DIR}/src/main.cpp")

# 2. Executável do Aplicativo (usa src/main.cpp e as classes em src/domain/)
add_executable(edusocial src/main.cpp ${ALL_SRC})

# 3. Executável de Testes (usa arquivos da pasta tests e as classes em src/domain/)
file(GLOB_RECURSE TEST_FILES "tests/*.cpp")
# Garante que a main de teste não seja tratada como fonte de classe
list(REMOVE_ITEM TEST_FILES "${CMAKE_SOURCE_DIR}/tests/main.cpp")

add_executable(run_tests ${TEST_FILES} ${ALL_SRC})