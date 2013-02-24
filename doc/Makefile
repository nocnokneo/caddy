DOXYGEN ?= doxygen

# caddy_in_arena.png is a special case not handled automatically by Doxygen
# because it is hard-coded into the title page (header.tex)
all: Doxyfile
	$(MAKE) -C images
	$(DOXYGEN) $<
	cp images/caddy_in_arena.png latex/
	$(MAKE) -C latex
