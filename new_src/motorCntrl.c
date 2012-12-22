//*****************************************************************************
// motorCntrl.c
//
// Motor control functions.
//
// Revision History:
//    3/21/05 created by Mike, based on motorTest.c
//       added #define's
//       added support for speed, motor selection
//       all speeds declared as 8 bit, u08
//   3/23/05 modified by Mike for use with the caddy
//       not sure which pwm controls which though..
//       so could be wrong
//
//
//
//  assumes motor enable is connected to PWM A,B
//    defined in timer.h
//*****************************************************************************
#include "motorCntrl.h"


void forward(u08 motorSelect, u08 speed)
{
   switch(motorSelect)
   {
      case LEFT_MOTOR:
         sbi(MC_PORT, FORWARD_LEFT);
         cbi(MC_PORT, REVERSE_LEFT);
         PWM_LEFT(speed);
         break;
      case RIGHT_MOTOR:
         sbi(MC_PORT, FORWARD_RIGHT);
         cbi(MC_PORT, REVERSE_RIGHT);
         PWM_RIGHT(speed);
         break;
      case BOTH:
         // both motors forward
         sbi(MC_PORT, FORWARD_LEFT);
         sbi(MC_PORT, FORWARD_RIGHT);
         cbi(MC_PORT, REVERSE_LEFT);
         cbi(MC_PORT, REVERSE_RIGHT);
         PWM_RIGHT(speed);
         PWM_LEFT(speed);
         break;
   }
}


void tickWheels(s16 leftTicks, s16 rightTicks, u08 speed) 
{   
   if (leftTicks >= 0)
   {
      forward(LEFT_MOTOR, speed);
   }
   else
   {
      reverse(LEFT_MOTOR, speed);
      leftTicks *= -1;
   }

   if (rightTicks >= 0)
   {
      forward(RIGHT_MOTOR, speed);
   }
   else
   {
      reverse(RIGHT_MOTOR, speed);
      rightTicks *= -1;
   }
   
   encoderSetPosition(LEFT_ENC, 0);
   encoderSetPosition(RIGHT_ENC, 0);
   
   while( encoderGetPosition(LEFT_ENC) < leftTicks || encoderGetPosition(RIGHT_ENC) < rightTicks )
   {
      if( encoderGetPosition(LEFT_ENC) >= leftTicks )
      {
         brake(LEFT_MOTOR);
      }
      
      if( encoderGetPosition(RIGHT_ENC) >= rightTicks )
      {
         brake(RIGHT_MOTOR);
      }
#if DEBUGGING
      lcdPrintHex(encoderGetPosition(1)>>8, 1, 8);
      lcdPrintHex(encoderGetPosition(1), 1, 10);
      lcdPrintHex(encoderGetPosition(0)>>8, 1, 12);
      lcdPrintHex(encoderGetPosition(0), 1, 14);
#endif
   }
   neutral();
}

/* 
 * Move staight forward (positive) or straight back (negative)
 */
void moveStraight(s16 ticks, u08 speed)
{
   tickWheels(ticks, ticks, speed);
}

/* 
 * Brake one wheel, turn the other
 */
void tractorTurn(u08 speed, s08 brads) 
{
   if (brads > 0)
   {
      tickWheels(brads, 0, speed);
      delay(tractorOvershootDelay);
      tickWheels(brads-encoderGetPosition(LEFT_ENC), 0, speed);
      delay(tractorOvershootDelay); //***temporary?
   }
   else
   {
      brads *= -1;
      tickWheels(0, brads, speed);
      delay(tractorOvershootDelay);
      tickWheels(0, brads-encoderGetPosition(RIGHT_ENC), speed);
      delay(tractorOvershootDelay); //***temporary?
   }
}

/* 
 * Turn on a dime (like a tank!)
 */
void tankTurn(u08 speed, s08 brads)
{   
   s08 halfBrads = brads / 2;
   tickWheels(halfBrads, (-1 * halfBrads), speed);
   // Now we correct/prevent overshoot
   delay(TANK_OVERSHOOT_DELAY);
   if (brads < 0)
   {
      tickWheels(encoderGetPosition(LEFT_ENC)+halfBrads, 
                 -1*halfBrads-encoderGetPosition(RIGHT_ENC), speed);
   }
   else
   {
      tickWheels(halfBrads-encoderGetPosition(LEFT_ENC), 
                 encoderGetPosition(RIGHT_ENC)-halfBrads, speed);
   }
}

/*
 * Forward without changing PWM.
 */
/*
void fwd( void )
{
   sbi(MC_PORT, FORWARD_LEFT);
   sbi(MC_PORT, FORWARD_RIGHT);
   cbi(MC_PORT, REVERSE_LEFT);
   cbi(MC_PORT, REVERSE_RIGHT);
}
*/

void reverse(u08 motorSelect, u08 speed)
{
   switch(motorSelect)
   {
      case LEFT_MOTOR:
         sbi(MC_PORT, REVERSE_LEFT);
         cbi(MC_PORT, FORWARD_LEFT);
         PWM_LEFT(speed);
         break;
      case RIGHT_MOTOR:
         sbi(MC_PORT, REVERSE_RIGHT);
         cbi(MC_PORT, FORWARD_RIGHT);
         PWM_RIGHT(speed);
         break;
      case BOTH:
         // both motors reverse
         sbi(MC_PORT, REVERSE_LEFT);
         sbi(MC_PORT, REVERSE_RIGHT);
         cbi(MC_PORT, FORWARD_LEFT);
         cbi(MC_PORT, FORWARD_RIGHT);
         PWM_RIGHT(speed);
         PWM_LEFT(speed);
         break;
   }
}


void neutral(void)
{
   // both motors coast, disable
   PWM_RIGHT(0);
   PWM_LEFT(0);
}


//brake selected motor
//full brake assumed
void brake(u08 motorSelect)
{
   switch(motorSelect)
   {
      case LEFT_MOTOR:
         cbi(MC_PORT, REVERSE_LEFT);
         cbi(MC_PORT, FORWARD_LEFT);
         break;
      case RIGHT_MOTOR:
         cbi(MC_PORT, REVERSE_RIGHT);
         cbi(MC_PORT, FORWARD_RIGHT);
         break;
      case BOTH:
         // both motors reverse
         cbi(MC_PORT, REVERSE_LEFT);
         cbi(MC_PORT, REVERSE_RIGHT);
         cbi(MC_PORT, FORWARD_LEFT);
         cbi(MC_PORT, FORWARD_RIGHT);
         break;
   }
   PWM_RIGHT(MAX_BRAKE);
   PWM_LEFT(MAX_BRAKE);
}


/*
void motor_pin_test(void)
{
   forward(LEFT_MOTOR, 255);
   lcdWriteStr("FWD LEFT        ", 0, 0);
   myDelay(40);
   
   brake(LEFT_MOTOR);
   lcdWriteStr("BRK LEFT        ", 0, 0);
   myDelay(40);
   
   forward(RIGHT_MOTOR, 255);
   lcdWriteStr("FWD RIGHT       ", 0, 0);
   myDelay(40);
   
   brake(RIGHT_MOTOR);
   lcdWriteStr("BRK RIGHT       ", 0, 0);
   myDelay(40);
   
   reverse(LEFT_MOTOR, 255);
   lcdWriteStr("REV LEFT        ", 0, 0);
   myDelay(40);
   
   brake(LEFT_MOTOR);
   lcdWriteStr("BRK LEFT        ", 0, 0);
   myDelay(40);
   
   reverse(RIGHT_MOTOR, 255);
   lcdWriteStr("REV RIGHT       ", 0, 0);
   myDelay(40);
   
   brake(RIGHT_MOTOR);
   lcdWriteStr("BRK RIGHT       ", 0, 0);
   myDelay(40);

}
*/


void enableMotors( void )
{
   timer1PWMAOn();
   timer1PWMBOn();
}


void disableMotors( void )
{
   timer1PWMAOff();
   timer1PWMBOff();
}
