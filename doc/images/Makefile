source_images := $(wildcard *.png *.dia)
png_images := $(addsuffix .png,$(basename $(source_images)))
eps_images := $(addsuffix .eps,$(basename $(source_images)))

all: $(eps_images) $(png_images)

# Generate .png version of .dia diagrams
%.png: %.dia
	dia --nosplash --export $@ $<

# Generate EPS format copies of all images in PNG format. (LaTeX requires
# images in EPS format while HTML output must use an image format supported by
# web browsers)
%.eps: %.png
	convert $< $@

clean:
	$(RM) $(eps_images)
