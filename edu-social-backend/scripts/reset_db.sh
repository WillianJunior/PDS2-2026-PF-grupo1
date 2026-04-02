#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
DATABASE_PATH="$PROJECT_ROOT/database/app.db"

if [[ -f "$DATABASE_PATH" ]]; then
	rm -f "$DATABASE_PATH"
	echo "Banco removido com sucesso."
else
	echo "Nenhum banco existente para remover."
fi

echo "O schema sera recriado automaticamente na proxima execucao."
