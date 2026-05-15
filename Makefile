.PHONY: run setup serve reset-db test docs

ifeq ($(OS),Windows_NT)
SETUP_CMD = powershell -ExecutionPolicy Bypass -File scripts/setup.ps1
RUN_CMD = powershell -ExecutionPolicy Bypass -File scripts/run.ps1
RESET_DB_CMD = powershell -ExecutionPolicy Bypass -File scripts/reset_db.ps1
TEST_CMD = powershell -ExecutionPolicy Bypass -File scripts/test.ps1
DOCS_CMD = powershell -ExecutionPolicy Bypass -File scripts/docs.ps1
else
SETUP_CMD = bash scripts/setup.sh
RUN_CMD = bash scripts/run.sh
RESET_DB_CMD = bash scripts/reset_db.sh
TEST_CMD = bash scripts/test.sh
DOCS_CMD = bash scripts/docs.sh
endif

run: setup serve

setup:
	$(SETUP_CMD)

serve:
	$(RUN_CMD)

reset-db:
	$(RESET_DB_CMD)

test:
	$(TEST_CMD)

docs:
	$(DOCS_CMD)
