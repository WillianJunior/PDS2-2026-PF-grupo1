#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
DATABASE_PATH="$PROJECT_ROOT/database/app.db"

if [[ -f "$DATABASE_PATH" ]]; then
	rm -f "$DATABASE_PATH"
	echo "Database removed successfully."
else
	echo "No existing database file was found."
fi

echo "The schema will be recreated automatically on the next run."
