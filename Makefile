BUILD_DIR := build
BUILD_TYPE ?= Debug
CMAKE_ARGS := -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_CXX_FLAGS="--coverage" -DCMAKE_EXE_LINKER_FLAGS="--coverage"
JOBS ?= 4

.PHONY: all configure build run test docs clean help

all: build

configure:
	@echo "[cmake] Configurando projeto (BUILD_TYPE=$(BUILD_TYPE))..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. $(CMAKE_ARGS)

build: configure
	@echo "[make] Compilando com $(JOBS) thread(s)..."
	@cmake --build $(BUILD_DIR) -- -j$(JOBS)

run: build
	@echo "[run] Iniciando EduSocial..."
	@./bin/edusocial

test: build
	@echo "[test] Executando testes..."
	@./bin/run_tests
	@echo "\n[coverage] Gerando relatorio de cobertura com gcovr..."
	@gcovr -r . --exclude ".*doctest\.h" --exclude ".*main\.cpp" --exclude ".*test_.*\.cpp"
	@mkdir -p coverage
	@gcovr -r . --exclude ".*doctest\.h" --exclude ".*main\.cpp" --exclude ".*test_.*\.cpp" --html-details coverage/coverage.html
	@echo "[sucesso] Relatorio HTML detalhado gerado na pasta 'coverage/'"

docs:
	@echo "[docs] Gerando documentacao com Doxygen..."
	@doxygen design/Doxyfile

clean:
	@echo "[clean] Removendo diretorio de build, binarios e coverage..."
	@rm -rf $(BUILD_DIR) bin/edusocial bin/run_tests coverage/

help:
	@echo
	@echo "Uso: make [alvo] [VARIAVEL=valor]"
	@echo
	@echo "Alvos:"
	@echo "  all        Compila o projeto"
	@echo "  configure  Configura o CMake"
	@echo "  build      Compila o projeto"
	@echo "  run        Executa o programa principal"
	@echo "  test       Executa os testes unitarios e gera relatorio gcovr"
	@echo "  docs       Gera documentacao"
	@echo "  clean      Remove o diretorio build, binarios e relatorios"
	@echo
	@echo "Exemplos:"
	@echo "  make build BUILD_TYPE=Release"
	@echo "  make test JOBS=2"