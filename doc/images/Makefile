generated_png_images := $(addsuffix .png,$(basename $(wildcard *.dia)))

all: $(generated_png_images)

# Generate .png version of .dia diagrams
%.png: %.dia
	dia --nosplash --export $@ $<

clean:
	$(RM) $(generated_png_images)
