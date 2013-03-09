png_images := $(addsuffix .png,$(basename $(wildcard *.dia)))

all: $(png_images)

# Generate .png version of .dia diagrams
%.png: %.dia
	dia --nosplash --export $@ $<
