# Makefile for AVR function library development and examples
# Author: Pascal Stang

AVRLIB = ../thirdparty/avrlib

# Target mcu here (at90s8515, at90s8535, attiny22, atmega603 etc.)
MCU = atmega32

# Basename of the file containing main()
TRG = caddy

# FOR DEBUGGING:
SRC = encoder.c $(AVRLIB)/buffer.c $(AVRLIB)/uart.c $(AVRLIB)/rprintf.c $(AVRLIB)/timer.c debugger.c nodeList.c botCntrl.c servos.c helperFunctions.c trackLine.c junctionCode.c updatePath.c buttons.c camera.c motorCntrl.c ourLCD.c trackColor.c eeProm.c testCode.c linkedList.c perms.c $(TRG).c

# FOR NOT DEBUGGING:
#SRC = encoder.c $(AVRLIB)/buffer.c $(AVRLIB)/uart.c $(AVRLIB)/rprintf.c $(AVRLIB)/timer.c nodeList.c botCntrl.c servos.c helperFunctions.c trackLine.c junctionCode.c updatePath.c buttons.c camera.c motorCntrl.c trackColor.c eeProm.c $(TRG).c

# Additional assembler source files
ASRC =

# Additional libraries and object files to link
LIB =

# Additional includes to compile
INC =

# Assembler flags
ASFLAGS = -Wa, -gstabs

# Compiler flags
CPFLAGS	= -g -Os -Wall -Wstrict-prototypes -I$(AVRLIB) -Wa,-ahlms=$(<:.c=.lst)

# Linker flags
LDFLAGS = -Wl,-Map=$(TRG).map,--cref
#LDFLAGS = -Wl,-Map=$(TRG).map,--cref -lm


########### you should not need to change the following line #############
include $(AVRLIB)/make/avrproj_make

buffer.o: buffer.c buffer.h
uart.o: uart.c uart.h global.h
uart2.o: uart2.c uart2.h global.h
rprintf.o: rprintf.c rprintf.h
a2d.o: a2d.c a2d.h
timer.o: timer.c timer.h global.h
pulse.o: pulse.c pulse.h timer.h global.h
lcd.o: lcd.c lcd.h global.h
i2c.o: i2c.c i2c.h global.h
spi.o: spi.c spi.h global.h
swpwm.o: swpwm.c swpwm.h global.h
servo.o: servo.c servo.h global.h
swuart.o: swuart.c swuart.h global.h
tsip.o: tsip.c tsip.h global.h
nmea.o: nmea.c nmea.h global.h
vt100.o: vt100.c vt100.h global.h
gps.o: gps.c gps.h global.h
$(TRG).o: $(TRG).c global.h