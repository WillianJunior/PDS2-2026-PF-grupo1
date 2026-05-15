#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
DOXYFILE_PATH="$PROJECT_ROOT/Doxyfile"

log_step() {
	echo "[docs]  $1"
}

log_info() {
	echo "[info]  $1"
}

log_fail() {
	echo "[error] $1" >&2
}

main() {
	if ! command -v doxygen >/dev/null 2>&1; then
		log_fail "Doxygen was not found in PATH."
		log_fail "Install Doxygen and open a new terminal before running this script again."
		exit 1
	fi

	if [[ ! -f "$DOXYFILE_PATH" ]]; then
		log_fail "Doxyfile was not found in the project root."
		exit 1
	fi

	cd "$PROJECT_ROOT"
	log_step "Generating documentation with Doxygen"
	log_info "Command: doxygen $DOXYFILE_PATH"
	doxygen "$DOXYFILE_PATH"
	log_step "Documentation generated"
	log_info "Open build/docs/html/index.html to browse the generated pages."
}

main "$@"
