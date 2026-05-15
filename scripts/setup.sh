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

clear_fetchcontent_subbuilds() {
	local deps_dir="$BUILD_DIR/_deps"
	if [[ ! -d "$deps_dir" ]]; then
		return
	fi

	find "$deps_dir" -mindepth 1 -maxdepth 1 -type d -name '*-subbuild' -exec rm -rf {} +
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

clear_build_artifacts() {
	log_step "Cleaning build artifacts for generator switch"
	if [[ ! -d "$BUILD_DIR" ]]; then
		return
	fi

	find "$BUILD_DIR" -mindepth 1 -maxdepth 1 ! -name '.gitkeep' -exec rm -rf {} +
}

invoke_cmake_configure() {
	log_step "Configurando projeto com CMake"
	log_info "Executando: cmake -S $PROJECT_ROOT -B $BUILD_DIR ${TOOLCHAIN_ARGS[*]}"
	log_info "Dependency resolution may take some time during the first configure step."

	clear_fetchcontent_subbuilds

	local log_file="$BUILD_DIR/cmake-configure.log"
	rm -f "$log_file"

	local configure_output
	cmake -S "$PROJECT_ROOT" -B "$BUILD_DIR" "${TOOLCHAIN_ARGS[@]}" 2>&1 | tee "$log_file"
	local configure_status=${PIPESTATUS[0]}
	configure_output="$(cat "$log_file")"
	if [[ $configure_status -eq 0 ]]; then
		return
	fi

	if [[ "$configure_output" == *"Does not match the generator used previously"* ]]; then
		log_info "Generator mismatch detected during configure. Cleaning build directory and retrying once."
		clear_build_artifacts
		cmake -S "$PROJECT_ROOT" -B "$BUILD_DIR" "${TOOLCHAIN_ARGS[@]}" 2>&1 | tee "$log_file"
		local retry_status=${PIPESTATUS[0]}
		if [[ $retry_status -eq 0 ]]; then
			return
		fi

		local retry_output
		retry_output="$(cat "$log_file")"
		if [[ "$retry_output" == *"Could not connect to server"* ]]; then
			log_info "Dependency download failed. Check network access to github.com and sqlite.org."
		fi

		return $retry_status
	fi

	if [[ "$configure_output" == *"Could not connect to server"* ]]; then
		log_info "Dependency download failed. Check network access to github.com and sqlite.org."
	fi

	return $configure_status
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
		clear_build_artifacts
	fi

	invoke_cmake_configure
	invoke_cmd "Compilando binario" cmake --build "$BUILD_DIR" --config Debug
	log_step "Bootstrap finalizado"
	log_info "Use scripts/run.sh or make serve to start the server."
}

main "$@"
