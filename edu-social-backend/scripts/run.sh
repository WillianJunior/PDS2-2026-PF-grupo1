#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BINARY_PATH="$PROJECT_ROOT/build/bin/edu_social_backend"

cd "$PROJECT_ROOT"

if [[ ! -f "$BINARY_PATH" ]]; then
	echo "Error: binary was not found. Run scripts/setup.sh first." >&2
	exit 1
fi

echo "Iniciando servidor em http://localhost:18080 ..."
"$BINARY_PATH"
