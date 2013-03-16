SCHEM_DIR := ../../schem
generated_png_images += $(addsuffix .png,$(wildcard *.dia))
generated_png_images += $(addsuffix .png,$(notdir $(wildcard $(SCHEM_DIR)/*.sch)))

all: $(generated_png_images)

# Generate .png version of .dia diagrams
%.dia.png: %.dia
	dia --nosplash --export $@ $<

# Generate .png version of .sch schematic diagrams
%.sch.png: $(SCHEM_DIR)/%.sch
	cd $(dir $<); gschem -p -o $(CURDIR)/$@ -s export_image.scm $(notdir $<)

clean:
	$(RM) $(generated_png_images)
