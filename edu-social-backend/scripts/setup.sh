#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"
BINARY_PATH="$BUILD_DIR/bin/edu_social_backend"

log_step() {
	echo "[setup] $1"
}

log_info() {
	echo "[info]  $1"
}

log_fail() {
	echo "[error] $1" >&2
}

command_exists() {
	command -v "$1" >/dev/null 2>&1
}

invoke_cmd() {
	local description="$1"
	shift

	log_step "$description"
	log_info "Executando: $*"
	"$@"
}

resolve_toolchain_args() {
	TOOLCHAIN_ARGS=()

	if command_exists ninja; then
		log_info "Estrategia selecionada: Ninja"
		TOOLCHAIN_ARGS+=("-G" "Ninja")
		return
	fi

	if command_exists gcc && command_exists g++; then
		log_info "Estrategia selecionada: gerador padrao + GCC/G++"
		TOOLCHAIN_ARGS+=("-DCMAKE_C_COMPILER=$(command -v gcc)")
		TOOLCHAIN_ARGS+=("-DCMAKE_CXX_COMPILER=$(command -v g++)")
		return
	fi

	if command_exists clang && command_exists clang++; then
		log_info "Estrategia selecionada: gerador padrao + Clang/Clang++"
		TOOLCHAIN_ARGS+=("-DCMAKE_C_COMPILER=$(command -v clang)")
		TOOLCHAIN_ARGS+=("-DCMAKE_CXX_COMPILER=$(command -v clang++)")
		return
	fi

	log_info "Nenhum compilador explicito detectado. CMake usara o default do sistema."
}

get_selected_generator() {
	local idx=0
	while [[ $idx -lt ${#TOOLCHAIN_ARGS[@]} ]]; do
		if [[ "${TOOLCHAIN_ARGS[$idx]}" == "-G" && $((idx + 1)) -lt ${#TOOLCHAIN_ARGS[@]} ]]; then
			echo "${TOOLCHAIN_ARGS[$((idx + 1))]}"
			return
		fi
		idx=$((idx + 1))
	done
}

get_cached_generator() {
	local cache_path="$BUILD_DIR/CMakeCache.txt"
	if [[ ! -f "$cache_path" ]]; then
		return
	fi

	grep -m1 '^CMAKE_GENERATOR:INTERNAL=' "$cache_path" | sed 's/^CMAKE_GENERATOR:INTERNAL=//'
}

clear_cmake_configure_cache() {
	log_step "Limpando cache de configuracao do CMake"
	rm -f "$BUILD_DIR/CMakeCache.txt"
	rm -rf "$BUILD_DIR/CMakeFiles"
}

ensure_local_intellisense_config() {
	local vscode_dir="$PROJECT_ROOT/.vscode"
	local config_path="$vscode_dir/c_cpp_properties.json"

	log_step "Garantindo configuracao local do IntelliSense"
	if [[ -f "$config_path" ]]; then
		log_info "c_cpp_properties.json ja existe. Nenhuma alteracao necessaria."
		return
	fi

	mkdir -p "$vscode_dir"
	cat > "$config_path" << 'EOF'
{
  "configurations": [
    {
      "name": "Linux",
      "includePath": [
        "${workspaceFolder}/include",
        "${workspaceFolder}/build/_deps/sqlite_amalgamation-src",
        "${workspaceFolder}/build/_deps/crow-src/include",
        "${workspaceFolder}/build/_deps/asio-src/asio/include"
      ],
      "defines": [],
      "compileCommands": "${workspaceFolder}/build/compile_commands.json",
      "cppStandard": "c++17",
      "cStandard": "c17",
      "intelliSenseMode": "linux-gcc-x64"
    }
  ],
  "version": 4
}
EOF
	log_info "Arquivo .vscode/c_cpp_properties.json criado."
}

main() {
	cd "$PROJECT_ROOT"

	if ! command_exists cmake; then
		log_fail "CMake was not found in PATH."
		log_fail "Install CMake and open a new terminal before running this script again."
		exit 1
	fi

	log_step "Bootstrap iniciado"
	log_info "Projeto:   $PROJECT_ROOT"
	log_info "Build dir: $BUILD_DIR"

	resolve_toolchain_args

	local selected_generator
	selected_generator="$(get_selected_generator || true)"
	local cached_generator
	cached_generator="$(get_cached_generator || true)"

	if [[ -n "$selected_generator" && -n "$cached_generator" && "$selected_generator" != "$cached_generator" ]]; then
		log_info "Gerador em cache detectado: $cached_generator"
		log_info "Gerador atual selecionado: $selected_generator"
		clear_cmake_configure_cache
	fi

	invoke_cmd "Configurando projeto com CMake" cmake -S "$PROJECT_ROOT" -B "$BUILD_DIR" "${TOOLCHAIN_ARGS[@]}"
	ensure_local_intellisense_config
	invoke_cmd "Compilando binario" cmake --build "$BUILD_DIR" --config Debug

	if [[ ! -f "$BINARY_PATH" ]]; then
		log_fail "Binary was not found after compilation: $BINARY_PATH"
		exit 1
	fi

	log_step "Inicializando servidor"
	log_info "Executavel: $BINARY_PATH"
	log_info "Endpoint health esperado: http://localhost:18080/health"
	"$BINARY_PATH"
}

main "$@"
