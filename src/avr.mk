# AVR-GCC standard Makefile
# This makefile is to be used by including it from a project-specific makefile
# which defines the source files and compiler/linker options. At a minium it
# must define the following make variables:
#
#  * MCU - Name of the target AVR chip (e.g. atmega32, at90s8515, at90s8535,
#          attiny22, ...)
#  * TRG - The name of the ELF output file. This will be the basename of the
#          various output formats such as .bin, .hex, .srec
#
# Implicit rules are used where possible so any variables used by those recipes
# can be modified to affect the build.
#
# Based on avrproj_make from AVRLIB

CC	= avr-gcc
AS	= avr-gcc -x assembler-with-cpp	
OBJCOPY	= avr-objcopy
SIZE	= avr-size

# -I. is needed so AVRLIB sources can find the project's global.h
CPPFLAGS += -mmcu=$(MCU) -I. -I$(AVRLIB)
ASFLAGS += -mmcu=$(MCU) -I. -I$(AVRLIB)
LDFLAGS += -mmcu=$(MCU)

### Define all the object files needed to build the $(TRG) ELF file

SRC	+= $(addprefix $(AVRLIB)/,$(AVRLIB_SRC))
OBJ	= $(ASRC:.s=.o) $(SRC:.c=.o) 

.PHONY: size clean

# Establish just the top-level rule, but no recipe. The rest is managed by
# implicit rules and auto-dependency generation.
$(TRG): $(OBJ)

### Pattern rules for various output formats

# Use Secondary Expansion of Static Pattern Rules so that $$* variable is set
# to the pattern stem in prerequisite lists
.SECONDEXPANSION:

%.eeprom.hex: $$*
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	    --change-section-lma .eeprom=0 -O ihex $< $@

%.eeprom.srec: $$*
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	    --change-section-lma .eeprom=0 -O srec $< $@

%.bin: $$*
	$(OBJCOPY) -O binary -R .eeprom $< $@

%.hex: $$*
	$(OBJCOPY) -O ihex -R .eeprom $< $@

%.srec: $$*
	$(OBJCOPY) -O srec -R .eeprom $< $@

clean:
	$(RM) $(OBJ)
	$(RM) $(SRC:.c=.lst)
	$(RM) $(SRC:.c=.d)
	$(RM) $(TRG)
	$(RM) $(TRG).map
	$(RM) $(TRG).elf
	$(RM) $(TRG).obj
	$(RM) $(TRG).a90
	$(RM) $(TRG).sym
	$(RM) $(TRG).eeprom.*
	$(RM) $(TRG).hex
	$(RM) $(TRG).srec
	$(RM) $(TRG).bin

# Convenience target for printing memory usage information
size: $(TRG)
	$(SIZE) $<

### Pattern rule for autodependendency generation

# Copied from the GNU make manual: "Generating Prerequisites Automatically"
# http://www.gnu.org/software/make/manual/make.html#Automatic-Prerequisites
%.d: %.c
	@set -e; $(RM) $@; \
	  $(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	  sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	  $(RM) $@.$$$$
include $(SRC:.c=.d)
