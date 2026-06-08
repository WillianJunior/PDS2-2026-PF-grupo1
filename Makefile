BUILD_DIR := build
BUILD_TYPE ?= Debug
CMAKE_ARGS := -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
JOBS ?= 4

.PHONY: all configure build run test docs clean help

all: build

configure:
	@echo "[cmake] Configurando projeto (BUILD_TYPE=$(BUILD_TYPE))..."
	@cmake -S . -B $(BUILD_DIR) $(CMAKE_ARGS)

build: configure
	@echo "[make] Compilando com $(JOBS) thread(s)..."
	@cmake --build $(BUILD_DIR) --parallel $(JOBS)

run: build
	@echo "[run] Iniciando servidor..."
	@cmake --build $(BUILD_DIR) --target edu_social_backend

test: build
	@echo "[test] Executando testes..."
	@ctest --test-dir $(BUILD_DIR) --output-on-failure --parallel $(JOBS)

docs:
	@echo "[docs] Gerando documentação com Doxygen..."
	@doxygen design/Doxyfile

clean:
	@echo "[clean] Removendo diretório de build..."
	@cmake -E remove_directory $(BUILD_DIR)

help:
	@echo
	@echo "Uso: make [alvo] [VARIAVEL=valor]"
	@echo
	@echo "Alvos:"
	@echo "  all        Compila o projeto"
	@echo "  configure  Configura o CMake"
	@echo "  build      Compila o projeto"
	@echo "  run        Compila o backend"
	@echo "  test       Executa os testes"
	@echo "  docs       Gera documentação"
	@echo "  clean      Remove o diretório build"
	@echo
	@echo "Exemplos:"
	@echo "  make build BUILD_TYPE=Release"
	@echo "  make test JOBS=2"