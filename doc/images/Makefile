SCHEM_DIR := ../../schem
generated_images += $(addsuffix .png,$(subst .,_,$(wildcard *.dia)))
generated_images += $(addsuffix .png,$(subst .,_,$(notdir $(wildcard $(SCHEM_DIR)/*.sch))))
generated_images += $(addsuffix .eps,$(subst .,_,$(notdir $(wildcard $(SCHEM_DIR)/*.sch))))

all: $(generated_images)

# Generate .png version of .dia diagrams
%_dia.png: %.dia
	dia --nosplash --export $@ $<

# Generate .png and .eps version of .sch schematic diagrams
%_sch.png: $(SCHEM_DIR)/%.sch
	gaf export --size=auto --color -o $@ $<
%_sch.eps: $(SCHEM_DIR)/%.sch
	gaf export --size=auto --color -o $@ $<

clean:
	$(RM) $(generated_images)
