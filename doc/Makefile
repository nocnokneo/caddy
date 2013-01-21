DOXYGEN ?= doxygen

all: Doxyfile
	$(MAKE) -C images
	$(DOXYGEN) $<
	$(MAKE) -C latex
