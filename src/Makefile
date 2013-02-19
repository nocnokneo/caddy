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
SRC += nodeList.c
SRC += botCntrl.c
SRC += servos.c
SRC += helperFunctions.c
SRC += trackLine.c
SRC += junctionCode.c
SRC += updatePath.c
SRC += buttons.c
SRC += camera.c
SRC += motorCntrl.c
SRC += trackColor.c
SRC += eeProm.c
SRC += linkedList.c
SRC += perms.c
SRC += $(TRG).c

# For debugging
SRC += tetherUI.c
SRC += ourLCD.c
SRC += testCode.c

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
