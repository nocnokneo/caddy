# Makefile for Caddy. Depends on avrproj_make from AVRLIB

# Basename of the file containing main().
TRG = caddy

# Target mcu here (at90s8515, at90s8535, attiny22, atmega603 etc.)
MCU = atmega32

# Path to AVRLIB base directory
AVRLIB = ../thirdparty/avrlib

### Default make target that defines the desired output formats (.hex == Intel HEX)
all: $(TRG) $(TRG).hex $(TRG).eeprom.hex $(TRG).bin

AVRLIB_SRC += buffer.c
AVRLIB_SRC += uart.c
AVRLIB_SRC += rprintf.c
AVRLIB_SRC += timer.c

SRC += encoder.c
SRC += node_list.c
SRC += robot_control.c
SRC += servos.c
SRC += utility.c
SRC += line_tracking.c
SRC += junctionCode.c
SRC += path_planning.c
SRC += buttons.c
SRC += camera.c
SRC += motor_control.c
SRC += ball_tracking.c
SRC += tweak_data.c
SRC += permutation.c
SRC += $(TRG).c

# For debugging
SRC += tether_ui.c
SRC += lcd_16x2.c
SRC += test_routines.c

# Assembler flags
ASFLAGS += -Wa, -gstabs

# Compiler flags
CFLAGS += -g -Os -Wall

# For compatibilty with avr-libc >= 1.6
CPPFLAGS += -D__AVR_LIBC_DEPRECATED_ENABLE__
# For compatibilty with avr-libc >= 1.8
CPPFLAGS += -D__PROG_TYPES_COMPAT__

# Turn on listings
#CFLAGS += -Wa,-ahlms=$(<:.c=.lst)

# Linker flags
LDFLAGS += -Wl,-Map=$(TRG).map,--cref

include avr.mk
