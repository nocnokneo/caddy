/*
 * This can replace the interrupt handler that is built into the
 * encoder.c avrlib module. It requires some very simple external
 * circuitry (one XOR gate) and one more I/O pin (3 instead of 2) but
 * provides a 4-fold increase in precision.
 */

struct encData {
  s32 position;
  uint8_t prevState;
}

// Global variables
volatile struct encData encoders[2];
static uint8_t encTable[][] = { {0,  1, -1,  0},
			    {-1, 0,  0,  1},
			    {1,  0,  0, -1},
			    {0, -1,  1,  0} };

/*
 *  ENC0_SIGNAL must be the phaseA and phaseB signals XOR'd together
 *  and set to interupt on both rising and falling edge
 */
SIGNAL(ENC0_SIGNAL) 
{
  uint8_t newState = ((inb(ENC0_PHASEAB_PORTIN)>>ENC0_PHASEB_PIN) & 0x03);

  encoders[0].position += encTable[encoders[0].prevState][newState];
  encoders[0].prevState = newState;
}
