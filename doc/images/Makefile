SCHEM_DIR := ../../schem
generated_images += $(addsuffix .png,$(subst .,_,$(wildcard *.dia)))
generated_images += $(addsuffix .eps,$(subst .,_,$(wildcard *.dia)))
generated_images += $(addsuffix .png,$(subst .,_,$(notdir $(wildcard $(SCHEM_DIR)/*.sch))))
generated_images += $(addsuffix .eps,$(subst .,_,$(notdir $(wildcard $(SCHEM_DIR)/*.sch))))

all: $(generated_images)

# Generate .png and .eps version of .dia diagrams
%_dia.png: %.dia
	dia --nosplash --export $@ $<
%_dia.eps: %.dia
	dia --nosplash --export $@ $<

# Generate .png and .eps version of .sch schematic diagrams
%_sch.png: $(SCHEM_DIR)/%.sch
	gaf export --size=auto --margins="20 1" --color -o $@ $<
%_sch.eps: $(SCHEM_DIR)/%.sch
	gaf export --size=auto --margins="20 1" --color -o $@ $<

clean:
	$(RM) $(generated_images)
