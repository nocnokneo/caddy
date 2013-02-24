DOXYGEN ?= doxygen

# Works with 1.8.3.1. Does not work with 1.6.1.
# TODO: Determine what the true minimum version is.
DOXYGEN_MIN_VERSION=1.8.0

# caddy_in_arena.png is a special case not handled automatically by Doxygen
# because it is hard-coded into the title page (header.tex)
all: Doxyfile check_doxygen_version
	$(MAKE) -C images
	$(DOXYGEN) $<
	cp images/caddy_in_arena.png latex/
	$(MAKE) -C latex

check_doxygen_version:
	@[ $(DOXYGEN_MIN_VERSION) = `echo -e "$(shell $(DOXYGEN) --version)\n$(DOXYGEN_MIN_VERSION)" | \
	  sort -V | head -n1` ] || \
	  (echo "Doxygen version must be >= $(DOXYGEN_MIN_VERSION). Your version is $(shell $(DOXYGEN) --version)."; \
	  exit 1)
.PHONY: check_doxygen_version
