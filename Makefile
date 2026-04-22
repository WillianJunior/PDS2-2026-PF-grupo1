.PHONY: run setup serve reset-db

run setup serve reset-db:
	$(MAKE) -C edu-social-backend $@
