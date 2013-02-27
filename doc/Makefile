DOXYGEN ?= doxygen

# Works with 1.8.3.1. Does not work with 1.6.1.
# TODO: Determine what the true minimum version is.
DOXYGEN_MIN_VERSION=1.8.0

# caddy_in_arena.png is a special case not handled automatically by Doxygen
# because it is hard-coded into the title page (header.tex)
all: Doxyfile check_doxygen_version html/.git
	$(MAKE) -C images
	$(DOXYGEN) $<
	cp images/caddy_in_arena.png latex/
	$(MAKE) -C latex
	cp latex/refman.pdf html/caddy.pdf
	@echo
	@echo '========================================================================'
	@echo 'Documentation generated sucessfully. Publish with:'
	@echo
	@echo 'cd html/'
	@echo 'git add .'
	@echo 'git commit -m "Update doxygen-generated documentation"'
	@echo 'git push origin gh-pages'
	@echo
	@echo '========================================================================'

# Create a second clone of the caddy git repository from the main
# GitHub-hosted one and switch to the special gh-pages "orphan" branch:
html/.git:
	rm -rf html
	git clone git@github.com:nocnokneo/caddy.git html
	cd html && \
	  git checkout gh-pages && \
	  git branch -d master && \
	  git config http.postBuffer 100000000

check_doxygen_version:
	@[ $(DOXYGEN_MIN_VERSION) = `echo -e "$(shell $(DOXYGEN) --version)\n$(DOXYGEN_MIN_VERSION)" | \
	  sort -V | head -n1` ] || \
	  (echo "Doxygen version must be >= $(DOXYGEN_MIN_VERSION). Your version is $(shell $(DOXYGEN) --version)."; \
	  exit 1)
.PHONY: check_doxygen_version
