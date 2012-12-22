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
//      not sure which pwm controls which though..
//      so could be wrong
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
   //timer1PWMAOff();
   //timer1PWMBOff();
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

void tractor_right(u08 speed)
{
   // brake right, forward left
   brake(RIGHT_MOTOR);
   forward(LEFT_MOTOR, speed);
}

void tractor_left(u08 speed)
{
   // brake left, forward right
   brake(LEFT_MOTOR);
   forward(RIGHT_MOTOR, speed);
}

void tank_right(u08 speed)
{
   // forward left, reverse right
   forward(LEFT_MOTOR, speed);
   reverse(RIGHT_MOTOR, speed);
}

void tank_left(u08 speed)
{
   // forward right, reverse left
   forward(RIGHT_MOTOR, speed);
   reverse(LEFT_MOTOR, speed);
}
