#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

BUILD_DIR="${BUILD_DIR:-build}"
BUILD_TYPE="${BUILD_TYPE:-Debug}"
JOBS="${JOBS:-4}"
REPORT_DIR="report"
HTML_FILE="$REPORT_DIR/coverage.html"
OPEN_FILE="$ROOT/$HTML_FILE"

GCOVR_EXCLUDE=(
  --exclude ".*doctest\.h"
  --exclude ".*main\.cpp"
  --exclude ".*test_.*\.cpp"
)

echo "[coverage] Executando testes..."
ctest --test-dir "$BUILD_DIR" -C "$BUILD_TYPE" --output-on-failure --parallel "$JOBS"

if ! command -v gcovr >/dev/null 2>&1; then
  echo "[coverage] gcovr nao encontrado. Instale: sudo apt install gcovr"
  exit 1
fi

echo "[coverage] Relatorio no terminal:"
gcovr -r . "${GCOVR_EXCLUDE[@]}"

rm -rf "$REPORT_DIR"
mkdir -p "$REPORT_DIR"
echo "[coverage] Gerando HTML em $REPORT_DIR/..."
gcovr -r . "${GCOVR_EXCLUDE[@]}" --html-details "$HTML_FILE"

if [[ -n "${COPY_REPORT_TO:-}" ]]; then
  rm -rf "$COPY_REPORT_TO"
  cp -r "$REPORT_DIR" "$COPY_REPORT_TO"
  OPEN_FILE="$COPY_REPORT_TO/coverage.html"
fi

echo
if command -v wslpath >/dev/null 2>&1; then
  echo "[coverage] Relatorio salvo em: $(wslpath -w "$OPEN_FILE")"
else
  echo "[coverage] Relatorio salvo em: $OPEN_FILE"
fi

if command -v explorer.exe >/dev/null 2>&1; then
  echo "[coverage] Abrindo no navegador..."
  if command -v wslpath >/dev/null 2>&1; then
    explorer.exe "$(wslpath -w "$OPEN_FILE")" >/dev/null 2>&1 || true
  else
    explorer.exe "$OPEN_FILE" >/dev/null 2>&1 || true
  fi
fi
