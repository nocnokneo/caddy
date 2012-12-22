/* eeProm.c
 *
 *    For loading and storing tweak values into eeProm.
 *
 */

#include "eeProm.h"

// Initializes constants that can be tweaked by debugger
void loadTweakValues( void )
{
   cli();               // disable all interrupts

   /*  Comment these out once eeProm is working
   l_base = INIT_LEFT_BASE_SPEED;
   r_base = INIT_RIGHT_BASE_SPEED;
   slopeCoef = INIT_SLOPE_COEF;
   offCoef = INIT_OFF_COEF;
   dampCoef = INIT_DAMP_COEF;
   lineCenter = INIT_LINE_X_CENTER;
   
   turnPoint = INIT_TURN_POINT;        // <- These were in botCntrl.c
   turnSubtract = INIT_TURN_SUBTRACT;
   */

   // EEPROM Reads
   l_base = EEPROM_read(EE_ADDR_LEFT_BASE);
   r_base = EEPROM_read(EE_ADDR_RIGHT_BASE);
   slopeCoef = (EEPROM_read(EE_ADDR_SLOPE_COEF)<<8)+EEPROM_read(EE_ADDR_SLOPE_COEF+1);
   offCoef = (EEPROM_read(EE_ADDR_OFF_COEF)<<8)+EEPROM_read(EE_ADDR_OFF_COEF+1);
   dampCoef = EEPROM_read(EE_ADDR_DAMP_COEF);
   lineCenter = EEPROM_read(EE_ADDR_LINE_X_CENTER);
   turnPoint = EEPROM_read(EE_ADDR_TURN_POINT);
   turnSubtract = EEPROM_read(EE_ADDR_TURN_SUBTRACT);
   panOffset = EEPROM_read(EE_ADDR_PAN_OFFSET);
   tiltOffset = EEPROM_read(EE_ADDR_TILT_OFFSET);
   tractorOvershootDelay = (EEPROM_read(EE_ADDR_TRACTOR_OVERSHOOT_DELAY)<<8)+EEPROM_read(EE_ADDR_TRACTOR_OVERSHOOT_DELAY+1);
   tempTweak1 = EEPROM_read(EE_ADDR_TEMP_TWEAK1);
   tempTweak2 = EEPROM_read(EE_ADDR_TEMP_TWEAK2);
   tempTweak3 = (EEPROM_read(EE_ADDR_TEMP_TWEAK3)<<8)+EEPROM_read(EE_ADDR_TEMP_TWEAK3+1);
   tempTweak4 = (EEPROM_read(EE_ADDR_TEMP_TWEAK4)<<8)+EEPROM_read(EE_ADDR_TEMP_TWEAK4+1);

   sei();               // enable all interrupts
}

// Saves constants after they have been changed by the debugger
void storeTweakValues( void )
{
   cli();               // disable all interrupts
   
   // EEPROM writes
   EEPROM_write(EE_ADDR_LEFT_BASE,l_base);
   EEPROM_write(EE_ADDR_RIGHT_BASE,r_base);
   EEPROM_write(EE_ADDR_SLOPE_COEF,slopeCoef>>8);
   EEPROM_write(EE_ADDR_SLOPE_COEF+1,slopeCoef);
   EEPROM_write(EE_ADDR_OFF_COEF,offCoef>>8);
   EEPROM_write(EE_ADDR_OFF_COEF+1,offCoef);
   EEPROM_write(EE_ADDR_DAMP_COEF,dampCoef);
   EEPROM_write(EE_ADDR_LINE_X_CENTER,lineCenter);
   EEPROM_write(EE_ADDR_TURN_POINT,turnPoint);
   EEPROM_write(EE_ADDR_TURN_SUBTRACT,turnSubtract);
   EEPROM_write(EE_ADDR_PAN_OFFSET,panOffset);
   EEPROM_write(EE_ADDR_TILT_OFFSET,tiltOffset);
   EEPROM_write(EE_ADDR_TRACTOR_OVERSHOOT_DELAY,tractorOvershootDelay>>8);
   EEPROM_write(EE_ADDR_TRACTOR_OVERSHOOT_DELAY+1,tractorOvershootDelay);
   EEPROM_write(EE_ADDR_TEMP_TWEAK1,tempTweak1);
   EEPROM_write(EE_ADDR_TEMP_TWEAK2,tempTweak2);
   EEPROM_write(EE_ADDR_TEMP_TWEAK3,tempTweak3>>8);
   EEPROM_write(EE_ADDR_TEMP_TWEAK3+1,tempTweak3);
   EEPROM_write(EE_ADDR_TEMP_TWEAK4,tempTweak4>>8);
   EEPROM_write(EE_ADDR_TEMP_TWEAK4+1,tempTweak4);

   sei();               // enable all interrupts
}

u08 EEPROM_read(unsigned int uiAddress)
{
   // Wait for completion of previous write
   while(EECR & (1<<EEWE))
      ;
   // Set up address register
   EEAR = uiAddress;
   // Start eeprom read by writing EERE
   EECR |= (1<<EERE);
   // Return data from data register
   return EEDR;
}

void EEPROM_write(unsigned int uiAddress, u08 ucData)
{
   // Wait for completion of previous write
   while(EECR & (1<<EEWE))
      ;
   // Set up address and data registers
   EEAR = uiAddress;
   EEDR = ucData;
   // Write logical one to EEMWE
   EECR |= (1<<EEMWE);
   // Start eeprom write by setting EEWE
   EECR |= (1<<EEWE);
   // EEMWE and EEWE are automatically cleared back to 0 by hardware
}
