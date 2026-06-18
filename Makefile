BUILD_DIR := build
BUILD_TYPE ?= Debug
JOBS ?= 4

ifeq ($(OS),Windows_NT)
APP_EXTENSION := .exe
CMAKE_ARGS := -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
else
APP_EXTENSION :=
CMAKE_ARGS := -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
endif

APP_PATH := $(BUILD_DIR)/bin/edu_social_backend$(APP_EXTENSION)
COMMITS_BIN := $(BUILD_DIR)/bin/count_commits_alunos$(APP_EXTENSION)

DEMO_INPUT ?= scripts/demo.in
DATA_DIR := data
DATA_CSVS := $(DATA_DIR)/usuarios.csv $(DATA_DIR)/perfis.csv $(DATA_DIR)/comunidades.csv $(DATA_DIR)/posts.csv $(DATA_DIR)/comentarios.csv

.PHONY: all configure build run run-demo run-demo-clean test docs clean help commits commits-alunos build-commits

all: build

configure:
	@echo "[cmake] Configurando projeto (BUILD_TYPE=$(BUILD_TYPE))..."
	@cmake -S . -B $(BUILD_DIR) $(CMAKE_ARGS)

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
	@echo "[clean] Removendo diretorio de build..."
	@cmake -E remove_directory $(BUILD_DIR)

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
	@echo "  run             Compila e executa o app (uso normal)"
	@echo "  build           So compila"
	@echo "  test            Executa os testes"
	@echo "  run-demo        Demo automatica (scripts/demo.in)"
	@echo "  run-demo-clean  Apaga CSVs em data/ e roda demo do zero"
	@echo "  clean           Remove a pasta build/"
	@echo "  commits alunos  Contagem de commits por integrante"
	@echo "  docs            Gera documentacao Doxygen"
	@echo
	@echo "Exemplos:"
	@echo "  make build BUILD_TYPE=Release"
	@echo "  make run-demo DEMO_INPUT=scripts/meu_teste.in"
