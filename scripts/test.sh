#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"
COVERAGE_DIR="$PROJECT_ROOT/coverage"
TOOLCHAIN_ARGS=()

step() {
	echo "[test]  $1"
}

info() {
	echo "[info]  $1"
}

resolve_toolchain_args() {
	TOOLCHAIN_ARGS=()

	if command -v ninja >/dev/null 2>&1 && command -v gcc >/dev/null 2>&1 && command -v g++ >/dev/null 2>&1; then
		TOOLCHAIN_ARGS+=("-G" "Ninja")
		TOOLCHAIN_ARGS+=("-DCMAKE_C_COMPILER=$(command -v gcc)")
		TOOLCHAIN_ARGS+=("-DCMAKE_CXX_COMPILER=$(command -v g++)")
		return
	fi

	if command -v gcc >/dev/null 2>&1 && command -v g++ >/dev/null 2>&1; then
		TOOLCHAIN_ARGS+=("-DCMAKE_C_COMPILER=$(command -v gcc)")
		TOOLCHAIN_ARGS+=("-DCMAKE_CXX_COMPILER=$(command -v g++)")
		return
	fi

	echo "Error: a GCC-based toolchain is required for gcovr coverage." >&2
	exit 1
}

if ! command -v cmake >/dev/null 2>&1; then
	echo "Error: CMake was not found in PATH." >&2
	exit 1
fi

if ! command -v gcovr >/dev/null 2>&1; then
	echo "Error: gcovr was not found in PATH." >&2
	exit 1
fi

cd "$PROJECT_ROOT"
resolve_toolchain_args

step "Configuring tests with coverage"
info "cmake -S $PROJECT_ROOT -B $BUILD_DIR -DENABLE_COVERAGE=ON ${TOOLCHAIN_ARGS[*]}"
cmake -S "$PROJECT_ROOT" -B "$BUILD_DIR" -DENABLE_COVERAGE=ON "${TOOLCHAIN_ARGS[@]}"

step "Building unit tests"
info "cmake --build $BUILD_DIR --config Debug --target edu_social_tests"
cmake --build "$BUILD_DIR" --config Debug --target edu_social_tests

step "Running unit tests"
info "ctest --test-dir $BUILD_DIR --output-on-failure --build-config Debug"
ctest --test-dir "$BUILD_DIR" --output-on-failure --build-config Debug

mkdir -p "$COVERAGE_DIR"

step "Generating coverage reports"
info "gcovr --root $PROJECT_ROOT --filter $PROJECT_ROOT/src --html-details $COVERAGE_DIR/index.html --xml $COVERAGE_DIR/coverage.xml --print-summary"
gcovr \
	--root "$PROJECT_ROOT" \
	--filter "$PROJECT_ROOT/src" \
	--html-details "$COVERAGE_DIR/index.html" \
	--xml "$COVERAGE_DIR/coverage.xml" \
	--print-summary
