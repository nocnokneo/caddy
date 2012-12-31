SUBDIRS := src doc

.PHONY: $(SUBDIRS)

all: $(SUBDIRS)

src:
	$(MAKE) -C $@

doc:
	$(MAKE) -C $@
