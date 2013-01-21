eps_images := $(addsuffix .eps,$(basename $(wildcard *.png)))

all: $(eps_images)

# Generate EPS format copies of all images in PNG format. (LaTeX requires
# images in EPS format while HTML output must use an image format supported by
# web browsers)
%.eps: %.png
	convert $< $@

clean:
	$(RM) $(eps_images)
