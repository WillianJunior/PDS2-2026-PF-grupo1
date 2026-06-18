BUILD_DIR := build
BUILD_TYPE ?= Debug
CMAKE_ARGS := -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_CXX_FLAGS="--coverage" -DCMAKE_EXE_LINKER_FLAGS="--coverage"
JOBS ?= 4
APP_EXTENSION :=
APP_PATH := $(BUILD_DIR)/bin/edu_social_backend$(APP_EXTENSION)
COMMITS_BIN := $(BUILD_DIR)/bin/count_commits_alunos$(APP_EXTENSION)

ifeq ($(OS),Windows_NT)
APP_EXTENSION := .exe
APP_PATH := $(BUILD_DIR)/bin/edu_social_backend$(APP_EXTENSION)
COMMITS_BIN := $(BUILD_DIR)/bin/count_commits_alunos$(APP_EXTENSION)
endif

DEMO_INPUT ?= scripts/demo.in
DATA_DIR := data
DATA_CSVS := $(DATA_DIR)/usuarios.csv $(DATA_DIR)/perfis.csv $(DATA_DIR)/comunidades.csv $(DATA_DIR)/posts.csv $(DATA_DIR)/comentarios.csv

.PHONY: all configure build run run-demo run-demo-clean test docs clean help commits commits-alunos build-commits

all: build

configure:
	@echo "[cmake] Configurando projeto (BUILD_TYPE=$(BUILD_TYPE))..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. $(CMAKE_ARGS)

build: configure
	@echo "[make] Compilando com $(JOBS) thread(s)..."
	@cmake --build $(BUILD_DIR) --config $(BUILD_TYPE) --parallel $(JOBS)

run: build
	@echo "[run] Iniciando aplicativo..."
	@$(APP_PATH)

run-demo: build
	@echo "[run-demo] Garantindo usuario demo (ignora se ja existir)..."
	-$(APP_PATH) scripts/criar_usuario.in
	@echo "[run-demo] Executando demo com $(DEMO_INPUT)..."
	@$(APP_PATH) $(DEMO_INPUT)

run-demo-clean: build
	@echo "[run-demo-clean] Apagando CSVs em $(DATA_DIR)/..."
	@-cmake -E rm -f $(DATA_CSVS)
	@echo "[run-demo-clean] Criando usuario demo..."
	@$(APP_PATH) scripts/criar_usuario.in
	@echo "[run-demo-clean] Executando demo com $(DEMO_INPUT)..."
	@$(APP_PATH) $(DEMO_INPUT)

test: build
	@echo "[test] Executando testes..."
	@ctest --test-dir $(BUILD_DIR) -C $(BUILD_TYPE) --output-on-failure --parallel $(JOBS)

docs:
	@echo "[docs] Gerando documentacao com Doxygen..."
	@doxygen design/Doxyfile

clean:
	@echo "[clean] Removendo diretorio de build, binarios e coverage..."
	@rm -rf $(BUILD_DIR) bin/edusocial bin/run_tests coverage/

# Permite: make commits alunos
ifneq (,$(filter commits,$(MAKECMDGOALS)))
  COMMITS_MODE := $(filter-out commits,$(MAKECMDGOALS))
  $(COMMITS_MODE):
	@:
endif

build-commits: configure
	@echo "[commits] Compilando contador de commits..."
	@cmake --build $(BUILD_DIR) --config $(BUILD_TYPE) --target count_commits_alunos

commits:
ifeq ($(COMMITS_MODE),alunos)
	@$(MAKE) build-commits
	@$(COMMITS_BIN)
else ifeq ($(COMMITS_MODE),)
	@echo "[commits] Uso: make commits alunos"
else
	@echo "[commits] Modo desconhecido: $(COMMITS_MODE)"
	@echo "[commits] Uso: make commits alunos"
	@exit 1
endif

commits-alunos: build-commits
	@$(COMMITS_BIN)

help:
	@echo
	@echo "Uso: make [alvo] [VARIAVEL=valor]"
	@echo
	@echo "Alvos:"
	@echo "  all        Compila o projeto"
	@echo "  configure  Configura o CMake"
	@echo "  build      Compila o projeto"
	@echo "  run        Compila e executa o backend"
	@echo "  run-demo   Executa demo automatica (scripts/demo.in)"
	@echo "  run-demo-clean  Apaga CSVs e roda demo do zero"
	@echo "  test       Executa os testes"
	@echo "  docs       Gera documentação"
	@echo "  clean      Remove o diretório build"
	@echo "  commits    Contagem de commits (use: make commits alunos)"
	@echo
	@echo "Exemplos:"
	@echo "  make build BUILD_TYPE=Release"
	@echo "  make test JOBS=2"
	@echo "  make run-demo"
	@echo "  make run-demo DEMO_INPUT=scripts/meu_teste.in"
	@echo "  make commits alunos"
