# =============================================================================
# Makefile — edu_social
# Projeto C++ com CMake e Doctest
# =============================================================================

BUILD_DIR  := build
CMAKE_ARGS := -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
BUILD_TYPE ?= Debug
JOBS       ?= $(shell nproc 2>/dev/null || sysctl -n hw.logicalcpu 2>/dev/null || echo 4)

.PHONY: all configure build run test docs clean help

all: build

configure:
	@if [ ! -f $(BUILD_DIR)/CMakeCache.txt ]; then \
		echo "[cmake] Configurando projeto (BUILD_TYPE=$(BUILD_TYPE))..."; \
		cmake -S . -B $(BUILD_DIR) $(CMAKE_ARGS); \
	fi

build: configure
	@echo "[make] Compilando com $(JOBS) thread(s)..."
	cmake --build $(BUILD_DIR) --parallel $(JOBS)

run: build
	@echo "[run] Iniciando servidor..."
	./$(BUILD_DIR)/bin/edu_social_backend

test: build
	@echo "[test] Executando testes..."
	ctest --test-dir $(BUILD_DIR) --output-on-failure --parallel $(JOBS)

docs:
	@echo "[docs] Gerando documentação com Doxygen..."
	doxygen design/Doxyfile

clean:
	@echo "[clean] Removendo diretório de build..."
	rm -rf $(BUILD_DIR)

help:
	@echo ""
	@echo "Uso: make [alvo] [VARIÁVEL=valor]"
	@echo ""
	@echo "Alvos:"
	@echo "  all        Compila o projeto (padrão)"
	@echo "  configure  Executa o cmake -S . -B build"
	@echo "  build      Compila o projeto"
	@echo "  run        Compila e executa o servidor"
	@echo "  test       Compila e roda os testes (ctest)"
	@echo "  docs       Gera documentação com Doxygen"
	@echo "  clean      Remove o diretório de build"
	@echo ""
	@echo "Variáveis:"
	@echo "  BUILD_TYPE   Debug (padrão) | Release | RelWithDebInfo"
	@echo "  JOBS         Número de threads de compilação (padrão: nproc)"
	@echo ""
	@echo "Exemplos:"
	@echo "  make build BUILD_TYPE=Release"
	@echo "  make test  JOBS=2"
	@echo ""